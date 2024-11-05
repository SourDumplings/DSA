/*
 @Date    : 2018-04-09 19:31:43
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector类模板的动态操作方法
 */

#ifndef VECTOR_MODIFICATIONS_H
#define VECTOR_MODIFICATIONS_H

#include "Vector.h"

#include "../Algorithms/Swap.h"
#include <utility>

namespace CZ
{
    template <typename T>
    void Vector<T>::push_back(const T &x)
    {
        // 如有必要则扩容
        ++_size;
        if (_need_expand())
        {
            _expand();
        }
        // _elem[_size - 1] = x;
        new(_elem + _size - 1) T(x);
    }

    template <typename T>
    void Vector<T>::push_back(T &&x)
    {
        // 如有必要则扩容
        ++_size;
        if (_need_expand())
        {
            _expand();
        }
        // _elem[_size - 1] = std::move(x);
        new(_elem + _size - 1) T(std::move(x));
    }

    template <typename T>
    void Vector<T>::pop_back()
    {
        ASSERT_DEBUG(_size != 0, "no elements");
        (_elem + _size - 1)->~T();
        --_size;
        // 如有必要则缩容
        if (_need_shrink())
        {
            _shrink();
        }
    }

    // 插入一个元素到指定位置之前，返回指向插入的元素的迭代器
    template <typename T>
    typename Vector<T>::Iterator Vector<T>::insert(typename Vector<T>::Iterator itPos, const T &x)
    {
        typename Vector<T>::Rank r = itPos - begin();
        ASSERT_DEBUG(itPos <= end() && itPos >= begin(), "Invalid pos Iterator");
        Rank oldSize = _size;
        ++_size;
        if (_need_expand())
        {
            _expand();
        }

/*         for (uint32_t i = _size - 1; i != r; --i)
        {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = x; */
        memmove(reinterpret_cast<void *>(_elem + r + 1), reinterpret_cast<void *>(_elem + r), (oldSize - r) * sizeof(T));
        new(_elem + r) T(x);
        return begin() + r;
    }

    template <typename T>
    typename Vector<T>::Iterator Vector<T>::insert(typename Vector<T>::Iterator itPos, T &&x)
    {
        typename Vector<T>::Rank r = itPos - begin();
        ASSERT_DEBUG(itPos <= end() && itPos >= begin(), "Invalid pos Iterator");
        Rank oldSize = _size;
        ++_size;
        if (_need_expand())
        {
            _expand();
        }

/*         for (uint32_t i = _size - 1; i != r; --i)
        {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = std::move(x); */
        memmove(reinterpret_cast<void *>(_elem + r + 1), reinterpret_cast<void *>(_elem + r), (oldSize - r) * sizeof(T));
        new(_elem + r) T(std::move(x));
        return begin() + r;
    }

    // 插入一个迭代器范围的元素到指定位置之前，返回指向插入的元素的第一个元素的迭代器
    template <typename T>
    typename Vector<T>::Iterator Vector<T>::insert(typename Vector<T>::Iterator itPos,
        const T *b, const T *e)
    {
        typename Vector<T>::Rank r = itPos - begin();
        ASSERT_DEBUG(itPos <= end() && itPos >= begin(), "Invalid pos Iterator");
        ASSERT_DEBUG(b <= e, "Invalid Iterator range");
        typename Vector<T>::Rank n = e - b;
        Rank oldSize = _size;
        _size += n;
        if (_need_expand())
        {
            _expand();
        }

/*         typename Vector<T>::Rank rTemp = r;
        for (const T *it = b; it != e; ++it)
        {
            _elem[rTemp++] = *it;
        } */
        Vector<T> elems(b, e); // 将元素备份出来
        memmove(reinterpret_cast<void *>(_elem + r + n), reinterpret_cast<void *>(_elem + r), (oldSize - r) * sizeof(T));
        typename Vector<T>::Rank rTemp = r;
        for (const T &t : elems)
        {
            new(_elem + rTemp) T(std::move(t));
            ++rTemp;
        }
        return begin() + r;
    }

    template <typename T>
    inline typename Vector<T>::Iterator Vector<T>::insert(typename Vector<T>::Iterator itPos,
        const typename Vector<T>::Iterator &b, const typename Vector<T>::Iterator &e)
    {
        return insert(itPos, b.get(), e.get());
    }

    // 删除单元素，返回删除的元素之后的元素的迭代器
    template <typename T>
    typename Vector<T>::Iterator Vector<T>::erase(typename Vector<T>::Iterator itPos)
    {
        typename Vector<T>::Rank r = itPos - begin();
        ASSERT_DEBUG(itPos < end() && itPos >= begin(), "Invalid pos Iterator");

/*         for (Rank i = r; i != _size - 1; ++i)
        {
            _elem[i] = std::move(_elem[i + 1]);
        } */
        (_elem + r)->~T();
        memmove(reinterpret_cast<void *>(_elem + r), reinterpret_cast<void *>(_elem + r + 1), (_size - r - 1) * sizeof(T));

        --_size;
        if (_need_shrink())
        {
            _shrink();
        }
        return begin() + r;
    }

    // 删除一个迭代器区间范围内的元素，原来迭代器区间itEnd所指向的元素的值
    template <typename T>
    typename Vector<T>::Iterator Vector<T>::erase(typename Vector<T>::Iterator itBegin,
        typename Vector<T>::Iterator itEnd)
    {
        typename Vector<T>::Rank rB = itBegin - begin(), rE = itEnd - begin();
        ASSERT_DEBUG(((itBegin >= begin() && itBegin <= end())
            && (itEnd > begin() && itEnd <= end())
            && itBegin <= itEnd)
            , "Invalid Iterator range"
        );
        typename Vector<T>::Rank n = itEnd - itBegin;

/*         for (Rank i = rB; i != rE; ++i)
        {
            _elem[i] = std::move(_elem[i + n]);
        } */
        for (Rank i = rB; i != rE; ++i)
        {
            (_elem + i)->~T();
        }
        memmove(reinterpret_cast<void *>(_elem + rB), reinterpret_cast<void *>(_elem + rE), n * sizeof(T));

        _size -= n;
        if (_need_shrink())
        {
            _shrink();
        }
        return begin() + rB;
    }

    template <typename T>
    void Vector<T>::resize(typename Vector<T>::Rank n)
    {
        Rank oldSize = _size;
        _size = n;
        if (n < oldSize)
        {
            for (Rank i = oldSize - 1; _size <= i; --i)
            {
                (_elem + i)->~T();
            }

            if (_need_shrink())
            {
                _shrink();
            }
        }
        else if (n > oldSize)
        {
            if (_need_expand())
            {
                _expand();
            }

            for (Rank i = oldSize; i < _size; ++i)
            {
                new(_elem + i) T();
            }
        }
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

        Rank oldSize = _size;
        _size -= k;
        for (Rank i = _size; i != oldSize; ++i)
        {
            (_elem + i)->~T();
        }

        if (_need_shrink())
        {
            _shrink();
        }
    }

    template <typename T>
    void Vector<T>::reverse()
    {
        for (Rank i = 0; i < _size / 2; ++i)
        {
            Swap(_elem[i], _elem[_size - i - 1]);
        }
    }
}

#endif // VECTOR_MODIFICATIONS_H


