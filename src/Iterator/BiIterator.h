/*
 @Date    : 2018-05-30 10:29:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
双向迭代器类模板
 */

#ifndef BI_ITERATOR_H
#define BI_ITERATOR_H

#include "SeqIterator.h"

namespace CZ
{
    template <typename T>
    class BiIterator;
    template <typename T>
    bool operator==(const BiIterator<T> &lhs, const BiIterator<T> &rhs);
    template <typename T>
    bool operator!=(const BiIterator<T> &lhs, const BiIterator<T> &rhs);

    template <typename T>
    class BiIterator : public SeqIterator<T>
    {
        friend bool operator==<T>(const BiIterator<T> &lhs, const BiIterator<T> &rhs);
        friend bool operator!=<T>(const BiIterator<T> &lhs, const BiIterator<T> &rhs);

    public:
        typedef bi_iterator_tag iterator_category;

        BiIterator(const T *p_ = nullptr) : SeqIterator<T>(p_) {}

        virtual ~BiIterator() = default;

        virtual BiIterator<T> &operator--()
        {
            --SeqIterator<T>::_p;
            return *this;
        }
        virtual BiIterator<T> operator--(int)
        {
            BiIterator<T> temp = *this;
            --SeqIterator<T>::_p;
            return temp;
        }

        const char *get_entity_name() const override
        {
            return "BiIterator";
        }
    };

    template <typename T>
    bool operator==(const BiIterator<T> &lhs, const BiIterator<T> &rhs)
    {
        return lhs._p == rhs._p;
    }

    template <typename T>
    bool operator!=(const BiIterator<T> &lhs, const BiIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }
} // CZ

#endif // BI_ITERATOR_H
