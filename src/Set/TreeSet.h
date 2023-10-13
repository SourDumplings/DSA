/*
 @Date    : 2018-08-12 21:24:23
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
集合类模板，由红黑树实现，不允许重复元素
 */

#ifndef TREE_SET_H
#define TREE_SET_H

#include "../Base/AbstractSeqIterableContainer.h"
#include "../Tree/BinTree/RedBlackTree.h"
#include "TreeSetIterator.h"

namespace CZ
{
    template <typename T> class TreeSet;

    template <typename T> TreeSet<T> operator+(const TreeSet<T> &lhs, const TreeSet<T> &rhs);
    template <typename T> TreeSet<T> operator-(const TreeSet<T> &lhs, const TreeSet<T> &rhs);

    template <typename T>
    class TreeSet: public AbstractSeqIterableContainer<T, TreeSetIterator<T>>
    {
        friend TreeSet<T> operator+<T>(const TreeSet<T> &lhs, const TreeSet<T> &rhs);
        friend TreeSet<T> operator-<T>(const TreeSet<T> &lhs, const TreeSet<T> &rhs);
        friend class TreeSetIterator<T>;
    public:
        using Rank = typename AbstractSeqIterableContainer<T, TreeSetIterator<T>>::Rank;
        using Iterator = TreeSetIterator<T>;

        TreeSet();
        TreeSet(const std::initializer_list<T> &l);
        
        TreeSet(const T *begin, const T *end);

        template <typename It>
        TreeSet(const It &begin, const It &end);

        TreeSet(const TreeSet<T> &s);
        TreeSet(TreeSet<T> &&s) noexcept;

        // 数据访问接口
        Rank size() const override;
        bool contains(const T &value) const;
        Iterator begin() override;
        Iterator begin() const override;
        Iterator end() override;
        Iterator end() const override;
        T &front();
        const T &front() const;
        T &back();
        const T &back() const;

        // 插入，如果该值已经存在则插入失败，即什么都不做，返回 false
        bool insert(const T &value);
        // 删除，有元素被删除则返回 true
        bool remove(const T &value);
        void clear() override;

        TreeSet<T> &operator=(const TreeSet<T> &s);
        TreeSet<T> &operator=(TreeSet<T> &&s) noexcept;

        void print_info(const char *name = "") const;

        static TreeSet<T> intersection(const TreeSet<T> &s1, const TreeSet<T> &s2);

        const char *get_entity_name() const;

        static TreeSet<T> merge(const TreeSet<T> &s1, const TreeSet<T> &s2);
        static TreeSet<T> intersect(const TreeSet<T> &s1, const TreeSet<T> &s2);

    protected:
        Iterator search(const T &data) const;

    private:
        RedBlackTree<T> _T;

        template <typename It>
        void _construct_from(const It &begin, const It &end);
    };
} // CZ

#include "TreeSet_implementation.h"
#include "TreeSet_operations.h"

#endif // TREE_TreeSET_H

