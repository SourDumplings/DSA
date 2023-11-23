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

#include "../Base/Assert.h"

// 注册的接口
static const luaL_Reg CZLuaDLLFunctions[] = {
    {"SayHi", CZLuaF_SayHi},
    {"Add", CZLuaF_Add},
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
    CZ::ASSERT_RELEASE(lua_gettop(L) == 2, "Wrong params number: %d!", lua_gettop(L));
    int res = lua_tonumber(L, 1) + lua_tonumber(L, 2);
    lua_pushnumber(L, res);
    return 1;
}
