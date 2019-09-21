/*
 @Date    : 2018-05-30 10:45:40
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
随机访问迭代器类模板
 */

#ifndef RANDOM_ITERATOR_H
#define RANDOM_ITERATOR_H

#include "BiIterator.h"

namespace CZ
{
    template <typename T> class RandomIterator;
    using RandomIteratorRank = long long;

    template <typename T> bool operator==(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
    template <typename T> bool operator!=(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
    template <typename T> bool operator<(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
    template <typename T> bool operator<=(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
    template <typename T> bool operator>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
    template <typename T> bool operator>=(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
    template <typename T>
    RandomIteratorRank operator-(const RandomIterator<T> &lhs,
        const RandomIterator<T> &rhs);
    template <typename T>
    RandomIterator<T> operator+(const RandomIterator<T> &lhs, const RandomIteratorRank n);
    template <typename T>
    RandomIterator<T> operator-(const RandomIterator<T> &lhs, const RandomIteratorRank n);
    template <typename T>
    RandomIterator<T> operator+(const RandomIteratorRank n, const RandomIterator<T> &rhs);

    template <typename T>
    class RandomIterator: public BiIterator<T>
    {
        friend RandomIteratorRank operator-<T>(const RandomIterator<T> &lhs,
            const RandomIterator<T> &rhs);
        friend RandomIterator<T> operator+<T>(const RandomIterator<T> &lhs, const RandomIteratorRank n);
        friend RandomIterator<T> operator-<T>(const RandomIterator<T> &lhs, const RandomIteratorRank n);
        friend RandomIterator<T> operator+<T>(const RandomIteratorRank n, const RandomIterator<T> &rhs);
        friend bool operator==<T>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
        friend bool operator!=<T>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
        friend bool operator< <T>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
        friend bool operator<=<T>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
        friend bool operator><T>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
        friend bool operator>=<T>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs);
    public:
        using iterator_category = random_iterator_tag;
        using Rank = RandomIteratorRank;

        RandomIterator(T *p_ = nullptr): BiIterator<T>(p_) {}
        virtual ~RandomIterator() = default;

        virtual const T& operator[](const Rank index) const
        {
            return *(SeqIterator<T>::_p + index);
        }

        virtual T& operator[](const Rank index)
        {
            return const_cast<T&>(static_cast<const RandomIterator<T>&>(*this)[index]);
        }

        virtual RandomIterator<T>& operator+=(Rank n)
        {
            SeqIterator<T>::_p += n;
            return *this;
        }

        virtual RandomIterator<T>& operator-=(Rank n)
        {
            SeqIterator<T>::_p -= n;
            return *this;
        }
    };

    template <typename T>
    inline bool operator==(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs)
    { return lhs._p == rhs._p; }

    template <typename T>
    inline bool operator!=(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs)
    { return !(lhs == rhs); }

    template <typename T>
    inline bool operator<(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs)
    { return lhs._p < rhs._p; }

    template <typename T>
    inline bool operator<=(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs)
    { return lhs == rhs || lhs < rhs; }

    template <typename T>
    inline bool operator>(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs)
    { return lhs._p > rhs._p; }

    template <typename T>
    inline bool operator>=(const RandomIterator<T> &lhs, const RandomIterator<T> &rhs)
    { return lhs > rhs || lhs == rhs; }

    template <typename T>
    inline RandomIteratorRank operator-(const RandomIterator<T> &lhs,
        const RandomIterator<T> &rhs)
    { return lhs._p - rhs._p; }

    template <typename T>
    inline RandomIterator<T> operator+(const RandomIterator<T> &lhs, const RandomIteratorRank n)
    { return RandomIterator<T>(lhs._p + n); }

    template <typename T>
    inline RandomIterator<T> operator-(const RandomIterator<T> &lhs, const RandomIteratorRank n)
    { return RandomIterator<T>(lhs._p - n); }

    template <typename T>
    inline RandomIterator<T> operator+(const RandomIteratorRank n, const RandomIterator<T> &rhs)
    { return RandomIterator<T>(rhs._p + n); }
} // CZ

#endif // RANDOM_ITERATOR_H


