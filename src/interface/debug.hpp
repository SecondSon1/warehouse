#pragma once

#include <string>
void _Assert(bool var, const std::string & fail_message, const std::string & filename, uint32_t line);

#ifdef WAREHOUSE_DEBUG
#define Assert(x, msg) _Assert((x), (msg), __FILE__, __LINE__)
#else
#define Assert(x, msg) 42
#endif