#include "bsq.h"
#include <stdio.h>

void print_map_data(const bsq_map_d *map) {
    if (map == NULL) {
        printf("map is NULL\n");
        return;
    }

    printf("line_len: %d\n", map->line_len);
    printf("col_len: %d\n", map->col_len);
    printf("map_start_index: %d\n", map->map_start_index);

    // file_name NULL olabilir, kontrol et
    if (map->file_name != NULL) {
        printf("file_name: %s\n", map->file_name);
    } else {
        printf("file_name: (NULL)\n");
    }

    printf("space: %c\n", map->space);
    printf("obstacle: %c\n", map->obstacle);
    printf("full: %c\n", map->full);

    // map_data'yı YAZDIRMIYORUZ, çünkü soruda istenmiyor
    // printf("map_data: %p\n", (void *)map->map_data); // Sadece adresini yazdırabiliriz (isteğe bağlı)
}