#pragma once

#include "../supplier/request.hpp"

class IManager {
 public:
  IManager() = default;

  virtual void Submit(SupplierRequest & request) = 0;
};