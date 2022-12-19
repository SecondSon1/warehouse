#pragma once

#include <vector>
#include "product.hpp"

class ProductTable {
 public:
  // There can be only one product table
  // *Maybe* TODO: change
  ProductTable(std::vector<std::shared_ptr<Product>> && product) : products_(std::move(product)) {}
  ProductTable(const ProductTable &) = delete;

 public:
  size_t GetProductsAmount() const { return products_.size(); }

  std::weak_ptr<const Product> operator [] (uint32_t id) const { return products_[id]; }
  std::weak_ptr<Product> operator [] (uint32_t id) { return products_[id]; }

 private:
  std::vector<std::shared_ptr<Product>> products_;
};