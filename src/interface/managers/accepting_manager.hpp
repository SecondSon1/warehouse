#pragma once

#include "manager.hpp"

class AcceptingManager : public IManager {
 public:
  AcceptingManager() = default;

  void Submit(SupplierRequest & request) override {
    // Empty since manager accepts (doesn't modify) any request
  }
};