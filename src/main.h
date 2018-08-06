#ifndef H_MAIN
#define H_MAIN

#include "flags.h"

#define HELP_STRING "Usage\n"                                                   \
                    "-a [bin file]  | start managing bin file\n"                \
                    "-d [bin name]  | stop managing bin file\n"                 \
                    "-u [bin names] | update managed bin from bin's location\n" \
                    "-g             | get list of all managed bin files\n"      \
                    "-h             | show this menu\n"

#define NO_ENV_ERROR "BINMGR_FOLDER environment variable not detected\n" \
                     "Use install.sh to initialize\n"

#define BINMGR_FOLDER "BINMGR_FOLDER"

void print_help(FILE *fp);

#define GETOPT_STR "a:d:u:gh"

#endif // H_MAIN