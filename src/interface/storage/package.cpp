#include "package.hpp"
#include "../exceptions.hpp"
#include "../debug.hpp"

Package::Package(std::weak_ptr<const Product> product, uint32_t exp_date, uint32_t disc_date)
                 : product_(std::move(product)), expiration_date_(exp_date), discount_date_(disc_date) {
  if (product_.expired())
    throw ProductNotProvidedError();
  Assert(exp_date >= disc_date, "Expiration date cannot be larger than discount date");
}

Package::Package(std::weak_ptr<const Product> product, uint32_t day)
                 : product_(std::move(product)) {
  if (auto actual_product = product_.lock()) {
    expiration_date_ = day + actual_product->GetExpirationTime();
    discount_date_ = day + actual_product->GetDiscountTime();
  } else
    throw ProductNotProvidedError();
}
