#ifndef H_BINPARSER
#define H_BINPARSER

#include <buffers.h>

#ifdef BINPARSER_MAIN_FILE
#define ERROR_FILE stderr
#endif

typedef struct bin_data
{
    char *bin_name;
    char *desktop_file_path;
    char *icon_file_path;
    char *bin_path;
} bin_data;

#define BIN_DATA_ERR \
    (bin_data) { NULL, NULL, NULL, NULL }

BUFFER(bin_data)
parse_bindata_file(const char *file_path);
bin_data parse_bindata_line(BUFFER(char) in_line);
bool comp_bindata(bin_data left, bin_data right);

#endif // H_BINPARSER