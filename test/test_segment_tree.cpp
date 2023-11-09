/**
    * @projectName DSA
    * @author SourDumplings
    * @version 1.0.0
    * @date 2021/2/25 22:18
*/
#include "test_segment_tree.h"

#include "Tree/BinTree/SegmemtTree.h"
#include "Vector/Vector.h"
#include "CZString/CZString.h"
#include <functional>
#include <cstdio>
#include <iostream>

using namespace std;
using namespace CZ;

bool test_segment_tree()
{
    Vector<int> v({2, 4, 5, 7, 8, 9});
    Vector<CZString> vs({"a", "b", "cd", "hello", "world"});

    // 测试
    SegmentTree<int> T(v);
    cout << "T: " << T << endl;
    cout << "T.hash(): " << T.hash() << endl;
    printf("sumRange[0, 3] = %d\n", T.range_res(0, 3, 0));
    T.update(2, 3);
    cout << "T: " << T << endl;
    cout << "T.hash(): " << T.hash() << endl;
    printf("sumRange[1, 5] = %d\n", T.range_res(1, 5, 0));
    // 测试不同的运算
//    SegmentTree<int, std::multiplies<int>> T1(v);
//    printf("sumRange[0, 3] = %d\n", T1.range_res(0, 3, 1));
//    SegmentTree<CZString> T2(vs);
//    printf("sumRange[1, 3] = %s\n", T2.range_res(1, 3, "").c_str());
    return true;
}