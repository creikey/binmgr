#ifndef H_MAIN_TEST
#define H_MAIN_TEST

#include "greatest.h"

TEST test_args(void)
{
    PASS();
}

GREATEST_SUITE(main_test)
{
    RUN_TEST(test_args);
}

#endif // H_MAIN_TEST