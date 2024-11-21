/**
 * @file test.cpp
 * @author  SourDumplings (sourdumplings@qq.com)
 * @brief 单元测试程序
 * @version 1.0.0
 * @date 2023-10-25
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "test_hello_world.h"

#include "DSAString/DSAString.h"
#include <iostream>

bool test_hello_world()
{
    DSA::DSAString hello("Hello World!");
    std::cout << "hello: " << hello << std::endl;
    return true;
}
