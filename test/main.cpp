/**
 * @file main.cpp
 * @author chadchang (chadchang@tencent.com)
 * @brief 测试程序入口
 * @version 1.0.0
 * @date 2023-11-08
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "test_algorithms.h"
#include "test_allocator.h"
#include "test_asan.h"
#include "test_assert.h"
#include "test_avltree.h"
#include "test_binaryindextree.h"
#include "test_bintree.h"
#include "test_bintree_rotate.h"
#include "test_bitmap.h"
#include "test_bplustree.h"
#include "test_bst.h"
#include "test_btree.h"
#include "test_container_perf.h"
#include "test_czstring.h"
#include "test_deque.h"
#include "test_expression.h"
#include "test_flathashset.h"
#include "test_gperftools.h"
#include "test_graph.h"
#include "test_hash.h"
#include "test_hashmap.h"
#include "test_hashset.h"
#include "test_heap.h"
#include "test_hello_world.h"
#include "test_is_prime.h"
#include "test_kvpair.h"
#include "test_leftheap.h"
#include "test_list.h"
#include "test_lua.h"
#include "test_match.h"
#include "test_median.h"
#include "test_permutation.h"
#include "test_pow.h"
#include "test_primetable.h"
#include "test_queue.h"
#include "test_redblacktree.h"
#include "test_remove.h"
#include "test_reverse.h"
#include "test_segment_tree.h"
#include "test_shuffle.h"
#include "test_smart_pointer.h"
#include "test_sort.h"
#include "test_splaytree.h"
#include "test_stack.h"
#include "test_tree.h"
#include "test_treemap.h"
#include "test_treeset.h"
#include "test_unionfindset.h"
#include "test_vector.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "--------------------- Test start -----------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

#ifdef DEBUG
    std::cout << "------------------ Test on DEBUG mode ------------------" << std::endl;
#endif

    test_lua();

    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------- Test finish ----------------------" << std::endl;
    return 0;
}
