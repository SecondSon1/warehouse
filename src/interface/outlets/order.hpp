#pragma once

#include <utility>
#include <vector>
#include "../product.hpp"
#include "../product_table.hpp"

class OutletOrderElement {
 public:
  OutletOrderElement(std::weak_ptr<const Product> product, uint32_t fresh_amount, uint32_t discounted_amount)
                     : product_(std::move(product)), fresh_amount_(fresh_amount),
                       discounted_amount_(discounted_amount) {}

 public:
  std::weak_ptr<const Product> GetProduct() const { return product_; }
  uint32_t GetFreshAmount() const { return fresh_amount_; }
  uint32_t GetDiscountedAmount() const { return discounted_amount_; }

 private:
  std::weak_ptr<const Product> product_;
  uint32_t fresh_amount_;
  uint32_t discounted_amount_;
};

class OutletOrder {
 public:
  OutletOrder(std::vector<OutletOrderElement> order)
              : order_(std::move(order)) {}

 public:
  std::vector<OutletOrderElement> GetOrder() const { return order_; }

 private:
  std::vector<OutletOrderElement> order_;
};
