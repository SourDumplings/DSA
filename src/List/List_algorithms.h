/*
 @Date    : 2018-09-22 23:58:17
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List的一些特有算法
 */

#ifndef LIST_ALGORITHMS_H
#define LIST_ALGORITHMS_H

#include "List.h"


namespace CZ
{
    template <typename T>
    inline void List<T>::merge(const List<T> &l)
    {
        insert(end(), l.begin(), l.end());
    }

    template <typename T>
    void List<T>::merge(List<T> &&l)
    {
        _head->_prev->_next = l._head->_next;
        l._head->_next->_prev = _head->_prev;
        l._head->_next = l._head;

        _head->_prev = l._head->_prev;
        l._head->_prev->_next = _head;
        l._head->_prev = l._head;

        _size += l._size;
        l._size = 0;
    }

    template <typename T>
    inline void List<T>::swap(Iterator pos1, Iterator pos2)
    {
        Swap(*pos1, *pos2);
    }

    template <typename T>
    template <typename Cmp>
    void List<T>::mergeListForSort(ListNode<T> *pHead1, ListNode<T> *pHead2, ListNode<T> *pEnd, const Cmp &cmp)
    {
        if (pHead1 == pHead2->next() || pHead2 == pEnd)
        {
            return;
        }

        ListNode<T> *pNode1 = pHead1->next();
        ListNode<T> *pNode2 = pHead2->next();
        ListNode<T> *pHead = new ListNode<T>(T(), nullptr, nullptr);
        ListNode<T> *pHeadTemp = pHead;
        while (pNode1 != pHead2->next() && pNode2 != pEnd)
        {
            if (cmp(pNode2->data(), pNode1->data()))
            {
                pHeadTemp->_next = pNode2;
                pNode2->_prev = pHeadTemp;
                pNode2 = pNode2->next();
            }
            else
            {
                pHeadTemp->_next = pNode1;
                pNode1->_prev = pHeadTemp;
                pNode1 = pNode1->next();
            }
            pHeadTemp = pHeadTemp->next();
        }
        while (pNode1 != pHead2->next())
        {
            pHeadTemp->_next = pNode1;
            pNode1->_prev = pHeadTemp;
            pNode1 = pNode1->next();
            pHeadTemp = pHeadTemp->next();
        }
        while (pNode2 != pEnd)
        {
            pHeadTemp->_next = pNode2;
            pNode2->_prev = pHeadTemp;
            pNode2 = pNode2->next();
            pHeadTemp = pHeadTemp->next();
        }
        pHeadTemp->_next = pEnd;
        pEnd->_prev = pHeadTemp;
        pHead1->_next = pHead->next();
        pHead->_prev = pHead1;
        delete pHead;
    }

    template <typename T>
    template <typename Cmp>
    void List<T>::listMergeSort1(ListNode<T> *pHead, ListNode<T> *pEnd, typename List<T>::Rank n, const Cmp &cmp)
    {
        if (n < 2)
        {
            return;
        }

        // 找到中点
        ListNode<T> *pRightStart = pHead;
        for (typename List<T>::Rank i = 0; i <= n / 2; ++i)
        {
            pRightStart = pRightStart->next();
        }
        listMergeSort1(pHead, pRightStart, n / 2, cmp);
        ListNode<T> *pRightHead = pRightStart->prev();
        listMergeSort1(pRightHead, pEnd, n - n / 2, cmp);
        mergeListForSort(pHead, pRightHead, pEnd, cmp);
    }

    template <typename T>
    template <typename Cmp>
    void List<T>::listMergeSort2(ListNode<T> *pHead, ListNode<T> *pEnd, typename List<T>::Rank n, const Cmp &cmp)
    {
        if (n < 2)
        {
            return;
        }

        bool isSorted = false;
        for (Rank subL = 1; !isSorted && subL < n; subL *= 2)
        {
            ListNode<T> *pLeftHead = pHead;
            while (pLeftHead->next() != pEnd)
            {
                ListNode<T> *pRightHead = pLeftHead;
                for (Rank i = 0; pRightHead->next() != pEnd && i < subL; i++, pRightHead = pRightHead->next())
                    ;
                ListNode<T> *pRightEnd = pRightHead->next();
                for (Rank i = 0; pRightEnd != pEnd && i < subL; i++, pRightEnd = pRightEnd->next())
                    ;
                mergeListForSort(pLeftHead, pRightHead, pRightEnd, cmp);
                if (pLeftHead == pHead && pRightHead == pEnd)
                {
                    isSorted = true;
                    break;
                }
                pLeftHead = pRightEnd->prev();
            }
        }
    }

    template <typename T>
    template <typename Cmp>
    void List<T>::sort(const Cmp &cmp, const uint32_t version)
    {
        if (this->empty())
        {
            return;
        }
        switch (version)
        {
        case 0:
        {
            // 冒泡排序，对元素值进行操作
            bool isSorted = false;
            uint32_t unSortedNum = _size, checkedNum;
            while (!isSorted)
            {
                isSorted = true;
                checkedNum = 0;
                for (Iterator it = begin(); checkedNum != unSortedNum - 1 && it != end();
                     ++checkedNum)
                {
                    T &thisData = *it;
                    T &nextData = *++it;
                    if (cmp(nextData, thisData))
                    {
                        Swap(thisData, nextData);
                        isSorted = false;
                    }
                }
                --unSortedNum;
            }
            break;
        }
        case 1:
        {
            // 插入排序，对结点指针进行操作
            // 先将除了头结点外的结点摘出，然后一个一个进行插入排序
            ListNode<T> *first = _head->_next;
            _head->_prev->_next = nullptr;
            first->_prev = nullptr;
            _head->_next = _head->_prev = _head;

            ListNode<T> *tempNext = nullptr;
            for (ListNode<T> *p = first; p; p = tempNext)
            {
                ListNode<T> *f = _head;
                while (f->_next != _head && !cmp(p->_data, f->_next->_data))
                    f = f->_next;
                tempNext = p->_next;
                f->insert_as_next(p);
                p->_next->_prev = f->_next = p;
            }
            break;
        }
        case 2:
        {
            // 归并排序 1：自上而下，时间复杂度为 O(nlogn)，空间复杂度为 O(n)，空间开销来自递归栈
            // 参考：https://leetcode-cn.com/problems/sort-list/solution/pai-xu-lian-biao-by-leetcode-solution/
            listMergeSort1(_head, _head, _size, cmp);
            break;
        }
        case 3:
        {
            // 归并排序 2：自下而上，时间复杂度为 O(nlogn)，空间复杂度为 O(1)，没有递归栈，采用迭代实现
            // 参考：https://leetcode-cn.com/problems/sort-list/solution/pai-xu-lian-biao-by-leetcode-solution/
            listMergeSort2(_head, _head, _size, cmp);
            break;
        }
        }
    }

    template <typename T>
    template <typename Cmp>
    void List<T>::unique(bool sorted, const Cmp &cmp)
    {
        if (this->empty())
        {
            return;
        }
        if (sorted)
        {
            for (Iterator firstRepeat = begin(); firstRepeat != end();)
            {
                Iterator lastRepeat = firstRepeat;
                for (; cmp(*lastRepeat, *firstRepeat) && lastRepeat != end(); ++lastRepeat)
                    ;
                firstRepeat = erase(++Iterator(firstRepeat), lastRepeat);
            }
        }
        else
        {
            for (ListNode<T> *last = _head->_next; last != _head; last = last->_next)
            {
                for (ListNode<T> *p = last->_next; p != _head;)
                {
                    if (cmp(p->data(), last->data()))
                    {
                        p = erase(Iterator(p)).get();
                    }
                    else
                    {
                        p = p->_next;
                    }
                }
            }
        }
    }

    template <typename T>
    void List<T>::reverse()
    {
        if (!this->empty())
        {
            // 将除了头结点外的其它结点摘出，
            // 再用头插法把结点一个一个插进去
            ListNode<T> *first = _head->_next, *tempNext = _head->_next->_next;
            first->_prev = nullptr;
            _head->_prev->_next = nullptr;
            _head->_next = _head->_prev = _head;

            for (ListNode<T> *p = first; p; p = tempNext)
            {
                tempNext = p->_next;
                _head->insert_as_next(p);
                _head->_next->_prev = p;
                _head->_next = p;
            }
            _head->_prev = first;
        }
    }

    template <typename T>
    typename List<T>::Iterator List<T>::splice(Iterator pos, List<T> &l)
    {
        if (l.empty())
        {
            return pos;
        }
        _size += l._size;
        l._size = 0;
        ListNode<T> *first = l._head->_next, *last = l._head->_prev;
        l._head->_next = l._head->_prev = l._head;

        first->_prev = pos.get()->_prev;
        first->_prev->_next = first;
        last->_next = pos.get();
        pos.get()->_prev = last;
        return ListIterator<T>(first);
    }
} // CZ

#endif // LIST_ALGORITHMS_H
