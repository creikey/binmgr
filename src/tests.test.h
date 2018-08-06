#ifndef H_TESTS_TEST
#define H_TESTS_TEST

#include "greatest/greatest.h"

#include "main.test.h"
#include "flags.test.h"

extern SUITE(main_test);

#define RUN_ALL_SUITS()   \
    RUN_SUITE(main_test); \
    RUN_SUITE(flags_test);

#endif // H_TESTS_TEST
