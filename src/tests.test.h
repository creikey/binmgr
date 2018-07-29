#ifndef H_TESTS_TEST
#define H_TESTS_TEST

#include "greatest.h"

#include "main.test.h"

extern SUITE(main_test);

#define RUN_ALL_SUITS() \
    RUN_SUITE(main_test);

#endif // H_TESTS_TEST