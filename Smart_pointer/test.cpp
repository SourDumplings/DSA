/*
 @Date    : 2018-05-22 17:50:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试智能指针
 */

#include <cstdio>
#include <string>
#include "Shared_ptr.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Shared_ptr<string> ps1(new string("string1")), ps2(new string("string2"));
    printf("ps1.use_count() = %u\n", ps1.use_count());
    {
        Shared_ptr<string> ps3(ps1);
        printf("ps1.use_count() = %u\n", ps1.use_count());
        printf("ps3.use_count() = %u\n", ps3.use_count());
    }
    printf("ps1.use_count() = %u\n", ps1.use_count());
    printf("*ps1 = %s\n", (*ps1).c_str());
    printf("ps1->length() = %llu\n", ps1->length());

    (*ps1)[0] = 'a';
    printf("*ps1 = %s\n", (*ps1).c_str());

    printf("ps1.use_count() = %u\n", ps1.use_count());
    printf("ps2.use_count() = %u\n", ps2.use_count());
    ps1 = ps2;
    printf("ps1.use_count() = %u\n", ps1.use_count());
    printf("ps2.use_count() = %u\n", ps2.use_count());


    return 0;
}

