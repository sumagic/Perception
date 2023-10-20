#include "common.h"

#include <gtest/gtest.h>

TEST(LOG_PRINT, print_log)
{
    const char* x = (const char*)1234567;
    LOG_ERROR("%s %d %p %u %x", "haha", 123, x, 345, 987);
}