/*
 @Date    : 2018-04-06 19:59:41
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
按迭代器区间拷贝构造
 */

#ifndef INIT_FROM_H
#define INIT_FROM_H

#include "Vector.h"

namespace DSA
{
    // 迭代器区间的复制
    template <typename T>
    template <typename It>
    void Vector<T>::_init_from(const It &begin, const It &end)
    {
        clear();
        _size = end - begin;
        _capacity = 2 * _size;
        _elem = reinterpret_cast<T *>(malloc(_capacity * sizeof(T)));

        for (Rank i = 0; i < _size; ++i)
        {
            new(_elem + i) T(*(begin + i));
        }
    }
}

#endif // INIT_FROM_H

