#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "lib.h"

void open_input(const char *input_path, char *content, size_t buf_size)
{
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fgets(content, buf_size - 1, file);

    fclose(file);
}

bool repeats(const char *buff, int len, int p)
{
    const char *first = buff;

    for (int off = p; off < len; off += p) {
        if (memcmp(first, buff + off, p) != 0)
            return false;
    }
    return true;
}

bool is_invalid_id(long long num, enum PART part)
{
    if (num <= 0)
        return false;

    char buff[30];
    int len = snprintf(buff, sizeof(buff), "%lld", num);

    if (part == PART_1) {
        if (len % 2 != 0)
            return false;

        int half_len = len / 2;

        if (memcmp(buff, buff + half_len, half_len) == 0)
            return true;
    } else if (part == PART_2) {
        for (int p = 1; p <= len / 2; p++)
            if (len % p == 0 && repeats(buff, len, p)) return true;
    }

    return false;
}

void invalid_id(
    long long num_1,
    long long num_2,
    unsigned long long *total,
    enum PART part
) {
    for (long long cur_id = num_1; cur_id <= num_2; cur_id++) 
        if (is_invalid_id(cur_id, part))
            *total += cur_id;
}

void handle_reset(long long *num, char *buf, int buf_size, int *i)
{
    *num = atoll(buf);
    memset(buf, 0, buf_size);
    *i = 0;
}

unsigned long long solution(char *content, enum PART part)
{
    unsigned long long total = 0;
    int j = 0;
    char temp[256];
    long long num_1 = 0;
    long long num_2 = 0;

    for (int i = 0; content[i] != '\0'; i++) {
        switch (content[i]) {
            case ',':
                handle_reset(&num_2, temp, sizeof temp, &j);
                invalid_id(num_1, num_2, &total, part);
                num_1 = 0;
                break;
            case '-':
                handle_reset(&num_1, temp, sizeof temp, &j);
                break;
            default:
                temp[j++] = content[i];
                break;
        }
    }

    if (j > 0) {
        handle_reset(&num_2, temp, sizeof temp, &j);
        invalid_id(num_1, num_2, &total, part);
    }

    return total;
}

int main(void)
{
    const char *input_file = "input.txt";


    printf("\n--- Processing Day ---\n");
    char content[1024];
    open_input(input_file, content, sizeof(content));

    unsigned long long result1 = solution(content, PART_1);
    unsigned long long result2 = solution(content, PART_2);

    printf("Part 1 Result: %lld\n", result1);
    printf("Part 2 Result: %lld\n", result2);

    return EXIT_SUCCESS;
}
