#pragma once

#ifdef WAREHOUSE_DEBUG
#include <iostream>

void _Assert(bool var, const std::string & fail_message, const std::string & filename, uint32_t line) {
  if (!var) {
    std::cerr << "Assert triggered at file " << filename << " at line " << line << ":" << std::endl;
    std::cerr << fail_message << std::endl;
    exit(1);
  }
}

#define Assert(x, msg) _Assert((x), (msg), __FILE__, __LINE__)

#else
#define Assert(x, msg) 42
#endif