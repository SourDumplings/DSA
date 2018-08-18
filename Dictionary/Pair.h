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
    template <typename K, typename V> class Pair;
    template <typename K, typename V> bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs);
    template <typename K, typename V> bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs);

    template <typename K, typename V>
    class Pair
    {
        friend bool operator< <K, V>(const Pair<K, V> &lhs, const Pair<K, V> &rhs);
        friend bool operator> <K, V>(const Pair<K, V> &lhs, const Pair<K, V> &rhs);
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

    // 键值数对的大小比较是比较key
    template <typename K, typename V>
    inline bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    { return lhs._key < rhs._key; }

    template <typename K, typename V>
    inline bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    { return lhs._key > rhs._key; }

} // CZ

#endif // PAIR_H
