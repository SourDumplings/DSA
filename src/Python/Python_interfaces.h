/**
 * @file Python_interface.h
 * @author  SourDumplings (sourdumplings@qq.com)
 * @brief 可暴露给 Python3 调用的接口
 * @version 1.0.0
 * @date 2023-10-26
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#if !defined(PYTHON_INTERFACES_H)
#define PYTHON_INTERFACES_H

#include "../Base/BaseDef.h"
#include <cstdint>

extern "C"
{
    /**
     * @brief 判断是否是素数
     * 
     * @param [in] x 被判断目标，必须为非负整数
     * @param [in] method 判断方法：0 暴力方法；1 素数表法；2 正则表达式法
     * @return bool 判断结果 
     */
    DLL_EXPORT_IMPORT bool DSAPyF_Is_prime(uint32_t x, uint8_t method);

    /**
     * @brief 排序整型数组
     * 
     * @param [in] begin 数组起始地址
     * @param [in] n 数组大小
     */
    DLL_EXPORT_IMPORT void DSAPyF_Sort_int(int64_t *begin, uint32_t n);

    DLL_EXPORT_IMPORT int DSAPyF_Add(int x, int y);
}


#endif // PYTHON_INTERFACES_H