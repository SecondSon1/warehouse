#pragma once

#include <map>

#include "interface/system.hpp"
#include "interface/debug.hpp"


std::vector<std::pair<std::shared_ptr<const Product>, uint32_t>> GetProducts(const WarehouseSystem & system) {
  std::shared_ptr<const ProductTable> product_table = system.GetProductTable().lock();
  std::vector<std::pair<std::shared_ptr<const Product>, uint32_t>> ans(product_table->GetProductsAmount());
  std::vector<uint32_t> count = system.GetStatistics().GetCountByProduct();
  for (size_t i = 0; i < ans.size(); ++i) {
    ans[i].first = (*product_table)[i].lock();
    ans[i].second = count[i];
  }
  return ans;
}

std::vector<std::vector<std::wstring>> GetListOfProductSold(const WarehouseSystem & system) {
  // {L"Номер", L"Торг. точка", L"Товар", L"Количество", L"Выручка"}
  const Statistics & stats = system.GetStatistics();
  const std::vector<std::tuple<uint32_t, uint32_t, uint32_t, bool>> & sold = stats.GetCurrentDayOrders();
  std::vector<std::vector<std::wstring>> ans(sold.size());
  std::shared_ptr<const ProductTable> product_table = system.GetProductTable().lock();
  const std::vector<std::shared_ptr<Outlet>> & outlets = system.GetOutlets();

  uint32_t day = system.GetCurrentDay();
  if (day == 0)
    return {};
  --day;

  for (size_t i = 0; i < sold.size(); ++i) {
    uint32_t outlet_id = std::get<0>(sold[i]);
    uint32_t product_id = std::get<1>(sold[i]);
    uint32_t amount = std::get<2>(sold[i]);
    bool bought_fresh = std::get<3>(sold[i]);
    std::shared_ptr<const Product> product = (*product_table)[product_id].lock();
    ans[i] = {
        std::to_wstring(i + 1), outlets[outlet_id]->GetName(), product->GetName(), std::to_wstring(amount),
        std::to_wstring((bought_fresh ? product->GetFullPrice() : product->GetDiscountedPrice()) * amount)
    };
  }
}

std::vector<std::vector<std::wstring>> GetListOfPurchasedProduct(const WarehouseSystem & system) {
  // {L"Номер", L"Товар", L"Количество", L"Цена", L"Дата"}
  const Statistics & stats = system.GetStatistics();
  std::shared_ptr<const ProductTable> product_table = system.GetProductTable().lock();
  const auto & on_way = stats.GetProductsOnWay();
  std::vector<std::vector<std::wstring>> ans;
  for (size_t i = 0, nxt = 1; i < on_way.size(); ++i)
    for (size_t j = 0; j < on_way[i].size(); ++j)
      ans.push_back({
        std::to_wstring(nxt++), (*product_table)[i].lock()->GetName(),
        std::to_wstring(on_way[i][j].second.first), std::to_wstring(on_way[i][j].second.second)
      });
  return ans;
}

std::vector<std::vector<std::wstring>> GetProductsThatCame(const WarehouseSystem & system) {
  // {L"Номер", L"Товар", L"Количество", L"Дата заказа"}
  const Statistics & stats = system.GetStatistics();
  std::shared_ptr<const ProductTable> product_table = system.GetProductTable().lock();
  const auto & came = stats.GetProductsThatCame();
  std::vector<std::vector<std::wstring>> ans;
  for (size_t i = 0, nxt = 1; i < came.size(); ++i)
    for (size_t j = 0; j < came[i].size(); ++j)
      ans.push_back({
        std::to_wstring(nxt++), (*product_table)[i].lock()->GetName(),
        std::to_wstring(came[i][j].second.first), std::to_wstring(came[i][j].second.second)
      });
  return ans;
}

std::vector<std::vector<std::wstring>> GetListOfDecommissionedProducts(const WarehouseSystem & system) {
  const Statistics & stats = system.GetStatistics();
  const auto & expired = stats.GetExpiredByProduct();
  std::shared_ptr<const ProductTable> product_table = system.GetProductTable().lock();
  size_t products_amount = product_table->GetProductsAmount();
  std::vector<std::vector<std::wstring>> ans;
  // {L"Номер", L"Товар", L"Количество"}
  for (size_t i = 0; i < products_amount; ++i)
    if (expired[i])
      ans.push_back({ std::to_wstring(i + 1), (*product_table)[i].lock()->GetName(),
                      std::to_wstring(expired[i]) });
  return ans;
}

std::vector<std::vector<std::wstring>> GetListOfRequestsFromOutlets(const WarehouseSystem & system,
    const std::vector<std::vector<std::pair<uint32_t, uint32_t>>> & info) {
  // {L"Номер", L"Торг. точка", L"Товар", L"Количество"}
  std::vector<std::vector<std::wstring>> ans;
  const std::vector<std::shared_ptr<Outlet>> & outlets = system.GetOutlets();
  std::shared_ptr<const ProductTable> product_table = system.GetProductTable().lock();

  for (size_t i = 0, nxt = 1; i < info.size(); ++i) {
    for (size_t j = 0; j < info[i].size(); ++j) {
      if (info[i][j].first + info[i][j].second != 0)
        ans.push_back({ std::to_wstring(nxt++), outlets[i]->GetName(), (*product_table)[j].lock()->GetName(),
                        std::to_wstring(info[i][j].first + info[i][j].second) });
    }
  }
  return ans;
}

std::vector<std::vector<std::wstring>> GetStorage(const WarehouseSystem & system) {
  // {L"Количество упаковок", L"Срок годности" (осталось дней до истечения), L"Цена"}
  std::vector<std::vector<std::wstring>> ans;
  const Storage & storage = system.GetStorage();
  std::shared_ptr<const ProductTable> product_table = system.GetProductTable().lock();
  size_t product_amount = product_table->GetProductsAmount();

  uint32_t day = system.GetCurrentDay();
  if (day == 0) return {};
  --day;

  for (size_t i = 0; i < product_amount; ++i) {
    const std::vector<Package> & packages = storage[i];
    std::map<uint32_t, uint32_t> mp;
    for (const Package & package : packages) {
      mp[package.GetExpirationDate()]++;
    }
    std::shared_ptr<const Product> product = (*product_table)[i].lock();

    for (auto [date, amount] : mp) {
      uint32_t price;
      if (date < day + product->GetDiscountTime())
        price = product->GetFullPrice();
      else
        price = product->GetDiscountedPrice();
      Assert(date < day + product->GetExpirationTime(), "Lol expired product");

      ans.push_back({ std::to_wstring(amount), std::to_wstring(date - day), std::to_wstring(price) });
    }
  }
}