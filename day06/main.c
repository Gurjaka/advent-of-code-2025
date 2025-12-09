#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum PART {
    PART_1,
    PART_2
};

int open_input(const char *input_path, char (*content)[4096])
{
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < 4096 && fgets(content[i++], 4096, file));

    content[i][0] = '\0';

    fclose(file);

    return i - 1;
}

void convert(
    size_t (*arr)[4096],
    char *num,
    int num_size,
    int *iter,
    int line,
    int count
) {
    if (*iter >= num_size)
        num[num_size - 1] = '\0';
    else
        num[*iter] = '\0';

    arr[line][count] = (size_t) strtoul(num, NULL, 10);
    memset(num, 0, num_size);
    *iter = 0;
}

void parse_numbers(
    char (*content)[4096],
    size_t (*arr)[4096],
    int end,
    enum PART part
) {
    char temp[20] = { '\0' };
    int j = 0;

    if (part == PART_1) {
        int count = 0;

        for (int line = 0; line < end; line++) {
            for (int c = 0; content[line][c] != '\n'; c++) {
                if (content[line][c] == ' ' && temp[0] != '\0') {
                    convert(arr, temp, sizeof(temp), &j, line, count);
                    count++;
                }

                if (content[line][c] == ' ')
                    continue;

                temp[j++] = content[line][c];
            }

            convert(arr, temp, sizeof(temp), &j, line, count);
            count++;
            arr[line][count] = 0;
            count = 0;
        }
    } else if (part == PART_2) {
        int last_c = 0;
        while (content[0][last_c] != '\n') last_c++;
        last_c--;

        int row = 0;
        int col = 0;

        for (; last_c >= 0; last_c--) {
            bool found_digit = false;

            for (int line = 0; line < end; line++)
                if (content[line][last_c] != ' ') {
                    temp[j++] = content[line][last_c];
                    found_digit = true;
                }

            if (found_digit) {
                convert(arr, temp, sizeof(temp), &j, row, col);
                row++;
            } else if (row > 0){
                col++;
                row = 0;
            }
        }
    }
}

void parse_operators(
    char (*content)[4096],
    char *arr,
    int line,
    enum PART part
) {
    int count = 0;

    if (part == PART_1) {
        for (int i = 0; content[line][i] != '\n'; i++) {
            if (content[line][i] == ' ')
                continue;

            arr[count++] = content[line][i];
        }
    } else if (part == PART_2) {
        int last = 0;
        while (content[0][last] != '\n') last++;
        last--;

        for (; last >= 0; last--) {
            if (content[line][last] == ' ')
                continue;

            arr[count++] = content[line][last];
        }
    }

    arr[count] = '\0';
}

size_t solution(char (*content)[4096], int op_line, enum PART part)
{
    size_t num_arr[256][4096];
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 4096; j++)
            num_arr[i][j] = 0;

    char op_arr[4096];

    parse_numbers(content, num_arr, op_line, part);
    parse_operators(content, op_arr, op_line - 1, part);

    size_t total = 0;
    size_t last = 0;

    for (int i = 0; op_arr[i] != '\0'; i++) {
        for (int line = 0; line < op_line - 1; line++) {
            size_t v = num_arr[line][i];
            if (v == 0)
                continue;
            switch (op_arr[i]) {
                case '+':
                    last += v;
                    break;
                case '*':
                    last = last == 0 ? v : last * v;
                    break;
                default:
                    break;
            }
        }
        total += last;
        last = 0;
    }

    return total;
}

int main(void)
{
    const char *input_file = "input.txt";

    printf("\n--- Processing Day ---\n");
    char content[256][4096];
    int op_line = open_input(input_file, content);

    size_t result1 = solution(content, op_line, PART_1);
    size_t result2 = solution(content, op_line, PART_2);

    printf("Part 1 Result: %zd\n", result1);
    printf("Part 2 Result: %zd\n", result2);

    return EXIT_SUCCESS;
}
