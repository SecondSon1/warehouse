#include "supplier.hpp"

void Supplier::AcceptRequest(const SupplierRequest & request) {
  std::vector<SupplierOrder> orders = request.Decompose();

  double wait_time = nd_(rng_);
  if (wait_time < 1) wait_time = 1; // that's unlikely. Not impossible though
  else if (wait_time > 5) wait_time = 5;
  auto wait_time_whole = static_cast<uint32_t>(round(wait_time));

  for (SupplierOrder & order : orders) {
    double driving_time = nd_(rng_);
    if (driving_time < 1) driving_time = 1;
    else if (driving_time > 5) driving_time = 5;

    auto driving_time_whole = static_cast<uint32_t>(round(driving_time));

    uint32_t resulting_day = request.GetDay() + wait_time_whole + driving_time_whole;

    order.SetDepartureDate(request.GetDay() + wait_time_whole);

    FillUntil(resulting_day);
    orders_[resulting_day].push_back(order);
  }
}
