#pragma once

#include <vector>
#include "product.hpp"
#include "storage/package.hpp"

class Statistics {
 public:
  Statistics(uint32_t products_amount)
             : products_amount_(products_amount), by_product_count_(products_amount),
               by_product_profit_(products_amount) {}

 public:
  int32_t GetProfit() const { return static_cast<int32_t>(made_) - static_cast<int32_t>(spent_ + burnt_); }
  uint32_t GetBurnt() const { return burnt_; }
  uint32_t GetAmountOfOrders() const { return orders_count_; }

 public:
  void OrderedFromSupplier(uint32_t day, std::weak_ptr<const Product> ptr, uint32_t id, uint32_t amount);
  void CameFromSupplier(uint32_t day, std::weak_ptr<const Product> ptr, uint32_t amount, uint32_t request_id);
  void Expired(uint32_t day, const Package & package);
  void SoldToOutletFresh(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                         uint32_t outlet_id);
  void SoldToOutletDiscounted(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                              uint32_t outlet_id);
  void OutletRequested(uint32_t day, const std::weak_ptr<const Product> & product,
                       uint32_t fresh_amount, uint32_t discounted_amount, uint32_t outlet_id);

 private:
  uint32_t products_amount_;

  uint32_t spent_, burnt_, made_;
  uint32_t orders_count_;

  std::vector<uint32_t> by_product_count_;
  std::vector<uint32_t> by_product_profit_;

  std::vector<uint32_t> by_product_expired_;

  // vector of packages that came, first = id, second = when came
  std::vector<std::vector<std::pair<uint32_t, uint32_t>>> by_product_came_;

  // on_way_[product_id] = vector of pairs of orders of product, pair.first = id of order, pair.second = when ordered
  std::vector<std::vector<std::pair<uint32_t, uint32_t>>> on_way_;
};