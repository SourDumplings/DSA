/*
 @Date    : 2018-05-27 14:01:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试匹配算法
 */

#include "test_match.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <memory>

#include "Algorithms/Match/Paren_match.h"
#include "Algorithms/Match.h"
#include "Vector/Vector.h"
#include "CZString/CZString.h"
#include <cstring>

using namespace std;
using namespace CZ;

bool test_match()
{
    // // 测试括号匹配算法
    // const char en1[] = "dadad(d}a{da([d([ada])asda)dada)dadwda2121",
    //     en2[] = "<asdasd>a>dasd[dasd]adsasd(dasd2112)+__+32093289890()dasd))><<sd[asdas{asd}(asd",
    //     e3[] = "()3223{(4324)}2342[<[]>7698798](`12(dweas2{adas{asda}}))",
    //     en4[] = "()3223{(4324)}2342[<[]>7698798](`12(dweas2{adas{asda}))";
    // printf("en1 is good? %s\n", Paren_match(en1, strlen(en1)) ? "true" : "false");
    // printf("en2 is good? %s\n", Paren_match(en2, strlen(en2)) ? "true" : "false");
    // printf("e3 is good? %s\n", Paren_match(e3, strlen(e3)) ? "true" : "false");
    // printf("en4 is good? %s\n", Paren_match(en4, strlen(en4)) ? "true" : "false");

    // printf("en1 is good? %s\n",
    //     Paren_match(en1, strlen(en1), RECURSION_PAREN_MATCH) ? "true" : "false");
    // printf("en2 is good? %s\n",
    //     Paren_match(en2, strlen(en2), RECURSION_PAREN_MATCH) ? "true" : "false");
    // printf("e3 is good? %s\n",
    //     Paren_match(e3, strlen(e3), RECURSION_PAREN_MATCH) ? "true" : "false");
    // printf("en4 is good? %s\n",
    //     Paren_match(en4, strlen(en4), RECURSION_PAREN_MATCH) ? "true" : "false");

    // 测试串匹配算法
    CZString s("In the pAst 30 years the Past Chinese past search for a past past spouse has"),
        p1("past"), p2("Chinese");
    MatchRank pos1, pos2, pos3;
    // pos1 = Match(s.begin(), s.end(), p1.begin(), p1.end(), BRUTE_FORCE, 0);
    // pos2 = Match(s.begin(), s.end(), p2.begin(), p2.end(), BRUTE_FORCE, 0);
    // pos1 = Match(s.begin(), s.end(), p1.begin(), p1.end(), BRUTE_FORCE, 1);
    // pos2 = Match(s.begin(), s.end(), p2.begin(), p2.end(), BRUTE_FORCE, 1);
    // KMP
    // char cs[] = "1212121212222121211121222112121212", p3[] = "2122";
    char cs[] = "0001000010", p3[] = "000010";

    // pos1 = Match(s.begin(), s.end(), p1.begin(), p1.end(), KMP, 1);
    // pos2 = Match(s.begin(), s.end(), p2.begin(), p2.end(), KMP, 1);
    // pos3 = Match(begin(cs), end(cs)-1, begin(p3), end(p3)-1, KMP, 1);
    pos1 = Match(s.begin(), s.end(), p1.begin(), p1.end(), KMP, 0);
    pos2 = Match(s.begin(), s.end(), p2.begin(), p2.end(), KMP, 0);
    pos3 = Match(begin(cs), end(cs)-1, begin(p3), end(p3)-1, KMP, 0);

    printf("s.length() = %u\n", s.length());
    printf("cs.length() = %u\n", (int32_t)strlen(cs));
    printf("pos1 is %u, res = %s\n", pos1, s.substr(pos1, p1.end() - p1.begin()).c_str());
    printf("pos2 is %u, res = %s\n", pos2, s.substr(pos2, p2.end() - p2.begin()).c_str());
    // printf("pos3 is %u, res = %s\n", pos3, CZString(cs).substr(pos3, 4).c_str());
    printf("pos3 is %u, res = %s\n", pos3, CZString(cs).substr(pos3, 6).c_str());
    return true;
}

