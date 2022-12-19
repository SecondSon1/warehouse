#include "system.hpp"

WarehouseSystem::WarehouseSystem(std::vector<std::shared_ptr<Product>> && products, std::shared_ptr<IManager> manager,
                                 std::vector<std::shared_ptr<Outlet>> outlets, std::shared_ptr<Supplier> supplier)
                                 : product_table_(std::make_shared<ProductTable>(std::move(products))),
                                   manager_(std::move(manager)), day_(0),
                                   outlets_(std::move(outlets)), supplier_(std::move(supplier)) {

}

Report WarehouseSystem::NextDay() {
}
