#ifndef H_FLAGS
#define H_FLAGS

#include <stdio.h>
#include <stdbool.h>

typedef struct flag {
    char flag_char;
    char * data;
    bool takes_data;
    bool flagged;
} flag;

void print_flag(FILE * fp, flag f);

bool check_flag_structs(char in_char, flag * flag_arr, char * data, 
        size_t arr_sz);

#define new_flag(c, d) (flag){c, NULL, d, false}

#endif // H_FLAGS