/*
 * @Author: SourDumplings
 * @Date: 2022-11-16 14:43:07
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 顺序的可迭代容器抽象类模板
 */

#ifndef ABSTRACT_SEQ_ITERABLE_CONTAINER_H
#define ABSTRACT_SEQ_ITERABLE_CONTAINER_H

#include "AbstractIterableContainer.h"

namespace CZ
{
    template <typename T, typename It>
    class AbstractSeqIterableContainer : public AbstractIterableContainer<T, It>
    {
    public:
        using Rank = typename AbstractIterableContainer<T, It>::Rank;
        using RankPlus = typename AbstractIterableContainer<T, It>::RankPlus;

        // 相比于 AbstractIterableContainer，其哈希方法需要考虑到元素顺序
        HashRank hash() const override
        {
            HashRank hashValue = 0;
            const char *containerName = this->get_entity_name();
            for (const char *p = containerName; p && *p != '\0'; ++p)
            {
                hashValue = ((hashValue ^ Hash<char>()(*p)) << 8) | ((hashValue >> 56) & 0xF);
            }

            for (It it = this->begin(); it != this->end(); ++it)
            {
                hashValue = ((hashValue ^ Hash<T>()(*it)) << 8) | ((hashValue >> 56) & 0xF);
            }
            return hashValue;
        }
    };
}

#endif