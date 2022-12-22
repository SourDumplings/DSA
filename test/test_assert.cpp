/*
 * @Author: SourDumplings
 * @Date: 2022-12-13 15:41:54
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#include "Base/Assert.h"

using namespace CZ;

int main(int argc, char const *argv[])
{
    ASSERT_DEBUG(1, "test debug assertion fail.");
    ASSERT_DEBUG(1, "test release assertion fail.");
    ASSERT_DEBUG(0, "test debug assertion fail %d %s %f.", 1, "hello", 3.14);
    ASSERT_DEBUG(0, "test release assertion fail %d %s %f.", 2, "world", 3.15);

    return 0;
}
