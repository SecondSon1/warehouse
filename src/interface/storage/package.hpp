#pragma once
#include <cstdlib>
#include <memory>
#include "../product.hpp"

class Package {
 public:
  Package(std::weak_ptr<const Product> product, uint32_t exp_date, uint32_t disc_date);
  Package(std::weak_ptr<const Product> product, uint32_t day);

 public:
  [[nodiscard]] const std::weak_ptr<const Product> & GetProduct() const { return product_; }
  uint32_t GetExpirationDate() const { return expiration_date_; }
  uint32_t GetDiscountDate() const { return discount_date_; }

 private:
  std::weak_ptr<const Product> product_;
  uint32_t expiration_date_;
  uint32_t discount_date_;
};