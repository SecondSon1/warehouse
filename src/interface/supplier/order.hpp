#pragma once

#include <memory>
#include "../storage/package.hpp"

class SupplierOrder {
 public:
  SupplierOrder(std::shared_ptr<Package> package_ptr, uint32_t amount)
                : package_(std::move(package_ptr)), amount_(amount) {}

 public:
  std::shared_ptr<Package> GetPackage() const { return package_; }
  uint32_t GetAmount() const { return amount_; }

 private:
  std::shared_ptr<Package> package_;
  uint32_t amount_;
};