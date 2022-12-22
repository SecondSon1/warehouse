#pragma once

#include "interface/system.hpp"

std::vector<std::pair<std::shared_ptr<const Product>, uint32_t>> GetProducts(const WarehouseSystem & system);

std::vector<std::vector<std::wstring>> GetListOfProductSold(const WarehouseSystem & system);

std::vector<std::vector<std::wstring>> GetListOfPurchasedProduct(const WarehouseSystem & system);

std::vector<std::vector<std::wstring>> GetProductsThatCame(const WarehouseSystem & system);

std::vector<std::vector<std::wstring>> GetListOfDecommissionedProducts(const WarehouseSystem & system);

std::vector<std::vector<std::wstring>> GetListOfRequestsFromOutlets(const WarehouseSystem & system,
    const std::vector<std::vector<std::pair<uint32_t, uint32_t>>> & info);

std::vector<std::vector<std::wstring>> GetStorage(const WarehouseSystem & system);