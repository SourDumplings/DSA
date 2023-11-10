/*
 @Date    : 2018-05-24 09:08:14
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
队列类模板的实现
 */

#ifndef QUEUE_IMPLEMENTATION_H
#define QUEUE_IMPLEMENTATION_H

#include "Queue.h"

#include "../CZString/CZString.h"

#include <cstdio>
#include <utility>
#include <iostream>
#include <sstream>

namespace CZ
{
    template <typename T, typename C>
    inline typename Queue<T, C>::Rank Queue<T, C>::size() const
    {
        return _data.size();
    }

    template <typename T, typename C>
    const T &Queue<T, C>::front() const
    {
        ASSERT_DEBUG(!this->empty(), "empty queue");
        return _data.front();
    }

    template <typename T, typename C>
    inline T &Queue<T, C>::front()
    {
        return const_cast<T &>(static_cast<const Queue<T, C> &>(*this).front());
    }

    template <typename T, typename C>
    inline void Queue<T, C>::push(const T &x)
    {
        return _data.push_back(x);
    }

    template <typename T, typename C>
    inline void Queue<T, C>::push(T &&x)
    {
        return _data.push_back(std::move(x));
    }

    template <typename T, typename C>
    void Queue<T, C>::pop()
    {
        ASSERT_DEBUG(!this->empty(), "empty queue");
        return _data.pop_front();
    }

    template <typename T, typename C>
    inline void Queue<T, C>::clear()
    {
        return _data.clear();
    }

    template <typename T, typename C>
    void Queue<T, C>::print_info(const char *name) const
    {
        printf("for queue %s:\n", name);
        printf("size = %u\n", size());

#ifdef DEBUG
        printf("elements(from front to back): ");
        for (auto &x : _data)
        {
            std::cout << x << " ";
        }
#endif

        printf("\n\n");
    }

    template <typename T, typename C>
    const char *Queue<T, C>::get_entity_name() const
    {
        return "Queue";
    }

    template <typename T, typename C>
    HashRank Queue<T, C>::hash() const
    {
        return (CZString(get_entity_name()).hash() + _data.hash()) % CZ_MAX_HASH_VALUE;
    }

    template <typename T, typename C>
    const char *Queue<T, C>::c_str() const
    {
#ifdef DEBUG
        std::ostringstream oss;
        oss << get_entity_name() << "[";
        for (auto it = _data.begin(); it != _data.end(); ++it)
        {
            if (it != _data.begin())
            {
                oss << ", ";
            }
            oss << *it;
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
#else
        return this->get_entity_name();
#endif
    }

} // CZ

#endif // QUEUE_IMPLEMENTATION_H
