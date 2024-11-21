/*
 @Date    : 2018-07-01 22:42:14
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树模板，不允许关键码重复
 */

#ifndef B_TREE_H
#define B_TREE_H

#include "../../Base/AbstractBaseContainer.h"
#include "BTreeNode.h"

namespace DSA
{
    template <typename T>
    class BTree : public AbstractBaseContainer<T>
    {
    public:
        using Rank = typename AbstractBaseContainer<T>::Rank;

        BTree(Rank order_ = 3);
        BTree(const BTree &bt);
        BTree(BTree &&bt) noexcept;
        ~BTree();

        Rank order() const;
        Rank size() const override;
        Rank keys_num() const;
        Rank height() const;
        BTreeNode<T> *root() const;
        // 查找操作，查找成功返回对应的B树结点的指针，失败则返回nullptr
        BTreeNode<T> *search(const T &data) const;

        // 由于不允许关键码重复，故插入有可能失败，失败返回false
        bool insert(const T &data);
        // 删除成功返回true
        bool remove(const T &data);
        void clear() override;

        void print_info(const char *name = "") const;

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

    protected:
        Rank _size;                 // 存放的关键码总数
        Rank _order;                // B树的阶次，至少为3，创建时就指定，一般不能修改
        BTreeNode<T> *_root;        // 根结点的指针
        mutable BTreeNode<T> *_hot; // search()方法最后一次访问（除非树空）的非空结点的指针

        void free_node(BTreeNode<T> *);
        Rank get_height(BTreeNode<T> *) const;
        Rank get_keys_num(BTreeNode<T> *) const;
        BTreeNode<T> *construct_node_from(BTreeNode<T> *);
        void solve_overflow(BTreeNode<T> *);  // 分裂解决由于插入结点而可能导致的上溢
        void solve_underflow(BTreeNode<T> *); // 合并解决由于删除结点而可能导致的下溢
    };
} // DSA

#include "BTree_implementation.h"

#endif // B_TREE_H
