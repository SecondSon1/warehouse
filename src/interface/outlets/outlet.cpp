#include "outlet.hpp"

#include <utility>
#include "../debug.hpp"

Outlet::Outlet(std::vector<double> product_coefficients, std::vector<double> discounted_product_coefficients,
               std::weak_ptr<const ProductTable> product_table)
               : product_coefficients_(std::move(product_coefficients)), product_table_(std::move(product_table)),
                 discounted_product_coefficients_(std::move(discounted_product_coefficients)),
                 rng_(std::random_device{}()), nrd_(0.5, 0.15) {
  Assert(!product_table_.expired(), "Product table has expired");
  Assert(product_table.lock()->GetProductsAmount() == product_coefficients_.size(),
         "Product coefficients vector doesn't match size of product table");
  Assert(product_coefficients_.size() == discounted_product_coefficients_.size(),
         "Discounted product coefficients vector doesn't match size of product table");
}

OutletOrder Outlet::GenerateOrder() {
  Assert(!product_table_.expired(), "Product table has expired");
  std::shared_ptr<const ProductTable> product_table = product_table_.lock();
  std::vector<OutletOrderElement> elements;
  for (size_t id = 0; id < product_table->GetProductsAmount(); ++id) {
    double fresh = product_coefficients_[id] * nrd_(rng_);
    double discounted = discounted_product_coefficients_[id] * nrd_(rng_);

    auto fresh_amount = static_cast<uint32_t>(round(fresh));
    auto discounted_amount = static_cast<uint32_t>(round(discounted));

    elements.emplace_back((*product_table)[id], fresh_amount, discounted_amount);
  }
  return { elements };
}
