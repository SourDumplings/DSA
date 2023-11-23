/**
 * @file Lua_interfaces.h
 * @author  SourDumplings (changzheng300@foxmail.com)
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
 * @param [in] method 判断方法：0 暴力方法；1 素数表法；2 正则表达式法
 * @return bool 判断结果
 */
bool CZLuaF_Is_prime(uint32_t x, uint8_t method);

// /**
//  * @brief 排序整型数组
//  * 
//  * @param [in] begin 数组起始地址
//  * @param [in] n 数组大小
//  */
// void CZLuaF_Sort_int(int64_t *begin, uint32_t n);

int CZLuaF_Add(lua_State *L);

int CZLuaF_SayHi(lua_State *L);

extern "C" DLL_EXPORT_IMPORT int luaopen_DSALuaDLL(lua_State * L);

#endif // LUA_INTERFACES_H


