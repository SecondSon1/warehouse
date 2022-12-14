#pragma once

#include <vector>
#include "product.hpp"
#include "storage/package.hpp"

class Statistics {
 public:
  Statistics(uint32_t products_amount)
             : products_amount_(products_amount), by_product_count_(products_amount), on_way_(products_amount),
               by_product_expired_(products_amount), by_product_profit_(products_amount),
               by_product_came_(products_amount), made_(0), spent_(0), burnt_(0), orders_count_(0) {}

 public:
  int32_t GetProfit() const { return static_cast<int32_t>(made_) - static_cast<int32_t>(spent_); }
  uint32_t GetBurnt() const { return burnt_; }
  uint32_t GetAmountOfOrders() const { return orders_count_; }
  const std::vector<uint32_t> & GetCountByProduct() const { return by_product_count_; }
  const std::vector<int32_t> & GetProfitByProduct() const { return by_product_profit_; }
  const std::vector<uint32_t> & GetExpiredByProduct() const { return by_product_expired_; }
  const std::vector<std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>>> & GetProductsThatCame() const {
    return by_product_came_;
  }
  const std::vector<std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>>> & GetProductsOnWay() const {
    return on_way_;
  }
  const std::vector<std::tuple<uint32_t, uint32_t, uint32_t, bool>> & GetCurrentDayOrders() const {
    return current_day_orders_;
  }

 private:
  friend class WarehouseSystem;

  void OrderedFromSupplier(uint32_t day, const std::weak_ptr<const Product> & product,
                           uint32_t amount, uint32_t request_id);
  void CameFromSupplier(uint32_t day, const std::weak_ptr<const Product> & product,
                        uint32_t amount, uint32_t request_id);
  void Expired(uint32_t day, const Package & package);
  void SoldToOutletFresh(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                         uint32_t outlet_id);
  void SoldToOutletDiscounted(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                              uint32_t outlet_id);
  void OutletRequested(uint32_t day, const std::weak_ptr<const Product> & product,
                       uint32_t fresh_amount, uint32_t discounted_amount, uint32_t outlet_id);
  void BeginNextDay();

 private:
  uint32_t products_amount_;

  uint32_t orders_count_;
  uint32_t spent_, burnt_, made_;

  std::vector<uint32_t> by_product_count_;
  std::vector<int32_t> by_product_profit_;

  std::vector<uint32_t> by_product_expired_;

  // vector of packages that came, first = request id, second = { amount, when came }
  std::vector<std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>>> by_product_came_;

  // on_way_[product_id] = vector of pairs of orders of product,
  //                        pair.first = id of order (request), pair.second = { amount, when ordered }
  std::vector<std::vector<std::pair<uint32_t, std::pair<uint32_t, uint32_t>>>> on_way_;

  // get<0> = outlet id, get<1> = product id, get<2> = amount, get<3> = true if fresh, false if discounted
  std::vector<std::tuple<uint32_t, uint32_t, uint32_t, bool>> current_day_orders_;
};