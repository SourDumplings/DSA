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
        oss << this->get_entity_name() << "[";
        It b = begin(), e = end();
        for (It it = b; it != e; ++it)
        {
            if (it != b)
            {
                oss << ", ";
            }
            oss << *it;
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T, typename It>
    HashRank AbstractIterableContainer<T, It>::hash() const
    {
        HashRank hashValue = 0;
        const char *containerName = this->get_entity_name();
        for (const char *p = containerName; p && *p != '\0'; ++p)
        {
            hashValue = hashValue ^ Hash<char>()(*p);
        }
        It e = end();
        for (It it = begin(); it != e; ++it)
        {
            hashValue = hashValue ^ Hash<T>()(*it);
        }
        return hashValue;
    }

    template <typename T, typename It>
    bool operator==(const AbstractIterableContainer<T, It> &lhs, const AbstractIterableContainer<T, It> &rhs)
    {
        return Dict_equal(lhs, rhs);
    }

    template <typename T, typename It>
    bool operator!=(const AbstractIterableContainer<T, It> &lhs, const AbstractIterableContainer<T, It> &rhs)
    {
        return !(lhs == rhs);
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