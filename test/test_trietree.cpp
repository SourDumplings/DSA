#include "test_trietree.h"

#include "Tree/TrieTree/TrieTree.h"
#include "CZString/CZString.h"

using namespace CZ;
using namespace std;

bool test_trietree()
{
    Vector<int> seqi1({1, 10, 10, 8, 5, 6, 7, 4, 3}), seqi2({1, 2});
    Vector<CZString> seqs1({"Hello", "World", "Wor", "ZTT", "Hey", "I"});

    TrieTree<int> TI1;
    TrieTree<int> TI2(seqi1);
    TrieTree<int> TI3(seqi2);
    TrieTree<CZString> TS1(seqs1);
    TrieTree<CZString> TS2(TS1);

    TI1.print_info("TI1");
    TI2.print_info("TI2");
    TI3.print_info("TI3");
    TS1.print_info("TS1");
    TS2.print_info("TS2");

    TI2.insert_seq(Vector<int>({1, 10, 10, 8, 5, 6, 7, 5}));
    TI2.insert_seq(Vector<int>({1, 10, 10, 8, 9, 9}));
    TI2.insert_seq(Vector<int>({2, 10, 9}));
    TI2.print_info("TI2");

    TI2.remove_seq(Vector<int>({1, 10, 10}));
    TI2.print_info("TI2");

    TS2.insert_seq(Vector<CZString>({"Hello", "World", "Size", "Ignore"}));
    TS2.insert_seq(Vector<CZString>({"ZTT", "World", "Hey"}));
    TS2.print_info("TS2");

    TS2.remove_seq(Vector<CZString>({"Hello", "World", "Size"}));
    TS2.print_info("TS2");

    TS2.remove_seq(Vector<CZString>({"Hey", "I"}));
    TS2.print_info("TS2");
    return true;
}