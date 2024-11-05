/*
 @Date    : 2018-04-10 21:26:55
 @Author  : 酸饺子 (sourdumplings@qq.com)
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
    bool Vector<T>::_expand()
    {
        if (_need_expand())
        {
            T *oldElem = _elem;
            Rank oldCapacity = _capacity;
            while (_need_expand())
            {
                if (_capacity)
                {
                    _capacity <<= 1;
                }
                else
                    _capacity = 1;
            }

/*             _elem = new T[_capacity];
            for (Rank i = 0; i != tempC; ++i)
            {
                _elem[i] = oldElem[i];
            }
            delete [] oldElem; */
            _elem = reinterpret_cast<T *>(malloc(_capacity * sizeof(T)));
            memcpy(reinterpret_cast<void*>(_elem), reinterpret_cast<void*>(oldElem), oldCapacity * sizeof(T));
            free(oldElem);
            return true;
        }
        else
            return false;
    }

    template <typename T>
    inline bool Vector<T>::_need_expand() const
    {
        return _capacity <= _size;
    }
} // CZ

#endif // VECTOR_EXPAND_H
