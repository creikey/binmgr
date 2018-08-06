#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFERS_IMPLEMENTATION
#include <buffers.h>
#include <getopt.h>
#include "greatest/greatest.h"

#include "flags.h"
#include "main.h"
#include "tests.test.h"

/**
 * @brief prints help menu to fp
 * 
 * @param fp file to print help menu to
 */
void print_help(FILE *fp)
{
    fprintf(fp, HELP_STRING);
}

/**
 * @brief flags to check for
 * 
 */
flag flags[] = {
    new_flag('a', true),
    new_flag('d', true),
    new_flag('u', true),
    new_flag('g', false),
    new_flag('h', false)};

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
// if compiling for tests replace with greatest main signature
#ifdef DOTEST
    GREATEST_MAIN_BEGIN();
    RUN_ALL_SUITS();
    GREATEST_MAIN_END();
#else
    // check for config folder environment variable
    char *binmgr_folder = getenv(BINMGR_FOLDER);
    if (binmgr_folder == NULL)
    {
        fprintf(stderr, NO_ENV_ERROR);
        return 1;
    }
    // use array of flag structs for easily adding new commands
    size_t flags_len = sizeof(flags) / sizeof(*flags);

    int flag_err = set_flags(flags, flags_len, argc, argv, GETOPT_STR);

    // check for flag error in case improper flags
    if (flag_err != 0)
    {
        return flag_err;
    }

    // loop through all flag structs to see what opts to do
    for (int i = 0; i < flags_len; i++)
    {
        if (flags[i].flagged)
        {
            switch (flags[i].flag_char)
            {
            case 'h':
                print_help(stdout);
                return 0;
                break;
            case 'g':

                break;
            }
        }

        //print_flag(stdout, flags[i]);
    }

    return 0;
#endif // DOTEST
}