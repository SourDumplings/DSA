/*
 @Date    : 2018-04-10 21:31:27
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
当小于装填因子时
Vector类模板的缩容操作
 */

#ifndef VECTOR_SHRINK_H
#define VECTOR_SHRINK_H

#include "Vector.h"

namespace CZ
{
    template <typename T>
    bool Vector<T>::shrink()
    {
        // 以12.5%为界
        if ((_size << 3) < _capacity)
        {
            T *oldElem = _elem;
            while ((_size << 3) < _capacity)
            {
                _capacity >>= 1;
            }
            _elem = new T[_capacity];
            for (unsigned i = 0; i < _size; ++i)
            {
                _elem[i] = oldElem[i];
            }
            delete [] oldElem;
            return true;
        }
        return false;
    }
}

#endif // VECTOR_SHRINK_H


