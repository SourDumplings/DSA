/*
 @Date    : 2018-07-27 22:07:14
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
数据对类模板，尤其用于存储键值对

在 C++11 中，pair 支持多态，vector 等不支持，例如：
class B
{

};

class D: public B
{

};

int main()
{
    vector<D> vd;
    vector<B> vb(vd);  // 会编译错误，找不到相应的构造函数

    pair<D, int> pD;
    pair<B, int> pB(pD); // 正常编译
    return 0;
}

因此对于 KVPair 这里使用成员模板使之兼容多态性
 */

#ifndef PAIR_H
#define PAIR_H

#include "../Base/AbstractBaseEntity.h"
#include "../CZString/CZString.h"
#include <iostream>

namespace CZ
{
    template <typename K, typename V>
    class KVPair;
    template <typename K, typename V>
    bool operator<(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);
    template <typename K, typename V>
    bool operator>(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);
    template <typename K, typename V>
    bool operator==(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);
    template <typename K, typename V>
    bool operator!=(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);

    template <typename K, typename V>
    class KVPair : public AbstractBaseEntity 
    {
        friend bool operator< <K, V>(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);
        friend bool operator><K, V>(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);
        friend bool operator==<K, V>(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);
        friend bool operator!=<K, V>(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs);

    public:
        KVPair() = default;
        KVPair(const K &key_, const V &value_) : _key(key_), _value(value_){};
        // 成员模板复制构造函数，用于支持键值类为 K、V 子类的 KVPair
        template <typename KD, typename VD>
        KVPair(const KVPair<KD, VD> &p) : _key(p.key()), _value(p.value()){};

        K &key()
        {
            return _key;
        }
        const K &key() const
        {
            return _key;
        }
        V &value()
        {
            return _value;
        }
        const V &value() const
        {
            return _value;
        }

        // 赋值操作符函数
        template <typename KD, typename VD>
        KVPair<K, V> &operator=(const KVPair<KD, VD> &p)
        {
            if (reinterpret_cast<const KVPair<KD, VD> *>(this) != &p)
            {
                _key = p.key();
                _value = p.value();
            }
            return *this;
        }

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

    private:
        K _key;
        V _value;
    };

    template <typename K, typename V>
    inline const char *KVPair<K, V>::get_entity_name() const
    {
        return "KVPair";
    }

    template <typename K, typename V>
    inline HashRank KVPair<K, V>::hash() const
    {
        return (Hash<CZString>()(get_entity_name()) + Hash<K>()(_key) + Hash<V>()(_value)) % CZ_MAX_HASH_VALUE;
    }

    template <typename K, typename V>
    const char *KVPair<K, V>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "(" << _key << ", " << _value << ")";
        return this->get_c_str_from_stream(oss);
    }

    template <typename K, typename V>
    std::ostream &operator<<(std::ostream &os, const KVPair<K, V> &p)
    {
        os << "pair(" << p.key() << ", " << p.value() << ")";
        return os;
    }

    // 键值数对的大小比较即相等判断都是比较key
    template <typename K, typename V>
    inline bool operator<(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs)
    {
        return lhs._key < rhs._key;
    }

    template <typename K, typename V>
    inline bool operator>(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs)
    {
        return lhs._key > rhs._key;
    }

    template <typename K, typename V>
    inline bool operator==(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs)
    {
        return lhs._key == rhs._key;
    }

    template <typename K, typename V>
    inline bool operator!=(const KVPair<K, V> &lhs, const KVPair<K, V> &rhs)
    {
        return lhs._key != rhs._key;
    }
} // CZ

#endif // PAIR_H
