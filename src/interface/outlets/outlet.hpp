#pragma once

#include <vector>
#include <random>
#include "order.hpp"

class Outlet {
 public:
  Outlet(std::vector<double> product_coefficients, std::vector<double> discounted_product_coefficients,
         std::weak_ptr<const ProductTable> product_table);

 public:
  const std::vector<double> & GetProductCoefficients() const { return product_coefficients_; }
  const std::vector<double> & GetDiscountedProductCoefficients() const { return discounted_product_coefficients_; }

  OutletOrder GenerateOrder();

 private:
  std::vector<double> product_coefficients_;
  std::vector<double> discounted_product_coefficients_;
  std::weak_ptr<const ProductTable> product_table_;

  std::mt19937 rng_;
  std::normal_distribution<> nrd_;
};