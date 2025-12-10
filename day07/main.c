#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

enum PART {
   PART_1,
   PART_2
};

void open_input(
    const char *input_path,
    char (*content)[LINE_MAX],
    size_t buf_size
) {
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < LINE_MAX && fgets(content[i++], LINE_MAX, file));

    content[i][0] = '\0';

    fclose(file);
}

int process_split_p1(
    char (*content)[LINE_MAX],
    int *index_arr,
    int *next_arr,
    int row,
    int *count
) {
    bool seen[LINE_MAX] = {false};
    int row_len = strlen(content[row]);
    int next_len = 0;

    for (int j = 0, id; (id = index_arr[j]) != -1; j++) {
        if (id < 0 || id >= row_len) continue;

        char c = content[row][id];

        if (c == '^') {
            if (!seen[id]) {
                (*count)++;
                seen[id] = true;
            }

            if (id - 1 >= 0 && !seen[id - 1])
                next_arr[next_len++] = id - 1;

            if (id + 1 < row_len && !seen[id + 1]) 
                next_arr[next_len++] = id + 1;

        } else if (!seen[id] && next_len < LINE_MAX) {
            next_arr[next_len++] = id;
            seen[id] = true;
        }
    }

    return next_len;
}

void process_split_p2(
    char (*content)[LINE_MAX],
    unsigned long long *timeline_counts,
    unsigned long long *next_counts,
    int row
) {
    int row_len = strlen(content[row]);

    for (int id = 0; id < row_len; id++) {
        if (timeline_counts[id] == 0) continue;

        char c = content[row][id];
        unsigned long long count = timeline_counts[id];

        if (c == '^') {
            if (id - 1 >= 0) next_counts[id - 1] += count;
            if (id + 1 < row_len) next_counts[id + 1] += count;
        } else next_counts[id] += count;
    }
}

unsigned long long solution(char content[256][LINE_MAX], enum PART part)
{
    char input[256][LINE_MAX];
    for (int i = 0; i < 256; i++) strcpy(input[i], content[i]);

    int start = 0;
    for (; input[0][start] != 'S'; start++);

    if (input[0][start] != 'S') return 0;

    if (part == PART_1) {
        int index_arr[LINE_MAX] = {start};
        for (int i = 1; i < LINE_MAX; i++) index_arr[i] = -1;

        int count = 0;

        for (int row = 1; input[row][0] != '\0'; row++) {
            int next_arr[LINE_MAX];
            for (int i = 0; i < LINE_MAX; i++) next_arr[i] = -1;

            process_split_p1(input, index_arr, next_arr, row, &count);

            for (int i = 0; i < LINE_MAX; i++) index_arr[i] = next_arr[i];
        }

        return (unsigned long long)count;
    } else {
        unsigned long long timeline_counts[LINE_MAX] = {0};
        timeline_counts[start] = 1;

        for (int row = 1; input[row][0] != '\0'; row++) {
            unsigned long long next_counts[LINE_MAX] = {0};

            process_split_p2(input, timeline_counts, next_counts, row);

            memcpy(timeline_counts, next_counts, sizeof(timeline_counts));
        }

        unsigned long long total = 0;
        for (int i = 0; i < LINE_MAX; i++) total += timeline_counts[i];

        return total;
    }
}

int main(void)
{
    const char *input_file = "input.txt";

    printf("\n--- Processing Day ---\n");
    char content[256][LINE_MAX];
    open_input(input_file, content, sizeof(content));

    unsigned long long result1 = solution(content, PART_1);
    unsigned long long result2 = solution(content, PART_2);

    printf("Part 1 Result: %lld\n", result1);
    printf("Part 2 Result: %lld\n", result2);

    return EXIT_SUCCESS;
}
