#pragma once
#include <vector>
#include "package.hpp"
#include "../exceptions.hpp"

class Storage {
 public:
  Storage(size_t products_amount) : packages_(products_amount) {}

  const std::vector<Package> & operator [] (uint32_t id) const {
    return packages_[id];
  }

  const std::vector<Package> & operator [] (const std::weak_ptr<const Product> & product) const {
    if (product.expired())
      throw ProductNotProvidedError();
    return packages_[product.lock()->GetId()];
  }

  std::vector<Package> & operator [] (uint32_t id) {
    return packages_[id];
  }

  std::vector<Package> & operator [] (const std::weak_ptr<const Product> & product) {
    if (product.expired())
      throw ProductNotProvidedError();
    return packages_[product.lock()->GetId()];
  }

  std::vector<Package> GetFreshProducts(uint32_t day, uint32_t product_id) const {
    std::vector<Package> result;
    for (const Package & package : packages_[product_id])
      if (day < package.GetDiscountDate())
        result.push_back(package);
    return result;
  }
  std::vector<Package> GetDiscountedProducts(uint32_t day, uint32_t product_id) const {
    std::vector<Package> result;
    for (const Package & package : packages_[product_id])
      if (package.GetDiscountDate() <= day)
        result.push_back(package);
    return result;
  }

  std::vector<Package> GetFreshProducts(uint32_t day, const std::weak_ptr<const Product> & product) const {
    if (product.expired())
      throw ProductNotProvidedError();
    return GetFreshProducts(day, product.lock()->GetId());
  }
  std::vector<Package> GetDiscountedProducts(uint32_t day, const std::weak_ptr<const Product> & product) const {
    if (product.expired())
      throw ProductNotProvidedError();
    return GetDiscountedProducts(day, product.lock()->GetId());
  }

  void SoldFreshProducts(uint32_t day, uint32_t id, uint32_t amount);
  void SoldDiscountedProducts(uint32_t day, uint32_t id, uint32_t amount);

  void SoldFreshProducts(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount) {
    if (product.expired())
      throw ProductNotProvidedError();
    SoldFreshProducts(day, product.lock()->GetId(), amount);
  }
  void SoldDiscountedProducts(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount) {
    if (product.expired())
      throw ProductNotProvidedError();
    SoldDiscountedProducts(day, product.lock()->GetId(), amount);
  }

 private:
  std::vector<std::vector<Package>> packages_;
};