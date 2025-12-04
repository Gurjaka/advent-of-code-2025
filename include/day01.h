#ifndef DAY01_H
    #define DAY01_H

    #include <stdbool.h>
    #include "lib.h"

    #define TRACK_SIZE 100

void process_rotation(
    int rotation_distance,
    bool is_left,
    int *current_ptr,
    int *password_counter_ptr,
    enum PART part
);
int solve(char *content, enum PART part);

#endif // DAY01_H
