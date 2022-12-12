#include "storage.hpp"

#include <utility>

Storage::Storage(std::vector<std::vector<Package>>  packages)
                 : packages_(std::move(packages)) {
}
