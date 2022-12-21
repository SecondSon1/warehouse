#include <iostream>
#include "simplifier.hpp"
#include "interface/managers/accepting_manager.hpp"

int32_t main() {

  std::vector<std::shared_ptr<Product>> products;
  products.push_back(std::make_shared<Product>(0, L"Product 1",10, 5, 100,
                                               130, 70, 10, 50));
  products.push_back(std::make_shared<Product>(1, L"Product 2",10, 5, 100,
                                               130, 70, 10, 50));
  std::shared_ptr<IManager> manager = std::make_shared<AcceptingManager>();
  std::vector<std::shared_ptr<Outlet>> outlets;
  std::vector<double> v = { 4.0, 10.0 }, v2 = { 2.0, 0.0 };
  outlets.push_back(std::make_shared<Outlet>(0, L"FTL", v, v2));
  std::shared_ptr<Supplier> supplier = std::make_shared<Supplier>();

  WarehouseSystem system(std::move(products), manager, outlets, supplier);
  auto result = system.NextDay();
  auto stats = system.GetStatistics();
  auto a = GetProducts(system);
  auto b = GetListOfPurchasedProduct(system);
  std::cout << result[0][0].first << " " << result[0][0].second << std::endl;
  std::cout << result[0][1].first << " " << result[0][1].second << std::endl;

  return 0;
}