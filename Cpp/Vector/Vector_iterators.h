/*
 @Date    : 2018-04-07 11:42:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
迭代器函数
 */

#ifndef VECTOR_ITERATORS_H
#define VECTOR_ITERATORS_H

#include "Vector.h"

namespace CZ
{
    template <typename T>
    inline typename Vector<T>::iterator Vector<T>::begin()
    {
        return _elem;
    }

    template <typename T>
    inline typename Vector<T>::iterator Vector<T>::end()
    {
        return _elem + _size;
    }
}



#endif // VECTOR_ITERATORS_H



