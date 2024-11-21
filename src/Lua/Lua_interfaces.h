/**
 * @file Lua_interfaces.h
 * @author  SourDumplings (sourdumplings@qq.com)
 * @brief 可暴露给 Lua 调用的接口
 * @version 1.0.0
 * @date 2023-11-22
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */
#if !defined(LUA_INTERFACES_H)
#define LUA_INTERFACES_H

#include "../Base/BaseDef.h"
#include <cstdint>
#include "lua.hpp"

/**
 * @brief 判断是否是素数
 *
 * @param [in] x 被判断目标，必须为非负整数
 * @param [in] method 判断方法（可选）：0 暴力方法；1 素数表法（默认）；2 正则表达式法
 * @return int 判断结果：0 代表非素数
 */
int DSALuaF_Is_prime(lua_State *L);

/**
 * @brief 排序整型数组
 * 
 * @param [in] A 待排序的整型数组 table
 */
int DSALuaF_Sort_int(lua_State *L);

int DSALuaF_Add(lua_State *L);

int DSALuaF_SayHi(lua_State *L);

extern "C" DLL_EXPORT_IMPORT int luaopen_DSALuaDLL(lua_State * L);

#endif // LUA_INTERFACES_H


