/*
 @Date    : 2018-05-23 10:23:48
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试堆栈类模板
 */
#include "test_stack.h"

#include <iostream>
#include <cstdio>
#include <string>

#include "Stack/Stack.h"
#include "List/List.h"

using namespace std;
using namespace DSA;

bool test_stack()
{
    // Stack<string> Ss;
    // Ss.print_info("Ss");
    // Ss.push("hello"); Ss.push("hello kitty"); Ss.push("world");
    // Ss.print_info("Ss");
    // printf("Ss.top() = %s\n", Ss.top().c_str());
    // Ss.pop();
    // Ss.print_info("Ss");
    // Stack<string> Ss2(Ss);
    // Ss2.print_info("Ss2");
    // Ss2.clear();
    // Ss2.print_info("Ss2");
    // printf("Ss2 is empty? %d\n", Ss2.empty());
    // printf("Ss is empty? %d\n", Ss.empty());

    // 测试用List实现堆栈
    Stack<string, List<string>> Ss;
    Ss.print_info("Ss");
    Ss.push("hello"); Ss.push("hello kitty"); Ss.push("world");
    Ss.print_info("Ss");
    printf("Ss.top() = %s\n", Ss.top().c_str());
    Ss.pop();
    Ss.print_info("Ss");
    Stack<string, List<string>> Ss2(Ss);
    Ss2.print_info("Ss2");
    Ss2.clear();
    Ss2.print_info("Ss2");
    printf("Ss2 is empty? %d\n", Ss2.empty());
    printf("Ss is empty? %d\n", Ss.empty());
    std::cout << "Ss: " << Ss << std::endl;
    std::cout << "Ss.hash(): " << Ss.hash() << std::endl;
    std::cout << "Ss.c_str(): " << Ss.c_str() << std::endl;
    return true;
}

