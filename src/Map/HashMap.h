/*
 @Date    : 2018-07-27 20:55:09
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
HashMap 类模板
默认使用 Vector 作为数据容器
支持哈希函数定制(接受值和哈希表大小两个参数)，内置线性和平方探测法
内置了取余的哈希函数，因此如果存放非数值类则必须定制哈希函数
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "../Vector/Vector.h"
#include "KVPair.h"
#include "../Algorithms/Hash.h"

namespace CZ
{
    // 探测方法
    enum ProbingMethod
    {
        LINEAR_PROBING,
        SQUARE_PROBING
    };

    template <typename T, typename H = Hash<T>>
    class HashMap
    {
    public:
        using Rank = uint64_t;

        // 构造函数，默认大小10000，使用取模作为哈希函数，采用线性探测法
        HashMap(const Rank tableSize_ = 10000,
            const ProbingMethod probingMethod_ = LINEAR_PROBING);

        // 查找函数，返回所在的秩，如果元素不存在则返回-1
        Rank search(const T &value) const;
        // 数据访问接口
        const T& get(const Rank pos) const;
        Rank size() const;
        Rank table_size() const;

        // 插入和删除，可以选择失败时是抛出异常还是返回false，默认返回false
        // 默认允许重复元素
        bool insert(const T &value, const bool nonexcept = true, const bool repeatable = true);
        bool remove(const T &value, const bool nonexcept = true);

        // 列出所有存在的元素
        void print_info(const char *name = "") const;
    private:
        // 用Vector存储数据对，数据及是否有效的标志
        // 无效指该位置没有放数据或者被懒惰删除了
        Vector<KVPair<T, bool>> _data;
        Rank _tableSize, _size;
        ProbingMethod _probingMethod;
        // 探测方法， 如果探测不到空位则返回-1
        Rank _linear_probing(const Rank h) const;
        Rank _square_probing(const Rank h) const;
        // 查找方法，如果找不到对应值则返回-1
        Rank _linear_search(const Rank h, const T &value) const;
        Rank _square_search(const Rank h, const T &value) const;
    };
} // CZ

#include "HashMap_implementation.h"

#endif // HASH_MAP_H

