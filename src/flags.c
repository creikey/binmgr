#include "flags.h"

void print_flag(FILE * fp, flag f)
{
    fprintf(fp, "%c - ", f.flag_char);
    if(f.takes_data)
    {
        if(f.data == NULL)
        {
            fprintf(fp, "no data yet|");
        } else {
            fprintf(fp, "data `%s`|", f.data);
        }
    }
    if(f.flagged)
    {
        fprintf(fp, "flagged|");
    } else {
        fprintf(fp, "not flagged yet|");
    }
    fprintf(fp, "|\n");
}

// flags correct flags, returns false if not found
bool check_flag_structs(char in_char, flag * flag_arr, char * data, 
        size_t arr_sz)
{
    for(size_t i = 0; i < arr_sz; i++)
    {
        if(in_char == flag_arr[i].flag_char)
        {
            if(flag_arr[i].takes_data)
            {
                flag_arr[i].data = data;
            }
            flag_arr[i].flagged = true;
            return true;
        }
    }
    return false;
}