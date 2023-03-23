/*
 * @Author: SourDumplings
 * @Date: 2023-03-09 19:58:41
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#include "Base/Assert.h"
#include "Deque/Deque.h"
#include "List/List.h"
#include "Tester/ContainerTester.h"
#include "Set/FlatHashSet.h"
#include "Set/HashSet.h"
#include "Set/TreeSet.h"
#include <deque>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>

using namespace CZ;

template <typename Key>
using StdSet = std::set<Key, std::less<Key>, std::allocator<Key>>;

template <typename Key>
using StdUSet = std::unordered_set<Key, std::hash<Key>, std::equal_to<Key>, std::allocator<Key>>;

template <typename T>
using StdVec = std::vector<T, std::allocator<T>>;

template <typename T>
using StdList = std::list<T, std::allocator<T>>;

template <typename T>
using StdList = std::list<T, std::allocator<T>>;

template <typename T>
using StdDeq = std::deque<T, std::allocator<T>>;

int main(int argc, char const *argv[])
{
    // 测试 set
    ContainerTester<int, FlatHashSet> cst1;
    ContainerTester<int, HashSet> cst2;
    ContainerTester<int, TreeSet> cst3;
    ContainerTester<int, StdSet> cst4;
    ContainerTester<int, StdUSet> cst5;

    const uint32_t cSize = 1000000U;
    const uint32_t testNo = 10;
    for (uint32_t i = 0; i < testNo; i++)
    {
        int randSeed = time(nullptr);
        printf("Testing %u...\n", i);

        // uint32_t s1 = cst1.test_insert_random("CZ::FlatHashSet", randSeed, cSize);
        // uint32_t s2 = cst2.test_insert_random("CZ::HashSet", randSeed, cSize);
        // ASSERT_DEBUG(s1 == s2, "Wrong size!");
        cst3.test_insert_random("CZ::TreeSet", randSeed, cSize);
        cst4.test_insert_random("std::set", randSeed, cSize);
        // cst5.test_insert_random("std::unordered_set", randSeed, cSize);

        // cst1.test_insert_random_then_remove("CZ::FlatHashSet", randSeed, cSize);
        // cst2.test_insert_random_then_remove("CZ::HashSet", randSeed, cSize);
        cst3.test_insert_random_then_remove("CZ::TreeSet", randSeed, cSize);
        cst4.test_insert_random_then_erase("std::set", randSeed, cSize);
        // cst5.test_insert_random_then_erase("std::unordered_set", randSeed, cSize);
    }

    // 测试顺序容器
    /* ContainerTester<int, Vector> cst6;
    ContainerTester<int, StdVec> cst7;
    ContainerTester<int, List> cst8;
    ContainerTester<int, StdList> cst9;
    ContainerTester<int, Deque> cst10;
    ContainerTester<int, StdDeq> cst11;

    const uint32_t cSize = 10000U;
    const uint32_t testNo = 10;
    for (uint32_t i = 0; i < testNo; i++)
    {
        int randSeed = time(nullptr);
        printf("Testing %u...\n", i);

        cst6.test_push_back_and_erase_at_random_pos("CZ::Vector", randSeed, cSize);
        cst7.test_push_back_and_erase_at_random_pos("std::vector", randSeed, cSize);
        cst8.test_push_back_and_erase_at_random_pos("CZ::List", randSeed, cSize);
        cst9.test_push_back_and_erase_at_random_pos("std::list", randSeed, cSize);
        cst10.test_push_back_and_erase_at_random_pos("CZ::Deque", randSeed, cSize);
        cst11.test_push_back_and_erase_at_random_pos("std::deque", randSeed, cSize);

        cst8.test_push_pop_back_front_randomly("CZ::List", randSeed, cSize);
        cst9.test_push_pop_back_front_randomly("std::list", randSeed, cSize);
        cst10.test_push_pop_back_front_randomly("CZ::Deque", randSeed, cSize);
        cst11.test_push_pop_back_front_randomly("std::deque", randSeed, cSize);

        cst6.test_at_random_pos("CZ::Vector", randSeed, cSize);
        cst7.test_at_random_pos("std::vector", randSeed, cSize);
        cst8.test_at_random_pos("CZ::List", randSeed, cSize);
        cst10.test_at_random_pos("CZ::Deque", randSeed, cSize);
        cst11.test_at_random_pos("std::deque", randSeed, cSize);
    } */


    return 0;
}
