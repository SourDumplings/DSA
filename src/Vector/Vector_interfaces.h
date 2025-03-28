/*
 @Date    : 2018-04-07 11:42:41
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector类模板的数据访问接口方法
 */

#ifndef VECTOR_INTERFACES_H
#define VECTOR_INTERFACES_H

#include "Vector.h"

namespace DSA
{
    template <typename T>
    inline typename Vector<T>::Iterator Vector<T>::begin()
    {
        return _elem;
    }

    template <typename T>
    inline typename Vector<T>::Iterator Vector<T>::begin() const
    {
        return _elem;
    }

    template <typename T>
    inline typename Vector<T>::Iterator Vector<T>::end()
    {
        return _elem + _size;
    }

    template <typename T>
    inline typename Vector<T>::Iterator Vector<T>::end() const
    {
        return _elem + _size;
    }

    template <typename T>
    inline typename Vector<T>::Rank Vector<T>::size() const
    {
        return _size;
    }

    template <typename T>
    inline typename Vector<T>::Rank Vector<T>::capacity()
    {
        return _capacity;
    }

    template <typename T>
    inline typename Vector<T>::Rank Vector<T>::capacity() const
    {
        return _capacity;
    }

    template <typename T>
    const T &Vector<T>::back() const
    {
        ASSERT_DEBUG(_size != 0, "no elements");
        return _elem[_size - 1];
    }

    template <typename T>
    T &Vector<T>::back()
    {
        ASSERT_DEBUG(_size != 0, "no elements");
        return _elem[_size - 1];
    }

    template <typename T>
    const T &Vector<T>::front() const
    {
        ASSERT_DEBUG(_size != 0, "no elements");
        return _elem[0];
    }

    template <typename T>
    T &Vector<T>::front()
    {
        ASSERT_DEBUG(_size != 0, "no elements");
        return _elem[0];
    }

    template <typename T>
    const T &Vector<T>::at(RankPlus index) const
    {
        if (index >= 0)
        {
            return (*this)[static_cast<Rank>(index)];
        }
        else
            return (*this)[static_cast<Rank>(_size + index)];
    }

    template <typename T>
    T &Vector<T>::at(RankPlus index)
    {
        return const_cast<T &>(static_cast<const Vector<T> &>(*this).at(index));
    }

    template <typename T>
    const char *Vector<T>::get_entity_name() const
    {
        return "Vector";
    }
}

#endif // VECTOR_INTERFACES_H
