#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void add_voltage(const char *content, int n, size_t *total)
{
    int len = strlen(content);
    int start = 0;
    char num[20];

    for (int i = 0; i < n; i++) {
        char max_digit = '0';
        int max_pos = start;
        int end = len - (n - i);

        for (int j = start; j < end; j++) {
            if (content[j] > max_digit) {
                max_digit = content[j];
                max_pos = j;
            }
        }

        num[i] = max_digit;
        start = max_pos + 1;
    }

    num[n] = '\0';
    *total += atol(num);
}

size_t solution(const char *input_path, int n)
{
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t size = 0;
    ssize_t nread;
    size_t total = 0;

    while ((nread = getline(&line, &size, file)) > 0)
        add_voltage(line, n, &total);

    fclose(file);

    return total;
}


int main(void)
{
    const char *input_file = "input.txt";

    printf("\n--- Processing Day ---\n");
    size_t result1 = solution(input_file, 2);
    size_t result2 = solution(input_file, 12);

    printf("Part 1 Result: %ld\n", result1);
    printf("Part 2 Result: %ld\n", result2);

    return EXIT_SUCCESS;
}
