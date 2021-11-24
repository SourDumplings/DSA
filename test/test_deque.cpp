/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 20:22:19
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
 */

#include "Deque/Deque.h"
#include "CZString/CZString.h"

using namespace CZ;

int main(int argc, char const *argv[])
{
    
    Deque<int> dq1(20, 5);
    Deque<int> dq2;
    Deque<int> dq3(dq1.begin(), dq1.end());
    Deque<int> dq4(dq1.begin(), dq1.begin() + 7);
    Deque<int> dq41(dq1.begin(), dq1.begin() + 10);
    int a[] = {1, 3, 5, 7, 9, 11, 13, 15};
    Deque<int> dq5(a, a + 5);
    Deque<int> dq6({2, 4, 6, 8, 10});
    Deque<int> dq61({2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28}, 3);
    Deque<int> dq7(dq6);
    Deque<int> dq8(dq61.end() - 3, dq61.end());
    Deque<int> dq81(dq61.begin(), dq61.end() - 8, 4);

    // 测试构造函数
    // dq1.print_info("dq1");
    // dq2.print_info("dq2");
    // dq3.print_info("dq3");
    // dq4.print_info("dq4");
    // dq41.print_info("dq41");
    // dq5.print_info("dq5");
    // dq6.print_info("dq6");
    // dq61.print_info("dq61");
    // dq7.print_info("dq7");
    // dq8.print_info("dq8");
    // dq81.print_info("dq81");

    // 测试数据访问接口
    // printf("dq3.empty() = %d, dq3.size() = %d\n", dq3.empty(), dq3.size());
    // printf("dq2.empty() = %d, dq2.size() = %d\n", dq2.empty(), dq2.size());

    // 测试 push_back
    // dq1.push_back(1);
    // dq1.print_info("dq1");
    // for (int i = 0; i < 25; ++i)
    // {
    //     dq1.push_back(i);
    // }
    // dq1.print_info("dq1");
    // for (int i = 0; i < 100; ++i)
    // {
    //     dq2.push_back(i);
    // }
    // dq2.print_info("dq2");
    // Deque<CZString> dqs1;
    // CZString s = "hello";
    // for (int i = 0; i < 20; ++i)
    // {
    //     dqs1.push_back(s + (i + '0'));
    // }
    // dqs1.print_info("dqs1");

    // 测试 push_front
    // dq1.push_front(1);
    // dq1.print_info("dq1");
    // for (int i = 0; i < 25; ++i)
    // {
    //     dq1.push_front(i);
    // }
    // dq1.print_info("dq1");
    // for (int i = 0; i < 100; ++i)
    // {
    //     dq2.push_front(i);
    // }
    // dq2.print_info("dq2");
    // Deque<CZString> dqs1;
    // CZString s = "hello";
    // for (int i = 0; i < 20; ++i)
    // {
    //     dqs1.push_front(s + (i + '0'));
    // }
    // dqs1.print_info("dqs1");

    // 测试 insert
    // dq2.print_info("dq2");
    // for (int i = 0; i < 5; i++)
    // {
    //     auto it = dq2.end();
    //     dq2.insert(it, i);
    // }
    // dq2.print_info("dq2");
    // auto it = dq2.end();
    // for (int i = 0; i < 16; i++)
    // {
    //     it = dq2.insert(it, i + 100);
    // }
    // dq2.print_info("dq2");
    // dq2.insert(dq2.end(), dq61.begin() + 1, dq61.end() - 2);
    // dq2.insert(dq2.end(), dq1.begin() + 1, dq1.end());
    // dq2.insert(dq2.end(), dq1.begin() + 10, dq1.end());
    // dq2.print_info("dq2");
    // dq1.print_info("dq1");
    // dq1.insert(dq1.begin(), dq61.begin(), dq61.end() - 10);
    // dq1.insert(dq1.begin(), dq61.begin(), dq61.end() - 11);
    // dq1.insert(dq1.begin(), dq61.begin() + 1, dq61.end());
    // dq1.insert(dq1.begin() + 11, dq61.begin() + 1, dq61.end());
    // dq1.print_info("dq1");
    // auto it = dq1.begin();
    // for (int i = 0; i < 5; ++i)
    // {
    //     it = dq1.insert(it, dq5.begin(), dq5.end());
    //     dq1.print_info("dq1");
    // }

    // 测试 pop
    for (size_t i = 0; i < 50; i++)
    {
        dq2.push_back(i);
    }
    dq2.print_info("dq2");
    for (size_t i = 0; i < 50; i++)
    {
        // dq2.pop_back();
        dq2.pop_front();
        dq2.print_info("dq2");
    }
    
    return 0;
}
