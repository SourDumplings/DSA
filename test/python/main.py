"""python 测试脚本入口
"""
import ctypes
import platform

import test_is_prime


def main():
    print("Running python test on " + platform.system())
    if platform.system() == "Windows":
        # https://stackoverflow.com/questions/74074742/when-importing-a-dll-to-python-using-ctypes-istream-and-ostream-can-be-found-b
        libdsa = ctypes.CDLL("E:/Github/DSA/dist/x64/Release/dsa.dll")
    else:
        libdsa = ctypes.CDLL("../../dist/lib/shared/libdsa.so")

    print("Start test is_prime...")
    test_is_prime.test(libdsa)


if __name__ == "__main__":
    main()