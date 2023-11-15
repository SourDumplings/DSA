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
SELECT_SORT version 0 cost: 5155541 micro seconds this round.
QUICK_SORT version 0 cost: 9601 micro seconds this round.
QUICK_SORT version 1 cost: 7351 micro seconds this round.
HEAP_SORT version 0 cost: 68428 micro seconds this round.
SHELL_SORT version 0 cost: 19103 micro seconds this round.
SHELL_SORT version 1 cost: 49493 micro seconds this round.
SHELL_SORT version 2 cost: 43798 micro seconds this round.
SHELL_SORT version 3 cost: 84200 micro seconds this round.
BUBBLE_SORT version 0 cost: 12590071 micro seconds this round.
BUBBLE_SORT version 1 cost: 12399178 micro seconds this round.
INSERTION_SORT version 0 cost: 4334836 micro seconds this round.
MERGE_SORT version 0 cost: 100846 micro seconds this round.
STL sort cost: 9540 micro seconds this round.

Test round 1....
SELECT_SORT version 0 cost: 5180657 micro seconds this round.
QUICK_SORT version 0 cost: 9251 micro seconds this round.
QUICK_SORT version 1 cost: 7171 micro seconds this round.
HEAP_SORT version 0 cost: 67666 micro seconds this round.
SHELL_SORT version 0 cost: 60296 micro seconds this round.
SHELL_SORT version 1 cost: 90434 micro seconds this round.
SHELL_SORT version 2 cost: 86363 micro seconds this round.
SHELL_SORT version 3 cost: 136278 micro seconds this round.
BUBBLE_SORT version 0 cost: 12486156 micro seconds this round.
BUBBLE_SORT version 1 cost: 12384310 micro seconds this round.
INSERTION_SORT version 0 cost: 4246911 micro seconds this round.
MERGE_SORT version 0 cost: 85000 micro seconds this round.
STL sort cost: 9631 micro seconds this round.

Test round 2....
SELECT_SORT version 0 cost: 5141025 micro seconds this round.
QUICK_SORT version 0 cost: 9846 micro seconds this round.
QUICK_SORT version 1 cost: 7516 micro seconds this round.
HEAP_SORT version 0 cost: 67468 micro seconds this round.
SHELL_SORT version 0 cost: 100630 micro seconds this round.
SHELL_SORT version 1 cost: 135619 micro seconds this round.
SHELL_SORT version 2 cost: 124326 micro seconds this round.
SHELL_SORT version 3 cost: 172303 micro seconds this round.
BUBBLE_SORT version 0 cost: 12516003 micro seconds this round.
BUBBLE_SORT version 1 cost: 12392927 micro seconds this round.
INSERTION_SORT version 0 cost: 4265004 micro seconds this round.
MERGE_SORT version 0 cost: 83781 micro seconds this round.
STL sort cost: 9669 micro seconds this round.

Test round 3....
SELECT_SORT version 0 cost: 5106287 micro seconds this round.
QUICK_SORT version 0 cost: 10004 micro seconds this round.
QUICK_SORT version 1 cost: 7702 micro seconds this round.
HEAP_SORT version 0 cost: 67409 micro seconds this round.
SHELL_SORT version 0 cost: 141333 micro seconds this round.
SHELL_SORT version 1 cost: 170676 micro seconds this round.
SHELL_SORT version 2 cost: 165970 micro seconds this round.
SHELL_SORT version 3 cost: 215896 micro seconds this round.
BUBBLE_SORT version 0 cost: 12579585 micro seconds this round.
BUBBLE_SORT version 1 cost: 12423263 micro seconds this round.
INSERTION_SORT version 0 cost: 4249633 micro seconds this round.
MERGE_SORT version 0 cost: 83371 micro seconds this round.
STL sort cost: 9491 micro seconds this round.

Test round 4....
SELECT_SORT version 0 cost: 5119366 micro seconds this round.
QUICK_SORT version 0 cost: 9949 micro seconds this round.
QUICK_SORT version 1 cost: 7673 micro seconds this round.
HEAP_SORT version 0 cost: 67352 micro seconds this round.
SHELL_SORT version 0 cost: 180395 micro seconds this round.
SHELL_SORT version 1 cost: 207284 micro seconds this round.
SHELL_SORT version 2 cost: 205636 micro seconds this round.
SHELL_SORT version 3 cost: 243404 micro seconds this round.
BUBBLE_SORT version 0 cost: 12542919 micro seconds this round.
BUBBLE_SORT version 1 cost: 12416061 micro seconds this round.
INSERTION_SORT version 0 cost: 4242783 micro seconds this round.
MERGE_SORT version 0 cost: 84928 micro seconds this round.
STL sort cost: 9659 micro seconds this round.

Test round 5....
SELECT_SORT version 0 cost: 5157709 micro seconds this round.
QUICK_SORT version 0 cost: 10005 micro seconds this round.
QUICK_SORT version 1 cost: 7548 micro seconds this round.
HEAP_SORT version 0 cost: 67962 micro seconds this round.
SHELL_SORT version 0 cost: 223004 micro seconds this round.
SHELL_SORT version 1 cost: 255341 micro seconds this round.
SHELL_SORT version 2 cost: 247772 micro seconds this round.
SHELL_SORT version 3 cost: 297844 micro seconds this round.
BUBBLE_SORT version 0 cost: 12608494 micro seconds this round.
BUBBLE_SORT version 1 cost: 12383435 micro seconds this round.
INSERTION_SORT version 0 cost: 4225296 micro seconds this round.
MERGE_SORT version 0 cost: 84741 micro seconds this round.
STL sort cost: 9543 micro seconds this round.

Test round 6....
SELECT_SORT version 0 cost: 5205112 micro seconds this round.
QUICK_SORT version 0 cost: 10380 micro seconds this round.
QUICK_SORT version 1 cost: 8098 micro seconds this round.
HEAP_SORT version 0 cost: 67349 micro seconds this round.
SHELL_SORT version 0 cost: 262144 micro seconds this round.
SHELL_SORT version 1 cost: 302919 micro seconds this round.
SHELL_SORT version 2 cost: 286893 micro seconds this round.
SHELL_SORT version 3 cost: 338705 micro seconds this round.
BUBBLE_SORT version 0 cost: 12580468 micro seconds this round.
BUBBLE_SORT version 1 cost: 12436443 micro seconds this round.
INSERTION_SORT version 0 cost: 4226049 micro seconds this round.
MERGE_SORT version 0 cost: 84436 micro seconds this round.
STL sort cost: 9592 micro seconds this round.

Test round 7....
SELECT_SORT version 0 cost: 5147999 micro seconds this round.
QUICK_SORT version 0 cost: 10391 micro seconds this round.
QUICK_SORT version 1 cost: 7905 micro seconds this round.
HEAP_SORT version 0 cost: 67656 micro seconds this round.
SHELL_SORT version 0 cost: 303496 micro seconds this round.
SHELL_SORT version 1 cost: 338273 micro seconds this round.
SHELL_SORT version 2 cost: 327548 micro seconds this round.
SHELL_SORT version 3 cost: 371731 micro seconds this round.
BUBBLE_SORT version 0 cost: 12532449 micro seconds this round.
BUBBLE_SORT version 1 cost: 12403303 micro seconds this round.
INSERTION_SORT version 0 cost: 4278759 micro seconds this round.
MERGE_SORT version 0 cost: 84200 micro seconds this round.
STL sort cost: 9489 micro seconds this round.

Test round 8....
SELECT_SORT version 0 cost: 5128815 micro seconds this round.
QUICK_SORT version 0 cost: 11515 micro seconds this round.
QUICK_SORT version 1 cost: 7048 micro seconds this round.
HEAP_SORT version 0 cost: 68632 micro seconds this round.
SHELL_SORT version 0 cost: 343549 micro seconds this round.
SHELL_SORT version 1 cost: 376151 micro seconds this round.
SHELL_SORT version 2 cost: 367591 micro seconds this round.
SHELL_SORT version 3 cost: 408317 micro seconds this round.
BUBBLE_SORT version 0 cost: 12526816 micro seconds this round.
BUBBLE_SORT version 1 cost: 12370939 micro seconds this round.
INSERTION_SORT version 0 cost: 4227152 micro seconds this round.
MERGE_SORT version 0 cost: 85070 micro seconds this round.
STL sort cost: 9468 micro seconds this round.

Test round 9....
SELECT_SORT version 0 cost: 5111587 micro seconds this round.
QUICK_SORT version 0 cost: 10095 micro seconds this round.
QUICK_SORT version 1 cost: 7830 micro seconds this round.
HEAP_SORT version 0 cost: 67392 micro seconds this round.
SHELL_SORT version 0 cost: 382695 micro seconds this round.
SHELL_SORT version 1 cost: 436242 micro seconds this round.
SHELL_SORT version 2 cost: 407563 micro seconds this round.
SHELL_SORT version 3 cost: 475887 micro seconds this round.
BUBBLE_SORT version 0 cost: 12511795 micro seconds this round.
BUBBLE_SORT version 1 cost: 12392264 micro seconds this round.
INSERTION_SORT version 0 cost: 4225016 micro seconds this round.
MERGE_SORT version 0 cost: 84094 micro seconds this round.
STL sort cost: 9685 micro seconds this round.
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
