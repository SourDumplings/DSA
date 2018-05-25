/*
 @Date    : 2018-05-25 15:05:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树结点类模板
 */

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "..\Vector\Vector.h"
#include "..\Smart_pointer\Shared_ptr.h"

namespace CZ
{
    template <typename T>
    class TreeNode
    {
    public:
        TreeNode(const T &data_ = T(), unsigned height_ = 0, Shared_ptr<TreeNode<T>> father_ = nullptr);
        virtual ~TreeNode();

        Shared_ptr<TreeNode<T>> father();
        const Shared_ptr<TreeNode<T>> father() const;

        const Shared_ptr<TreeNode<T>> oldest_child() const;
        Shared_ptr<TreeNode<T>> oldest_child();

        const T& data() const;
        T& data();

        virtual bool is_leaf() const;

        const unsigned& height() const;
        unsigned& height();
    protected:
        Vector<Shared_ptr<TreeNode<T>>> _children;
    private:
        Shared_ptr<TreeNode<T>> _father = nullptr;
        T _data;
        unsigned _height = 0;
    };
} // CZ

#include "TreeNode_implementation.h"

#endif // TREE_NODE_H
