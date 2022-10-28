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

#include "../Base/AbstractBaseContainer.h"
#include "../Vector/Vector.h"

namespace CZ
{
    template <typename T, typename C = Vector<T>>
    class Stack : public AbstractBaseContainer<T>
    {
    public:
        using Rank = typename AbstractBaseContainer<T>::Rank;

        const T &top() const;
        T &top();
        Rank size() const override;

        void push(const T &x);
        void push(T &&x);
        void pop();
        void clear() override;

        HashRank hash() const override;
        const char *c_str() const override;

        void print_info(const char *name = "") const;

    protected:
        const char *get_container_name() const override;

    private:
        C _data;
    };
} // CZ

#include "Stack_implementation.h"

#endif // STACK_H
