/*
 @Date    : 2018-05-24 09:04:29
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
队列类模板(容器适配器)，默认采用List实现
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "../List/List.h"

namespace CZ
{
    template <typename T, typename C = List<T>>
    class Queue
    {
    public:
        using Rank = unsigned;

        bool empty() const;
        Rank size() const;
        const T& front() const;
        T& front();

        void push(const T &x);
        void push(T &&x);
        void pop();
        void clear();

        void print_info(const char *name = "") const;
    private:
        C _data;
    };
} // CZ

#include "Queue_implementation.h"

#endif // QUEUE_H


