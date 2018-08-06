#include <errno.h>
#include <buffers.h>
#include <stdbool.h>

#define BINPARSER_MAIN_FILE
#include "binparser.h"

/**
 * @brief parses bindata file putting data into an array
 * 
 * @param file path of file to parse 
 * @return BUFFER(bin_data) buffer to return, returns null on fail
 */
BUFFER(bin_data)
parse_bindata_file(const char *file_path)
{
    bin_data cur_bin_data; // variable for holding bin data to check for errors
    BUFFER(char)
    cur_line;         // buffer for parsing the file_path
    int ret_err;      // variable for catching returned errors
    char *err;        // error string for catching errno
    size_t linecount; // linecount for allocating array
    FILE *fp;         // conf file path for reading configuration
    bin_data *to_ret; // array to return
    // open file and check error in case file not found
    fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        err = strerror(errno);
        fprintf(stderr, "Failed to open %s: %s\n", file_path, err);
        return NULL;
    }
    // count number of lines in file for linecount
    ret_err = fseek(fp, 0, SEEK_END);
    if (ret_err != 0)
    {
        err = strerror(errno);
        fprintf(stderr, "Failed to count lines in %s: %s\n", file_path, err);
        return NULL;
    }
    linecount = ftell(fp);
    if (linecount == -1L)
    {
        err = strerror(errno);
        fprintf(stderr, "Failed to fseek lines in %s: %s\n", file_path, err);
        return NULL;
    }
    // create the buffer to return
    to_ret = buff_new(sizeof *to_ret, linecount);
    // loop over every line adding a new bin_data to it
    for (size_t i = 0; i < linecount; i++)
    {
        // get a line of text into a buffer
        cur_line = buff_new(sizeof *cur_line, 1);
        for (char cc = fgetc(fp); cc != '\n' && cc != EOF; cc = fgetc(fp))
        {
            buff_append(cur_line, cc);
        }
        buff_append(cur_line, '\0');
        // parse the current line, check for errors, and append the bin_data
        cur_bin_data = parse_bindata_line(cur_line);
        if (comp_bindata(cur_bin_data, BIN_DATA_ERR))
        {
            buff_destroy(cur_line);
            buff_destroy(to_ret);
            return NULL;
        }
        buff_append(to_ret, cur_bin_data);
        // free line of text
        buff_destroy(cur_line);
    }
    // close the file and return
    fclose(fp);
    return to_ret;
}

/**
 * @brief parses a line of bindata into a bin_data struct
 * 
 * @param in_line string of bindata conf file to parse
 * @return bin_data struct that was parsed, returns BIN_DATA_ERR on fail
 */
bin_data parse_bindata_line(BUFFER(char) in_line)
{
    int cur_conf;    // current index of conf_arr
    bin_data to_ret; // bin_data to return
    // reset data to get rid of compiler warning
    to_ret.bin_name = NULL;
    to_ret.desktop_file_path = NULL;
    to_ret.icon_file_path = NULL;
    to_ret.bin_path = NULL;
    // an array of struct things to assign from conf
    char *conf_arr[] = {to_ret.bin_name,
                        to_ret.desktop_file_path,
                        to_ret.icon_file_path,
                        to_ret.bin_path};
    // size of conf_arr
    size_t conf_arr_size = sizeof(conf_arr) / sizeof(conf_arr[0]);
    cur_conf = 0;
    conf_arr[cur_conf] = buff_new(sizeof *conf_arr[cur_conf], 1);
    for (buff_iter(i, in_line))
    {
        if (in_line[i] == ':')
        {
            cur_conf += 1;
            if (cur_conf < conf_arr_size)
            {
                buff_append(conf_arr[cur_conf], '\0');
                conf_arr[cur_conf] = buff_new(sizeof *conf_arr[cur_conf], 1);
            }
            else
            {
                fprintf(stderr, "Fatal error parsing conf file: too many ':'\n");
                return BIN_DATA_ERR;
            }
        }
        buff_append(conf_arr[cur_conf], in_line[i]);
    }
    buff_append(conf_arr[cur_conf], '\0');
    return to_ret;
}

/**
 * @brief returns true if equal, false if otherwise
 * 
 * @param left left comparator
 * @param right right comparator
 * @return true structs are equal
 * @return false structs aren't equal
 */
bool comp_bindata(bin_data left, bin_data right)
{
    return (left.bin_name == right.bin_name) && (left.desktop_file_path == right.desktop_file_path) && (left.icon_file_path == right.icon_file_path) && (left.bin_path == right.bin_path);
}
