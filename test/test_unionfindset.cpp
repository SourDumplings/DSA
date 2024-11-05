/*
 @Date    : 2018-06-01 13:52:38
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
并查集类模板的测试
 */
#include "test_unionfindset.h"

#include <string>
#include <iostream>
#include <cstdio>
#include <utility>
#include "UnionFindSet/UnionFindSet.h"

using namespace std;
using namespace CZ;

bool test_unionfindset()
{
    using Node = UnionFindSet<string>::UnionFindSetNode;

    // 测试构造函数
    UnionFindSet<string> us1({"hello", "world"});
    us1.print_info("us1");

    Node *pr = new Node("hi");
    Node *pc1 = new Node("I", pr), *pc2 = new Node("am", pr), *pc3 = new Node("cat", pr);

    UnionFindSet<string> us2(pr), us3(us1);
    us2.print_info("us2");
    cout << "us2: " << us2 << endl;
    cout << "us2.hash(): " << us2.hash() << endl;

    us3.print_info("us3");
    cout << "us3: " << us3 << endl;
    cout << "us3.hash(): " << us3.hash() << endl;

    UnionFindSet<string> us4(std::move(us3));
    us4.print_info("us4");
    cout << "us4: " << us4 << endl;
    cout << "us4.hash(): " << us4.hash() << endl;
    us3.print_info("us3");
    cout << "us3: " << us3 << endl;
    cout << "us3.hash(): " << us3.hash() << endl;
    us1.print_info("us1");

    printf("%s is in us2? %s\n", pc2->data().c_str(), us2.is_family(pc2) ? "true" : "false");
    printf("%s is in us2? %s\n", pc1->data().c_str(), us2.is_family(pc1) ? "true" : "false");
    printf("%s is in us1? %s\n", pc1->data().c_str(), us1.is_family(pc1) ? "true" : "false");
    Node *pc4 = new Node("hey");
    printf("%s and %s are family? %s\n", pc4->data().c_str(), pc3->data().c_str(),
           UnionFindSet<string>::are_family(pc4, pc3) ? "true" : "false");
    printf("%s and %s are family? %s\n", pc1->data().c_str(), pc3->data().c_str(),
           UnionFindSet<string>::are_family(pc1, pc3) ? "true" : "false");

    // 测试插入删除
    printf("\n\n------------- testing modifications -----------------\n\n");

    us3.merge(std::move(us4));
    us3.print_info("us3");
    cout << "us3: " << us3 << endl;
    cout << "us3.hash(): " << us3.hash() << endl;
    us4.print_info("us4");
    cout << "us4: " << us4 << endl;
    cout << "us4.hash(): " << us4.hash() << endl;

    us2.print_info("us2");
    cout << "us2: " << us2 << endl;
    cout << "us2.hash(): " << us2.hash() << endl;
    us2.remove(pc3);
    us2.print_info("us2");
    cout << "us2: " << us2 << endl;
    cout << "us2.hash(): " << us2.hash() << endl;
    printf("%s and %s are family? %s\n", pc1->data().c_str(), pc3->data().c_str(),
           UnionFindSet<string>::are_family(pc1, pc3) ? "true" : "false");
    printf("%s and %s are family? %s\n", pc1->data().c_str(), pc4->data().c_str(),
           UnionFindSet<string>::are_family(pc1, pc4) ? "true" : "false");
    UnionFindSet<string>::merge(pc1, pc4);
    printf("%s and %s are family? %s\n", pc1->data().c_str(), pc4->data().c_str(),
           UnionFindSet<string>::are_family(pc1, pc4) ? "true" : "false");
    us2.print_info("us2");
    printf("%s is in us2? %s\n", pc4->data().c_str(), us2.is_family(pc4) ? "true" : "false");

    us1.insert(pc3);
    us1.print_info("us1");
    us1.insert("kitty");
    us1.insert("cute");
    us1.print_info("us1");
    UnionFindSet<string> us5(us1.remove(pc3));
    us1.print_info("us1");
    us5.print_info("us5");

    us1.clear();
    us1.print_info("us1");

    return true;
}
