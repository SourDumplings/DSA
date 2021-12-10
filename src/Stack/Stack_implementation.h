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

#include "Stack.h"

namespace CZ
{
    template <typename T, typename C>
    const T& Stack<T, C>::top() const
    {
        try
        {
            if (empty())
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
    inline T& Stack<T, C>::top()
    { return const_cast<T&>(static_cast<const Stack<T, C>&>(*this).top()); }

    template <typename T, typename C>
    inline typename Stack<T, C>::Rank Stack<T, C>::size() const
    { return _data.size(); }

    template <typename T, typename C>
    inline bool Stack<T, C>::empty() const
    { return _data.empty(); }

    template <typename T, typename C>
    inline void Stack<T, C>::push(const T &x)
    { return _data.push_back(x); }

    template <typename T, typename C>
    inline void Stack<T, C>::push(T &&x)
    { return _data.push_back(std::move(x)); }

    template <typename T, typename C>
    void Stack<T, C>::pop()
    {
        try
        {
            if (empty())
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
    { return _data.clear(); }

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

    template <typename T>
    inline std::ostream& operator<<(std::ostream &os, const Stack<T> &s) { return os; }
} // CZ

#endif // STACK_IMPLEMENTATION_H

