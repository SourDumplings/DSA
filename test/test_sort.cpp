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

--------------------------------------------------------
Operating System: Windows
CPU Architecture: x86-64, 64-bit
Compiler: MSVC, Version: 1936
Cpp version: 199711
------------------ Test on DEBUG mode ------------------
--------------------- Test start -----------------------
--------------------------------------------------------
--------------------------------------------------------
Test round 0....
SELECT_SORT version 0 cost: 14694556 micro seconds this round.
QUICK_SORT version 0 cost: 11273 micro seconds this round.
QUICK_SORT version 1 cost: 9649 micro seconds this round.
HEAP_SORT version 0 cost: 70793 micro seconds this round.
SHELL_SORT version 0 cost: 22612 micro seconds this round.
SHELL_SORT version 1 cost: 44724 micro seconds this round.
SHELL_SORT version 2 cost: 23311 micro seconds this round.
SHELL_SORT version 3 cost: 53662 micro seconds this round.
BUBBLE_SORT version 0 cost: 38148482 micro seconds this round.
BUBBLE_SORT version 1 cost: 38351208 micro seconds this round.
INSERTION_SORT version 0 cost: 11572925 micro seconds this round.
MERGE_SORT version 0 cost: 263904 micro seconds this round.
STL sort cost: 19894 micro seconds this round.

Test round 1....
SELECT_SORT version 0 cost: 15799973 micro seconds this round.
QUICK_SORT version 0 cost: 11665 micro seconds this round.
QUICK_SORT version 1 cost: 10260 micro seconds this round.
HEAP_SORT version 0 cost: 74444 micro seconds this round.
SHELL_SORT version 0 cost: 22958 micro seconds this round.
SHELL_SORT version 1 cost: 49546 micro seconds this round.
SHELL_SORT version 2 cost: 24579 micro seconds this round.
SHELL_SORT version 3 cost: 61829 micro seconds this round.
BUBBLE_SORT version 0 cost: 39392208 micro seconds this round.
BUBBLE_SORT version 1 cost: 38163535 micro seconds this round.
INSERTION_SORT version 0 cost: 10144923 micro seconds this round.
MERGE_SORT version 0 cost: 221311 micro seconds this round.
STL sort cost: 19684 micro seconds this round.

Test round 2....
SELECT_SORT version 0 cost: 14277097 micro seconds this round.
QUICK_SORT version 0 cost: 10912 micro seconds this round.
QUICK_SORT version 1 cost: 11838 micro seconds this round.
HEAP_SORT version 0 cost: 1078961 micro seconds this round.
SHELL_SORT version 0 cost: 22567 micro seconds this round.
SHELL_SORT version 1 cost: 52605 micro seconds this round.
SHELL_SORT version 2 cost: 24535 micro seconds this round.
SHELL_SORT version 3 cost: 64264 micro seconds this round.
BUBBLE_SORT version 0 cost: 38117050 micro seconds this round.
BUBBLE_SORT version 1 cost: 38158686 micro seconds this round.
INSERTION_SORT version 0 cost: 10219586 micro seconds this round.
MERGE_SORT version 0 cost: 222760 micro seconds this round.
STL sort cost: 20704 micro seconds this round.

Test round 3....
SELECT_SORT version 0 cost: 15118344 micro seconds this round.
QUICK_SORT version 0 cost: 11054 micro seconds this round.
QUICK_SORT version 1 cost: 9512 micro seconds this round.
HEAP_SORT version 0 cost: 70411 micro seconds this round.
SHELL_SORT version 0 cost: 22166 micro seconds this round.
SHELL_SORT version 1 cost: 68205 micro seconds this round.
SHELL_SORT version 2 cost: 23398 micro seconds this round.
SHELL_SORT version 3 cost: 80663 micro seconds this round.
BUBBLE_SORT version 0 cost: 38002918 micro seconds this round.
BUBBLE_SORT version 1 cost: 38079371 micro seconds this round.
INSERTION_SORT version 0 cost: 10129101 micro seconds this round.
MERGE_SORT version 0 cost: 228128 micro seconds this round.
STL sort cost: 20035 micro seconds this round.

Test round 4....
SELECT_SORT version 0 cost: 15241161 micro seconds this round.
QUICK_SORT version 0 cost: 11197 micro seconds this round.
QUICK_SORT version 1 cost: 9283 micro seconds this round.
HEAP_SORT version 0 cost: 76081 micro seconds this round.
SHELL_SORT version 0 cost: 21820 micro seconds this round.
SHELL_SORT version 1 cost: 57257 micro seconds this round.
SHELL_SORT version 2 cost: 22994 micro seconds this round.
SHELL_SORT version 3 cost: 67272 micro seconds this round.
BUBBLE_SORT version 0 cost: 38212723 micro seconds this round.
BUBBLE_SORT version 1 cost: 38305489 micro seconds this round.
INSERTION_SORT version 0 cost: 11215662 micro seconds this round.
MERGE_SORT version 0 cost: 223639 micro seconds this round.
STL sort cost: 20550 micro seconds this round.

Test round 5....
SELECT_SORT version 0 cost: 14237218 micro seconds this round.
QUICK_SORT version 0 cost: 11077 micro seconds this round.
QUICK_SORT version 1 cost: 9796 micro seconds this round.
HEAP_SORT version 0 cost: 70538 micro seconds this round.
SHELL_SORT version 0 cost: 22262 micro seconds this round.
SHELL_SORT version 1 cost: 51592 micro seconds this round.
SHELL_SORT version 2 cost: 22820 micro seconds this round.
SHELL_SORT version 3 cost: 67421 micro seconds this round.
BUBBLE_SORT version 0 cost: 38155565 micro seconds this round.
BUBBLE_SORT version 1 cost: 39236826 micro seconds this round.
INSERTION_SORT version 0 cost: 10126963 micro seconds this round.
MERGE_SORT version 0 cost: 223103 micro seconds this round.
STL sort cost: 20694 micro seconds this round.

Test round 6....
SELECT_SORT version 0 cost: 14135142 micro seconds this round.
QUICK_SORT version 0 cost: 11276 micro seconds this round.
QUICK_SORT version 1 cost: 9591 micro seconds this round.
HEAP_SORT version 0 cost: 70478 micro seconds this round.
SHELL_SORT version 0 cost: 22787 micro seconds this round.
SHELL_SORT version 1 cost: 51867 micro seconds this round.
SHELL_SORT version 2 cost: 22910 micro seconds this round.
SHELL_SORT version 3 cost: 61556 micro seconds this round.
BUBBLE_SORT version 0 cost: 39227780 micro seconds this round.
BUBBLE_SORT version 1 cost: 39785568 micro seconds this round.
INSERTION_SORT version 0 cost: 10711527 micro seconds this round.
MERGE_SORT version 0 cost: 224246 micro seconds this round.
STL sort cost: 19727 micro seconds this round.

Test round 7....
SELECT_SORT version 0 cost: 15446675 micro seconds this round.
QUICK_SORT version 0 cost: 11469 micro seconds this round.
QUICK_SORT version 1 cost: 9483 micro seconds this round.
HEAP_SORT version 0 cost: 70762 micro seconds this round.
SHELL_SORT version 0 cost: 22040 micro seconds this round.
SHELL_SORT version 1 cost: 65032 micro seconds this round.
SHELL_SORT version 2 cost: 23578 micro seconds this round.
SHELL_SORT version 3 cost: 78750 micro seconds this round.
BUBBLE_SORT version 0 cost: 38115738 micro seconds this round.
BUBBLE_SORT version 1 cost: 39230891 micro seconds this round.
INSERTION_SORT version 0 cost: 10305431 micro seconds this round.
MERGE_SORT version 0 cost: 222152 micro seconds this round.
STL sort cost: 20128 micro seconds this round.

Test round 8....
SELECT_SORT version 0 cost: 14114463 micro seconds this round.
QUICK_SORT version 0 cost: 11137 micro seconds this round.
QUICK_SORT version 1 cost: 9758 micro seconds this round.
HEAP_SORT version 0 cost: 70789 micro seconds this round.
SHELL_SORT version 0 cost: 22273 micro seconds this round.
SHELL_SORT version 1 cost: 52351 micro seconds this round.
SHELL_SORT version 2 cost: 22004 micro seconds this round.
SHELL_SORT version 3 cost: 59332 micro seconds this round.
BUBBLE_SORT version 0 cost: 39027460 micro seconds this round.
BUBBLE_SORT version 1 cost: 36881803 micro seconds this round.
INSERTION_SORT version 0 cost: 10055113 micro seconds this round.
MERGE_SORT version 0 cost: 1219009 micro seconds this round.
STL sort cost: 19891 micro seconds this round.

Test round 9....
SELECT_SORT version 0 cost: 14068961 micro seconds this round.
QUICK_SORT version 0 cost: 11030 micro seconds this round.
QUICK_SORT version 1 cost: 9334 micro seconds this round.
HEAP_SORT version 0 cost: 69361 micro seconds this round.
SHELL_SORT version 0 cost: 22296 micro seconds this round.
SHELL_SORT version 1 cost: 49805 micro seconds this round.
SHELL_SORT version 2 cost: 23124 micro seconds this round.
SHELL_SORT version 3 cost: 56836 micro seconds this round.
BUBBLE_SORT version 0 cost: 37893125 micro seconds this round.
BUBBLE_SORT version 1 cost: 38157281 micro seconds this round.
INSERTION_SORT version 0 cost: 10305221 micro seconds this round.
MERGE_SORT version 0 cost: 1222818 micro seconds this round.
STL sort cost: 20080 micro seconds this round.

--------------------------------------------------------
--------------------------------------------------------
--------------------- Test finish ----------------------
--------------------------------------------------------

--------------------------------------------------------
Operating System: Windows
CPU Architecture: x86-64, 64-bit
Compiler: MSVC, Version: 1936
Cpp version: 199711
------------------ Test on RELEASE mode ------------------
--------------------- Test start -----------------------
--------------------------------------------------------
--------------------------------------------------------
Test round 0....
SELECT_SORT version 0 cost: 4088008 micro seconds this round.
QUICK_SORT version 0 cost: 2641 micro seconds this round.
QUICK_SORT version 1 cost: 2824 micro seconds this round.
HEAP_SORT version 0 cost: 3244 micro seconds this round.
SHELL_SORT version 0 cost: 2679 micro seconds this round.
SHELL_SORT version 1 cost: 5899 micro seconds this round.
SHELL_SORT version 2 cost: 4962 micro seconds this round.
SHELL_SORT version 3 cost: 6377 micro seconds this round.
BUBBLE_SORT version 0 cost: 7892124 micro seconds this round.
BUBBLE_SORT version 1 cost: 6887208 micro seconds this round.
INSERTION_SORT version 0 cost: 1201489 micro seconds this round.
MERGE_SORT version 0 cost: 5141 micro seconds this round.
STL sort cost: 2307 micro seconds this round.

Test round 1....
SELECT_SORT version 0 cost: 3940551 micro seconds this round.
QUICK_SORT version 0 cost: 2507 micro seconds this round.
QUICK_SORT version 1 cost: 2377 micro seconds this round.
HEAP_SORT version 0 cost: 3138 micro seconds this round.
SHELL_SORT version 0 cost: 2638 micro seconds this round.
SHELL_SORT version 1 cost: 5692 micro seconds this round.
SHELL_SORT version 2 cost: 4410 micro seconds this round.
SHELL_SORT version 3 cost: 5820 micro seconds this round.
BUBBLE_SORT version 0 cost: 6841145 micro seconds this round.
BUBBLE_SORT version 1 cost: 7933051 micro seconds this round.
INSERTION_SORT version 0 cost: 1203324 micro seconds this round.
MERGE_SORT version 0 cost: 5083 micro seconds this round.
STL sort cost: 2312 micro seconds this round.

Test round 2....
SELECT_SORT version 0 cost: 3954727 micro seconds this round.
QUICK_SORT version 0 cost: 2486 micro seconds this round.
QUICK_SORT version 1 cost: 2359 micro seconds this round.
HEAP_SORT version 0 cost: 3370 micro seconds this round.
SHELL_SORT version 0 cost: 2725 micro seconds this round.
SHELL_SORT version 1 cost: 5182 micro seconds this round.
SHELL_SORT version 2 cost: 4548 micro seconds this round.
SHELL_SORT version 3 cost: 5628 micro seconds this round.
BUBBLE_SORT version 0 cost: 6808610 micro seconds this round.
BUBBLE_SORT version 1 cost: 7871797 micro seconds this round.
INSERTION_SORT version 0 cost: 208177 micro seconds this round.
MERGE_SORT version 0 cost: 7018 micro seconds this round.
STL sort cost: 2547 micro seconds this round.

Test round 3....
SELECT_SORT version 0 cost: 4046368 micro seconds this round.
QUICK_SORT version 0 cost: 2570 micro seconds this round.
QUICK_SORT version 1 cost: 2416 micro seconds this round.
HEAP_SORT version 0 cost: 3084 micro seconds this round.
SHELL_SORT version 0 cost: 2651 micro seconds this round.
SHELL_SORT version 1 cost: 5009 micro seconds this round.
SHELL_SORT version 2 cost: 4409 micro seconds this round.
SHELL_SORT version 3 cost: 5242 micro seconds this round.
BUBBLE_SORT version 0 cost: 6862810 micro seconds this round.
BUBBLE_SORT version 1 cost: 7811539 micro seconds this round.
INSERTION_SORT version 0 cost: 191776 micro seconds this round.
MERGE_SORT version 0 cost: 4924 micro seconds this round.
STL sort cost: 2302 micro seconds this round.

Test round 4....
SELECT_SORT version 0 cost: 3932448 micro seconds this round.
QUICK_SORT version 0 cost: 2476 micro seconds this round.
QUICK_SORT version 1 cost: 2503 micro seconds this round.
HEAP_SORT version 0 cost: 3008 micro seconds this round.
SHELL_SORT version 0 cost: 2713 micro seconds this round.
SHELL_SORT version 1 cost: 5606 micro seconds this round.
SHELL_SORT version 2 cost: 4223 micro seconds this round.
SHELL_SORT version 3 cost: 5681 micro seconds this round.
BUBBLE_SORT version 0 cost: 7762839 micro seconds this round.
BUBBLE_SORT version 1 cost: 7808345 micro seconds this round.
INSERTION_SORT version 0 cost: 188611 micro seconds this round.
MERGE_SORT version 0 cost: 4792 micro seconds this round.
STL sort cost: 2314 micro seconds this round.

Test round 5....
SELECT_SORT version 0 cost: 3932761 micro seconds this round.
QUICK_SORT version 0 cost: 2533 micro seconds this round.
QUICK_SORT version 1 cost: 2325 micro seconds this round.
HEAP_SORT version 0 cost: 3206 micro seconds this round.
SHELL_SORT version 0 cost: 2669 micro seconds this round.
SHELL_SORT version 1 cost: 5060 micro seconds this round.
SHELL_SORT version 2 cost: 4252 micro seconds this round.
SHELL_SORT version 3 cost: 5521 micro seconds this round.
BUBBLE_SORT version 0 cost: 7767366 micro seconds this round.
BUBBLE_SORT version 1 cost: 7797240 micro seconds this round.
INSERTION_SORT version 0 cost: 190461 micro seconds this round.
MERGE_SORT version 0 cost: 4852 micro seconds this round.
STL sort cost: 2278 micro seconds this round.

Test round 6....
SELECT_SORT version 0 cost: 3930827 micro seconds this round.
QUICK_SORT version 0 cost: 2487 micro seconds this round.
QUICK_SORT version 1 cost: 2511 micro seconds this round.
HEAP_SORT version 0 cost: 3127 micro seconds this round.
SHELL_SORT version 0 cost: 3110 micro seconds this round.
SHELL_SORT version 1 cost: 5483 micro seconds this round.
SHELL_SORT version 2 cost: 4456 micro seconds this round.
SHELL_SORT version 3 cost: 5963 micro seconds this round.
BUBBLE_SORT version 0 cost: 7765522 micro seconds this round.
BUBBLE_SORT version 1 cost: 6777836 micro seconds this round.
INSERTION_SORT version 0 cost: 1197792 micro seconds this round.
MERGE_SORT version 0 cost: 4797 micro seconds this round.
STL sort cost: 2271 micro seconds this round.

Test round 7....
SELECT_SORT version 0 cost: 3933800 micro seconds this round.
QUICK_SORT version 0 cost: 2500 micro seconds this round.
QUICK_SORT version 1 cost: 2325 micro seconds this round.
HEAP_SORT version 0 cost: 3059 micro seconds this round.
SHELL_SORT version 0 cost: 2703 micro seconds this round.
SHELL_SORT version 1 cost: 5231 micro seconds this round.
SHELL_SORT version 2 cost: 4422 micro seconds this round.
SHELL_SORT version 3 cost: 5576 micro seconds this round.
BUBBLE_SORT version 0 cost: 6766273 micro seconds this round.
BUBBLE_SORT version 1 cost: 7788983 micro seconds this round.
INSERTION_SORT version 0 cost: 188678 micro seconds this round.
MERGE_SORT version 0 cost: 4946 micro seconds this round.
STL sort cost: 2333 micro seconds this round.

Test round 8....
SELECT_SORT version 0 cost: 3938473 micro seconds this round.
QUICK_SORT version 0 cost: 2650 micro seconds this round.
QUICK_SORT version 1 cost: 2336 micro seconds this round.
HEAP_SORT version 0 cost: 3200 micro seconds this round.
SHELL_SORT version 0 cost: 3237 micro seconds this round.
SHELL_SORT version 1 cost: 7011 micro seconds this round.
SHELL_SORT version 2 cost: 4534 micro seconds this round.
SHELL_SORT version 3 cost: 6163 micro seconds this round.
BUBBLE_SORT version 0 cost: 7790368 micro seconds this round.
BUBBLE_SORT version 1 cost: 7780954 micro seconds this round.
INSERTION_SORT version 0 cost: 200520 micro seconds this round.
MERGE_SORT version 0 cost: 4753 micro seconds this round.
STL sort cost: 2492 micro seconds this round.

Test round 9....
SELECT_SORT version 0 cost: 3931846 micro seconds this round.
QUICK_SORT version 0 cost: 2567 micro seconds this round.
QUICK_SORT version 1 cost: 2322 micro seconds this round.
HEAP_SORT version 0 cost: 3248 micro seconds this round.
SHELL_SORT version 0 cost: 2640 micro seconds this round.
SHELL_SORT version 1 cost: 5040 micro seconds this round.
SHELL_SORT version 2 cost: 4317 micro seconds this round.
SHELL_SORT version 3 cost: 5261 micro seconds this round.
BUBBLE_SORT version 0 cost: 7769883 micro seconds this round.
BUBBLE_SORT version 1 cost: 7787693 micro seconds this round.
INSERTION_SORT version 0 cost: 190071 micro seconds this round.
MERGE_SORT version 0 cost: 4776 micro seconds this round.
STL sort cost: 2295 micro seconds this round.

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
