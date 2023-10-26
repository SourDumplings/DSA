import sys
sys.path.append("../../dist/lib/shared")

import libdsa
import random

for i in range(100):
    num = random.randint(0, 1000)
    isPrime = bool(libdsa.Is_prime(num, 1))
    if isPrime:
        print("%d is prime." % num)
    else:
        print("%d is not prime" % num)

