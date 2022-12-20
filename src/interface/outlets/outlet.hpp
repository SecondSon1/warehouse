#pragma once

#include <vector>
#include <random>
#include "order.hpp"

class Outlet {
 public:
  Outlet(uint32_t id, std::wstring name, std::vector<double> product_coefficients,
         std::vector<double> discounted_product_coefficients);

 public:
  uint32_t GetId() const { return id_; }
  std::wstring GetName() const { return name_; }
  const std::vector<double> & GetProductCoefficients() const { return product_coefficients_; }
  const std::vector<double> & GetDiscountedProductCoefficients() const { return discounted_product_coefficients_; }

  OutletOrder GenerateOrder();

 private:
  friend class WarehouseSystem;
  void SetProductTable(std::weak_ptr<const ProductTable> product_table) {
    product_table_ = std::move(product_table);
  }

 private:
  uint32_t id_;
  std::wstring name_;

  std::vector<double> product_coefficients_;
  std::vector<double> discounted_product_coefficients_;
  std::weak_ptr<const ProductTable> product_table_;

  std::mt19937 rng_;
  std::normal_distribution<> nrd_;
};