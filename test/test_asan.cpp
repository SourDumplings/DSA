/*
 * @Author: SourDumplings
 * @Date: 2022-12-01 11:21:06
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
 */

#include <cstdio>
#include "Vector/Vector.h"

using namespace CZ;
using namespace std;

void test_heap_overflow()
{
    int *arr = new int[1024];
    arr[0] = 11;
    arr[1024] = 12;
    printf("HeapBufferOverflow arr[0]=%d, arr[1024]=%d\n",arr[0], arr[1024]);
}

void test_unknow_address()
{
    int *p = reinterpret_cast<int*>(123456);
    *p = 5;
}

void test_use_after_free_with_dsa()
{
    Vector<int> *pV = new Vector<int>({1, 2, 3});
    int *p = &((*pV)[0]);
    delete pV;
    *p = 4;
}

void test_dereference_null_pointer()
{
    int *p = nullptr;
    *p = 1;
}

void test_stack_overflow()
{
    int arr[10];
    arr[10] = 1;
}

void test_memory_leak()
{
    int *p = new int(5);
}

int main()
{
    test_unknow_address();
    return 0;
}
