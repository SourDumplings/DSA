/*
 @Date    : 2018-05-29 18:06:39
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试算术表达式类
 */

#include <iostream>
#include <cstdio>
#include "Expression.h"
#include "Expression.cpp"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Expression e1("1+2*3"), e2("(3-5)*2"), e3("(4!)*(3^(1+2)) * 2.0 ^ 5");
    e1.print_info("e1");
    printf("e1 = %f\n", e1.calc_value());
    printf("e2 = %f\n", e2.calc_value());
    printf("e3 = %f\n", e3.calc_value());
    return 0;
}

