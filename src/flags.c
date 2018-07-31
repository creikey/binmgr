#include <stdlib.h>
#include <unistd.h>
#include <bits/getopt_core.h>
#include "flags.h"

// prints to fp
void print_flag(FILE *fp, flag f)
{
    fprintf(fp, "%c - ", f.flag_char);
    if (f.takes_data)
    {
        if (f.data == NULL)
        {
            fprintf(fp, "no data yet|");
        }
        else
        {
            fprintf(fp, "data `%s`|", f.data);
        }
    }
    if (f.flagged)
    {
        fprintf(fp, "flagged|");
    }
    else
    {
        fprintf(fp, "not flagged yet|");
    }
    fprintf(fp, "|\n");
}

// flags correct flags based on input character, returns false if not found
bool check_flag_structs(char in_char, flag *flag_arr, char *data, size_t flag_arr_sz)
{
    for (size_t i = 0; i < flag_arr_sz; i++)
    {
        if (in_char == flag_arr[i].flag_char)
        {
            if (flag_arr[i].takes_data)
            {
                flag_arr[i].data = data;
            }
            flag_arr[i].flagged = true;
            return true;
        }
    }
    return false;
}

// sets flags based on arguments
int set_flags(flag *in_flags, size_t in_flags_len, int argc, char **argv, const char *getopt_str)
{
    opterr = 0;
    int c;
    while ((c = getopt(argc, argv, getopt_str)) != -1)
    {
        // process cmdline parsing error
        if (c == '?')
        {
            // see if no data provided in a data flag
            for (size_t i = 0; i < in_flags_len; i++)
            {
                if (in_flags[i].flag_char == optopt && in_flags[i].takes_data)
                {
                    fprintf(stderr, "Flag `%c` expected data\n", optopt);
                    print_help();
                    return 1;
                }
            }
            // print if printable
            if (isprint(optopt))
            {
                fprintf(stderr, "Unkown option `-%c`\n", optopt);
                print_help();
                return 1;
            }
            // print ascii code if not printable
            fprintf(stderr, "Unknown unprintable character \\x%x\n", optopt);
            print_help();
            return 1;
        }
        else
        {
            // check all flags' structs
            bool flag_found = check_flag_structs(c, in_flags, optarg, in_flags_len);
            if (!flag_found)
            {
                abort();
            }
        }
    }
    return 0;
}