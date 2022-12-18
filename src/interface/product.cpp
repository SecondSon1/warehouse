#include "product.hpp"

Product::Product(uint32_t id, std::wstring name, uint32_t expiration_time, uint32_t discount_time, uint32_t price,
                 uint32_t full_price, uint32_t discounted_price, uint32_t package_amount, uint32_t packages_limit)
                 : id_(id), name_(std::move(name)), expiration_time_(expiration_time), discount_time_(discount_time),
                   price_(price), full_price_(full_price), discounted_price_(discounted_price),
                   package_amount_(package_amount), packages_limit_(packages_limit) {
}