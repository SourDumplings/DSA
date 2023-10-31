/**
 * @file Python_interface.h
 * @author  SourDumplings (changzheng300@foxmail.com)
 * @brief 可暴露给 Python3 调用的接口
 * @version 1.0.0
 * @date 2023-10-26
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

extern "C"
{
    bool Is_prime(int x, int method);

    int Add(int x, int y);
}
