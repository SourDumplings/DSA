/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 17:40:59
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树模板，允许关键码重复
 * 
 * 模板参数：K 关键码类型，V 数据类型
 * 对于数据，该B+树不负责管理其生命周期
 */

#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include "BPlusTreeNode.h"

namespace CZ
{
template<typename K, typename V>
class BPlusTree
{
public:
    using Rank = unsigned;

    BPlusTree(Rank order_ = 3);
    BPlusTree(const BPlusTree &bt);
    BPlusTree(BPlusTree &&bt);
    ~BPlusTree();

    Rank order() const;
    Rank size() const;
    Rank node_num() const;
    Rank height() const;
    BPlusTreeNode<K, V> *root() const;
    bool empty() const;

    void insert(const K &key, V *pData);
    void remove(const K &key);

    void print_info(const char *name = "") const;


private:
    Rank _size;                        // 存放的关键码总数
    Rank _nodeNum;                     // 树中结点的总数
    const Rank _order;                 // B树的阶次，至少为3，创建时就指定，一般不能修改
    BPlusTreeNode<K, V> *_root;        // 根结点的指针
    mutable BPlusTreeNode<K, V> *_hot; // search()方法最后一次访问（除非树空）的非空结点的指针

    void free_node(BPlusTreeNode<K, V> *);
    BPlusTreeNode<K, V> *construct_node_from(BPlusTreeNode<K, V> *);
    // 查找包含或者应该包含关键码 key 的叶结点
    BPlusTreeNode<K, V> *find_leaf(const K &key) const;
    // 把关键码和指针插入到适当的结点 node 处，不会更新计数信息
    void insert_in_node(BPlusTreeNode<K, V> *node, const K &key, void *p);
    // 将关键码 keyUp 插入 lNode 的父结点并插入合适的孩子指针指向 rNode，用以解决上溢问题
    void insert_in_father(BPlusTreeNode<K, V> *lNode,
                          const K &keyUp,
                          BPlusTreeNode<K, V> *rNode);
    // 将 lNode 作为左侧结点等分，返回分裂后的右侧结点
    BPlusTreeNode<K, V> *split_node(BPlusTreeNode<K, V> *lNode);

    void print_keys_in_node(BPlusTreeNode<K, V> *node) const;
};
} // namespace CZ

#include "BPlusTree_implementation.h"

#endif // B_PLUS_TREE_H
