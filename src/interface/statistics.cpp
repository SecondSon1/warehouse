#include "statistics.hpp"
#include "debug.hpp"

void Statistics::OrderedFromSupplier(uint32_t day, const std::weak_ptr<const Product> & product,
                                     uint32_t amount, uint32_t request_id) {
  Assert(!product.expired(), "Product expired");
  std::shared_ptr<const Product> ptr = product.lock();
  uint32_t product_id = ptr->GetId();
  on_way_[product_id].emplace_back(request_id, std::make_pair(amount, day));
  spent_ += ptr->GetPrice();
}

void Statistics::CameFromSupplier(uint32_t day, const std::weak_ptr<const Product> & product,
                                  uint32_t amount, uint32_t request_id) {
  Assert(!product.expired(), "Product expired");
  std::shared_ptr<const Product> ptr = product.lock();
  uint32_t product_id = ptr->GetId();
  for (size_t i = 0; i < on_way_[product_id].size(); ++i) {
    if (on_way_[product_id][i].first == request_id) {
      Assert(amount == on_way_[product_id][i].second.first, "Amount on callback and statistics don't match");
      on_way_[product_id].erase(on_way_[product_id].begin() + static_cast<long>(i));
      break;
    }
  }
  by_product_came_[product_id].emplace_back(request_id, std::make_pair(amount, day));
}

void Statistics::Expired(uint32_t day, const Package &package) {
  const std::weak_ptr<const Product> & product_weak = package.GetProduct();
  Assert(!product_weak.expired(), "Product expired");
  std::shared_ptr<const Product> product = product_weak.lock();
  burnt_ += product->GetPrice();
  ++by_product_expired_[product->GetId()];
}

void Statistics::SoldToOutletFresh(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                                   uint32_t outlet_id) {
  Assert(!product.expired(), "Product expired");
  std::shared_ptr<const Product> ptr = product.lock();
  auto sold_for = static_cast<int32_t>(ptr->GetFullPrice());
  auto bought_for = static_cast<int32_t>(ptr->GetPrice());
  ++by_product_count_[ptr->GetId()];
  by_product_profit_[ptr->GetId()] += sold_for - bought_for;
  made_ += sold_for;
  current_day_orders_.emplace_back(outlet_id, ptr->GetId(), amount, true);
}

void Statistics::SoldToOutletDiscounted(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t amount,
                                        uint32_t outlet_id) {
  Assert(!product.expired(), "Product expired");
  std::shared_ptr<const Product> ptr = product.lock();
  auto sold_for = static_cast<int32_t>(ptr->GetDiscountedPrice());
  auto bought_for = static_cast<int32_t>(ptr->GetPrice());
  ++by_product_count_[ptr->GetId()];
  by_product_profit_[ptr->GetId()] += sold_for - bought_for;
  made_ += sold_for;
  current_day_orders_.emplace_back(outlet_id, ptr->GetId(), amount, false);
}

void Statistics::OutletRequested(uint32_t day, const std::weak_ptr<const Product> & product, uint32_t fresh_amount,
                                 uint32_t discounted_amount, uint32_t outlet_id) {
  // Nothing to contribute, all outlet REQUEST related info is returned from WarehouseSystem::NextDay()
}

void Statistics::BeginNextDay() {
  current_day_orders_.clear();
}

