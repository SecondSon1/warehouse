#include "supplier.hpp"

void Supplier::AcceptRequest(const SupplierRequest & request) {
  std::vector<SupplierOrder> orders = request.Decompose();

  for (const SupplierOrder & order : orders) {

  }
}
