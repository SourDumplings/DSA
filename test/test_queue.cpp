/*
 @Date    : 2018-05-24 09:21:06
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试队列类模板
 */

#include <iostream>
#include <cstdio>
#include <string>

#include "Queue/Queue.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Queue<string> Qs;
    Qs.print_info("Qs");
    for (int32_t i = 0; i < 10; ++i)
    {
        Qs.push("hello" + to_string(i));
    }
    Qs.print_info("Qs");
    printf("Qs.front() = %s\n", Qs.front().c_str());
    Qs.pop(); Qs.pop(); Qs.pop();
    Qs.print_info("Qs");
    Queue<string> Qs2(Qs);
    Qs2.print_info("Qs2");
    Qs2.clear();
    Qs2.print_info("Qs2");
    printf("Qs2 is empty? %d\n", Qs2.empty());
    printf("Qs is empty? %d\n", Qs.empty());
    std::cout << "Qs: " << Qs << std::endl;
    std::cout << "Qs.hash(): " << Qs.hash() << std::endl;
    std::cout << "Qs.c_str(): " << Qs.c_str() << std::endl;
    return 0;
}

