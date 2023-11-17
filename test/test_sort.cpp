/*
 * @Author: SourDumplings
 * @Date: 2023-02-06 19:16:09
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#include "Algorithms/Sort.h"
#include "Algorithms/Stable_sort.h"
#include <algorithm>
#include <cstdlib>

#ifdef _WIN32
#include "Base/WinTime.h"
#elif __linux__
#include <sys/time.h>
#endif

using namespace CZ;
using namespace std;

bool test_sort_correctiness(int *tempV, uint32_t n)
{
    for (uint32_t i = 0; i < n - 1; ++i)
    {
        if (tempV[i + 1] < tempV[i])
        {
            return false;
        }
    }
    return true;
}

long test_sort_prof(const Vector<int> &v, typename SortAccessories::UnStableSortMethod sortMethod, int version)
{
    typename Vector<int>::Rank n = v.size();
    int *tempV = new int[n];
    for (uint32_t i = 0; i < n; i++)
    {
        tempV[i] = v[i];
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);

    long start = tv.tv_sec * 1000000 + tv.tv_usec;

    Sort(tempV, tempV + n, sortMethod, version);

    gettimeofday(&tv, NULL);
    long stop = tv.tv_sec * 1000000 + tv.tv_usec;

    ASSERT_DEBUG(test_sort_correctiness(tempV, n), "Wrong sort!");
    delete[] tempV;
    return stop - start;
}

long test_sort_prof(const Vector<int> &v, typename SortAccessories::StableSortMethod sortMethod, int version)
{
    typename Vector<int>::Rank n = v.size();
    int *tempV = new int[n];
    for (uint32_t i = 0; i < n; i++)
    {
        tempV[i] = v[i];
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);

    long start = tv.tv_sec * 1000000 + tv.tv_usec;

    Sort(tempV, tempV + n, sortMethod, version);

    gettimeofday(&tv, NULL);
    long stop = tv.tv_sec * 1000000 + tv.tv_usec;

    ASSERT_DEBUG(test_sort_correctiness(tempV, n), "Wrong sort!");
    delete [] tempV;
    return stop - start;
}

long test_sort_prof(const Vector<int> &v)
{
    typename Vector<int>::Rank n = v.size();
    int *tempV = new int[n];
    for (uint32_t i = 0; i < n; i++)
    {
        tempV[i] = v[i];
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);

    long start = tv.tv_sec * 1000000 + tv.tv_usec;

    sort(tempV, tempV + n);

    gettimeofday(&tv, NULL);
    long stop = tv.tv_sec * 1000000 + tv.tv_usec;

    ASSERT_DEBUG(test_sort_correctiness(tempV, n), "Wrong sort!");
    delete [] tempV;
    return stop - start;
}

void test_perf()
{
    srand(time(NULL));
    constexpr int size = 50000;
    constexpr int test = 10;
    for (int i = 0; i < test; i++)
    {
        printf("Test round %d....\n", i);
        Vector<int> v;

        for (int j = 0; j < size; j++)
        {
            v.push_back(rand());
        }

        long costTimeInMicroS = 0;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::SELECT_SORT, 0);
        cout << "SELECT_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::QUICK_SORT, 0);
        cout << "QUICK_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::QUICK_SORT, 1);
        cout << "QUICK_SORT version 1 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::HEAP_SORT, 0);
        cout << "HEAP_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::SHELL_SORT, 0);
        cout << "SHELL_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::SHELL_SORT, 1);
        cout << "SHELL_SORT version 1 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::SHELL_SORT, 2);
        cout << "SHELL_SORT version 2 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::SHELL_SORT, 3);
        cout << "SHELL_SORT version 3 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::BUBBLE_SORT, 0);
        cout << "BUBBLE_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::BUBBLE_SORT, 1);
        cout << "BUBBLE_SORT version 1 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::INSERTION_SORT, 0);
        cout << "INSERTION_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v, SortAccessories::MERGE_SORT, 0);
        cout << "MERGE_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        costTimeInMicroS = test_sort_prof(v);
        cout << "STL sort cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        putchar('\n');
    }

/* 性能测试结果：size = 50000
Test round 0....
SELECT_SORT version 0 cost: 5912872 micro seconds this round.
QUICK_SORT version 0 cost: 11446 micro seconds this round.
QUICK_SORT version 1 cost: 9405 micro seconds this round.
HEAP_SORT version 0 cost: 61461 micro seconds this round.
SHELL_SORT version 0 cost: 20068 micro seconds this round.
SHELL_SORT version 1 cost: 38767 micro seconds this round.
SHELL_SORT version 2 cost: 21973 micro seconds this round.
SHELL_SORT version 3 cost: 44809 micro seconds this round.
BUBBLE_SORT version 0 cost: 15707566 micro seconds this round.
BUBBLE_SORT version 1 cost: 15644963 micro seconds this round.
INSERTION_SORT version 0 cost: 4439391 micro seconds this round.
MERGE_SORT version 0 cost: 99180 micro seconds this round.
STL sort cost: 10985 micro seconds this round.

Test round 1....
SELECT_SORT version 0 cost: 5968004 micro seconds this round.
QUICK_SORT version 0 cost: 11327 micro seconds this round.
QUICK_SORT version 1 cost: 9375 micro seconds this round.
HEAP_SORT version 0 cost: 65236 micro seconds this round.
SHELL_SORT version 0 cost: 20353 micro seconds this round.
SHELL_SORT version 1 cost: 49792 micro seconds this round.
SHELL_SORT version 2 cost: 21199 micro seconds this round.
SHELL_SORT version 3 cost: 56549 micro seconds this round.
BUBBLE_SORT version 0 cost: 15683550 micro seconds this round.
BUBBLE_SORT version 1 cost: 15613427 micro seconds this round.
INSERTION_SORT version 0 cost: 4406102 micro seconds this round.
MERGE_SORT version 0 cost: 76575 micro seconds this round.
STL sort cost: 10982 micro seconds this round.

Test round 2....
SELECT_SORT version 0 cost: 5941317 micro seconds this round.
QUICK_SORT version 0 cost: 11391 micro seconds this round.
QUICK_SORT version 1 cost: 9836 micro seconds this round.
HEAP_SORT version 0 cost: 61995 micro seconds this round.
SHELL_SORT version 0 cost: 19991 micro seconds this round.
SHELL_SORT version 1 cost: 43693 micro seconds this round.
SHELL_SORT version 2 cost: 21546 micro seconds this round.
SHELL_SORT version 3 cost: 49724 micro seconds this round.
BUBBLE_SORT version 0 cost: 15670225 micro seconds this round.
BUBBLE_SORT version 1 cost: 15612466 micro seconds this round.
INSERTION_SORT version 0 cost: 4420282 micro seconds this round.
MERGE_SORT version 0 cost: 76729 micro seconds this round.
STL sort cost: 11099 micro seconds this round.

Test round 3....
SELECT_SORT version 0 cost: 5937896 micro seconds this round.
QUICK_SORT version 0 cost: 11527 micro seconds this round.
QUICK_SORT version 1 cost: 9372 micro seconds this round.
HEAP_SORT version 0 cost: 61241 micro seconds this round.
SHELL_SORT version 0 cost: 20388 micro seconds this round.
SHELL_SORT version 1 cost: 42564 micro seconds this round.
SHELL_SORT version 2 cost: 21547 micro seconds this round.
SHELL_SORT version 3 cost: 51301 micro seconds this round.
BUBBLE_SORT version 0 cost: 15721465 micro seconds this round.
BUBBLE_SORT version 1 cost: 15733526 micro seconds this round.
INSERTION_SORT version 0 cost: 4423854 micro seconds this round.
MERGE_SORT version 0 cost: 76894 micro seconds this round.
STL sort cost: 10949 micro seconds this round.

Test round 4....
SELECT_SORT version 0 cost: 5795579 micro seconds this round.
QUICK_SORT version 0 cost: 11385 micro seconds this round.
QUICK_SORT version 1 cost: 9357 micro seconds this round.
HEAP_SORT version 0 cost: 61248 micro seconds this round.
SHELL_SORT version 0 cost: 20814 micro seconds this round.
SHELL_SORT version 1 cost: 40641 micro seconds this round.
SHELL_SORT version 2 cost: 21601 micro seconds this round.
SHELL_SORT version 3 cost: 49003 micro seconds this round.
BUBBLE_SORT version 0 cost: 15709160 micro seconds this round.
BUBBLE_SORT version 1 cost: 15648245 micro seconds this round.
INSERTION_SORT version 0 cost: 4481194 micro seconds this round.
MERGE_SORT version 0 cost: 76927 micro seconds this round.
STL sort cost: 10830 micro seconds this round.

Test round 5....
SELECT_SORT version 0 cost: 5786410 micro seconds this round.
QUICK_SORT version 0 cost: 11413 micro seconds this round.
QUICK_SORT version 1 cost: 9423 micro seconds this round.
HEAP_SORT version 0 cost: 60978 micro seconds this round.
SHELL_SORT version 0 cost: 20052 micro seconds this round.
SHELL_SORT version 1 cost: 62577 micro seconds this round.
SHELL_SORT version 2 cost: 21894 micro seconds this round.
SHELL_SORT version 3 cost: 71655 micro seconds this round.
BUBBLE_SORT version 0 cost: 15692834 micro seconds this round.
BUBBLE_SORT version 1 cost: 15619481 micro seconds this round.
INSERTION_SORT version 0 cost: 4431515 micro seconds this round.
MERGE_SORT version 0 cost: 77060 micro seconds this round.
STL sort cost: 10960 micro seconds this round.

Test round 6....
SELECT_SORT version 0 cost: 6011089 micro seconds this round.
QUICK_SORT version 0 cost: 11596 micro seconds this round.
QUICK_SORT version 1 cost: 9438 micro seconds this round.
HEAP_SORT version 0 cost: 65036 micro seconds this round.
SHELL_SORT version 0 cost: 20400 micro seconds this round.
SHELL_SORT version 1 cost: 49084 micro seconds this round.
SHELL_SORT version 2 cost: 22119 micro seconds this round.
SHELL_SORT version 3 cost: 56637 micro seconds this round.
BUBBLE_SORT version 0 cost: 15711645 micro seconds this round.
BUBBLE_SORT version 1 cost: 15638717 micro seconds this round.
INSERTION_SORT version 0 cost: 4406699 micro seconds this round.
MERGE_SORT version 0 cost: 80165 micro seconds this round.
STL sort cost: 10891 micro seconds this round.

Test round 7....
SELECT_SORT version 0 cost: 5940398 micro seconds this round.
QUICK_SORT version 0 cost: 11396 micro seconds this round.
QUICK_SORT version 1 cost: 9393 micro seconds this round.
HEAP_SORT version 0 cost: 61288 micro seconds this round.
SHELL_SORT version 0 cost: 20289 micro seconds this round.
SHELL_SORT version 1 cost: 47351 micro seconds this round.
SHELL_SORT version 2 cost: 21458 micro seconds this round.
SHELL_SORT version 3 cost: 53225 micro seconds this round.
BUBBLE_SORT version 0 cost: 15676604 micro seconds this round.
BUBBLE_SORT version 1 cost: 15637835 micro seconds this round.
INSERTION_SORT version 0 cost: 4423689 micro seconds this round.
MERGE_SORT version 0 cost: 76924 micro seconds this round.
STL sort cost: 11192 micro seconds this round.

Test round 8....
SELECT_SORT version 0 cost: 5844638 micro seconds this round.
QUICK_SORT version 0 cost: 11473 micro seconds this round.
QUICK_SORT version 1 cost: 9491 micro seconds this round.
HEAP_SORT version 0 cost: 61389 micro seconds this round.
SHELL_SORT version 0 cost: 20149 micro seconds this round.
SHELL_SORT version 1 cost: 55740 micro seconds this round.
SHELL_SORT version 2 cost: 21973 micro seconds this round.
SHELL_SORT version 3 cost: 67072 micro seconds this round.
BUBBLE_SORT version 0 cost: 15671692 micro seconds this round.
BUBBLE_SORT version 1 cost: 15600830 micro seconds this round.
INSERTION_SORT version 0 cost: 4438391 micro seconds this round.
MERGE_SORT version 0 cost: 80382 micro seconds this round.
STL sort cost: 10719 micro seconds this round.

Test round 9....
SELECT_SORT version 0 cost: 5864252 micro seconds this round.
QUICK_SORT version 0 cost: 11443 micro seconds this round.
QUICK_SORT version 1 cost: 9372 micro seconds this round.
HEAP_SORT version 0 cost: 61465 micro seconds this round.
SHELL_SORT version 0 cost: 20260 micro seconds this round.
SHELL_SORT version 1 cost: 41911 micro seconds this round.
SHELL_SORT version 2 cost: 21310 micro seconds this round.
SHELL_SORT version 3 cost: 48694 micro seconds this round.
BUBBLE_SORT version 0 cost: 15700544 micro seconds this round.
BUBBLE_SORT version 1 cost: 15599162 micro seconds this round.
INSERTION_SORT version 0 cost: 4421284 micro seconds this round.
MERGE_SORT version 0 cost: 77148 micro seconds this round.
STL sort cost: 11070 micro seconds this round.
 */
}

bool test_sort()
{
    // 测试排序算法
    // 基本逻辑测试
/*     Vector<int> v1{1, 8, 5, 4, 3, 0};
    Vector<string> vs1{"jsds", "ass", "abab", "aaaa", "ab", "bsds", "ghsl"}, vs2(vs1);
    v1.print_info("v1");
    Sort(v1.begin(), v1.end(), SortAccessories::MERGE_SORT);
    Sort(v1.begin(), v1.end());
    Sort(v1.begin(), v1.end(), SortAccessories::QUICK_SORT, 1);
    Sort(v1.begin(), v1.end(), SortAccessories::HEAP_SORT);
    Sort(v1.begin(), v1.end(), SortAccessories::SELECT_SORT);
    Sort(v1.begin(), v1.end(), SortAccessories::INSERTION_SORT);
    Sort(v1.begin(), v1.end(), SortAccessories::SHELL_SORT);
    Sort(v1.begin(), v1.end(), SortAccessories::SHELL_SORT, 1);
    Sort(v1.begin(), v1.end(), SortAccessories::SHELL_SORT, 2);
    Sort(v1.begin(), v1.end(), SortAccessories::SHELL_SORT, 3);
    v1.print_info("v1");
    vs1.print_info("vs1");
    Sort(vs1.begin(), vs1.end(), SortAccessories::QUICK_SORT);
    Sort(vs1.begin(), vs1.end(), SortAccessories::QUICK_SORT, 1);
    Sort(vs1.begin(), vs1.end(), SortAccessories::HEAP_SORT, 0);
    Stable_sort(vs1.begin(), vs1.end(), SortAccessories::BUBBLE_SORT, 1);
    // Stable_sort(vs1.begin(), vs1.end(), SortAccessories::SELECT_SORT, 1);
    Stable_sort(vs1.begin(), vs1.end(), SortAccessories::MERGE_SORT);
    Stable_sort(vs1.begin(), vs1.end(), SortAccessories::INSERTION_SORT);
    Sort(vs1.begin(), vs1.end(), SortAccessories::SHELL_SORT);
    vs1.print_info("vs1");
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    { return s1.length() < s2.length(); }, SortAccessories::SELECT_SORT, 0);
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    { return s1.length() < s2.length(); }, SortAccessories::INSERTION_SORT, 0);
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        { return s1.length() < s2.length(); }, SortAccessories::MERGE_SORT, 0);
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    { return s1.length() < s2.length(); }, SortAccessories::BUBBLE_SORT, 0);
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    { return s1.length() < s2.length(); });
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    { return s1.length() < s2.length(); }, SortAccessories::QUICK_SORT, 1);
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        { return s1.length() < s2.length(); }, SortAccessories::HEAP_SORT);
    Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    { return s1.length() < s2.length(); }, SortAccessories::SHELL_SORT, 2);
    vs2.print_info("vs2");

    Vector<int> vDup(100);
    vDup.print_info("vDup");
    Sort(vDup.begin(), vDup.end()); */


    // 性能测试
    test_perf();
    return true;
}
