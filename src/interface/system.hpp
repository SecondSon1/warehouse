#pragma once

#include <vector>
#include "product.hpp"
#include "product_table.hpp"
#include "managers/manager.hpp"
#include "outlets/outlet.hpp"
#include "supplier/supplier.hpp"
#include "statistics.hpp"
#include "storage/storage.hpp"

class WarehouseSystem {
 public:
  WarehouseSystem(std::vector<std::shared_ptr<Product>> && products, std::shared_ptr<IManager> manager,
                  std::vector<std::shared_ptr<Outlet>> outlets, std::shared_ptr<Supplier> supplier);

 public:
  std::weak_ptr<const ProductTable> GetProductTable() const { return product_table_; }
  const Statistics & GetStatistics() const { return stats_; }
  const Storage & GetStorage() const { return storage_; }
  uint32_t GetCurrentDay() const { return day_; }
  const std::vector<std::shared_ptr<Outlet>> & GetOutlets() const { return outlets_; }

 public:
  std::vector<std::vector<std::pair<uint32_t, uint32_t>>> NextDay();

 private:
  void ReviseStorage();
  void AcceptFromSupplier();
  void SendToOutlets();
  void DevelopDistributionToOutlets();
  void OrderFromSupplier();

 private:
  Storage storage_;

  std::shared_ptr<ProductTable> product_table_;
  std::shared_ptr<IManager> manager_;

  std::vector<std::shared_ptr<Outlet>> outlets_;
  std::shared_ptr<Supplier> supplier_;

  uint32_t day_;

  Statistics stats_;

  // distribution_[outlet_id][product_id] = { how many fresh, how many discounted }
  std::vector<std::vector<std::pair<uint32_t, uint32_t>>> distribution_;
};