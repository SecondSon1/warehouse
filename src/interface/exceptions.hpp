#pragma once

#include <stdexcept>

class ProductNotProvidedError : public std::runtime_error {
 public:
  ProductNotProvidedError() : std::runtime_error("No product provided") {}

  [[nodiscard]] const char * what() const noexcept override {
    return "No product provided";
  }
};