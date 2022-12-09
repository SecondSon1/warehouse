#pragma once

#ifdef WAREHOUSE_DEBUG
#include <cassert>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) 42
#endif