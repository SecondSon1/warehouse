#include "statistics.hpp"

void Statistics::OrderedFromSupplier(uint32_t day, std::weak_ptr<const Product> ptr, uint32_t id, uint32_t amount) {

}

void Statistics::CameFromSupplier(uint32_t day, std::weak_ptr<const Product> ptr, uint32_t amount, uint32_t id) {

}

void Statistics::Expired(uint32_t day, const Package &package) {

}

void Statistics::SoldToOutletFresh(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                                   uint32_t outlet_id) {

}

void Statistics::SoldToOutletDiscounted(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                                        uint32_t outlet_id) {

}

void Statistics::OutletRequested(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t fresh_amount,
                                 uint32_t discounted_amount, uint32_t outlet_id) {

}

