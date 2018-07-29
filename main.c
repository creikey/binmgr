#include <stdio.h>
#define BUFFERS_IMPLEMENTATION
#include <buffers.h>

typedef struct bin_data {
    char * bin_name;
    char * bin_path;
} bin_data;

// flag should be with leading pipe, like `-b` 
bool is_flaggged(int argc, char ** argv, const char * flag)
{
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], flag) == 0)
        {
            return true;
        }
    }
    return false;
}

void print_help()
{
    printf("Usage\nThe arg that doesn't have a trailing pip is the bin name/file name\n[no args] - show this menu\n-a | add bin file\n-d | delete bin file\n-u | update bin file\n-g | get a list of all bin files\n");
}

int main(int argc, char ** argv)
{
    if(argc <= 1)
    {
        print_help();
        return 1;
    }
    // check flags without context
    if(is_flagged(argc, argv, "-g"))
    {
        // get all bin files
        // TODO
    }
    // fetch the context for the operation
    char * context = NULL;
    for(int i = 0; i < argc; i++)
    {
        // check for flag
        if(argv[i][0] == '-')
        {

        } else {
            // make sure no other context
            if(context != NULL)
            {
                printf("Can only have one context\n");
                print_help();
                return 1;
            }
            context = argv[i];
        }
    }
    
    // check flags with context
    if(is_flagged(argc, argv, "-a"))
    {
        // add bin file
        // TODO
    }
    if(is_flagged(argc, argv, "-d"))
    {
        // delete bin file
        // TODO
    }
    if(is_flagged(argc, argv, "-u"))
    {
        // update specific bin file
        // TODO
    }

    // no flags given
    printf("Must specify a flag for operation\n");
    print_help();
    return 1;
}
