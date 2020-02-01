/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 18:42:47
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树的动态操作
 */

#ifndef B_PLUS_TREE_MODIFICATIONS_H
#define B_PLUS_TREE_MODIFICATIONS_H

#include "BPlusTree.h"
#include "../../Algorithms/Search.h"

namespace CZ
{

template<typename K, typename V>
void BPlusTree<K, V>::insert(const K &key, V *pData)
{
    if (empty())
    {
        _root = new BPlusTreeNode<K, V>(key, nullptr, true, pData);
        ++_nodeNum;
    }
    else
    {
        // 找到应该包含关键码 key 的叶结点
        BPlusTreeNode<K, V> *leaf = find_leaf(key);
        insert_in_node(leaf, key, pData);

        if (_order == leaf->_keys.size())
        {
            // 上溢
            auto rNode = split_node(leaf);
            // 父亲结点插入关键码
            insert_in_father(leaf, rNode->_keys.front(), rNode);
        }
    }
    _size += 1;
}

template<typename K, typename V>
void BPlusTree<K, V>::insert_in_node(CZ::BPlusTreeNode<K, V> *node,
                                     const K &key,
                                     void *p)
{
    Vector<K> &keys = node->_keys;
    Vector<void *> &children = node->_children;

    typename Vector<K>::Rank keysNum = keys.size();
    typename Vector<K>::Rank i = 0;
    for (; i < keysNum; ++i)
    {
        if (key < keys[i])
        {
            break;
        }
    }
    keys.insert(keys.begin() + i, key);
    if (node->_isLeaf)
    {
        // 如果是叶结点，就把 key 左侧的指针赋值为 p
        children.insert(children.begin() + i, p);
    }
    else
    {
        // 如果是非叶结点，就把 key 右侧的指针赋值为 p
        children.insert(children.begin() + i + 1, p);
    }
}

template<typename K, typename V>
void BPlusTree<K, V>::insert_in_father(BPlusTreeNode <K, V> *lNode,
                                       const K &keyUp,
                                       BPlusTreeNode <K, V> *rNode)
{
    if (lNode == _root)
    {
        // 遇到 root 则升高
        _root = new BPlusTreeNode<K, V>(keyUp);
        _root->_children.front() = lNode;
        _root->_children.back() = rNode;
        rNode->_father = lNode->_father = _root;
        ++_nodeNum;
    }
    else
    {
        BPlusTreeNode<K, V> *f = lNode->_father;
        insert_in_node(f, keyUp, rNode);
        rNode->_father = f;
        if (f->_keys.size() == _order)
        {
            // 上溢
            auto r = split_node(f);
            const K &key = f->_keys.back();
            f->_keys.pop_back();
            // 父亲结点插入关键码
            insert_in_father(f, key, r);
        }
    }

}

template<typename K, typename V>
BPlusTreeNode <K, V> *
BPlusTree<K, V>::split_node(BPlusTreeNode <K, V> *lNode)
{
    auto rNode = new BPlusTreeNode<K, V>();
    Vector<K> &lKeys = lNode->_keys;
    Vector<K> &rKeys = rNode->_keys;
    Vector<void *> &lChildren = lNode->_children;
    Vector<void *> &rChildren = rNode->_children;

    // 分裂关键码和指针向量
    // 对于非叶结点，将本该上移的关键码暂时放在左侧结点的末尾
    typename BPlusTreeNode<K, V>::Rank leftKeyNum = (lKeys.size() + 1) / 2;
    rKeys.insert(rKeys.end(), lKeys.begin() + leftKeyNum, lKeys.end());
    lKeys.erase(lKeys.begin() + leftKeyNum, lKeys.end());
    rChildren.insert(rChildren.end(),
                     lChildren.begin() + leftKeyNum,
                     lChildren.end());
    lChildren.erase(lChildren.begin() + leftKeyNum,
                    lChildren.end());

    if (lNode->_isLeaf)
    {
        rNode->_isLeaf = true;
        // 叶结点分裂
        lChildren.insert(lChildren.end(), rNode);
    }
    else
    {
        // 对于非叶结点，右侧结点的孩子结点需要更新父结点的指针
        for (void *c : rChildren)
        {
            reinterpret_cast<BPlusTreeNode<K, V> *>(c)->_father = rNode;
        }
    }
    ++_nodeNum;
    return rNode;
}

template<typename K, typename V>
void BPlusTree<K, V>::remove(const K &key)
{
}
} // namespace CZ

#endif // B_PLUS_TREE_MODIFICATIONS_H
