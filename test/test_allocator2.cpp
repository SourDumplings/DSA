#include "test_allocator2.h"

#include "Allocator/Allocator2.h"
#include <cstdio>
#include "Vector/Vector.h"
#include "Map/KVPair.h"

using namespace CZ;

static void test_alloc_and_free()
{
    printf("Test alloc...\n");
    Allocator2 &alloc = Allocator2::get_instance();
    size_t NUM = 500;
    int64_t *A[NUM];
    for (size_t i = 0; i < NUM; i++)
    {
        A[i] = static_cast<int64_t*>(alloc.allocate(sizeof(int64_t)));
        printf("A[%lu] = %p\n", i, A[i]);
    }

    printf("Then free...\n");
    for (size_t i = 0; i < NUM; i++)
    {
        alloc.deallocate(A[i], sizeof(int64_t));
        printf("A[%lu] = %p freed!\n", i, A[i]);
    }
}

static void test_alloc_and_free_randomly()
{
    printf("Test alloc and free randomly...\n");
    Allocator2 &alloc = Allocator2::get_instance();
    size_t NUM = 500;
    Vector<KVPair<int64_t*, bool>> ptrs;
    for (size_t i = 0; i < NUM; i++)
    {
        int num = rand();
        if (num % 2)
        {
            // alloc
            int64_t *ptr = static_cast<int64_t*>(alloc.allocate(sizeof(int64_t)));
            printf("%lu: alloc %p succ!\n", i, ptr);
            ptrs.push_back(KVPair<int64_t*, bool>(ptr, true));
        }
        else
        {
            // dealloc
            int idx = rand() % ptrs.size();
            if (ptrs[idx].value())
            {
                int64_t *ptr = ptrs[idx].key();
                alloc.deallocate(ptr, sizeof(int64_t));
                ptrs[idx].value() = false;
                printf("%lu: %d: dealloc %p succ!\n", i, idx, ptr);
            }
        }
    }

    for (const auto &p : ptrs)
    {
        if (p.value())
        {
            alloc.deallocate(p.key(), sizeof(int64_t));
        }
        
    }
    
}

bool test_allocator2()
{
    test_alloc_and_free_randomly();
    return true;
}