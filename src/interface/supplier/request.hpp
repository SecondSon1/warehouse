#pragma once

#include <utility>
#include <vector>
#include "../storage/package.hpp"
#include "order.hpp"

class SupplierRequest {
 public:
  SupplierRequest(std::vector<std::pair<std::weak_ptr<const Product>, uint32_t>> request, uint32_t day_of_submitting,
                  uint32_t id)
                  : request_(std::move(request)), day_(day_of_submitting), id_(id) {
  }

 public:
  uint32_t GetDay() const { return day_; }
  uint32_t GetId() const { return id_; }

  std::vector<SupplierOrder> Decompose() const {
    std::vector<SupplierOrder> res;
    res.reserve(request_.size());
    for (auto & [ptr, amount] : request_)
      res.emplace_back(id_, ptr, amount, 0);
    return res;
  }


 private:
  friend class IManager;

  uint32_t id_;
  uint32_t day_;
  std::vector<std::pair<std::weak_ptr<const Product>, uint32_t>> request_;
};