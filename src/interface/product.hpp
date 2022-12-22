#pragma once
#include <cstdlib>
#include <string>

class Product {
 public:

  Product(uint32_t id, std::wstring name, uint32_t expiration_time, uint32_t discount_time, uint32_t price,
          uint32_t full_price, uint32_t discounted_price, uint32_t package_amount, uint32_t packages_limit);

  Product(const Product &) = delete; // no copying, only moving

 public: // boilerplate
  uint32_t GetId() const { return id_; }
  const std::wstring & GetName() const { return name_; }
  uint32_t GetExpirationTime() const { return expiration_time_; }
  uint32_t GetDiscountTime() const { return discount_time_; }
  uint32_t GetPrice() const { return price_; }
  uint32_t GetFullPrice() const { return full_price_; }
  uint32_t GetDiscountedPrice() const { return discounted_price_; }
  uint32_t GetPackageAmount() const { return package_amount_; }
  uint32_t GetPackagesLimit() const { return packages_limit_; }

 private:
  uint32_t id_;
  std::wstring name_;
  uint32_t expiration_time_;
  uint32_t discount_time_;
  // Price is for a package, not one product since we deal only with those
  uint32_t price_;             // Price from suppliers
  uint32_t full_price_;        // Price to be sold to outlets
  uint32_t discounted_price_;  // Price of products nearing expiration date
  uint32_t package_amount_;
  uint32_t packages_limit_;
};