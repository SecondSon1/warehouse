#pragma once

#include <vector>
#include "order.hpp"
#include "request.hpp"

class Supplier {
 public:
  Supplier() = default;

 public:
  void AcceptRequest(const SupplierRequest & request);

  std::vector<SupplierOrder> GetOrdersForToday(uint32_t day) const {
    if (day >= orders_.size())
      return {};
    return orders_[day];
  }

 private:
  void FillUntil(uint32_t size) {
    for (size_t i = orders_.size(); i < size; ++i)
      orders_.emplace_back();
  }

 private:
  std::vector<std::vector<SupplierOrder>> orders_;
};