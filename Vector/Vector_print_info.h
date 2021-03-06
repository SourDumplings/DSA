/*
 @Date    : 2018-04-06 19:52:28
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
打印向量中的元素
 */

#ifndef VECTOR_PRINT_H
#define VECTOR_PRINT_H

#include "Vector.h"
#include <cstdio>
#include <iostream>

namespace CZ
{
    // 打印所有元素，空格隔开，末尾换行
    template <typename T>
    void Vector<T>::print_info(const char *name) const
    {
        printf("Vector %s:\n", name);
        printf("capacity = %u, size = %u\n", _capacity, _size);
        printf("including: ");
        int output = 0;
        for (Vector<T>::Rank i = 0; i < _size; ++i)
        {
            if (output++)
            {
                putchar(' ');
            }
            std::cout << _elem[i];
        }
        printf("\n\n");
        return;
    }
}

#endif

