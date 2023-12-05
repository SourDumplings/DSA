/**
 * @file Lua_interfaces.cpp
 * @author  SourDumplings (changzheng300@foxmail.com)
 * @brief 可暴露给 Lua 调用的接口实现
 * @version 1.0.0
 * @date 2023-11-22
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "Lua_interfaces.h"

#include "../Algorithms/Is_prime.h"
#include "../Algorithms/Sort.h"
#include "../Vector/Vector.h"

// 注册的接口
static const luaL_Reg CZLuaDLLFunctions[] = {
    {"SayHi", CZLuaF_SayHi},
    {"Add", CZLuaF_Add},
    {"Is_prime", CZLuaF_Is_prime},
    {"Sort_int", CZLuaF_Sort_int},
    {NULL, NULL}
};

// 将所有函数放到一个 table 中并压栈
extern "C" int luaopen_DSALuaDLL(lua_State * L)
{
    luaL_newlib(L, CZLuaDLLFunctions);
    return 1;
}

// 接口函数实现
int CZLuaF_SayHi(lua_State *L)
{
    printf("CZ says hello world!\n");
    return 0;
}

int CZLuaF_Add(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        lua_pushstring(L, "Wrong params number!");
        lua_error(L);
        return 0;
    }

    int res = lua_tonumber(L, 1) + lua_tonumber(L, 2);
    lua_pushnumber(L, res);
    return 1;
}

int CZLuaF_Is_prime(lua_State *L)
{
    if (lua_gettop(L) < 1)
    {
        lua_pushstring(L, "Wrong params number!");
        lua_error(L);
        return 0;
    }

    CZ::PrimeAccessories::IsPrimeMethod method = static_cast<CZ::PrimeAccessories::IsPrimeMethod>(
        2 <= lua_gettop(L) ? lua_tonumber(L, 2) : 1
    );
    uint32_t x = lua_tonumber(L, 1);

    // printf("Using method: %d to judge %u if prime\n", method, x);
    bool res = CZ::Is_prime(x, method);
    lua_pushboolean(L, res);
    return 1;
}

int CZLuaF_Sort_int(lua_State *L)
{
    // Check if the argument is a table
    if (!lua_istable(L, 1))
    {
        lua_pushstring(L, "Argument must be a table");
        lua_error(L);
        return 0;
    }

    // Convert Lua table to C++ vector
    CZ::Vector<int> vec;
    lua_pushnil(L);  // Push nil to start iterating the table
    while (lua_next(L, 1) != 0)
    {
        if (lua_isnumber(L, -1))
        {
            int value = lua_tonumber(L, -1);
            vec.push_back(value);
        }
        lua_pop(L, 1);  // Pop the value, keep the key for next iteration
    }

    // Sort the vector
    Sort(vec.begin(), vec.end());

    // Create a new Lua table and push the sorted values
    lua_newtable(L);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        lua_pushnumber(L, vec[i]);
        lua_rawseti(L, -2, i + 1);
    }

    return 1;  // Return the sorted Lua table
}
