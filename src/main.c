#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFERS_IMPLEMENTATION
#include <buffers.h>
#include <bits/getopt_core.h>
#include "greatest.h"

#include "flags.h"
#include "main.h"
#include "tests.test.h"

typedef struct bin_data
{
    char *bin_name;
    char *desktop_file_path; // defaults to NO_DESKTOP_FILE
    char *bin_path;
} bin_data;

void print_help(FILE *fp)
{
    fprintf(fp, HELP_STRING);
}

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
    // use array of flag structs for easily adding new commands

    size_t flags_len = sizeof(flags) / sizeof(*flags);

    set_flags(flags, flags_len, argc, argv, GETOPT_STR);

    // loop through all flag structs to see what opts to do
    for (int i = 0; i < flags_len; i++)
    {
        if (flags[i].flagged)
        {
            switch (flags[i].flag_char)
            {
            case 'a':

                break;
            }
        }

        //print_flag(stdout, flags[i]);
    }

    return 0;
#endif // DOTEST
}
