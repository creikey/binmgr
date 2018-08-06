#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <bits/getopt_core.h>
#define FLAGS_MAIN_FILE
#include "flags.h"

/**
 * @brief prints the input flag to fp
 * 
 * @param fp file to print flag diagnostic output to
 * @param f flag to print
 */
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
/**
 * @brief flags the correct flag in flag_arr from in_char
 * 
 * @param in_char character to flag flags on
 * @param flag_arr array of flags to flag
 * @param data cmdline string argument passed to flag
 * @param flag_arr_sz size of the flag array
 * @return true if the character was matched with a flag
 * @return false if no flag in the array could be matched
 */
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

/**
 * @brief Set the flags based off of command line input
 * 
 * @param in_flags array of flags to set
 * @param in_flags_len length of the flags array
 * @param argc count of arguments in main
 * @param argv value of arguments in main
 * @param getopt_str getopt string configuration
 * @return int 0 when successfull, fail when 1
 */
int set_flags(flag *in_flags, size_t in_flags_len, int argc, char *const *argv, const char *getopt_str)
{
    opterr = 0;
    optind = 1;
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
                    fprintf(ERROR_FILE, "Flag `%c` expected data\n", optopt);
                    //print_help();
                    return 1;
                }
            }
            // print if printable
            if (isprint(optopt))
            {
                fprintf(ERROR_FILE, "Unkown option `-%c`\n", optopt);
                //print_help();
                return 1;
            }
            // print ascii code if not printable
            fprintf(ERROR_FILE, "Unknown unprintable character \\x%x\n", optopt);
            //print_help();
            return 1;
        }
        else
        {
            // check all flags' structs
            bool flag_found = check_flag_structs(c, in_flags, optarg, in_flags_len);
            // behavior shouldn't be possible
            if (!flag_found)
            {
                fprintf(ERROR_FILE, "Getopt failed to catch an error - undefined\n");
                fprintf(ERROR_FILE, "Current character: %c\n", c);
                //return 1;
            }
        }
    }
    for (int index = optind; index < argc; index++)
    {
        fprintf(ERROR_FILE, "Unknown argument %s in index %d\n", argv[index], index);
    }
    if (optind < argc)
    {
        return 1;
    }
    return 0;
}