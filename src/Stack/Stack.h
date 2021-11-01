/*
 @Date    : 2018-05-23 10:09:02
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
堆栈类模板（容器适配器），默认是通过Vector实现的
 */

#ifndef STACK_H
#define STACK_H

#include "../Vector/Vector.h"

namespace CZ
{
    template <typename T, typename C = Vector<T>>
    class Stack
    {
    public:
        using Rank = unsigned;

        const T& top() const;
        T& top();
        Rank size() const;
        bool empty() const;

        void push(const T &x);
        void push(T &&x);
        void pop();
        void clear();

        void print_info(const char *name = "") const;
    private:
        C _data;
    };
} // CZ

#include "Stack_implementation.h"

#endif // STACK_H
