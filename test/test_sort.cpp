/*
 * @Author: SourDumplings
 * @Date: 2023-02-06 19:16:09
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#include "Algorithms/Sort.h"
#include "Algorithms/Stable_sort.h"
#include <cstdlib>
#include <sys/time.h>

using namespace CZ;
using namespace std;

__suseconds_t test_sort_prof(const Vector<int> &v, typename SortAccessories::UnStableSortMethod sortMethod, int version)
{
    Vector<int> tempV(v);
    struct timeval tv;
    gettimeofday(&tv, NULL);

    __suseconds_t start = tv.tv_sec * 1000000 + tv.tv_usec;

    Sort(tempV.begin(), tempV.end(), sortMethod, version);

    gettimeofday(&tv, NULL);
    __suseconds_t stop = tv.tv_sec * 1000000 + tv.tv_usec;
    return stop - start;
}

__suseconds_t test_sort_prof(const Vector<int> &v, typename SortAccessories::StableSortMethod sortMethod, int version)
{
    Vector<int> tempV(v);
    struct timeval tv;
    gettimeofday(&tv, NULL);

    __suseconds_t start = tv.tv_sec * 1000000 + tv.tv_usec;

    Sort(tempV.begin(), tempV.end(), sortMethod, version);

    gettimeofday(&tv, NULL);
    __suseconds_t stop = tv.tv_sec * 1000000 + tv.tv_usec;
    return stop - start;
}

int main(int argc, char const *argv[])
{
    // 测试排序算法
    // 基本逻辑测试
    /* Vector<int> v1{1, 8, 5, 4, 3, 0};
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
 */
    // 性能测试
    srand(time(NULL));
    const int size = 10000;
    const int test = 10;
    for (int i = 0; i < test; i++)
    {
        printf("Test round %d....\n", i);
        Vector<int> v;

        for (int j = 0; j < size; j++)
        {
            v.push_back(rand());
        }

        /*
Test round 0....
SELECT_SORT version 0 cost: 803401 micro seconds this round.
QUICK_SORT version 0 cost: 15020 micro seconds this round.
QUICK_SORT version 1 cost: 11791 micro seconds this round.
HEAP_SORT version 0 cost: 11215 micro seconds this round.
SHELL_SORT version 0 cost: 39614 micro seconds this round.
SHELL_SORT version 1 cost: 79235 micro seconds this round.
SHELL_SORT version 2 cost: 62988 micro seconds this round.
SHELL_SORT version 3 cost: 135048 micro seconds this round.
BUBBLE_SORT version 0 cost: 5172993 micro seconds this round.
BUBBLE_SORT version 1 cost: 5080768 micro seconds this round.
INSERTION_SORT version 0 cost: 2617586 micro seconds this round.
MERGE_SORT version 0 cost: 26188 micro seconds this round.

Test round 1....
SELECT_SORT version 0 cost: 793823 micro seconds this round.
QUICK_SORT version 0 cost: 14455 micro seconds this round.
QUICK_SORT version 1 cost: 12500 micro seconds this round.
HEAP_SORT version 0 cost: 16978 micro seconds this round.
SHELL_SORT version 0 cost: 100498 micro seconds this round.
SHELL_SORT version 1 cost: 125049 micro seconds this round.
SHELL_SORT version 2 cost: 125420 micro seconds this round.
SHELL_SORT version 3 cost: 173859 micro seconds this round.
BUBBLE_SORT version 0 cost: 5191455 micro seconds this round.
BUBBLE_SORT version 1 cost: 5311532 micro seconds this round.
INSERTION_SORT version 0 cost: 2597839 micro seconds this round.
MERGE_SORT version 0 cost: 22336 micro seconds this round.

Test round 2....
SELECT_SORT version 0 cost: 793548 micro seconds this round.
QUICK_SORT version 0 cost: 16164 micro seconds this round.
QUICK_SORT version 1 cost: 13475 micro seconds this round.
HEAP_SORT version 0 cost: 11246 micro seconds this round.
SHELL_SORT version 0 cost: 164221 micro seconds this round.
SHELL_SORT version 1 cost: 201478 micro seconds this round.
SHELL_SORT version 2 cost: 187573 micro seconds this round.
SHELL_SORT version 3 cost: 252215 micro seconds this round.
BUBBLE_SORT version 0 cost: 5161264 micro seconds this round.
BUBBLE_SORT version 1 cost: 5137544 micro seconds this round.
INSERTION_SORT version 0 cost: 2611239 micro seconds this round.
MERGE_SORT version 0 cost: 23157 micro seconds this round.

Test round 3....
SELECT_SORT version 0 cost: 797697 micro seconds this round.
QUICK_SORT version 0 cost: 15457 micro seconds this round.
QUICK_SORT version 1 cost: 12800 micro seconds this round.
HEAP_SORT version 0 cost: 11298 micro seconds this round.
SHELL_SORT version 0 cost: 227673 micro seconds this round.
SHELL_SORT version 1 cost: 258743 micro seconds this round.
SHELL_SORT version 2 cost: 250944 micro seconds this round.
SHELL_SORT version 3 cost: 314091 micro seconds this round.
BUBBLE_SORT version 0 cost: 5147773 micro seconds this round.
BUBBLE_SORT version 1 cost: 5629367 micro seconds this round.
INSERTION_SORT version 0 cost: 3286063 micro seconds this round.
MERGE_SORT version 0 cost: 22444 micro seconds this round.

Test round 4....
SELECT_SORT version 0 cost: 805890 micro seconds this round.
QUICK_SORT version 0 cost: 15625 micro seconds this round.
QUICK_SORT version 1 cost: 12843 micro seconds this round.
HEAP_SORT version 0 cost: 11807 micro seconds this round.
SHELL_SORT version 0 cost: 293998 micro seconds this round.
SHELL_SORT version 1 cost: 329124 micro seconds this round.
SHELL_SORT version 2 cost: 314353 micro seconds this round.
SHELL_SORT version 3 cost: 384433 micro seconds this round.
BUBBLE_SORT version 0 cost: 5157608 micro seconds this round.
BUBBLE_SORT version 1 cost: 5083407 micro seconds this round.
INSERTION_SORT version 0 cost: 2611130 micro seconds this round.
MERGE_SORT version 0 cost: 22373 micro seconds this round.

Test round 5....
SELECT_SORT version 0 cost: 795570 micro seconds this round.
QUICK_SORT version 0 cost: 14132 micro seconds this round.
QUICK_SORT version 1 cost: 13358 micro seconds this round.
HEAP_SORT version 0 cost: 18630 micro seconds this round.
SHELL_SORT version 0 cost: 372505 micro seconds this round.
SHELL_SORT version 1 cost: 376955 micro seconds this round.
SHELL_SORT version 2 cost: 376576 micro seconds this round.
SHELL_SORT version 3 cost: 431820 micro seconds this round.
BUBBLE_SORT version 0 cost: 5232047 micro seconds this round.
BUBBLE_SORT version 1 cost: 5064735 micro seconds this round.
INSERTION_SORT version 0 cost: 2695327 micro seconds this round.
MERGE_SORT version 0 cost: 22336 micro seconds this round.

Test round 6....
SELECT_SORT version 0 cost: 810671 micro seconds this round.
QUICK_SORT version 0 cost: 13927 micro seconds this round.
QUICK_SORT version 1 cost: 11224 micro seconds this round.
HEAP_SORT version 0 cost: 11234 micro seconds this round.
SHELL_SORT version 0 cost: 435472 micro seconds this round.
SHELL_SORT version 1 cost: 447582 micro seconds this round.
SHELL_SORT version 2 cost: 437117 micro seconds this round.
SHELL_SORT version 3 cost: 488166 micro seconds this round.
BUBBLE_SORT version 0 cost: 5245395 micro seconds this round.
BUBBLE_SORT version 1 cost: 5699049 micro seconds this round.
INSERTION_SORT version 0 cost: 2608146 micro seconds this round.
MERGE_SORT version 0 cost: 22343 micro seconds this round.

Test round 7....
SELECT_SORT version 0 cost: 795290 micro seconds this round.
QUICK_SORT version 0 cost: 14573 micro seconds this round.
QUICK_SORT version 1 cost: 12283 micro seconds this round.
HEAP_SORT version 0 cost: 11164 micro seconds this round.
SHELL_SORT version 0 cost: 477526 micro seconds this round.
SHELL_SORT version 1 cost: 506436 micro seconds this round.
SHELL_SORT version 2 cost: 502032 micro seconds this round.
SHELL_SORT version 3 cost: 552785 micro seconds this round.
BUBBLE_SORT version 0 cost: 5178628 micro seconds this round.
BUBBLE_SORT version 1 cost: 5095924 micro seconds this round.
INSERTION_SORT version 0 cost: 2599979 micro seconds this round.
MERGE_SORT version 0 cost: 22753 micro seconds this round.

Test round 8....
SELECT_SORT version 0 cost: 796906 micro seconds this round.
QUICK_SORT version 0 cost: 15368 micro seconds this round.
QUICK_SORT version 1 cost: 12489 micro seconds this round.
HEAP_SORT version 0 cost: 11212 micro seconds this round.
SHELL_SORT version 0 cost: 542714 micro seconds this round.
SHELL_SORT version 1 cost: 563169 micro seconds this round.
SHELL_SORT version 2 cost: 563958 micro seconds this round.
SHELL_SORT version 3 cost: 614047 micro seconds this round.
BUBBLE_SORT version 0 cost: 5165727 micro seconds this round.
BUBBLE_SORT version 1 cost: 5179322 micro seconds this round.
INSERTION_SORT version 0 cost: 2594388 micro seconds this round.
MERGE_SORT version 0 cost: 22353 micro seconds this round.

Test round 9....
SELECT_SORT version 0 cost: 800496 micro seconds this round.
QUICK_SORT version 0 cost: 15431 micro seconds this round.
QUICK_SORT version 1 cost: 12597 micro seconds this round.
HEAP_SORT version 0 cost: 11240 micro seconds this round.
SHELL_SORT version 0 cost: 604865 micro seconds this round.
SHELL_SORT version 1 cost: 624656 micro seconds this round.
SHELL_SORT version 2 cost: 629359 micro seconds this round.
SHELL_SORT version 3 cost: 675305 micro seconds this round.
BUBBLE_SORT version 0 cost: 5695443 micro seconds this round.
BUBBLE_SORT version 1 cost: 5171477 micro seconds this round.
INSERTION_SORT version 0 cost: 2608395 micro seconds this round.
MERGE_SORT version 0 cost: 22144 micro seconds this round.
         */

        __suseconds_t costTimeInMicroS = 0;

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

        costTimeInMicroS = test_sort_prof(v, SortAccessories::MERGE_SORT, 3);
        cout << "MERGE_SORT version 0 cost: " << costTimeInMicroS << " micro seconds this round." << endl;

        putchar('\n');
    }

    return 0;
}
