/*
 @Date    : 2018-05-17 19:20:04
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
打印列表模板类的信息
 */

#ifndef LIST_PRINT_INFO_H
#define LIST_PRINT_INFO_H

#include <iostream>
#include "List.h"

namespace CZ
{
    // 打印所有元素，空格隔开，末尾换行
    template <typename T>
    inline void List<T>::printInfo(const char *name)
    {
        printf("List %s:\n", name);
        printf("size = %u\n", _size);
        printf("including: ");
        int output = 0;
        for (iterator it = begin(); it != end(); ++it)
        {
            if (output++)
            {
                putchar(' ');
            }
            // std::cout << *it;
            std::cout << it->data();
        }
        printf("\n\n");
        return;
    }
} // CZ

#endif // LIST_PRINT_INFO_H


