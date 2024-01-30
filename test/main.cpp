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
#include "test_allocator2.h"
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
#include "test_trietree.h"
#include "test_tree.h"
#include "test_treemap.h"
#include "test_treeset.h"
#include "test_unionfindset.h"
#include "test_vector.h"

#include <iostream>
#include <cstdlib>

void print_runtime_environment_info()
{
    // 打印操作系统类型
    #ifdef _WIN32
        std::cout << "Operating System: Windows" << std::endl;
    #elif __linux__
        std::cout << "Operating System: Linux" << std::endl;
    #elif __APPLE__
        std::cout << "Operating System: macOS" << std::endl;
    #else
        std::cout << "Operating System: Unknown" << std::endl;
    #endif

    // 打印处理器架构
    std::cout << "CPU Architecture: ";
    #if defined(__x86_64__) || defined(_M_X64)
        std::cout << "x86-64";
    #elif defined(__i386) || defined(_M_IX86)
        std::cout << "x86";
    #elif defined(__arm__) || defined(_M_ARM)
        std::cout << "ARM";
    #elif defined(__aarch64__) || defined(_M_ARM64)
        std::cout << "ARM64";
    #else
        std::cout << "Unknown";
    #endif
    
    std::cout << ", " << sizeof(void*) * 8 << "-bit" << std::endl;

    // 打印编译器信息
    std::cout << "Compiler: ";
    
    #ifdef __clang__
        std::cout << "Clang";
    #elif defined(__GNUC__)
        std::cout << "GCC";
    #elif defined(_MSC_VER)
        std::cout << "MSVC";
    #else
        std::cout << "Unknown";
    #endif
    
    std::cout << ", Version: ";
    
    #if defined(__clang__)
        std::cout << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__;
    #elif defined(__GNUC__)
        std::cout << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__;
    #elif defined(_MSC_VER)
        std::cout << _MSC_VER;
    #else
        std::cout << "Unknown";
    #endif
    
    std::cout << std::endl;

    // 打印语言标准
    std::cout << "Cpp version: " << __cplusplus << std::endl;

    // 打印构建模式
    #ifdef DEBUG
    std::cout << "------------------ Test on DEBUG mode ------------------" << std::endl;
    #else
    std::cout << "------------------ Test on RELEASE mode ------------------" << std::endl;
    #endif
}

int main(int argc, char const *argv[])
{
    std::cout << "--------------------------------------------------------" << std::endl;
    print_runtime_environment_info();

    std::cout << "--------------------- Test start -----------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    test_trietree();

    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "--------------------- Test finish ----------------------" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    return 0;
}
