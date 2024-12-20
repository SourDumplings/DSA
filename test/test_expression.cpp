/*
 @Date    : 2018-05-29 18:06:39
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试算术表达式类
 */

#include "test_expression.h"

#include <iostream>
#include <cstdio>
#include "Expression/Expression.h"

using namespace std;
using namespace DSA;

bool test_expression()
{
    // 测试中缀表达式求值
    Expression e1("1+2*3"), e2("(3-5)*2"), e3("(4!)*(3^(1+2)) * 2.0 ^ 5");
    e1.print_info("e1");
    cout << "e1: " << e1 << endl;
    cout << "e1.hash(): " << e1.hash() << endl;
    printf("e1 = %f\n", e1.calc_value());
    printf("e2 = %f\n", e2.calc_value());
    printf("e3 = %f\n", e3.calc_value());
    e3.print_info("e3");
    cout << "e3: " << e3 << endl;
    cout << "e3.hash(): " << e3.hash() << endl;

    // 测试逆波兰表达式转换
    // Expression e3("(4!)*(3^(1+2)) * 2.1 ^ 5");
    e3.print_info("e3");
    printf("e3's RPN's size = %u\n", e3.to_RPN().size());
    printf("e3's RPN: %s\n", e3.to_RPN().c_str());
    e3.print_info("e3");
    cout << "e3: " << e3 << endl;
    cout << "e3.hash(): " << e3.hash() << endl;
    printf("e3 = %f\n", e3.calc_value());

    // printf("input an expression: \n");
    // DSAString s;
    // cin >> s;
    // Expression e4(s);
    // e4.print_info("e4");
    // printf("e4's RPN: %s\n", e4.to_RPN().c_str());

    // 测试波兰式转换
    printf("e3's PN: %s\n", e3.to_PN().c_str());

    return true;
}
