#pragma once

#include <utility>
#include <vector>
#include "../storage/package.hpp"
#include "order.hpp"

class SupplierRequest {
 public:
  SupplierRequest(std::vector<std::pair<std::shared_ptr<Package>, uint32_t>>  request)
                  : request_(std::move(request)) {}

 public:
  std::vector<SupplierOrder> Decompose() const {
    std::vector<SupplierOrder> res;
    res.reserve(request_.size());
    for (auto & [ptr, amount] : request_)
      res.emplace_back(ptr, amount);
    return res;
  }

 private:
  std::vector<std::pair<std::shared_ptr<Package>, uint32_t>> request_;
};