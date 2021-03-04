/*
 @Date    : 2018-08-16 09:11:00
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
边模板类
 */

#ifndef EDGE_H
#define EDGE_H

#include <iostream>

namespace CZ
{
    template <typename T> class Edge;
    template <typename ED, typename VD> class Graph;

    template <typename T>
    class Edge
    {
        template <typename ED, typename VD> friend class Graph;
    public:
        using Rank = unsigned;

        Edge(Rank s_ = 0, Rank d_ = 0, const T &data_ = T()):
            _s(s_), _d(d_), _data(data_), _valid(false) {}

        Rank source() const { return _s; }
        Rank destination() const { return _d; }
        const T& data() const { return _data; }
        T& data() { return _data; }

        void set_valid() { _valid = true; return; }
        void set_invalid() { _valid = false; return; }
        bool valid() const { return _valid; }

    private:
        Rank _s, _d;
        T _data;
        bool _valid; // 记录这条边是否有效，即是否存在，新创建的边默认为无效
    };

    template <typename T>
    std::ostream& operator<<(std::ostream &os, const Edge<T> &e)
    {
        os << e.data() << "(" << e.source() << ", " << e.destination() << ")";
        return os;
    }
} // CZ

#endif // EDGE_H

