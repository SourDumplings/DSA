/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 20:22:19
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description:
 */

#include "test_deque.h"

#include "Deque/Deque.h"
#include "CZString/CZString.h"

using namespace CZ;
using namespace std;

bool test_deque()
{
    // 测试构造函数
    Deque<int> dq1(20);
    Deque<int> dq2;
    Deque<int> dq3(dq1.begin(), dq1.end());
    Deque<int> dq4(dq1.begin(), dq1.begin() + 7);
    Deque<int> dq41(dq1.begin(), dq1.begin() + 10);
    int a[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
    Deque<int> dq5(a, a + 5);
    Deque<int> dq6({ 2, 4, 6, 8, 10 });
    Deque<int> dq61({ 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28 });
    Deque<int> dq7(dq6);
    Deque<int> dq8(dq61.end() - 3, dq61.end());
    Deque<int> dq81(dq61.begin(), dq61.end() - 8);
    Deque<string> dqs({ "abc", "hello", "ztt" });

    std::cout << "dq6: " << dq6 << std::endl;
    std::cout << "dq6.hash(): " << dq6.hash() << std::endl;
    std::cout << "dq6.c_str(): " << dq6.c_str() << std::endl;

    dq1.print_info("dq1");
    dq2.print_info("dq2");
    dq3.print_info("dq3");
    dq4.print_info("dq4");
    dq41.print_info("dq41");
    dq5.print_info("dq5");
    dq6.print_info("dq6");
    dq61.print_info("dq61");
    dq7.print_info("dq7");
    dq8.print_info("dq8");
    dq81.print_info("dq81");
    dqs.print_info("dqs");

    // 测试数据访问接口
    printf("dq3.empty() = %d, dq3.size() = %d\n", dq3.empty(), dq3.size());
    printf("dq2.empty() = %d, dq2.size() = %d\n", dq2.empty(), dq2.size());

    // 测试 push_back
    dq1.push_back(1);
    dq1.print_info("dq1");
    for (int i = 0; i < 25; ++i)
    {
        dq1.push_back(i);
    }
    dq1.print_info("dq1");
    for (int i = 0; i < 100; ++i)
    {
        dq2.push_back(i);
    }
    dq2.print_info("dq2");
    Deque<CZString> dqs1;
    CZString s = "hello";
    for (int i = 0; i < 20; ++i)
    {
        dqs1.push_back(s + (i + '0'));
        dqs.push_back(s + (i + '0'));
    }
    dqs1.print_info("dqs1");
    dqs.print_info("dqs");

    // 测试 push_front
    dq1.push_front(1);
    dq1.print_info("dq1");
    dq1.clear();
    for (int i = 0; i < 25; ++i)
    {
        dq1.push_front(i);
    }
    dq1.print_info("dq1");
    // dqs.clear();
    for (int i = 0; i < 20; ++i)
    {
        dqs1.push_front(s + (i + '0'));
    }
    dqs1.print_info("dqs1");
    for (int i = 0; i < 100; ++i)
    {
        dq2.push_front(i);
    }
    dq2.print_info("dq2");

    // 测试 insert
    dq2.insert(dq2.begin(), 999);
    dq2.print_info("dq2");
    for (int i = 0; i < 5; i++)
    {
        auto it = dq2.end();
        printf("Inserting %d at %" PRId64 "....\n", i, it - dq2.begin());
        dq2.insert(it, i);
        // dq2.print_info("dq2");
    }

    auto it = dq2.end();
    for (int i = 0; i < 16; i++)
    {
        printf("Inserting %d at %" PRId64 "....\n", i + 100, it - dq2.begin());
        it = dq2.insert(it, i + 100);
        // dq2.print_info("dq2");
    }
    dq2.insert(dq2.end(), dq61.begin() + 1, dq61.end() - 2);
    dq2.insert(dq2.end(), dq1.begin() + 1, dq1.end());
    dq2.insert(dq2.end(), dq1.begin() + 10, dq1.end());
    dq2.print_info("dq2");
    dq1.print_info("dq1");
    dq1.insert(dq1.begin(), dq61.begin(), dq61.end() - 10);
    dq1.insert(dq1.begin(), dq61.begin(), dq61.end() - 11);
    dq1.insert(dq1.begin(), dq61.begin() + 1, dq61.end());
    dq1.insert(dq1.begin() + 11, dq61.begin() + 1, dq61.end());
    dq1.print_info("dq1");
    it = dq1.begin();
    for (int i = 0; i < 5; ++i)
    {
        it = dq1.insert(it, dq5.begin(), dq5.end());
        dq1.print_info("dq1");
    }

    // 测试 pop
    for (size_t i = 0; i < 50; i++)
    {
        dq2.push_back(i);
    }
    dq2.print_info("dq2");
    for (size_t i = 0; i < 50; i++)
    {
        dq2.pop_back();
        // dq2.pop_front();
        dq2.print_info("dq2");
    }

    // push_pop 交错测试
    dq2.push_front(1);
    dq2.pop_front();
    dq2.push_front(2);
    dq2.print_info("dq2");

    // 测试 erase
    dq61.print_info("dq61");
    dq61.erase(dq61.end() - 1);
    dq61.print_info("dq61");
    dq6.print_info("dq6");
    dq6.erase(dq6.end() - 2);
    dq6.print_info("dq6");
    for (size_t i = 0; i < 50; i++)
    {
        dq2.push_back(i);
    }
    dq2.print_info("dq2");
    it = dq2.begin();
    for (size_t i = 0; i < 50; i++)
    {
        printf("Erasing pos %" PRId64 "....\n", it - dq2.begin());
        it = dq2.erase(it);
        dq2.print_info("dq2");
    }
    for (size_t i = 0; i < 10; i++)
    {
        it = dq2.erase(it, it + 5);
        dq2.print_info("dq2");
    }
    for (size_t i = 0; i < 2; i++)
    {
        it = dq2.erase(it, it + 25);
        dq2.print_info("dq2");
    }
    it = dq2.end();
    for (size_t i = 0; i < 5; i++)
    {
        it = dq2.erase(it - 10, it);
        it = dq2.erase(it - 3, it);
        it = dq2.erase(it - 7, it - 1);
        dq2.print_info("dq2");
    }

    // 测试 back、front
    printf("dq1.front() = %d\n", dq1.front());
    printf("dq1.back() = %d\n", dq1.back());
    dqs1 = Deque<CZString>({"abc", "def", "hello", "world"});
    printf("dqs1.front().c_str() = %s\n", dqs1.front().c_str());
    printf("dqs1.back().c_str() = %s\n", dqs1.back().c_str());
    Deque<CZString> dqs2(dqs1);
    printf("dqs2.front().c_str() = %s\n", dqs2.front().c_str());
    printf("dqs2.back().c_str() = %s\n", dqs2.back().c_str());

    // 测试索引接口
    for (uint32_t i = 0; i < dq61.size(); i++)
    {
        printf("dq61[%d] = %d, dq61.at(%d) = %d\n", i, dq61[i], i, dq61.at(i));
    }

    for (uint32_t i = 0; i < 100; ++i)
    {
        dq2.push_back(i);
    }
    dq2.print_info("dq2");
    for (int i = -1; -i <= static_cast<int>(dq2.size()); i--)
    {
        printf("dq2.at(%d): %d\n", i, dq2.at(i));
    }

    // 测试赋值
    dq1.print_info("dq1");
    dq1 = dq6;
    dq1.print_info("dq1");
    dq6.print_info("dq6");
    dq61.print_info("dq61");
    dq1 = dq6 = dq61;
    dq6.print_info("dq6");
    dq1.print_info("dq1");
    dq5.print_info("dq5");
    dq1 = std::move(dq5);
    dq1.print_info("dq1");
    printf("dq5.size() = %u\n", dq5.size());

    // 测试 remove
    dq1.print_info("dq1");
    dq1.remove(5);
    dq1.print_info("dq1");
    for (size_t i = 0; i < 100; i++)
    {
        dq2.push_back(rand() % 10);
    }
    dq2.print_info("dq2");
    dq2.remove(3);
    dq2.print_info("dq2");
    dq2.remove(11);
    dq2.print_info("dq2");

    // 大数据测试
/*     Deque<int> dq9;
    uint32_t size = 1000;
    srand(1678349090);
    for (uint32_t j = 0; j < size; j++)
    {
        int value = rand() % size;
        dq9.push_back(value);
    }
    for (uint32_t j = 0; j < size; j++)
    {
        uint32_t idx = rand() % dq9.size();
        dq9.print_info("dq9");
        std::cout << "erase at pos " << idx << std::endl;

        dq9.erase(dq9.begin() + idx);
    } */
    return 0;
}
