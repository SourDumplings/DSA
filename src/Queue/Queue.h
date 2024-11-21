/*
 @Date    : 2018-05-24 09:04:29
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
队列类模板(容器适配器)，默认采用List实现
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "../Base/AbstractBaseContainer.h"
#include "../List/List.h"

namespace DSA
{
    template <typename T, typename C = List<T>>
    class Queue : public AbstractBaseContainer<T>
    {
    public:
        using Rank = typename AbstractBaseContainer<T>::Rank;

        Rank size() const override;
        const T &front() const;
        T &front();

        void push(const T &x);
        void push(T &&x);
        void pop();
        void clear() override;

        HashRank hash() const override;
        const char *c_str() const override;

        void print_info(const char *name = "") const;

        const char *get_entity_name() const override;

    private:
        C _data;
    };
} // DSA

#include "Queue_implementation.h"

#endif // QUEUE_H
