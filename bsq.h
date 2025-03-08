#ifndef BSQ_H
#define BSQ_H
#include <unistd.h>

struct bsq_map_d
{
    
    int line_len;
    char *file_name;
    char space;
    char obstacle;
    char full;
    char **map_data;
};


#endif
