#pragma once

#include <memory>
#include "../storage/package.hpp"

class SupplierOrder {
 public:
  SupplierOrder(std::shared_ptr<Package> package_ptr, uint32_t amount, uint32_t departure_date)
                : package_(std::move(package_ptr)), amount_(amount), departure_date_(departure_date) {}

 public:
  std::shared_ptr<Package> GetPackage() const { return package_; }
  uint32_t GetAmount() const { return amount_; }
  uint32_t GetDepartureDate() const { return departure_date_; }

 private:
  friend class Supplier;
  void SetDepartureDate(uint32_t date) { departure_date_ = date; }

 private:
  std::shared_ptr<Package> package_;
  uint32_t amount_;
  uint32_t departure_date_;
};