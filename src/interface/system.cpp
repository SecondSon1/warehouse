#include "system.hpp"
#include "debug.hpp"
#include <algorithm>

WarehouseSystem::WarehouseSystem(std::vector<std::shared_ptr<Product>> && products, std::shared_ptr<IManager> manager,
                                 std::vector<std::shared_ptr<Outlet>> outlets, std::shared_ptr<Supplier> supplier)
                                 : product_table_(std::make_shared<ProductTable>(std::move(products))),
                                   manager_(std::move(manager)), day_(0), storage_(products.size()),
                                   distribution_(outlets_.size(),
                                                 std::vector<std::pair<uint32_t, uint32_t>>(
                                                     product_table_->GetProductsAmount()
                                                     )
                                                 ),
                                   stats_(product_table_->GetProductsAmount()),
                                   outlets_(std::move(outlets)), supplier_(std::move(supplier)) {
  for (const std::shared_ptr<Outlet> & outlet : outlets_)
    outlet->SetProductTable(product_table_);
}

std::vector<std::vector<std::pair<uint32_t, uint32_t>>> WarehouseSystem::NextDay() {

  AcceptFromSupplier();
  ReviseStorage();
  SendToOutlets();
  for (const std::shared_ptr<Outlet> & outlet : outlets_)
    distribution_[outlet->GetId()].assign(product_table_->GetProductsAmount(), { 0ul, 0ul });
  DevelopDistributionToOutlets();
  OrderFromSupplier();
  ++day_;
  return distribution_;
}

void WarehouseSystem::ReviseStorage() {
  for (size_t i = 0; i < product_table_->GetProductsAmount(); ++i) {
    std::vector<Package> & packages = storage_[i];
    size_t size = packages.size();
    for (size_t j = 0; j < packages.size(); ) {
      if (packages[j].GetExpirationDate() == day_) {
        stats_.Expired(day_, packages[j]);
        packages.erase(packages.begin() + static_cast<long>(j));
      }
      else
        ++j;
    }
  }
}

void WarehouseSystem::AcceptFromSupplier() {
  std::vector<SupplierOrder> orders = supplier_->GetOrdersForToday(day_);
  for (const SupplierOrder & order : orders) {
    std::weak_ptr<const Product> product_weak = order.GetProduct();
    stats_.CameFromSupplier(day_, product_weak, order.GetAmount(), order.GetRequestId());

    Assert(!product_weak.expired(), "Product expired (lol wtf how lmao)");
    std::shared_ptr<const Product> product = product_weak.lock();

    for (size_t i = 0; i < order.GetAmount(); ++i) {
      // expiration date counts from departure, not from arrival at our warehouse
      storage_[product->GetId()].emplace_back(product, order.GetDepartureDate());
    }
  }
}

void WarehouseSystem::SendToOutlets() {
  for (size_t product_id = 0; product_id < product_table_->GetProductsAmount(); ++product_id) {
    std::weak_ptr<const Product> product = (*product_table_)[product_id];

    uint32_t ordered_fresh = 0, ordered_discounted = 0;
    size_t fresh_sold = 0, discounted_sold = 0;

    std::vector<Package> have_fresh = storage_.GetFreshProducts(day_, product_id);
    std::vector<Package> have_discounted = storage_.GetDiscountedProducts(day_, product_id);

    std::vector<std::pair<uint32_t, uint32_t>> ordered_fresh_by_outlet;
    std::vector<std::pair<uint32_t, uint32_t>> ordered_discounted_by_outlet;

    for (const std::shared_ptr<Outlet> & outlet : outlets_) {
      uint32_t outlet_id = outlet->GetId();
      ordered_fresh += distribution_[outlet_id][product_id].first;
      ordered_discounted += distribution_[outlet_id][product_id].second;

      if (distribution_[outlet_id][product_id].first > 0)
        ordered_fresh_by_outlet.emplace_back(distribution_[outlet_id][product_id].first, outlet_id);
      if (distribution_[outlet_id][product_id].second > 0)
        ordered_discounted_by_outlet.emplace_back(distribution_[outlet_id][product_id].second, outlet_id);
    }

    std::sort(ordered_fresh_by_outlet.begin(), ordered_fresh_by_outlet.end());
    std::sort(ordered_discounted_by_outlet.begin(), ordered_discounted_by_outlet.end());

    for (size_t i = 0; i < ordered_fresh_by_outlet.size(); ++i) {
      size_t rem = ordered_fresh_by_outlet.size() - i;
      if (ordered_fresh_by_outlet[i].first * rem <= ordered_fresh) {
        ordered_fresh -= ordered_fresh_by_outlet[i].first;
        stats_.SoldToOutletFresh(day_, product, ordered_fresh_by_outlet[i].first,
                                 ordered_fresh_by_outlet[i].second);
        fresh_sold += ordered_fresh_by_outlet[i].first;
      } else {
        uint32_t uniform_distribution = ordered_fresh / rem; // each from here to end gets this amount
        uint32_t extra = ordered_fresh - uniform_distribution * rem; // if left over last $extra get extra one
        for (; i < ordered_fresh_by_outlet.size(); ++i) {
          ordered_fresh -= uniform_distribution;
          stats_.SoldToOutletFresh(day_, product, uniform_distribution,
                                   ordered_fresh_by_outlet[i].second);
          fresh_sold += uniform_distribution;
        }
        for (size_t mn = i - extra; i > mn; --i) {
          ordered_fresh -= 1;
          stats_.SoldToOutletFresh(day_, product, 1,ordered_fresh_by_outlet[i].second);
          fresh_sold += 1;
        }
      }
    }

    // copy-pasted bit, don't like it but there is no other choice
    for (size_t i = 0; i < ordered_discounted_by_outlet.size(); ++i) {
      size_t rem = ordered_discounted_by_outlet.size() - i;
      if (ordered_discounted_by_outlet[i].first * rem <= ordered_discounted) {
        ordered_discounted -= ordered_discounted_by_outlet[i].first;
        stats_.SoldToOutletDiscounted(day_, product, ordered_discounted_by_outlet[i].first,
                                      ordered_discounted_by_outlet[i].second);
        discounted_sold += ordered_discounted_by_outlet[i].first;
      } else {
        uint32_t uniform_distribution = ordered_discounted / rem; // each from here to end gets this amount
        uint32_t extra = ordered_discounted - uniform_distribution * rem; // if left over last $extra get extra one
        for (; i < ordered_discounted_by_outlet.size(); ++i) {
          ordered_discounted -= uniform_distribution;
          stats_.SoldToOutletDiscounted(day_, product, uniform_distribution,
                                        ordered_discounted_by_outlet[i].second);
          discounted_sold += uniform_distribution;
        }
        for (size_t mn = i - extra; i > mn; --i) {
          ordered_discounted -= 1;
          stats_.SoldToOutletDiscounted(day_, product, 1,ordered_discounted_by_outlet[i].second);
          discounted_sold += 1;
        }
      }
    }

    storage_.SoldFreshProducts(day_, product_id, fresh_sold);
    storage_.SoldDiscountedProducts(day_, product_id, discounted_sold);
  }
}

void WarehouseSystem::DevelopDistributionToOutlets() {
  for (const std::shared_ptr<Outlet> & outlet : outlets_) {
    uint32_t outlet_id = outlet->GetId();
    std::vector<OutletOrderElement> result = outlet->GenerateOrder().GetOrder();
    for (const OutletOrderElement & element : result) {
      std::weak_ptr<const Product> product = element.GetProduct();
      Assert(!product.expired(), "Product pointer expired...");
      uint32_t product_id = product.lock()->GetId();
      distribution_[outlet_id][product_id] = { element.GetFreshAmount(), element.GetDiscountedAmount() };
      stats_.OutletRequested(day_, product, element.GetFreshAmount(),
                             element.GetDiscountedAmount(), outlet_id);
    }
  }
}

void WarehouseSystem::OrderFromSupplier() {
  // TODO: do + not forget to call stats callback
}
