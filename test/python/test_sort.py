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
Cpp sort costs 0.593584 seconds
Python sort costs 4.236202 seconds
Test round 1...
Cpp sort costs 0.604615 seconds
Python sort costs 4.027337 seconds
Test round 2...
Cpp sort costs 0.600406 seconds
Python sort costs 3.930394 seconds
Test round 3...
Cpp sort costs 0.599764 seconds
Python sort costs 3.897122 seconds
Test round 4...
Cpp sort costs 0.599517 seconds
Python sort costs 3.923864 seconds
Test round 5...
Cpp sort costs 0.602069 seconds
Python sort costs 3.887575 seconds
Test round 6...
Cpp sort costs 0.598927 seconds
Python sort costs 3.899475 seconds
Test round 7...
Cpp sort costs 0.600208 seconds
Python sort costs 3.916687 seconds
Test round 8...
Cpp sort costs 0.596409 seconds
Python sort costs 3.930904 seconds
Test round 9...
Cpp sort costs 0.616687 seconds
Python sort costs 3.898012 seconds
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