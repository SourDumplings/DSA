/*
 @Date    : 2018-05-23 10:16:05
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
堆栈类模板的实现
 */

#ifndef STACK_IMPLEMENTATION_H
#define STACK_IMPLEMENTATION_H

#include <utility>
#include <stdexcept>
#include <cstdio>
#include <iostream>
#include <sstream>

#include "Stack.h"

#include "../CZString/CZString.h"

namespace CZ
{
    template <typename T, typename C>
    const T &Stack<T, C>::top() const
    {
        try
        {
            if (this->empty())
            {
                throw "empty stack";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }
        return _data.back();
    }

    template <typename T, typename C>
    inline T &Stack<T, C>::top()
    {
        return const_cast<T &>(static_cast<const Stack<T, C> &>(*this).top());
    }

    template <typename T, typename C>
    inline typename Stack<T, C>::Rank Stack<T, C>::size() const
    {
        return _data.size();
    }

    template <typename T, typename C>
    inline void Stack<T, C>::push(const T &x)
    {
        return _data.push_back(x);
    }

    template <typename T, typename C>
    inline void Stack<T, C>::push(T &&x)
    {
        return _data.push_back(std::move(x));
    }

    template <typename T, typename C>
    void Stack<T, C>::pop()
    {
        try
        {
            if (this->empty())
            {
                throw "empty stack";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }
        return _data.pop_back();
    }

    template <typename T, typename C>
    inline void Stack<T, C>::clear()
    {
        return _data.clear();
    }

    template <typename T, typename C>
    void Stack<T, C>::print_info(const char *name) const
    {
        printf("for stack %s:\n", name);
        printf("size = %u\n", size());
        printf("elements(from bottom to top): ");
        for (auto &x : _data)
        {
            std::cout << x << " ";
        }
        printf("\n\n");
        return;
    }

    template <typename T, typename C>
    inline const char *Stack<T, C>::get_entity_name() const
    {
        return "Stack";
    }

    template <typename T, typename C>
    inline HashRank Stack<T, C>::hash() const
    {
        return (CZString(get_entity_name()).hash() + _data.hash()) % CZ_MAX_HASH_VALUE;
    }

    template <typename T, typename C>
    const char *Stack<T, C>::c_str() const
    {
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
        this->_pStr = static_cast<char *>(malloc(sizeof(char) * (oss.str().length() + 1)));
        strcpy(this->_pStr, oss.str().c_str());
        return this->_pStr;
    }
} // CZ

#endif // STACK_IMPLEMENTATION_H
