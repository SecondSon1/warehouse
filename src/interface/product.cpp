#include "product.hpp"

Product::Product(uint32_t id, std::string name, uint32_t expiration_date, uint32_t discount_date, uint32_t full_price,
                 uint32_t discounted_price, uint32_t package_amount, uint32_t package_limit)
                 : id_(id), name_(std::move(name)), expiration_time_(expiration_date), discount_time_(discount_date),
                   full_price_(full_price), discounted_price_(discounted_price), package_amount_(package_amount),
                   package_limit_(package_limit) {
}
