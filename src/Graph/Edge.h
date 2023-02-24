/*
 @Date    : 2018-08-16 09:11:00
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
边类模板
 */

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "../Base/AbstractBaseEntity.h"
#include "../CZString/CZString.h"

namespace CZ
{
    template <typename T>
    class Edge;
    template <typename ED, typename VD>
    class Graph;

    template <typename T>
    class Edge : public AbstractBaseEntity
    {
        template <typename ED, typename VD>
        friend class Graph;

    public:
        using Rank = uint32_t;

        Edge(Rank s_ = 0, Rank d_ = 0, const T &data_ = T()) : _s(s_), _d(d_), _data(data_), _valid(false) {}

        Rank source() const { return _s; }
        Rank destination() const { return _d; }
        const T &data() const { return _data; }
        T &data() { return _data; }

        void set_valid()
        {
            _valid = true;
        }
        void set_invalid()
        {
            _valid = false;
        }
        bool valid() const { return _valid; }

        const char *c_str() const override;

        HashRank hash() const override
        {
            return (Hash<CZString>()(get_entity_name()) + Hash<T>()(_data) + Hash<Rank>()(_s) + Hash<Rank>()(_d) + Hash<bool>()(_valid)) % CZ_MAX_HASH_VALUE;
        }

        const char *get_entity_name() const override
        {
            return "Edge";
        }

    private:
        Rank _s, _d;
        T _data;
        bool _valid; // 记录这条边是否有效，即是否存在，新创建的边默认为无效
    };

    template <typename T>
    const char *Edge<T>::c_str() const
    {
        std::ostringstream oss;
        oss << this->get_entity_name() << "(" << source() << ", " << destination() << ")";
        return this->get_c_str_from_stream(oss);
    }
} // CZ

#endif // EDGE_H
