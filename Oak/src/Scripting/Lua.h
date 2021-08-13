#pragma once
extern "C"
{
#include "vendor/Lua/include/Lua.h"
#include "vendor/Lua/include/lauxlib.h"
#include "vendor/Lua/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "vendor/Lua/liblua54.a")
#endif