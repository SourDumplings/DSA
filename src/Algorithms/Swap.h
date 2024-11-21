/*
 @Date    : 2018-05-10 21:07:58
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
交换函数模板，要求元素必须实现复制构造函数和拷贝赋值操作符
 */

#ifndef SWAP_H
#define SWAP_H

#include "../Base/BaseDef.h"

namespace DSA
{
    template <typename T>
    void Swap(T &a, T &b)
    {
        T temp(a);
        a = b;
        b = temp;
    }

    template <>
    DLL_EXPORT_IMPORT void Swap<int>(int &a, int &b);
} // DSA

#endif // SWAP_H


