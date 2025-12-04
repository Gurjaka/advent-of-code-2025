#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day01.h"

void open_input(const char *input_path, char *content, size_t buf_size)
{
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(content, 1, buf_size - 1, file);
    content[bytes_read] = '\0';

    fclose(file);
}

void process_rotation(
    int rotation_distance,
    bool is_left,
    int *current_ptr,
    int *password_counter_ptr,
    enum PART part
) {
    int current = *current_ptr;
    int password_count = *password_counter_ptr;

    if (part == PART_1) {
        if (is_left)
            current -= rotation_distance;
        else
            current += rotation_distance;

        current = (current % 100 + 100) % 100;

        if (current == 0)
            password_count++;

        goto finalize;
    }

    if (is_left) {
        if (current == 0) {
            if (rotation_distance > 0) {
                int cycles = (rotation_distance + TRACK_SIZE - 1) / TRACK_SIZE;
                password_count += cycles - 1;
            }
        } else if (rotation_distance >= current) {
            int magnitude_past_zero = rotation_distance - current + 1;
            password_count += (magnitude_past_zero + TRACK_SIZE - 1) / TRACK_SIZE;
        }

        current -= rotation_distance;
    } else {
        password_count += (current + rotation_distance) / TRACK_SIZE;
        current += rotation_distance;
    }

    current = (current % TRACK_SIZE + TRACK_SIZE) % TRACK_SIZE;

finalize:
    *current_ptr = current;
    *password_counter_ptr = password_count;
}

int solve(char *content, enum PART part)
{
    char temp[256];
    int current = 50;
    int j = 0;
    int password_count = 0;
    bool is_left_rotation = false;

    for (int i = 0; content[i] != '\0'; i++) {
        switch (content[i]) {
            case 'L':
                is_left_rotation = true;
                break;
            case 'R':
                is_left_rotation = false;
                break;
            case '\n':
                temp[j] = '\0';
                int rotation_distance = atoi(temp);
                process_rotation(rotation_distance, is_left_rotation, &current, &password_count, part);

                j = 0;
                break;
            default:
                if (j < (int)sizeof(temp) - 1)
                temp[j++] = content[i];
                break;
        }
    }

    if (j > 0) {
        temp[j] = '\0';
        int rotation_distance = atoi(temp);
        process_rotation(rotation_distance, is_left_rotation, &current, &password_count, part);
    }

    return password_count;
}

int main(void)
{
    const char *input_file = "input.txt";

    printf("\n--- Processing Day ---\n");
    char content[30000];
    open_input(input_file, content, sizeof(content));
    int result1 = solve(content, PART_1);
    int result2 = solve(content, PART_2);

    printf("Part 1 Result: %d\n", result1);
    printf("Part 2 Result: %d\n", result2);

    return EXIT_SUCCESS;
}
