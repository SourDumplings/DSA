//
// Created by CHANG Zheng on 2020/3/2.

// 全排列，用的是回溯算法
//

#ifndef DSA_PERMUTATE_H
#define DSA_PERMUTATE_H

#include "../Vector/Vector.h"
#include "../Bitmap/Bitmap.h"

namespace DSA
{
namespace PermutateMethod
{
template<typename T>
void
backtrack(const Vector<T> &elems, typename Vector<T>::Rank i, bool visited[],
          Vector<T> &thisList, Vector<Vector<T>> &res)
{
    visited[i] = true;
    thisList.push_back(elems[i]);

    typename Vector<T>::Rank l = elems.size();

    if (thisList.size() == l)
    {
        res.push_back(Vector<T>(thisList));
    }
    else
    {
        for (typename Vector<T>::Rank j = 0; j < l; ++j)
        {
            if (!visited[j])
            {
                backtrack(elems, j, visited, thisList, res);
            }
        }
    }

    visited[i] = false;
    thisList.pop_back();
}
}

template<typename T>
Vector<Vector<T>> Permutate(Vector<T> elems)
{
    Vector <Vector<T>> res;
    Vector <T> thisList;
    typename Vector<T>::Rank l = elems.size();
    bool *visited = new bool[l];
    for (typename Vector<T>::Rank j = 0; j < l; ++j)
    {
        visited[j] = false;
    }

    for (typename Vector<T>::Rank i = 0; i < l; ++i)
    {
        PermutateMethod::backtrack(elems, i, visited, thisList, res);
    }
    delete[] visited;

    return std::move(res);
}
} // DSA

#endif //DSA_PERMUTATE_H
