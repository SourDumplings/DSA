/*
 @Date    : 2018-07-27 22:07:14
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
数据对模板类，尤其用于存储键值对
 */

#ifndef PAIR_H
#define PAIR_H

#include <iostream>

namespace CZ
{
    template <typename K, typename V>
    class Pair
    {
    public:
        Pair() = default;
        Pair(const K &key_, const V &value_): _key(key_), _value(value_) {};
        K& key() { return _key; }
        const K& key() const { return _key; }
        V& value() { return _value; }
        const V& value() const { return _value; }
    private:
        K _key;
        V _value;
    };

    template <typename K, typename V>
    std::ostream& operator<<(std::ostream &os, const Pair<K, V> &p)
    {
        os << "pair(" << p.key() << ", " << p.value() << ")";
        return os;
    }

} // CZ

#endif // PAIR_H
