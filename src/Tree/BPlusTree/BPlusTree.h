/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 17:40:59
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: B+树模板，不支持关键码重复
 *
 * 模板参数：K关键码类型，V数据类型
 * 对于数据，该B+树不负责管理其生命周期
 *
 * n阶B+树：
 * 叶结点，最多 n - 1 个搜索键的值，最少上取整((n - 1)/2)个。指针最多 n 个，最少上取整((n - 1)/2) + 1个。
 * 内部结点的指针数最多 n 个，最少上取整(n/2)个。搜索键值最多 n - 1 个，最少(上取整(n/2)) - 1 个。
 * 根结点最少的为 1 个搜索键值，2个指针，最多和非根结点一样。
 */

#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include "BPlusTreeNode.h"
#include "../../Map/KVPair.h"

namespace DSA
{
    template <typename K, typename V>
    class BPlusTree : public AbstractBaseEntity
    {
    public:
        using Rank = uint32_t;

        BPlusTree(Rank order_ = 3);
        BPlusTree(const BPlusTree &bt);
        BPlusTree(BPlusTree &&bt) noexcept;
        // bottom-up 地批量建立 B+ 树索引，注意输入的 indexDataV 必须是按照索引排好序的
        BPlusTree(const Vector<KVPair<K, V *>> &indexDataV, Rank order_ = 3);
        ~BPlusTree();

        Rank order() const;
        Rank size() const;
        Rank node_num() const;
        Rank height() const;
        BPlusTreeNode<K, V> *root() const;
        bool empty() const;

        // 查找单个关键码，返回指向数据的指针
        const V *search(const K &key) const;
        V *search(const K &key);
        // 范围查找关键码在闭区间 [minKey, maxKey] 上的所有数据指针
        Vector<const V *> search(const K &minKey, const K &maxKey) const;
        Vector<V *> search(const K &minKey, const K &maxKey);

        void insert(const K &key, V *pData);
        // 删除该关键码及对应的数据指针，对于不存在的关键码什么都不做
        void remove(const K &key);

        void print_info(const char *name = "") const;

        const char *c_str() const override;
        HashRank hash() const override;
        const char *get_entity_name() const override;

    private:
        Rank _size;                 // 存放的关键码总数
        Rank _nodeNum;              // 树中结点的总数
        const Rank _order;          // B树的阶次，至少为3，创建时就指定，一般不能修改
        BPlusTreeNode<K, V> *_root; // 根结点的指针

        void free_node(BPlusTreeNode<K, V> *);
        BPlusTreeNode<K, V> *construct_node_from(BPlusTreeNode<K, V> *);
        // 查找包含或者应该包含关键码 key 的叶结点，为插入而准备
        BPlusTreeNode<K, V> *find_leaf(const K &key) const;
        // 把关键码和指针插入到适当的结点 node 处，不会更新计数信息
        void insert_in_node(BPlusTreeNode<K, V> *node, const K &key, void *p);
        // 将关键码 keyUp 插入 lNode 的父结点并插入合适的孩子指针指向 rNode，用以解决上溢问题
        void insert_in_father(BPlusTreeNode<K, V> *lNode,
                              const K &keyUp,
                              BPlusTreeNode<K, V> *rNode);
        // 将 lNode 作为左侧结点等分，返回分裂后的右侧结点
        BPlusTreeNode<K, V> *split_node(BPlusTreeNode<K, V> *lNode);
        // 从 node 中删除该 index 对应的 key 以及相对应 child
        void remove_entry(BPlusTreeNode<K, V> *node,
                          const typename Vector<K>::Rank &index);
        // 判断是否下溢
        bool is_underflow(BPlusTreeNode<K, V> *node) const;
        // 判断是否上溢
        bool is_overflow(BPlusTreeNode<K, V> *node) const;
        bool is_overflow(typename Vector<void *>::Rank pointerNum) const;

        void print_keys_in_node(BPlusTreeNode<K, V> *node) const;
    };
} // namespace DSA

#include "BPlusTree_implementation.h"

#endif // B_PLUS_TREE_H
