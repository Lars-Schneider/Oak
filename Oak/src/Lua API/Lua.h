#pragma once
extern "C"
{
#include "Lua/include/lua.h"
#include "Lua/include/lauxlib.h"
#include "Lua/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "Lua/liblua54.a")
#endif