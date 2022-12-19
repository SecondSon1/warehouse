#pragma once

#include <vector>
#include "product.hpp"
#include "product_table.hpp"
#include "managers/manager.hpp"
#include "outlets/outlet.hpp"
#include "supplier/supplier.hpp"
#include "report.hpp"

class WarehouseSystem {
 public:
  WarehouseSystem(std::vector<std::shared_ptr<Product>> && products, std::shared_ptr<IManager> manager,
                  std::vector<std::shared_ptr<Outlet>> outlets, std::shared_ptr<Supplier> supplier);

 public:
  std::weak_ptr<const ProductTable> GetProductTable() const { return product_table_; }

  Report NextDay();

 private:


 private:
  std::shared_ptr<ProductTable> product_table_;
  std::shared_ptr<IManager> manager_;

  std::vector<std::shared_ptr<Outlet>> outlets_;
  std::shared_ptr<Supplier> supplier_;

  uint32_t day_;
  std::vector<Report> reports_;

  uint32_t current_spent_;
  uint32_t current_earned_;
};