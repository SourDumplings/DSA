#include <iostream>
#include <unistd.h>
#include "Algorithms/Sort.h"

int *create(unsigned int size)
{
    return new int[size];
}

void test_heap_mem()
{
    std::cout << "test heap mem" << std::endl;
    int count = 10;
    int *array[count];

    unsigned int size = 1024 * 1024;
    for (int i = 0; i < count; ++i)
    {
        sleep(1);
        array[i] = create(10 * size);

        int *b = new int[2 * size];
    }

    for (int i = 0; i < count; ++i)
    {
        delete[] array[i];
    }
}

void test_cpu_prof()
{
    std::cout << "test cpu prof" << std::endl;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << "round " << i << "..." << std::endl;
        constexpr int NUM = 1000000;
        int A[NUM];
        srand(time(0));
        for (size_t j = 0; j < NUM; j++)
        {
            A[j] = rand(); 
        }
        DSA::Sort(A, A + NUM, DSA::SortAccessories::HEAP_SORT);
    }
    
}

bool test_gperf_tools()
{
    test_cpu_prof();
    test_heap_mem();
    return true;
}