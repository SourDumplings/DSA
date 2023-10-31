/**
 * @file test.cpp
 * @author  SourDumplings (changzheng300@foxmail.com)
 * @brief 单元测试程序
 * @version 1.0.0
 * @date 2023-10-25
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "CZString/CZString.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    CZ::CZString hello("Hello World!");
    std::cout << "hello: " << hello << std::endl;
    return 0;
}
