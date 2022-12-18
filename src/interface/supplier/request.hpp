#pragma once

#include <utility>
#include <vector>
#include "../storage/package.hpp"
#include "order.hpp"

class SupplierRequest {
 public:
  SupplierRequest(std::vector<std::pair<std::shared_ptr<Package>, uint32_t>> request, uint32_t day_of_submitting)
                  : request_(std::move(request)), day_(day_of_submitting) {}

 public:
  uint32_t GetDay() const { return day_; }

  std::vector<SupplierOrder> Decompose() const {
    std::vector<SupplierOrder> res;
    res.reserve(request_.size());
    for (auto & [ptr, amount] : request_)
      res.emplace_back(ptr, amount, 0);
    return res;
  }


 private:
  friend class IManager;

  uint32_t day_;
  std::vector<std::pair<std::shared_ptr<Package>, uint32_t>> request_;
};