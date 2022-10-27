/*
 * @Author: SourDumplings
 * @Date: 2022-10-24 18:41:58
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 可迭代遍历的容器类模板
 */

#ifndef ABSTRACT_ITERABLE_CONTAINER_H
#define ABSTRACT_ITERABLE_CONTAINER_H

#include "../Algorithms/Dict_compare.h"
#include "AbstractBaseContainer.h"
#include <cstring>
#include <sstream>

namespace CZ
{
    template <typename T, typename It>
    class AbstractIterableContainer : public AbstractBaseContainer<T>
    {
    public:
        using Rank = typename AbstractBaseContainer<T>::Rank;
        using RankPlus = typename AbstractBaseContainer<T>::RankPlus;
        using Iterator = It;

        const char *c_str() const override;
        HashRank hash() const override;

        virtual Iterator begin() = 0;
        virtual Iterator end() = 0;
        virtual Iterator begin() const = 0;
        virtual Iterator end() const = 0;
    };

    template <typename T, typename It>
    const char *AbstractIterableContainer<T, It>::c_str() const
    {
        std::ostringstream oss;
        oss << hash() << "[";
        for (It it = begin(); it != end(); ++it)
        {
            if (it != begin())
            {
                oss << ", ";
            }
            oss << *it;
        }
        oss << "]";
        this->_pStr = static_cast<char *>(malloc(sizeof(char) * (oss.str().length() + 1)));
        strcpy(this->_pStr, oss.str().c_str());
        return this->_pStr;
    }

    template <typename T, typename It>
    HashRank AbstractIterableContainer<T, It>::hash() const
    {
        HashRank hashValue = 0;
        for (It it = begin(); it != end(); ++it)
        {
            hashValue = (hashValue + Hash<T>()(*it)) % CZ_MAX_HASH_VALUE;
        }
        return hashValue;
    }

    template <typename T, typename It>
    bool operator==(const AbstractIterableContainer<T, It> &lhs, const AbstractIterableContainer<T, It> &rhs)
    {
        return Dict_equal(lhs, rhs);
    }

    template <typename T, typename It>
    bool operator<(const AbstractIterableContainer<T, It> &lhs, const AbstractIterableContainer<T, It> &rhs)
    {
        return Dict_less(lhs, rhs);
    }

    template <typename T, typename It>
    bool operator<=(const AbstractIterableContainer<T, It> &lhs, const AbstractIterableContainer<T, It> &rhs)
    {
        return Dict_less_or_equal(lhs, rhs);
    }

    template <typename T, typename It>
    bool operator>(const AbstractIterableContainer<T, It> &lhs, const AbstractIterableContainer<T, It> &rhs)
    {
        return Dict_greater(lhs, rhs);
    }

    template <typename T, typename It>
    bool operator>=(const AbstractIterableContainer<T, It> &lhs, const AbstractIterableContainer<T, It> &rhs)
    {
        return Dict_greater_or_equal(lhs, rhs);
    }
}

#endif