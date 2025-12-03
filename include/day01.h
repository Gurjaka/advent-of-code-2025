#ifndef DAY01_H
    #define DAY01_H

    #include <stdio.h>
    #include <stdbool.h>
    #define TRACK_SIZE 100

enum PART {
    PART_1,
    PART_2
};

char *open_input(const char *input_path, char *content, size_t buf_size);
void process_rotation(
    int rotation_distance,
    bool is_left,
    int *current_ptr,
    int *password_counter_ptr,
    enum PART part
);
int solve(char *content, enum PART part);

#endif // DAY01_H
