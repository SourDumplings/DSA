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
#include "../../Algorithms/Swap.h"

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

        if (is_overflow(leaf))
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
void BPlusTree<K, V>::insert_in_father(BPlusTreeNode<K, V> *lNode,
                                       const K &keyUp,
                                       BPlusTreeNode<K, V> *rNode)
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
        if (is_overflow(f))
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
BPlusTreeNode<K, V> *
BPlusTree<K, V>::split_node(BPlusTreeNode<K, V> *lNode)
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
    // 找到包含该关键码的叶结点
    BPlusTreeNode<K, V> *leaf = find_leaf(key);
    if (leaf != nullptr)
    {
        typename Vector<K>::Rank index = 0;
        Vector<K> &keysOfLeaf = leaf->_keys;
        for (; index != keysOfLeaf.size() && key != keysOfLeaf[index]; ++index)
        {}
        remove_entry(leaf, index);
        --_size;
    }
}

template<typename K, typename V>
void BPlusTree<K, V>::remove_entry(BPlusTreeNode<K, V> *node,
                                   const typename Vector<K>::Rank &index)
{
    node->print_info("node is going to remove_entry");
    printf("index = %d\n", index);

    node->_keys.erase(node->_keys.begin() + index);
    if (node->_isLeaf)
    {
        // 如果 node 是叶结点，删掉其左侧指针
        node->_children.erase(node->_children.begin() + index);
    }
    else
    {
        // 如果 node 是内部结点，删掉其右侧指针
        node->_children.erase(node->_children.begin() + index + 1);
    }

    if (node == _root && node->_children.size() == 1)
    {
        // 如果 node 是根结点并且其只有一个儿子
//        BPlusTreeNode<K, V> *temp = node->_children.front();
//        delete _root;
//        --_nodeNum;
//        _root = temp;
//        _root->_father = nullptr;
    }
    else if (is_underflow(node))
    {
        // 下溢
        BPlusTreeNode<K, V> *father = node->_father;
        Vector<void *> &brothers = father->_children;
        typename Vector<void *>::Rank childIndex = 0;
        for (; childIndex < brothers.size() && node != brothers[childIndex];
               ++childIndex)
        {}

        typename Vector<K>::Rank indexOfKeysBetweenTwo = 0;
        BPlusTreeNode<K, V>
            *brother = reinterpret_cast<BPlusTreeNode<K, V> *>(brothers[1]);
        if (childIndex != 0)
        {
            indexOfKeysBetweenTwo = childIndex - 1;
            brother =
                reinterpret_cast<BPlusTreeNode<K, V> *>(brothers[childIndex
                    - 1]);
        }

        if (is_overflow(brother->_keys.size() + node->_keys.size()))
        {
            // 如果 brother 和 node 不能合并
        }
        else
        {
            // 如果 brother 和 node 可以合并
            if (childIndex == 0)
            {
                // node 是哥哥，就交换二者，始终保证 brother 指向哥哥，node指向弟弟
                Swap(brother, node);
            }

            if (node->_isLeaf)
            {
                // 如果兄弟俩是叶结点，合并两个结点
                brother->_keys.insert(brother->_keys.end(),
                                      node->_keys.begin(),
                                      node->_keys.end());
                // 去掉哥哥指向弟弟的指针，然后将弟弟的儿子都给哥哥
                brother->_children.back() = node->_children.front();
                brother->_children.insert(brother->_children.end(),
                                          node->_children.begin() + 1,
                                          node->_children.end());
            }
            else
            {
                // 如果兄弟俩是内部结点

            }

            remove_entry(father, indexOfKeysBetweenTwo);
            --_nodeNum;
            delete node;
        }

    }

}
} // namespace CZ

#endif // B_PLUS_TREE_MODIFICATIONS_H
