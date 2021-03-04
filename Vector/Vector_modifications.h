/*
 @Date    : 2018-04-09 19:31:43
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector类模板的动态操作方法
 */

#ifndef VECTOR_MODIFICATIONS_H
#define VECTOR_MODIFICATIONS_H

#include "Vector.h"
#include <stdexcept>
#include <utility>

namespace CZ
{
    template <typename T>
    inline void Vector<T>::clear()
    {
        _size = 0;
        shrink();
        return;
    }

    template <typename T>
    inline void Vector<T>::push_back(const T &x)
    {
        // 如有必要则扩容
        ++_size;
        expand();
        _elem[_size-1] = x;
        return;
    }

    template <typename T>
    inline void Vector<T>::push_back(T &&x)
    {
        // 如有必要则扩容
        ++_size;
        expand();
        _elem[_size-1] = std::move(x);
        return;
    }

    template <typename T>
    void Vector<T>::pop_back()
    {
        try
        {
            if (_size == 0)
            {
                throw "no elements";
            }
            --_size;
            // 如有必要则缩容
            shrink();
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector pop_back: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    // 插入一个元素到指定位置之前，返回指向插入的元素的迭代器
    template <typename T>
    typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::iterator itPos, const T &x)
    {
        typename Vector<T>::Rank r = itPos - begin();
        try
        {
            if (!(itPos <= end() && itPos >= begin()))
            {
                throw "Invalid pos iterator";
            }
            ++_size;
            expand();
            for (unsigned i = _size - 1; i != r; --i)
            {
                _elem[i] = _elem[i-1];
            }
            _elem[r] = x;
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector insert: %s\n", errMsg);
            throw std::exception();
        }
        return begin() + r;
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::iterator itPos, T &&x)
    {
        typename Vector<T>::Rank r = itPos - begin();
        try
        {
            if (!(itPos <= end() && itPos >= begin()))
            {
                throw "Invalid pos iterator";
            }
            ++_size;
            expand();
            for (unsigned i = _size - 1; i != r; --i)
            {
                _elem[i] = _elem[i-1];
            }
            _elem[r] = std::move(x);
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector insert: %s\n", errMsg);
            throw std::exception();
        }
        return begin() + r;
    }

    // 插入一个迭代器范围的元素到指定位置之前，返回指向插入的元素的第一个元素的迭代器
    template <typename T>
    typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::iterator itPos,
        const T *b, const T *e)
    {
        typename Vector<T>::Rank r = itPos - begin();
        try
        {
            if (!(itPos <= end() && itPos >= begin()))
            {
                throw "Invalid pos iterator";
            }
            if (!(b <= e))
            {
                throw "Invalid iterator range";
            }
            typename Vector<T>::Rank n = e - b;
            _size += n;
            expand();
            for (unsigned i = _size - 1; n < i && i != r - 1; --i)
            {
                _elem[i] = _elem[i-n];
            }
            typename Vector<T>::Rank rTemp = r;
            for (const T *it = b; it != e; ++it)
            {
                _elem[rTemp++] = *it;
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector insert: %s\n", errMsg);
            throw std::exception();
        }
        return begin() + r;
    }

    template <typename T>
    inline typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::iterator itPos,
        const typename Vector<T>::iterator &b, const typename Vector<T>::iterator &e)
    { return insert(itPos, b.get(), e.get()); }

    // 删除单元素，返回删除的元素之后的元素的迭代器
    template <typename T>
    typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::iterator itPos)
    {
        typename Vector<T>::Rank r = itPos - begin();
        try
        {
            if (!(itPos < end() && itPos >= begin()))
            {
                throw "Invalid pos iterator";
            }
            for (unsigned i = r; i != _size - 1; ++i)
            {
                _elem[i] = _elem[i+1];
            }
            --_size;
            shrink();
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector erase: %s\n", errMsg);
            throw std::exception();
        }
        return begin() + r;
    }

    // 删除一个迭代器区间范围内的元素，原来迭代器区间itEnd所指向的元素的值
    template <typename T>
    typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::iterator itBegin,
        typename Vector<T>::iterator itEnd)
    {
        typename Vector<T>::Rank rB = itBegin - begin(), rE = itEnd - begin();
        try
        {
            if (!((itBegin >= begin() && itBegin <= end()) &&
                (itEnd > begin() && itEnd <= end()) &&
                itBegin <= itEnd))
            {
                throw "Invalid iterator range";
            }
            typename Vector<T>::Rank n = itEnd - itBegin;
            for (unsigned i = rB; i != rE; ++i)
            {
                _elem[i] = _elem[i+n];
            }
            _size -= n;
            shrink();
        }
        catch (const char *errMsg)
        {
            printf("Error from Vector erase: %s\n", errMsg);
            throw std::exception();
        }
        return begin() + rB;
    }

    template <typename T>
    void Vector<T>::resize(typename Vector<T>::Rank n)
    {
        if (n < _size)
        {
            _size = n;
            shrink();
        }
        else if (n > _size)
        {
            _size = n;
            expand();
        }
        return;
    }

    template <typename T>
    void Vector<T>::assign(const typename Vector<T>::iterator &begin,
        const typename Vector<T>::iterator &end)
    {
        _size = end - begin;
        expand();
        for (Rank i= 0; i != _size; ++i)
        {
            _elem[i] = *(begin + i);
        }
        shrink();
        return;
    }

    template <typename T>
    void Vector<T>::remove(const T &value)
    {
        Rank k = 0;
        for (Rank i = 0; i != _size; ++i)
        {
            if (_elem[i] != value)
            {
                _elem[i - k] = _elem[i];
            }
            else
                ++k;
        }
        _size -= k;
        shrink();
        return;
    }
}

#endif // VECTOR_MODIFICATIONS_H


