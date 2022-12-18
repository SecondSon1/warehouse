#pragma once
#include <vector>
#include "package.hpp"
#include "../exceptions.hpp"

class Storage {
 public:
  Storage(std::vector<std::vector<Package>>  packages) : packages_(std::move(packages)) {}

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

 private:
  std::vector<std::vector<Package>> packages_;
};