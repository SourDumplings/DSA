/**
 * @file test_lua.cpp
 * @author  运行 Lua 测试脚本
 * @brief
 * @version 1.0.0
 * @date 2023-11-23
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "Lua/Lua_interfaces.h"
#include <iostream>

// 注册的模块
static const luaL_Reg CZLuaRegLibs[] = {
    {"base", luaopen_base},
    {"DSALuaDLL", luaopen_DSALuaDLL},
    {NULL, NULL}
};

bool test_lua()
{
    // 指向 Lua 解释器的指针
    lua_State *L = luaL_newstate();

    // 载入 Lua 基本库
    luaL_openlibs(L);

    // 注册 Lua 模块
    const luaL_Reg *lua_reg = CZLuaRegLibs;
    for (; lua_reg->func; ++lua_reg)
    {
        // 加载模块
        // 首先查找 package.loaded 表， 检测 modname 是否被加载过。
        // 如果被加载过，require 返回 package.loaded[modname] 中保存的值。
        // 如果 modname 不在 package.loaded 中， 则调用函数 openf ，并传入字符串 modname。
        // 将其返回值置入 package.loaded[modname]。
        // 如果最后一个参数为真， 同时也将模块设到全局变量 modname 里。在栈上留下该模块的副本。
        luaL_requiref(L, lua_reg->name, lua_reg->func, 1);
        // 从栈中弹出 1 个元素
        lua_pop(L, 1);
    }

    // 读 lua 文件并运行 Lua code
#ifdef PROJECT_SOURCE_DIR
    printf("PROJECT_SOURCE_DIR = %s\n", PROJECT_SOURCE_DIR);
    char luaFilePath[100];
    sprintf(luaFilePath, "%s/test/lua/test_sayhi.lua", PROJECT_SOURCE_DIR);

    /* 运行脚本 */
    luaL_dofile(L, luaFilePath);
#else
    printf("ERROR: No PROJECT_SOURCE_DIR defined!\n");
#endif
    // 关闭 state
    lua_close(L);
    return true;
}