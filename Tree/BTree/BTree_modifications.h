/*
 @Date    : 2018-07-09 21:49:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树的动态操作，插入和删除只能针对值
 */

#ifndef B_TREE_MODIFICATIONS_H
#define B_TREE_MODIFICATIONS_H

#include "BTree.h"
#include "../../Algorithms/Search.h"

namespace CZ
{
    template <typename T>
    void BTree<T>::solve_overflow(BTreeNode<T> *target)
    {
        if (!target || target->_children.size() <= _order)
        {
            // 当前结点并未上溢
            return;
        }
        else
        {
            Rank s = _order >> 1; // 轴点
            //（此时应有_order == target->_keys.size() == target->_children.size() - 1）
            BTreeNode<T> *right = new BTreeNode<T>(); // 注意新结点right已经有一个空孩子
            for (Rank i = 0; i < _order - s - 1; ++i)
            {
                // 右侧的_order - s - 1个结点及关键码分裂为右侧结点right
                right->_children.push_back(*target->_children.erase(target->_children.begin()+s+1));
                right->_keys.push_back(*target->_keys.erase(target->_keys.begin()+s+1));
            }
            right->_children.push_back(target->_children.erase(s + 1)); // 移动最靠右的那个孩子
            for (auto &c : right->_children)
            {
                c->_father = right;
            }

            BTreeNode<T> *f = target->_father;
            if (!f)
            {
                // 若是根节点则创造一个新的根结点
                f = new BTreeNode<T>();
                f->_children[0] = target;
                target->_father = f;
            }

            typename Vector<T>::Rank r =
                search(f->_keys.begin(), f->keys.end(), (right->_keys)[0], BINARY_SEARCH, 2) -
                    f->_keys.begin();
            f->_keys.insert(f->_keys.begin() + r, (target->_keys)[s]); // 轴点关键码上升
            f->_children.insert(f->_children.begin() + r + 1, right);
            right->_father = f;
            return solve_overflow(f); // 如有必要则继续分裂
        }
    }

    template <typename T>
    bool BTree<T>::insert(const T &data)
    {
        // 先查找，如果目标键值存在，则失败
        BTreeNode<T> *v = search(data);
        if (!v)
        {
            typename Vector<T>::iterator pos =
                search(_hot->_keys.begin(), _hot->keys.end(), data, BINARY_SEARCH, 2);
            _hot->_keys.insert(pos+1, data);
            _hot->_children.insert(pos+2, nullptr);
            ++_size;
            // 如有必要，需做分裂
            solve_overflow(_hot);
            return true;
        }
        return false;
    }

    template <typename T>
    void BTree<T>::solve_underflow(BTreeNode<T> *target)
    {
        // 刚发生下溢的结点刚好包含上取整(_order/2)-2，分支数(_order/2)-1
        if (!target || (_order + 1) / 2 <= target->_children.size())
        {
            // 结点并未下溢或者空结点
            return;
        }

        BTreeNode<T> *f = target->_father;

        if (!f)
        {
            // 根结点没有孩子的下限，但若是没有了关键码，且有唯一的非空孩子，则该结点应该被销毁
            // 树的高度降低一层
            if (target->_keys.empty() && target->_children[0])
            {
                _root = target->_children[0];
                _root->_father = nullptr;
                delete target;
                target = nullptr;
            }
            return;
        }

        // 确定target是第几个孩子，第r+1个
        typename Vector<T>::Rank r = 0;
        while (f->_children[r] != target) { ++r; }

        if (0 < r)
        {
            // 情况1，向左兄弟借结点
            // 若target不是f的第一个孩子，左兄弟必然存在
            BTreeNode<T> *l = f->_children[r-1];
            if ((_order + 1) / 2 < l->_children.size())
            {
                // 左兄弟足够胖，即借出一个结点后也不会下溢
                target->_key.insert(target->_key.begin(), (f->_keys)[r-1]);
                f->keys[r-1] = l->_keys.back(); l->_keys.pop_back();
                target->_children.insert(target->_children.begin(), l->_children.back());
                l->_children.pop_back();
                if (target->_children[0])
                {
                    target->_children[0]->_father = target;
                }
                return;
            }
        }

        if (r < f._children.size() - 1)
        {
            // 情况2，向右兄弟借结点
            // 若target不是f的倒数第一个孩子，右兄弟必然存在
            BTreeNode<T> *r = f->_children[r+1];
            if ((_order + 1) / 2 < r->_children.size())
            {
                // 右兄弟足够胖，即借出一个结点后也不会下溢
                target->_key.push_back((f->_keys)[r]);
                f->keys[r] = *(r->_keys.erase(r->_keys.begin()));
                target->_children.push_back(*(r->_children.erase(r->_children.begin())));
                if (target->_children.back())
                {
                    target->_children.back()->_father = target;
                }
                return;
            }
        }

        // 情况3，左右兄弟要么为空，要么太瘦，则需要合并
        if (0 < r)
        {
            // 与左兄弟合并
            // f的r-1号关键码转入左兄弟，target不再是r号孩子
            BTreeNode<T> l = f->_children[r-1];
            l->_keys.push_back(*(f->_keys.erase(f->_keys.begin()+r-1)));
            f->_children.erase(f->_children.begin()+r);
            // target的最左孩子过继给l作为最右孩子
            l->_children.push_back(*(target->_children.erase(target->_children.begin())));
            if (l->_children.back())
            {
                l->_children.back()->_father = l;
            }
            while (!target->_keys.empty())
            {
                // target中的剩余关键码和孩子都转入l中
                l->_keys.push_back(*(target->_keys.erase(target->_keys.begin())));
                l->_children.push_back(*(target->_children.erase(target->_children.begin())));
                if (l->_children.back())
                {
                    l->_children.back()->_father = l;
                }
            }
            delete target; target = nullptr;
        }
        else
        {
            // 与右兄弟合并
            BTreeNode<T> r = f->_children[r+1];
            r->_keys.insert(r->_keys.begin(), *(f->_keys.erase(f->_keys.begin()+r)));
            f->_children.erase(f->_children.begin()+r);
            // target的最右孩子过继给r作为最左孩子
            r->_children.insert(r->_children.begin(), target->_children.back());
            target->_children.pop_back();
            if (r->_children.front())
            {
                r->_children.front()->_father = r;
            }
            while (!target->_keys.empty())
            {
                // target中的剩余关键码和孩子都转入r中
                r->_keys.insert(r->_keys.begin(), target._keys.back()); target._keys.pop_back();
                r->_children.insert(r->_children.begin(), target._children.back());
                target._children.pop_back();
                if (r->_children.front())
                {
                    r->_children.front()->_father = r;
                }
            }
            delete target; target = nullptr;
        }
        return solve_underflow(f);
    }

    template <typename T>
    bool BTree<T>::remove(const T &data)
    {
        BTreeNode<T> *v = search(data);
        if (!v)
        {
            // 必须能找到才能删除
            return false;
        }

        typename Vector<T>::Rank r =
            search(v->_keys.begin(), v->keys.end(), data, BINARY_SEARCH, 2);
        if (v->_children[0])
        {
            // 如果v并非叶结点，则data的后继一定在叶结点中
            BTreeNode<T> *succ = v->_children[r+1];
            while (succ->_children[0])
            {
                succ = succ->_children[0];
            }
            // 将data与其后继交换位置
            v->_keys[r] = succ->_keys[0];
            v = succ;
            r = 0; // 至此v一定位于最底层且第r个关键码就是待删除者
        }
        // 执行删除
        v->_keys.erase(v->_keys.begin() + r);
        v->_children.erase(v->_children.begin() + r);
        --_size;
        // 如有必要，执行旋转或合并
        solve_underflow(v);
        return true;
    }
} // CZ

#endif // B_TREE_MODIFICATIONS_H

