/*
 @Date    : 2018-05-27 14:01:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试匹配算法
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "Paren_match.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 测试括号匹配算法
    const char en1[] = "dadad(d}a{da([d([ada])asda)dada)dadwda2121",
        en2[] = "<asdasd>a>dasd[dasd]adsasd(dasd2112)+__+32093289890()dasd))><<sd[asdas{asd}(asd",
        e3[] = "()3223{(4324)}2342[<[]>7698798](`12(dweas2{adas{asda}}))",
        en4[] = "()3223{(4324)}2342[<[]>7698798](`12(dweas2{adas{asda}))";
    printf("en1 is good? %s\n", Paren_match(en1, strlen(en1)) ? "true" : "false");
    printf("en2 is good? %s\n", Paren_match(en2, strlen(en2)) ? "true" : "false");
    printf("e3 is good? %s\n", Paren_match(e3, strlen(e3)) ? "true" : "false");
    printf("en4 is good? %s\n", Paren_match(en4, strlen(en4)) ? "true" : "false");

    printf("en1 is good? %s\n",
        Paren_match(en1, strlen(en1), RECURSION_PAREN_MATCH) ? "true" : "false");
    printf("en2 is good? %s\n",
        Paren_match(en2, strlen(en2), RECURSION_PAREN_MATCH) ? "true" : "false");
    printf("e3 is good? %s\n",
        Paren_match(e3, strlen(e3), RECURSION_PAREN_MATCH) ? "true" : "false");
    printf("en4 is good? %s\n",
        Paren_match(en4, strlen(en4), RECURSION_PAREN_MATCH) ? "true" : "false");
    return 0;
}

