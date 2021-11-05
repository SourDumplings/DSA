/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 20:22:19
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
 */

#include "Deque/Deque.h"

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
    dq1.print_info("dq1");
    dq2.print_info("dq2");
    dq3.print_info("dq3");
    dq4.print_info("dq4");
    dq41.print_info("dq41");
    dq5.print_info("dq5");
    dq6.print_info("dq6");
    dq61.print_info("dq61");
    dq7.print_info("dq7");
    return 0;
}
