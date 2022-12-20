#include "debug.hpp"
#include <iostream>

void _Assert(bool var, const std::string & fail_message, const std::string & filename, uint32_t line) {
  if (!var) {
    std::cerr << "Assert triggered at file " << filename << " at line " << line << ":" << std::endl;
    std::cerr << fail_message << std::endl;
    exit(1);
  }
}
