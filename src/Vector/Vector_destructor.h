/*
 @Date    : 2018-04-06 19:57:01
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
向量的析构函数
 */

#ifndef VECTOR_DESTRUCTOR
#define VECTOR_DESTRUCTOR

#include "Vector.h"

namespace CZ
{
    template <typename T>
    void Vector<T>::clear()
    {
        if (_elem == nullptr)
        {
            ASSERT_DEBUG(_capacity == 0 && _size == 0, "Error capacity %u and size %u.", _capacity, _size);
            return;
        }

        ASSERT_DEBUG(_size <= _capacity, "Error capacity %u and size %u.", _capacity, _size);

        for (Rank i = 0; i < _size; i++)
        {
            (_elem + i)->~T();
        }
        free(_elem);
        _size = _capacity = 0;
        _elem = nullptr;
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        clear();
    }
}

#endif

