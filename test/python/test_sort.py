""" 
测试排序
 """

import ctypes
import random
import time

def test_sort_prof(libdsa):
    NUMS = 10000000
    MAX_NUM = 10000
    for i in range(10):
        print("Test round %d..." % i)
        nums = []

        for i in range(NUMS):
            num = random.randint(0, MAX_NUM)
            nums.append(num)

        numsArray = (ctypes.c_int64 * len(nums))(*nums)
        start = time.time()
        libdsa.CZPyF_Sort_int(numsArray, NUMS)
        finish = time.time()
        print("Cpp sort costs %.6f seconds" % (finish - start))

        if not is_sorted(numsArray, NUMS):
            print("Error for Cpp sort!")
            return False

        start = time.time()
        nums.sort()
        finish = time.time()
        print("Python sort costs %.6f seconds" % (finish - start))

        if not is_sorted(nums, NUMS):
            print("Error for Python sort!")
            return False
    return True
""" 测试结果：
    NUMS = 10000000
    MAX_NUM = 10000
Running python test on Linux
Start test sort...
Test round 0...
Cpp sort costs 1.487382 seconds
Python sort costs 3.895837 seconds
Test round 1...
Cpp sort costs 1.458537 seconds
Python sort costs 3.844982 seconds
Test round 2...
Cpp sort costs 1.470404 seconds
Python sort costs 3.887146 seconds
Test round 3...
Cpp sort costs 1.462713 seconds
Python sort costs 3.882015 seconds
Test round 4...
Cpp sort costs 1.475652 seconds
Python sort costs 3.898359 seconds
Test round 5...
Cpp sort costs 1.445553 seconds
Python sort costs 3.897262 seconds
Test round 6...
Cpp sort costs 1.434608 seconds
Python sort costs 3.861650 seconds
Test round 7...
Cpp sort costs 1.442214 seconds
Python sort costs 3.969240 seconds
Test round 8...
Cpp sort costs 1.461499 seconds
Python sort costs 3.877917 seconds
Test round 9...
Cpp sort costs 1.460853 seconds
Python sort costs 3.850148 seconds
Finish test sort...

Running python test on Windows
Start test sort...
Test round 0...   
Cpp sort costs 0.422794 seconds
Python sort costs 1.801475 seconds
Test round 1...
Cpp sort costs 0.404694 seconds
Python sort costs 1.786247 seconds
Test round 2...
Cpp sort costs 0.413671 seconds
Python sort costs 2.185446 seconds
Test round 3...
Cpp sort costs 0.413137 seconds
Python sort costs 1.748599 seconds
Test round 4...
Cpp sort costs 0.439276 seconds
Python sort costs 1.857947 seconds
Test round 5...
Cpp sort costs 0.405554 seconds
Python sort costs 1.767668 seconds
Test round 6...
Cpp sort costs 0.416102 seconds
Python sort costs 1.757587 seconds
Test round 7...
Cpp sort costs 0.443556 seconds
Python sort costs 1.793826 seconds
Test round 8...
Cpp sort costs 0.413520 seconds
Python sort costs 2.010154 seconds
Test round 9...
Cpp sort costs 0.421472 seconds
Python sort costs 2.072021 seconds
Finish test sort...

可以看出 CPP 比 Python 排序上也是有性能优势的
 """


def is_sorted(nums, n):
    for i in range(n - 1):
        if nums[i + 1] < nums[i]:
            # print("Not sorted!")
            return False
    # print("Sorted!")
    return True

def test(libdsa):
    print("Start test sort...")
    test_sort_prof(libdsa)
    print("Finish test sort...")