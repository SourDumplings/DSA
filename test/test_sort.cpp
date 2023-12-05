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
}
/* 性能测试结果：size = 50000
--------------------------------------------------------
Operating System: Linux
CPU Architecture: x86-64, 64-bit
Compiler: GCC, Version: 8.3.1
Cpp version: 201103
------------------ Test on DEBUG mode ------------------
--------------------- Test start -----------------------
--------------------------------------------------------
--------------------------------------------------------
Test round 0....
SELECT_SORT version 0 cost: 5607773 micro seconds this round.
QUICK_SORT version 0 cost: 11592 micro seconds this round.
QUICK_SORT version 1 cost: 9611 micro seconds this round.
HEAP_SORT version 0 cost: 65213 micro seconds this round.
SHELL_SORT version 0 cost: 20863 micro seconds this round.
SHELL_SORT version 1 cost: 42073 micro seconds this round.
SHELL_SORT version 2 cost: 23599 micro seconds this round.
SHELL_SORT version 3 cost: 53954 micro seconds this round.
BUBBLE_SORT version 0 cost: 15549470 micro seconds this round.
BUBBLE_SORT version 1 cost: 15573627 micro seconds this round.
INSERTION_SORT version 0 cost: 4439478 micro seconds this round.
MERGE_SORT version 0 cost: 100799 micro seconds this round.
STL sort cost: 10931 micro seconds this round.

Test round 1....
SELECT_SORT version 0 cost: 5521117 micro seconds this round.
QUICK_SORT version 0 cost: 11418 micro seconds this round.
QUICK_SORT version 1 cost: 9438 micro seconds this round.
HEAP_SORT version 0 cost: 61260 micro seconds this round.
SHELL_SORT version 0 cost: 21538 micro seconds this round.
SHELL_SORT version 1 cost: 49235 micro seconds this round.
SHELL_SORT version 2 cost: 22147 micro seconds this round.
SHELL_SORT version 3 cost: 60123 micro seconds this round.
BUBBLE_SORT version 0 cost: 15682166 micro seconds this round.
BUBBLE_SORT version 1 cost: 16289712 micro seconds this round.
INSERTION_SORT version 0 cost: 4546920 micro seconds this round.
MERGE_SORT version 0 cost: 77383 micro seconds this round.
STL sort cost: 11147 micro seconds this round.

Test round 2....
SELECT_SORT version 0 cost: 5650626 micro seconds this round.
QUICK_SORT version 0 cost: 11606 micro seconds this round.
QUICK_SORT version 1 cost: 9547 micro seconds this round.
HEAP_SORT version 0 cost: 60972 micro seconds this round.
SHELL_SORT version 0 cost: 22339 micro seconds this round.
SHELL_SORT version 1 cost: 52609 micro seconds this round.
SHELL_SORT version 2 cost: 22460 micro seconds this round.
SHELL_SORT version 3 cost: 59792 micro seconds this round.
BUBBLE_SORT version 0 cost: 15730943 micro seconds this round.
BUBBLE_SORT version 1 cost: 16068796 micro seconds this round.
INSERTION_SORT version 0 cost: 4397633 micro seconds this round.
MERGE_SORT version 0 cost: 77230 micro seconds this round.
STL sort cost: 10916 micro seconds this round.

Test round 3....
SELECT_SORT version 0 cost: 5555457 micro seconds this round.
QUICK_SORT version 0 cost: 11440 micro seconds this round.
QUICK_SORT version 1 cost: 9416 micro seconds this round.
HEAP_SORT version 0 cost: 61218 micro seconds this round.
SHELL_SORT version 0 cost: 20711 micro seconds this round.
SHELL_SORT version 1 cost: 43174 micro seconds this round.
SHELL_SORT version 2 cost: 22215 micro seconds this round.
SHELL_SORT version 3 cost: 49430 micro seconds this round.
BUBBLE_SORT version 0 cost: 15498565 micro seconds this round.
BUBBLE_SORT version 1 cost: 15556105 micro seconds this round.
INSERTION_SORT version 0 cost: 4382712 micro seconds this round.
MERGE_SORT version 0 cost: 77093 micro seconds this round.
STL sort cost: 10912 micro seconds this round.

Test round 4....
SELECT_SORT version 0 cost: 5582937 micro seconds this round.
QUICK_SORT version 0 cost: 11703 micro seconds this round.
QUICK_SORT version 1 cost: 9799 micro seconds this round.
HEAP_SORT version 0 cost: 61153 micro seconds this round.
SHELL_SORT version 0 cost: 20798 micro seconds this round.
SHELL_SORT version 1 cost: 46924 micro seconds this round.
SHELL_SORT version 2 cost: 22204 micro seconds this round.
SHELL_SORT version 3 cost: 55801 micro seconds this round.
BUBBLE_SORT version 0 cost: 15525091 micro seconds this round.
BUBBLE_SORT version 1 cost: 15556011 micro seconds this round.
INSERTION_SORT version 0 cost: 4400756 micro seconds this round.
MERGE_SORT version 0 cost: 78110 micro seconds this round.
STL sort cost: 11143 micro seconds this round.

Test round 5....
SELECT_SORT version 0 cost: 5539801 micro seconds this round.
QUICK_SORT version 0 cost: 11565 micro seconds this round.
QUICK_SORT version 1 cost: 9442 micro seconds this round.
HEAP_SORT version 0 cost: 60907 micro seconds this round.
SHELL_SORT version 0 cost: 21093 micro seconds this round.
SHELL_SORT version 1 cost: 55625 micro seconds this round.
SHELL_SORT version 2 cost: 22730 micro seconds this round.
SHELL_SORT version 3 cost: 62972 micro seconds this round.
BUBBLE_SORT version 0 cost: 15555932 micro seconds this round.
BUBBLE_SORT version 1 cost: 15554000 micro seconds this round.
INSERTION_SORT version 0 cost: 4416313 micro seconds this round.
MERGE_SORT version 0 cost: 77200 micro seconds this round.
STL sort cost: 11054 micro seconds this round.

Test round 6....
SELECT_SORT version 0 cost: 5529659 micro seconds this round.
QUICK_SORT version 0 cost: 11342 micro seconds this round.
QUICK_SORT version 1 cost: 9704 micro seconds this round.
HEAP_SORT version 0 cost: 62907 micro seconds this round.
SHELL_SORT version 0 cost: 21066 micro seconds this round.
SHELL_SORT version 1 cost: 51384 micro seconds this round.
SHELL_SORT version 2 cost: 22246 micro seconds this round.
SHELL_SORT version 3 cost: 59314 micro seconds this round.
BUBBLE_SORT version 0 cost: 15514244 micro seconds this round.
BUBBLE_SORT version 1 cost: 15561022 micro seconds this round.
INSERTION_SORT version 0 cost: 4438783 micro seconds this round.
MERGE_SORT version 0 cost: 77343 micro seconds this round.
STL sort cost: 10791 micro seconds this round.

Test round 7....
SELECT_SORT version 0 cost: 5554734 micro seconds this round.
QUICK_SORT version 0 cost: 11483 micro seconds this round.
QUICK_SORT version 1 cost: 9547 micro seconds this round.
HEAP_SORT version 0 cost: 60802 micro seconds this round.
SHELL_SORT version 0 cost: 21259 micro seconds this round.
SHELL_SORT version 1 cost: 46246 micro seconds this round.
SHELL_SORT version 2 cost: 22448 micro seconds this round.
SHELL_SORT version 3 cost: 51436 micro seconds this round.
BUBBLE_SORT version 0 cost: 15523590 micro seconds this round.
BUBBLE_SORT version 1 cost: 15582829 micro seconds this round.
INSERTION_SORT version 0 cost: 4399413 micro seconds this round.
MERGE_SORT version 0 cost: 77878 micro seconds this round.
STL sort cost: 10956 micro seconds this round.

Test round 8....
SELECT_SORT version 0 cost: 5554975 micro seconds this round.
QUICK_SORT version 0 cost: 11425 micro seconds this round.
QUICK_SORT version 1 cost: 9567 micro seconds this round.
HEAP_SORT version 0 cost: 61442 micro seconds this round.
SHELL_SORT version 0 cost: 20584 micro seconds this round.
SHELL_SORT version 1 cost: 46534 micro seconds this round.
SHELL_SORT version 2 cost: 22704 micro seconds this round.
SHELL_SORT version 3 cost: 52400 micro seconds this round.
BUBBLE_SORT version 0 cost: 15563456 micro seconds this round.
BUBBLE_SORT version 1 cost: 15591374 micro seconds this round.
INSERTION_SORT version 0 cost: 4383815 micro seconds this round.
MERGE_SORT version 0 cost: 76653 micro seconds this round.
STL sort cost: 11038 micro seconds this round.

Test round 9....
SELECT_SORT version 0 cost: 5546823 micro seconds this round.
QUICK_SORT version 0 cost: 11392 micro seconds this round.
QUICK_SORT version 1 cost: 9435 micro seconds this round.
HEAP_SORT version 0 cost: 64503 micro seconds this round.
SHELL_SORT version 0 cost: 20685 micro seconds this round.
SHELL_SORT version 1 cost: 52519 micro seconds this round.
SHELL_SORT version 2 cost: 22237 micro seconds this round.
SHELL_SORT version 3 cost: 62384 micro seconds this round.
BUBBLE_SORT version 0 cost: 15493279 micro seconds this round.
BUBBLE_SORT version 1 cost: 15536639 micro seconds this round.
INSERTION_SORT version 0 cost: 4405306 micro seconds this round.
MERGE_SORT version 0 cost: 81357 micro seconds this round.
STL sort cost: 11113 micro seconds this round.

--------------------------------------------------------
--------------------------------------------------------
--------------------- Test finish ----------------------
--------------------------------------------------------


--------------------------------------------------------
Operating System: Linux
CPU Architecture: x86-64, 64-bit
Compiler: GCC, Version: 8.3.1
Cpp version: 201103
------------------ Test on RELEASE mode ------------------
--------------------- Test start -----------------------
--------------------------------------------------------
--------------------------------------------------------
Test round 0....
SELECT_SORT version 0 cost: 784786 micro seconds this round.
QUICK_SORT version 0 cost: 3568 micro seconds this round.
QUICK_SORT version 1 cost: 3463 micro seconds this round.
HEAP_SORT version 0 cost: 4929 micro seconds this round.
SHELL_SORT version 0 cost: 4718 micro seconds this round.
SHELL_SORT version 1 cost: 7584 micro seconds this round.
SHELL_SORT version 2 cost: 6116 micro seconds this round.
SHELL_SORT version 3 cost: 7035 micro seconds this round.
BUBBLE_SORT version 0 cost: 4142510 micro seconds this round.
BUBBLE_SORT version 1 cost: 4257990 micro seconds this round.
INSERTION_SORT version 0 cost: 394569 micro seconds this round.
MERGE_SORT version 0 cost: 5383 micro seconds this round.
STL sort cost: 3022 micro seconds this round.

Test round 1....
SELECT_SORT version 0 cost: 795723 micro seconds this round.
QUICK_SORT version 0 cost: 4389 micro seconds this round.
QUICK_SORT version 1 cost: 3523 micro seconds this round.
HEAP_SORT version 0 cost: 6419 micro seconds this round.
SHELL_SORT version 0 cost: 5030 micro seconds this round.
SHELL_SORT version 1 cost: 7827 micro seconds this round.
SHELL_SORT version 2 cost: 6104 micro seconds this round.
SHELL_SORT version 3 cost: 6455 micro seconds this round.
BUBBLE_SORT version 0 cost: 4041121 micro seconds this round.
BUBBLE_SORT version 1 cost: 4282899 micro seconds this round.
INSERTION_SORT version 0 cost: 388788 micro seconds this round.
MERGE_SORT version 0 cost: 5272 micro seconds this round.
STL sort cost: 3010 micro seconds this round.

Test round 2....
SELECT_SORT version 0 cost: 779729 micro seconds this round.
QUICK_SORT version 0 cost: 3515 micro seconds this round.
QUICK_SORT version 1 cost: 3628 micro seconds this round.
HEAP_SORT version 0 cost: 4752 micro seconds this round.
SHELL_SORT version 0 cost: 3814 micro seconds this round.
SHELL_SORT version 1 cost: 7233 micro seconds this round.
SHELL_SORT version 2 cost: 6080 micro seconds this round.
SHELL_SORT version 3 cost: 6667 micro seconds this round.
BUBBLE_SORT version 0 cost: 4156087 micro seconds this round.
BUBBLE_SORT version 1 cost: 4190511 micro seconds this round.
INSERTION_SORT version 0 cost: 403403 micro seconds this round.
MERGE_SORT version 0 cost: 5249 micro seconds this round.
STL sort cost: 3033 micro seconds this round.

Test round 3....
SELECT_SORT version 0 cost: 795991 micro seconds this round.
QUICK_SORT version 0 cost: 3601 micro seconds this round.
QUICK_SORT version 1 cost: 3479 micro seconds this round.
HEAP_SORT version 0 cost: 4863 micro seconds this round.
SHELL_SORT version 0 cost: 3804 micro seconds this round.
SHELL_SORT version 1 cost: 7060 micro seconds this round.
SHELL_SORT version 2 cost: 6079 micro seconds this round.
SHELL_SORT version 3 cost: 6825 micro seconds this round.
BUBBLE_SORT version 0 cost: 4061462 micro seconds this round.
BUBBLE_SORT version 1 cost: 4297490 micro seconds this round.
INSERTION_SORT version 0 cost: 406133 micro seconds this round.
MERGE_SORT version 0 cost: 5909 micro seconds this round.
STL sort cost: 3021 micro seconds this round.

Test round 4....
SELECT_SORT version 0 cost: 800934 micro seconds this round.
QUICK_SORT version 0 cost: 3604 micro seconds this round.
QUICK_SORT version 1 cost: 3490 micro seconds this round.
HEAP_SORT version 0 cost: 4767 micro seconds this round.
SHELL_SORT version 0 cost: 3847 micro seconds this round.
SHELL_SORT version 1 cost: 6897 micro seconds this round.
SHELL_SORT version 2 cost: 6120 micro seconds this round.
SHELL_SORT version 3 cost: 6460 micro seconds this round.
BUBBLE_SORT version 0 cost: 4045142 micro seconds this round.
BUBBLE_SORT version 1 cost: 4189651 micro seconds this round.
INSERTION_SORT version 0 cost: 386983 micro seconds this round.
MERGE_SORT version 0 cost: 5310 micro seconds this round.
STL sort cost: 3097 micro seconds this round.

Test round 5....
SELECT_SORT version 0 cost: 803592 micro seconds this round.
QUICK_SORT version 0 cost: 3551 micro seconds this round.
QUICK_SORT version 1 cost: 3618 micro seconds this round.
HEAP_SORT version 0 cost: 4774 micro seconds this round.
SHELL_SORT version 0 cost: 3854 micro seconds this round.
SHELL_SORT version 1 cost: 8843 micro seconds this round.
SHELL_SORT version 2 cost: 6138 micro seconds this round.
SHELL_SORT version 3 cost: 8620 micro seconds this round.
BUBBLE_SORT version 0 cost: 4014582 micro seconds this round.
BUBBLE_SORT version 1 cost: 4202196 micro seconds this round.
INSERTION_SORT version 0 cost: 388272 micro seconds this round.
MERGE_SORT version 0 cost: 5254 micro seconds this round.
STL sort cost: 3078 micro seconds this round.

Test round 6....
SELECT_SORT version 0 cost: 784038 micro seconds this round.
QUICK_SORT version 0 cost: 3694 micro seconds this round.
QUICK_SORT version 1 cost: 3589 micro seconds this round.
HEAP_SORT version 0 cost: 4777 micro seconds this round.
SHELL_SORT version 0 cost: 3854 micro seconds this round.
SHELL_SORT version 1 cost: 7234 micro seconds this round.
SHELL_SORT version 2 cost: 6155 micro seconds this round.
SHELL_SORT version 3 cost: 6968 micro seconds this round.
BUBBLE_SORT version 0 cost: 4064111 micro seconds this round.
BUBBLE_SORT version 1 cost: 4282164 micro seconds this round.
INSERTION_SORT version 0 cost: 385367 micro seconds this round.
MERGE_SORT version 0 cost: 5286 micro seconds this round.
STL sort cost: 3044 micro seconds this round.

Test round 7....
SELECT_SORT version 0 cost: 847913 micro seconds this round.
QUICK_SORT version 0 cost: 3519 micro seconds this round.
QUICK_SORT version 1 cost: 3603 micro seconds this round.
HEAP_SORT version 0 cost: 4796 micro seconds this round.
SHELL_SORT version 0 cost: 3832 micro seconds this round.
SHELL_SORT version 1 cost: 8145 micro seconds this round.
SHELL_SORT version 2 cost: 6117 micro seconds this round.
SHELL_SORT version 3 cost: 7659 micro seconds this round.
BUBBLE_SORT version 0 cost: 4062567 micro seconds this round.
BUBBLE_SORT version 1 cost: 4251648 micro seconds this round.
INSERTION_SORT version 0 cost: 409126 micro seconds this round.
MERGE_SORT version 0 cost: 5290 micro seconds this round.
STL sort cost: 3054 micro seconds this round.

Test round 8....
SELECT_SORT version 0 cost: 818287 micro seconds this round.
QUICK_SORT version 0 cost: 3618 micro seconds this round.
QUICK_SORT version 1 cost: 3664 micro seconds this round.
HEAP_SORT version 0 cost: 5413 micro seconds this round.
SHELL_SORT version 0 cost: 4349 micro seconds this round.
SHELL_SORT version 1 cost: 7726 micro seconds this round.
SHELL_SORT version 2 cost: 6212 micro seconds this round.
SHELL_SORT version 3 cost: 7914 micro seconds this round.
BUBBLE_SORT version 0 cost: 4118700 micro seconds this round.
BUBBLE_SORT version 1 cost: 4263326 micro seconds this round.
INSERTION_SORT version 0 cost: 461033 micro seconds this round.
MERGE_SORT version 0 cost: 6523 micro seconds this round.
STL sort cost: 2949 micro seconds this round.

Test round 9....
SELECT_SORT version 0 cost: 774024 micro seconds this round.
QUICK_SORT version 0 cost: 3551 micro seconds this round.
QUICK_SORT version 1 cost: 3607 micro seconds this round.
HEAP_SORT version 0 cost: 4744 micro seconds this round.
SHELL_SORT version 0 cost: 3775 micro seconds this round.
SHELL_SORT version 1 cost: 7752 micro seconds this round.
SHELL_SORT version 2 cost: 6196 micro seconds this round.
SHELL_SORT version 3 cost: 7500 micro seconds this round.
BUBBLE_SORT version 0 cost: 4062644 micro seconds this round.
BUBBLE_SORT version 1 cost: 4213067 micro seconds this round.
INSERTION_SORT version 0 cost: 388830 micro seconds this round.
MERGE_SORT version 0 cost: 5386 micro seconds this round.
STL sort cost: 3025 micro seconds this round.

--------------------------------------------------------
--------------------------------------------------------
--------------------- Test finish ----------------------
--------------------------------------------------------
 */

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
