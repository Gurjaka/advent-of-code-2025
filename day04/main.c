#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include "lib.h"

void open_input(const char *input_path, char (*content)[LINE_MAX])
{
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < LINE_MAX && fgets(content[i++], LINE_MAX, file));

    fclose(file);
}

int count_neighbors(
    char (*content)[LINE_MAX],
    int i,
    int j,
    int rows,
    int cols,
    enum PART part
) {
    int neighbors = 0;

    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;

            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && content[ni][nj] == '@') {
                neighbors++;
            }
        }
    }

    return neighbors;
}

int solution(char (*input)[LINE_MAX], enum PART part)
{
    char content[LINE_MAX][LINE_MAX];

    int total = 0;
    int rows = strlen(input[0]), cols = strlen(input[0]) - 1;

    for (int i = 0; i < rows; i++) {
        memcpy(content[i], input[i], cols + 1);
    }

    while (true) {
        bool changed = false;
        bool to_remove[LINE_MAX][LINE_MAX] = {false};

        for (int i = 0; content[i][0] != '\0'; i++)
            for (int j = 0; content[i][j] != '\n'; j++)
                if (content[i][j] == '@' && count_neighbors(content, i, j, rows, cols, part) < 4)
                    to_remove[i][j] = true;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (to_remove[i][j]) {
                    content[i][j] = '.';
                    total++;
                    changed = true;
                }
            }
        }

        if (part == PART_2 && changed)
            continue;

        break;
    }

    return total;
}

int main(void)
{
    const char *input_file = "input.txt";

    printf("\n--- Processing Day ---\n");
    char content[LINE_MAX][LINE_MAX];
    open_input(input_file, content);

    int result1 = solution(content, PART_1);
    int result2 = solution(content, PART_2);
    printf("Part 1 Result: %d\n", result1);
    printf("Part 2 Result: %d\n", result2);

    return EXIT_SUCCESS;
}
