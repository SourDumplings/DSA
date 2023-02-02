/*
 @Date    : 2023-01-16 20:55:09
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
FlatHashSet 类模板
相比于 HashSet，对于哈希碰撞采用探测填充的方法处理
不允许重复 key
 */

#ifndef FLAT_HASH_SET_H
#define FLAT_HASH_SET_H

#include "../Algorithms/Hash.h"
#include "../Base/AbstractBaseContainer.h"
#include "../Map/KVPair.h"
#include "../Vector/Vector.h"
#include "FlatHashSetIterator.h"
#include <initializer_list>

namespace CZ
{
    namespace FlatHashSetAccessories
    {
        enum ProbingMethod
        {
            LINEAR_PROBING,
            SQUARE_PROBING
        };
    }

    template <typename T>
    class FlatHashSet: public AbstractIterableContainer<T, FlatHashSetIterator<T>>
    {
        friend class FlatHashSetIterator<T>;

    public:
        using Rank = typename Vector<KVPair<T, bool>>::Rank;
        using RankPlus = typename Vector<KVPair<T, bool>>::RankPlus;
        using Iterator = FlatHashSetIterator<T>;

        static const Rank INITIAL_TABLE_SIZE = 32;

        // 构造函数，默认大小 32，使用取模作为哈希函数
        FlatHashSet(const std::initializer_list<T> &l, const FlatHashSetAccessories::ProbingMethod probingMethod_ = FlatHashSetAccessories::LINEAR_PROBING);

        FlatHashSet(const T *begin, const T *end, const FlatHashSetAccessories::ProbingMethod probingMethod_ = FlatHashSetAccessories::LINEAR_PROBING);

        template <typename It>
        FlatHashSet(const It &begin, const It &end, const FlatHashSetAccessories::ProbingMethod probingMethod_ = FlatHashSetAccessories::LINEAR_PROBING);

        FlatHashSet(const Rank tableSize_ = INITIAL_TABLE_SIZE, const FlatHashSetAccessories::ProbingMethod probingMethod_ = FlatHashSetAccessories::LINEAR_PROBING);

        FlatHashSet(const FlatHashSet<T> &rFlatHashSet) = default;

        FlatHashSet(FlatHashSet<T> &&rFlatHashSet);

        // 数据访问接口
        Rank size() const override;
        bool contains(const T &data) const;
        Rank table_size() const;

        // 插入和删除
        // 成功插入则返回 true
        bool insert(const T &data);
        // 成功删除了元素返回 true
        bool remove(const T &data);

        void clear() override;

        FlatHashSet<T> &operator=(const FlatHashSet<T> &s);
        FlatHashSet<T> &operator=(FlatHashSet<T> &&s);

        Iterator begin() override;
        Iterator end() override;
        Iterator begin() const override;
        Iterator end() const override;

        const char *get_entity_name() const override;

        // 列出所有存在的元素
        void print_info(const char *name = "") const;

    private:
        Vector<KVPair<T, bool>> _table; // 哈希表，存储 KVPair，键是数据，值代表其存在与否
        Rank _size;
        Rank _firstNonEmptyBucketIndex;
        Rank _lastNonEmptyBucketIndex;
        FlatHashSetAccessories::ProbingMethod _probingMethod;

        // 探测方法， 如果探测不到空位则返回-1
        Rank _linear_probing(const Rank h) const;
        Rank _square_probing(const Rank h) const;
        // 查找方法，如果找不到对应值则返回-1
        Rank _linear_search(const Rank h, const T &value) const;
        Rank _square_search(const Rank h, const T &value) const;

        Rank _search(const T &data) const;

        // 哈希表的扩容和缩容，扩缩容倍率都是 2 倍，每次扩缩容完了都需要 rehash
        bool _need_expand() const;
        bool _need_shrink() const;
        void _expand();
        void _shrink();
        void _rehash();

        Rank _do_insert(const T &data);

        template <typename It>
        void _construct_from(const It &begin, const It &end);

        Rank _get_suitable_table_size(Rank lowerLimit) const;
        
        // 将元素前压到前面去
        void _compress_forward();
    };
} // CZ

#include "FlatHashSet_implementation.h"

#endif // FLAT_HASH_SET_H
