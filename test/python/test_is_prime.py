"""测试素数判断
"""
import random
import time

def test_correctiness(libdsa):
    for i in range(100):
        num = random.randint(0, 1000)
        isPrime = bool(libdsa.DSAPyF_Is_prime(num, 1))
        if isPrime:
            print("%d is prime." % num)
        else:
            print("%d is not prime" % num)

def is_prime_violence(num):
    if num == 0 or num == 1:
        return False
    if num == 2:
        return True
    for i in range(2, int(num / 2) + 1):
        if num % i == 0:
            return False
    return True

def test_correctiness_and_prof(libdsa):
    NUMS = 1000000
    MAX_NUM = 10000

    for testNo in range(10):
        print("------ test %d ------" % testNo)
        nums = []
        for i in range(NUMS):
            num = random.randint(0, MAX_NUM)
            nums.append(num)

        start = time.time()
        for num in nums:
            isPrime = is_prime_violence(num)
        finish = time.time()
        print("------ Python is prime violence costs: %.6f seconds" % (finish - start))

        res = []
        for num in nums:
            isPrime = is_prime_violence(num)
            res.append(isPrime)
        
        for i in range(len(nums)):
            isPrime = bool(libdsa.DSAPyF_Is_prime(nums[i], 0))
            if isPrime != res[i]:
                print("Error for %d, python: %d, cpp: %d" % (nums[i], res[i], isPrime))

        start = time.time()
        for num in nums:
            isPrime = bool(libdsa.DSAPyF_Is_prime(num, 0))
        finish = time.time()
        print("------ Cpp is prime violence costs: %.6f seconds" % (finish - start))
        print()

        """ 测试结果
    NUMS = 1000000
    MAX_NUM = 10000
    Running python test on Linux
    Start test is_prime...
------ test 0 ------
------ Python is prime violence costs: 13.923038 seconds
------ Cpp is prime violence costs: 0.974024 seconds

------ test 1 ------
------ Python is prime violence costs: 13.565289 seconds
------ Cpp is prime violence costs: 0.960366 seconds

------ test 2 ------
------ Python is prime violence costs: 13.642014 seconds
------ Cpp is prime violence costs: 0.959018 seconds

------ test 3 ------
------ Python is prime violence costs: 13.771118 seconds
------ Cpp is prime violence costs: 0.985512 seconds

------ test 4 ------
------ Python is prime violence costs: 13.697527 seconds
------ Cpp is prime violence costs: 0.959303 seconds

------ test 5 ------
------ Python is prime violence costs: 14.050005 seconds
------ Cpp is prime violence costs: 0.956207 seconds

------ test 6 ------
------ Python is prime violence costs: 13.877172 seconds
------ Cpp is prime violence costs: 0.963617 seconds

------ test 7 ------
------ Python is prime violence costs: 13.959413 seconds
------ Cpp is prime violence costs: 0.966984 seconds

------ test 8 ------
------ Python is prime violence costs: 13.622165 seconds
------ Cpp is prime violence costs: 0.953583 seconds

------ test 9 ------
------ Python is prime violence costs: 13.711943 seconds
------ Cpp is prime violence costs: 0.965958 seconds

        可以看出同样的算法 Cpp 性能优势明显 
             """

def test(libdsa):
    print("Start test is_prime...")
    # test_correctiness(libdsa)
    test_correctiness_and_prof(libdsa)
    print("Finish test is_prime...")