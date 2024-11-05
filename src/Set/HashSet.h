/*
 @Date    : 2023-01-04 18:37:07
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
HashSet 类模板
默认使用 Vector 作为数据容器，采用拉链法实现哈希表，使用 Hash<T> 算法模板作为哈希函数
不允许重复 key
 */

#ifndef HASH_SET_H
#define HASH_SET_H

#include "../Base/AbstractBaseContainer.h"
#include "../List/List.h"
#include "../Vector/Vector.h"
#include "../Algorithms/Hash.h"
#include "HashSetIterator.h"
#include <initializer_list>

namespace CZ
{
    template <typename T>
    class HashSet: public AbstractIterableContainer<T, HashSetIterator<T>>
    {
        friend class HashSetIterator<T>;

    public:
        using Rank = typename Vector<List<T>>::Rank;
        using RankPlus = typename Vector<List<T>>::RankPlus;
        using Iterator = HashSetIterator<T>;

        static const Rank INITIAL_TABLE_SIZE = 32;

        // 构造函数，默认大小 32，使用取模作为哈希函数
        HashSet(const std::initializer_list<T> &l);

        HashSet(const T *begin, const T *end);

        template <typename It>
        HashSet(const It &begin, const It &end);

        HashSet(const Rank tableSize_ = INITIAL_TABLE_SIZE);

        HashSet(const HashSet<T> &rHashSet) = default;

        HashSet(HashSet<T> &&rHashSet) noexcept;

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

        HashSet<T> &operator=(const HashSet<T> &s);
        HashSet<T> &operator=(HashSet<T> &&s) noexcept;

        Iterator begin() override;
        Iterator end() override;
        Iterator begin() const override;
        Iterator end() const override;

        const char *get_entity_name() const override;

        // 列出所有存在的元素
        void print_info(const char *name = "") const;

        static HashSet<T> merge(const HashSet<T> &s1, const HashSet<T> &s2);
        static HashSet<T> intersect(const HashSet<T> &s1, const HashSet<T> &s2);

    protected:
        Iterator search(const T &data) const;

        // 成功插入则返回被插入元素的迭代器，失败则返回尾后迭代器
        Iterator insert_return_it(const T &data);

    private:
        Vector<List<T>> _table;
        Rank _size;
        Rank _firstNonEmptyBucketIndex;
        Rank _lastNonEmptyBucketIndex;

        // 哈希表的扩容和缩容，扩缩容倍率都是 2 倍，每次扩缩容完了都需要 rehash
        bool _need_expand() const;
        bool _need_shrink() const;
        void _expand();
        void _shrink();
        void _rehash();

        template <typename It>
        void _construct_from(const It &begin, const It &end);

        void _update_bucket_index_range();

        Rank _get_suitable_table_size(Rank lowerLimit) const;
    };

    template <typename T>
    HashSet<T> operator+(const HashSet<T> &lhs, const HashSet<T> &rhs);

    template <typename T>
    HashSet<T> operator-(const HashSet<T> &lhs, const HashSet<T> &rhs);
} // CZ

#include "HashSet_implementation.h"

#endif // HASH_SET_H
