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
#include "tests.test.h"

typedef struct bin_data {
    char * bin_name;
    char * desktop_file_path; // defaults to NO_DESKTOP_FILE
    char * bin_path;
} bin_data;


#define GETOPT_STR "a:d:u:gh"
void print_help()
{
    printf("Usage\n"
            "-a [bin file]  | start managing bin file\n"
            "-d [bin name]  | stop managing bin file\n"
            "-u [bin names] | update managed bin from bin's location\n"
            "-g             | get list of all managed bin files\n"
            "-h             | show this menu\n");
}

GREATEST_MAIN_DEFS();

int main(int argc, char ** argv)
{
    // if compiling for tests replace with greatest main signature
    #ifdef DOTEST
    GREATEST_MAIN_BEGIN();
    RUN_ALL_SUITS();
    GREATEST_MAIN_END();
    #else
    // use array of flag structs for easily adding new commands
    flag flags[] = {
        new_flag('a', true),
        new_flag('d', true),
        new_flag('u', true),
        new_flag('g', false),
        new_flag('h', false)};

    size_t flags_len = sizeof(flags) / sizeof(*flags);

    opterr = 0;
    int c;

    while((c = getopt(argc, argv, GETOPT_STR)) != -1)
    {
        // process cmdline parsing error
        if(c == '?')
        {
            // see if no data provided in a data flag
            for(size_t i = 0; i < flags_len; i++)
            {
                if(flags[i].flag_char == optopt && flags[i].takes_data)
                {
                    fprintf(stderr, "Flag `%c` expected data\n", optopt);
                    print_help();
                    return 1;
                }
            }
            // print if printable
            if(isprint(optopt))
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
        else {
            // check all flags' structs
           bool flag_found = check_flag_structs(c, flags, optarg, flags_len);
           if(!flag_found)
           {
               abort ();
           }
        }
    }

    // loop through all flag structs to see what opts to do
    for(int i = 0; i < flags_len; i++)
    {
        print_flag(stdout, flags[i]);
    }
    
    return 0;
    #endif // DOTEST
}
