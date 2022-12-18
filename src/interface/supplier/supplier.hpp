#pragma once

#include <vector>
#include <random>
#include "order.hpp"
#include "request.hpp"

class Supplier {
 public:
  Supplier() : rng_(std::random_device{}()), nd_(3.5, 0.45) {}

 public:
  void AcceptRequest(const SupplierRequest & request);

  std::vector<SupplierOrder> GetOrdersForToday(uint32_t day) const {
    if (day >= orders_.size())
      return {};
    return orders_[day];
  }

 private:
  void FillUntil(uint32_t size) {
    for (size_t i = orders_.size(); i <= size; ++i)
      orders_.emplace_back();
  }

 private:
  std::vector<std::vector<SupplierOrder>> orders_;
  std::mt19937 rng_;
  std::normal_distribution<double> nd_;
};