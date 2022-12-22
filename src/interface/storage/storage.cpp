#include "storage.hpp"
#include "../debug.hpp"

bool Comparator(const Package & lhs, const Package & rhs) {
  return lhs.GetExpirationDate() < rhs.GetExpirationDate();
}

void Storage::SoldFreshProducts(uint32_t day, uint32_t id, uint32_t amount) {
  Assert(amount <= GetFreshProducts(day, id).size(), "Lol amount of sold fresh is greater than we have");
  std::sort(packages_[id].begin(), packages_[id].end(), Comparator);
  for (size_t i = 0; i < packages_[id].size() && amount; )
    if (day < packages_[id][i].GetDiscountDate()) {
      packages_[id].erase(packages_[id].begin() + static_cast<long>(i));
      --amount;
    } else
      ++i;
  Assert(amount == 0, "Amount is not 0");
}

void Storage::SoldDiscountedProducts(uint32_t day, uint32_t id, uint32_t amount) {
  Assert(amount <= GetDiscountedProducts(day, id).size(), "Lol amount of sold discounted is greater than we have");
  std::sort(packages_[id].begin(), packages_[id].end(), Comparator);
  for (size_t i = 0; i < packages_[id].size() && amount; )
    if (packages_[id][i].GetDiscountDate() <= day) {
      packages_[id].erase(packages_[id].begin() + static_cast<long>(i));
      --amount;
    } else
      ++i;
  Assert(amount == 0, "Amount is not 0");
}