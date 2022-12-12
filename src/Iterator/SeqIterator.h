/*
 @Date    : 2018-05-30 10:18:32
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
单向迭代器类模板
 */

#ifndef SEQ_ITERATOR_H
#define SEQ_ITERATOR_H

#include "../Base/AbstractBaseEntity.h"
#include "Iterator_traits.h"
#include <iostream>

namespace CZ
{
    template <typename T>
    class SeqIterator;

    template <typename T>
    bool operator==(const SeqIterator<T> &lhs, const SeqIterator<T> &rhs);
    template <typename T>
    bool operator!=(const SeqIterator<T> &lhs, const SeqIterator<T> &rhs);

    template <typename T>
    class SeqIterator : public AbstractBaseEntity
    {
        friend bool operator==<T>(const SeqIterator<T> &lhs, const SeqIterator<T> &rhs);
        friend bool operator!=<T>(const SeqIterator<T> &lhs, const SeqIterator<T> &rhs);

    public:
        typedef seq_iterator_tag iterator_category;

        // 构造函数
        SeqIterator(const T *p_ = nullptr) : _p(const_cast<T *>(p_)) {}

        virtual ~SeqIterator() = default;

        // 操作符
        virtual T &operator*()
        {
            return *_p;
        }
        virtual const T &operator*() const
        {
            return *_p;
        }
        virtual T *operator->()
        {
            return _p;
        }
        virtual const T *operator->() const
        {
            return _p;
        }

        virtual SeqIterator<T> &operator++()
        {
            ++_p;
            return *this;
        }
        virtual SeqIterator<T> operator++(int)
        {
            SeqIterator<T> temp = *this;
            ++_p;
            return temp;
        }

        T *get() { return _p; }
        T *get() const { return _p; }

        const char *c_str() const override
        {
            std::ostringstream oss;
            oss << this->get_entity_name() << "(" << *_p << ")";
            
            return this->get_c_str_from_stream(oss);
        }

        HashRank hash() const override
        {
            return (Hash<const char *>()(get_entity_name()) + Hash<T *>()(_p)) % CZ_MAX_HASH_VALUE;
        }

        const char *get_entity_name() const override
        {
            return "SeqIterator";
        }

    protected:
        T *_p;
    };

    template <typename T>
    bool operator==(const SeqIterator<T> &lhs, const SeqIterator<T> &rhs)
    {
        return lhs._p == rhs._p;
    }
    template <typename T>
    bool operator!=(const SeqIterator<T> &lhs, const SeqIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }

} // CZ

#endif // SEQ_ITERATOR_H
