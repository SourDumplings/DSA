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
#include <sys/time.h>
#include <iostream>

namespace CZ
{
    template<typename T, template <typename E> class Container >
    uint32_t ContainerTester<T, Container>::test_insert_random(int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        __suseconds_t start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.insert(value);
        }

        gettimeofday(&tv, NULL);
        __suseconds_t stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "Inserting random value costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
        return c.size();
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_insert_random_then_remove(int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        __suseconds_t start = tv.tv_sec * 1000000 + tv.tv_usec;

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
        __suseconds_t stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "Inserting and remove random value costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_insert_random_then_erase(int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        __suseconds_t start = tv.tv_sec * 1000000 + tv.tv_usec;

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
        __suseconds_t stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "Inserting and erase random value costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_push_back_and_erase_at_random_pos(int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        __suseconds_t start = tv.tv_sec * 1000000 + tv.tv_usec;

        for (uint32_t j = 0; j < size; j++)
        {
            T value = rand() % size;
            c.push_back(value);
        }

        for (uint32_t j = 0; j < size; j++)
        {
            uint32_t idx = rand() % c.size();
            c.erase(c.begin() + idx);
        }

        gettimeofday(&tv, NULL);
        __suseconds_t stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "Pushing back and erase at random pos costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }

    template<typename T, template <typename E> class Container >
    void ContainerTester<T, Container>::test_push_pop_back_front_randomly(int randSeed, uint32_t size) const
    {
        Container<T> c;
        srand(randSeed);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        __suseconds_t start = tv.tv_sec * 1000000 + tv.tv_usec;

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
        __suseconds_t stop = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << "Pushing and poping back and front randomly costs: " << stop - start
            << " micro seconds, c.size() = " << c.size() << std::endl;
    }
}

#endif
