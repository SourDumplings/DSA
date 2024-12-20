/*
 * @Author: SourDumplings
 * @Date: 2023-02-06 16:51:25
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description:
 */

#include "test_shuffle.h"

#include "Algorithms/Shuffle.h"
#include "DSAString/DSAString.h"
#include "Vector/Vector.h"

using namespace DSA;
using namespace std;

bool test_shuffle()
{
    Vector<int> v;
    for (size_t i = 0; i < 100; i++)
    {
        v.push_back(i);
    }
    v.print_info("v");
    Shuffle(v.begin(), v.end());
    v.print_info("v");

    Vector<DSAString> vs({ "DSA", "Hello", "ZTT", "Oh", "YJY", "Y" });
    vs.print_info("vs");
    Shuffle(vs.begin(), vs.end());
    vs.print_info("vs");

    return true;
}
