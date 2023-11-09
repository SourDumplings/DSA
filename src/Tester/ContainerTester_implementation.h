/*
 * @Author: SourDumplings
 * @Date: 2023-03-09 21:07:48
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#ifndef CONTAINER_TESTER_IMPLEMENTATION_H
#define CONTAINER_TESTER_IMPLEMENTATION_H

#include "ContainerTester.h"

#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include "../Base/WinTime.h"
#elif __linux__
#include <sys/time.h>
#endif

namespace CZ
{
    template<typename T, template <typename E> class Container >
    uint32_t ContainerTester<T, Container>::test_insert_random(const char *containerName, int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.insert(value);
        }

        gettimeofday(&tv, NULL);
        long stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "For container " << containerName << " inserting random value costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
        return c.size();
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_insert_random_then_remove(const char *containerName, int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.insert(value);
        }

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.remove(value);
        }

        gettimeofday(&tv, NULL);
        long stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "For container " << containerName << " inserting and remove random value costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_insert_random_then_erase(const char *containerName, int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.insert(value);
        }

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.erase(value);
        }

        gettimeofday(&tv, NULL);
        long stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "For container " << containerName << " inserting and erase random value costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_push_back_and_erase_at_random_pos(const char *containerName, int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.push_back(value);
        }

        long additionalTime = 0;
        for (uint32_t j = 0; j < size; j++)
        {
            uint32_t idx = rand() % c.size();
            auto it = c.begin();

            struct timeval tvTemp;
            gettimeofday(&tvTemp, NULL);
            long tempStart = tvTemp.tv_sec * 1000000 + tvTemp.tv_usec;
            for (uint32_t i = 0; i < idx; ++i)
            {
                ++it;
            }
            gettimeofday(&tvTemp, NULL);
            long tempStop = tvTemp.tv_sec * 1000000 + tvTemp.tv_usec;
            additionalTime += tempStop - tempStart;

            c.erase(it);
        }

        gettimeofday(&tv, NULL);
        long stop = tv.tv_sec * 1000000 + tv.tv_usec;
        // std::cout << "For container " << containerName << " moving iterator costs: " << additionalTime << " micro seconds." << std::endl;
        std::cout << "For container " << containerName << " pushing back and erase at random pos costs: " << stop - start - additionalTime
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_push_pop_back_front_randomly(const char *containerName, int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t i = 0; i < size; i++)
        {
            T value = rand() % size;

            // c.print_info("c");
            // printf("value = %d\n", value);

            switch (value % 4)
            {
            case 0:
                c.push_back(value);
                break;
            case 1:
                if (c.empty())
                {
                    break;
                }
                c.pop_back();
                break;
            case 2:
                c.push_front(value);
                break;
            case 3:
                if (c.empty())
                {
                    break;
                }
                c.pop_front();
                break;

            default:
                break;
            }
        }

        gettimeofday(&tv, NULL);
        long stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "For container " << containerName << " pushing and poping back and front randomly costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_at_random_pos(const char *containerName, int randSeed, uint32_t size) const
    {
        Container<T> c(size);
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        long start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t j = 0; j < size; j++)
        {
            int64_t idx = rand() % size;

            c.at(idx);
        }

        gettimeofday(&tv, NULL);
        long stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "For container " << containerName << " at random pos costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }
}

#endif
