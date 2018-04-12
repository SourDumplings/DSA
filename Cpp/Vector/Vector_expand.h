/*
 @Date    : 2018-04-10 21:26:55
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector类模板的扩容操作
 */

#ifndef VECTOR_EXPAND_H
#define VECTOR_EXPAND_H

#include "Vector.h"

namespace CZ
{
    template <typename T>
    bool Vector<T>::expand()
    {
        if (_size >= _capacity)
        {
            T *oldElem = _elem;
            while (_size >= _capacity) _capacity <<= 1;
            _elem = new T[_capacity];
            for (unsigned i = 0; i != _size; ++i)
            {
                _elem[i] = oldElem[i];
            }
            delete [] oldElem;
            return true;
        }
        else
            return false;
    }
} // CZ

#endif // VECTOR_EXPAND_H
