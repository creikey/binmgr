#ifndef H_FLAGS_TEST
#define H_FLAGS_TEST

#include <stdlib.h>
#include <string.h>

#include "flags.h"
#include "greatest/greatest.h"

TEST test_check_flag_structs(void)
{
    flag mock_flags[] = {
        new_flag('c', false),
        new_flag('d', true)};
    size_t mock_flags_len = sizeof(mock_flags) / sizeof(mock_flags[0]);
    ASSERT(check_flag_structs('c', mock_flags, NULL, mock_flags_len));
    ASSERT(mock_flags[0].flagged);
    ASSERT(check_flag_structs('d', mock_flags, "DOO", mock_flags_len));
    ASSERT(mock_flags[1].flagged);
    ASSERT_STR_EQm("Incorrect data for flag d", mock_flags[1].data, "DOO");
    PASS();
}

TEST test_set_flags(void)
{
    // mock flags to test
    flag base_mock_flags[] = {
        new_flag('a', false),
        new_flag('b', false),
        new_flag('z', true),
        new_flag('x', true)};
    const char *mock_flags_conf = "abz:x:";
    size_t mock_flags_len = sizeof(base_mock_flags) / sizeof(base_mock_flags[0]);
    // check every flag to see if they get flagged and with data
    char cur_flag_str[3];
    const char *const_data_str = "foo";
    size_t const_data_str_len = 3;
    char *data_str = malloc(sizeof *data_str * (strlen(const_data_str) + 1));
    memcpy(data_str, const_data_str, (const_data_str_len + 1) * sizeof *data_str);
    const int cur_argc = 2;
    char *const cur_argv[2] = {"a.out", cur_flag_str};
    const int cur_argc_data = 3;
    char *const cur_argv_data[3] = {"a.out", cur_flag_str, data_str};

    flag *dynamic_mock_flags = malloc(sizeof *dynamic_mock_flags * mock_flags_len);
    for (int i = 0; i < mock_flags_len; i++)
    {
        // reset dynamic flags because set in set_flags method
        memcpy(dynamic_mock_flags, base_mock_flags, mock_flags_len * sizeof *dynamic_mock_flags);
        cur_flag_str[0] = '-';
        cur_flag_str[1] = base_mock_flags[i].flag_char;
        cur_flag_str[2] = '\0';
        // set the current flags
        int err;
        if (dynamic_mock_flags[i].takes_data)
        {
            err = set_flags(dynamic_mock_flags, mock_flags_len, cur_argc_data, cur_argv_data, mock_flags_conf);
        }
        else
        {
            err = set_flags(dynamic_mock_flags, mock_flags_len, cur_argc, cur_argv, mock_flags_conf);
        }
        // test
        ASSERT(err == 0);
        ASSERTm(cur_flag_str, dynamic_mock_flags[i].flagged);
        if (dynamic_mock_flags[i].takes_data)
        {
            ASSERTm("Invalid data from set_flags", strncmp(dynamic_mock_flags[i].data, data_str, const_data_str_len) == 0);
        }
    }

    free(data_str);
    free(dynamic_mock_flags);
    PASS();
}

GREATEST_SUITE(flags_test)
{
    RUN_TEST(test_check_flag_structs);
    RUN_TEST(test_set_flags);
}

#endif // H_FLAGS_TEST