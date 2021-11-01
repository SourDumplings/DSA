/*
 @Date    : 2018-06-11 16:26:11
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树的重构算法，传入的迭代器必须是随机访问迭代器
注意，传入的序列中不能含有重复元素
 */

#ifndef BIN_TREE_RECONSTRUCT_H
#define BIN_TREE_RECONSTRUCT_H

#include "BinTree.h"
#include "../../Iterator/Iterator_traits.h"
#include <cstdio>
#include <stdexcept>
#include <type_traits>

namespace CZ
{
    enum ConstructBinTreeFrom
    {
        PRE_IN,
        IN_PRE,
        POST_IN,
        IN_POST
    };

    namespace BinTreeReconstruct
    {
        template <typename It>
        auto doReconstruct_from_pre_in_traversal(It preB,
            It preE, It inB, It inE)
        -> BinTreeNode<typename std::remove_reference<decltype(*inB)>::type>*
        {
            if (preE == preB)
            {
                return nullptr;
            }

            using node = BinTreeNode<typename std::remove_reference<decltype(*inB)>::type>;
            node *root = new node(*preB);
            if (preB + 1 == preE)
            {
                return root;
            }

            It leftInEnd = inB + 1;
            for (It it = inB; it != inE; ++it)
            {
                if (*it == root->data())
                {
                    leftInEnd = it;
                    break;
                }
            }
            node *lc = doReconstruct_from_pre_in_traversal(preB + 1,
                preB + (leftInEnd - inB) + 1, inB, leftInEnd);
            root->insert_as_left_child(lc);

            node *rc =
            doReconstruct_from_pre_in_traversal(preB + (leftInEnd - inB) + 1, preE,
                leftInEnd + 1, inE);
            root->insert_as_right_child(rc);
            return root;
        }

        template <typename It>
        auto doReconstruct_from_post_in_traversal(It postB,
            It postE, It inB, It inE)
        -> BinTreeNode<typename std::remove_reference<decltype(*inB)>::type>*
        {
            if (postE == postB)
            {
                return nullptr;
            }

            using node = BinTreeNode<typename std::remove_reference<decltype(*inB)>::type>;
            node *root = new node(*(postE - 1));
            if (postB + 1 == postE)
            {
                return root;
            }

            It leftInEnd = inB + 1;
            for (It it = inB; it != inE; ++it)
            {
                if (*it == root->data())
                {
                    leftInEnd = it;
                    break;
                }
            }
            node *lc = doReconstruct_from_post_in_traversal(postB,
                postB + (leftInEnd - inB), inB, leftInEnd);
            root->insert_as_left_child(lc);

            node *rc = doReconstruct_from_post_in_traversal(postB + (leftInEnd - inB),
                postE - 1, leftInEnd + 1, inE);
            root->insert_as_right_child(rc);
            return root;
        }

        template <typename It>
        inline auto doReconstruct_from_in_pre_traversal(It inB,
            It inE, It preB, It preE)
        -> BinTreeNode<typename std::remove_reference<decltype(*inB)>::type>*
        { return doReconstruct_from_pre_in_traversal(preB, preE, inB, inE); }

        template <typename It>
        inline auto doReconstruct_from_in_post_traversal(It inB,
            It inE, It postB, It postE)
        -> BinTreeNode<typename std::remove_reference<decltype(*inB)>::type>*
        { return doReconstruct_from_post_in_traversal(postB, postE, inB, inE); }
    } // BinTreeReconstruct

    namespace TestIterator
    {
        template <typename It, typename T>
        void test_Iterator_for_reconstruct(BinTree<T> &res, It begin1, It end1,
            It begin2, It end2,
            random_iterator_tag, const ConstructBinTreeFrom &seqV)
        {
            if (end2 - begin2 != end1 - begin1)
            {
                printf("Error: seq1's length is %d, seq2's length is %d\n",
                    end1 - begin1, end2 - begin2);
                throw std::exception();
            }
            switch (seqV)
            {
                case PRE_IN:
                {
                    res.root() = BinTreeReconstruct::doReconstruct_from_pre_in_traversal(begin1,
                        end1, begin2, end2);
                    break;
                }
                case POST_IN:
                {
                    res.root() = BinTreeReconstruct::doReconstruct_from_post_in_traversal(begin1,
                        end1, begin2, end2);
                    break;
                }
                case IN_PRE:
                {
                    res.root() = BinTreeReconstruct::doReconstruct_from_in_pre_traversal(begin1,
                        end1, begin2, end2);
                    break;
                }
                case IN_POST:
                {
                    res.root() = BinTreeReconstruct::doReconstruct_from_in_post_traversal(begin1,
                        end1, begin2, end2);
                    break;
                }
            }
            return;
        }

        template <typename It, typename T>
        void test_Iterator_for_reconstruct(BinTree<T> &res, It begin1, It end1,
            It begin2, It end2,
            seq_iterator_tag, const ConstructBinTreeFrom &seqV)
        {
            printf("Error: Iterator is seq_Iterator, should be random_Iterator\n");
            throw std::exception();
            return;
        }

        template <typename It, typename T>
        void test_Iterator_for_reconstruct(BinTree<T> &res, It begin1, It end1,
            It begin2, It end2,
            bi_iterator_tag, const ConstructBinTreeFrom &seqV)
        {
            printf("Error: Iterator is bi_Iterator, should be random_Iterator\n");
            throw std::exception();
            return;
        }
    } // TestIterator



    template <typename T>
    template <typename It>
    BinTree<T> BinTree<T>::reconstruct_from_pre_in_traversal(It preB, It preE,
        It inB, It inE)
    {
        BinTree<T> t;
        TestIterator::test_Iterator_for_reconstruct(t, preB, preE, inB, inE,
            typename Iterator_traits<It>::iterator_category(), PRE_IN);
        t._size = inE - inB;
        return t;
    }

    template <typename T>
    template <typename It>
    BinTree<T> BinTree<T>::reconstruct_from_post_in_traversal(It postB, It postE,
        It inB, It inE)
    {
        BinTree<T> t;
        TestIterator::test_Iterator_for_reconstruct(t, postB, postE, inB, inE,
            typename Iterator_traits<It>::iterator_category(), POST_IN);
        t._size = inE - inB;
        return t;
    }

    template <typename T>
    template <typename It>
    BinTree<T> BinTree<T>::reconstruct_from_in_pre_traversal(It inB, It inE,
        It preB, It preE)
    {
        BinTree<T> t;
        TestIterator::test_Iterator_for_reconstruct(t, inB, inE, preB, preE,
            typename Iterator_traits<It>::iterator_category(), IN_PRE);
        t._size = inE - inB;
        return t;
    }

    template <typename T>
    template <typename It>
    BinTree<T> BinTree<T>::reconstruct_from_in_post_traversal(It inB, It inE,
        It postB, It postE)
    {
        BinTree<T> t;
        TestIterator::test_Iterator_for_reconstruct(t, inB, inE, postB, postE,
            typename Iterator_traits<It>::iterator_category(), IN_POST);
        t._size = inE - inB;
        return t;
    }
} // CZ

#endif // BIN_TREE_RECONSTRUCT_H
