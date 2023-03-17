/*
 * @Author: SourDumplings
 * @Date: 2023-03-09 19:46:45
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#ifndef CONTAINER_TESTER_H
#define CONTAINER_TESTER_H

#include <cstdint>

namespace CZ
{
    template<typename T, template <typename E> class Container >
    class ContainerTester
    {
    public:
        uint32_t test_insert_random(const char *containerName, int randSeed = 0, uint32_t size = 10000) const;

        void test_insert_random_then_remove(const char *containerName, int randSeed = 0, uint32_t size = 10000) const;

        void test_insert_random_then_erase(const char *containerName, int randSeed = 0, uint32_t size = 10000) const;

        void test_push_back_and_erase_at_random_pos(const char *containerName, int randSeed = 0, uint32_t size = 10000) const;

        void test_push_pop_back_front_randomly(const char *containerName, int randSeed = 0, uint32_t size = 10000) const;

        void test_at_random_pos(const char *containerName, int randSeed = 0, uint32_t size = 10000) const;
    };
}

#include "ContainerTester_implementation.h"

#endif