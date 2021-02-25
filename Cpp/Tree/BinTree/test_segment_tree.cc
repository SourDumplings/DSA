/**
    * @projectName DSA
    * @author SourDumplings
    * @version 1.0.0
    * @date 2021/2/25 22:18
*/

#include "SegmemtTree.h"
#include "../../Vector/Vector.h"
#include "../../CZString/CZString.h"
#include <functional>
#include <cstdio>

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Vector<int> v({2, 4, 5, 7, 8, 9});
    Vector<CZString> vs({"a", "b", "cd", "hello", "world"});

    // 测试列表实现实现
//    SegmentTree<int> T(v);
//    printf("sumRange[0, 3] = %d\n", T.range_res(0, 3, 0));
//    T.update(2, 3);
//    printf("sumRange[1, 5] = %d\n", T.range_res(1, 5, 0));
    // 测试不同的运算
    SegmentTree<int, std::multiplies<int>> T1(v);
    printf("sumRange[0, 3] = %d\n", T1.range_res(0, 3, 1));
    SegmentTree<CZString> T2(vs);
    printf("sumRange[1, 3] = %s\n", T2.range_res(1, 3, "").c_str());
    return 0;
}