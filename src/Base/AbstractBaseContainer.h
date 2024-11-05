/*
 * @Author: SourDumplings
 * @Date: 2022-10-24 18:41:58
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 基础容器类模板
 */

#ifndef ABSTRACT_BASE_CONTAINER_H
#define ABSTRACT_BASE_CONTAINER_H

#include "AbstractBaseEntity.h"

namespace CZ
{
    template <typename T>
    class AbstractBaseContainer : public AbstractBaseEntity
    {
    public:
        using Rank = uint32_t;
        using RankPlus = int64_t;

        bool empty() const;

        virtual Rank size() const = 0;

        virtual void clear() = 0;
    };

    template <typename T>
    inline bool AbstractBaseContainer<T>::empty() const
    {
        return size() == 0;
    }
}

#endif