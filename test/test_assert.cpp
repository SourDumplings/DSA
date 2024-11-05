/*
 * @Author: SourDumplings
 * @Date: 2022-12-13 15:41:54
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description:
 */

#include "test_assert.h"

#include "Base/Assert.h"

using namespace CZ;

bool test_assert()
{
    ASSERT_DEBUG(1, "test debug assertion fail.");
    ASSERT_RELEASE(1, "test release assertion fail.");
    ASSERT_DEBUG(0, "test debug assertion fail %d %s %f.", 1, "hello", 3.14);
    ASSERT_RELEASE(0, "test release assertion fail %d %s %f.", 2, "world", 3.15);

    return false;
}
