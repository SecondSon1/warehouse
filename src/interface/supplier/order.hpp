#pragma once

#include <memory>
#include "../storage/package.hpp"

class SupplierOrder {
 public:
  SupplierOrder(uint32_t request_id, std::weak_ptr<const Product> product, uint32_t amount, uint32_t departure_date)
                : request_id_(request_id), product_(std::move(product)), amount_(amount),
                  departure_date_(departure_date) {}

 public:
  uint32_t GetRequestId() const { return request_id_; }
  std::weak_ptr<const Product> GetProduct() const { return product_; }
  uint32_t GetAmount() const { return amount_; }
  uint32_t GetDepartureDate() const { return departure_date_; }

 private:
  friend class Supplier;
  void SetDepartureDate(uint32_t date) { departure_date_ = date; }

 private:
  uint32_t request_id_;
  std::weak_ptr<const Product> product_;
  uint32_t amount_;
  uint32_t departure_date_;
};