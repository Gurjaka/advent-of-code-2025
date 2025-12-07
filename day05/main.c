#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum PART {
    PART_1,
    PART_2
};

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

void convert(size_t *num, char *buf, int buf_size, int *i)
{
    *num = atol(buf);
    memset(buf, 0, buf_size);
    *i = 0;
}

int get_range(char *content, size_t (*arr)[2])
{
    char temp[256];
    int j = 0;
    int num = 0;
    int i = 0;
    for (; content[i] != '\0'; i++) {
        switch (content[i]) {
            case '-':
                convert(&arr[num][0], temp, sizeof temp, &j);
                break;
            case '\n':
                convert(&arr[num][1], temp, sizeof temp, &j);
                num++;
                if (content[i + 1] == '\n') {
                    i += 2;  // Skip both newlines
                    goto done;
                }
                break;
            default:
                temp[j++] = content[i];
                break;
        }
    }
done:
    arr[num][0] = -1;
    arr[num][1] = -1;

    return i;
}

void get_id(char *content, size_t *arr, int blank)
{
    char temp[256];
    int j = 0;
    int num = 0;

    for (int i = blank; content[i] != '\0'; i++) {
        if (content[i] == '\n') {
            convert(&arr[num], temp, sizeof temp, &j);
            num++;
            continue;
        }
        temp[j++] = content[i];
    }

    if (j > 0) {
        convert(&arr[num], temp, sizeof temp, &j);
        num++;
    }

    arr[num] = -1;
}

int cmp(const void *a, const void *b) {
    const size_t (*r1)[2] = a;
    const size_t (*r2)[2] = b;

    // Sort by first element ascending
    if ((*r1)[0] < (*r2)[0]) return -1;
    if ((*r1)[0] > (*r2)[0]) return 1;

    return 0;
}

size_t solution(
    char *content,
    size_t (*range_arr)[2],
    size_t *id_arr,
    enum PART part
) {
    size_t fresh = 0;

    if (part == PART_1) {
        for (int i = 0; id_arr[i] != (size_t)-1; i++)
            for (int j = 0; range_arr[j][0] != (size_t)-1; j++)
                if (id_arr[i] >= range_arr[j][0] && id_arr[i] <= range_arr[j][1]) {
                    fresh++;
                    break;
                }

    } else if (part == PART_2) {
        int num_ranges = 0;

        while (range_arr[num_ranges][0] != (size_t)-1)
            num_ranges++;

        qsort(range_arr, num_ranges, sizeof range_arr[0], cmp);

        size_t last[2] = {-1, -1};

        for (int i = 0; i < num_ranges; i++) {
            size_t low = range_arr[i][0];
            size_t high = range_arr[i][1];

            if (last[0] == (size_t)-1 && last[1] == (size_t)-1) {
                last[0] = low;
                last[1] = high;
            } else if (low > last[1]) {
                fresh += last[1] - last[0] + 1;
                last[0] = low;
                last[1] = high;
            } else
                last[1] = high > last[1] ? high : last[1];
        }

        fresh += last[1] - last[0] + 1;
    }

    return fresh;
}

int main(void)
{
    const char *input_file = "input.txt";

    printf("\n--- Processing Day ---\n");
    char content[30000];
    open_input(input_file, content, sizeof(content));

    size_t range_arr[BUFSIZ][2];
    size_t id_arr[BUFSIZ];

    int blank = get_range(content, range_arr);
    get_id(content, id_arr, blank);

    size_t result1 = solution(content, range_arr, id_arr, PART_1);
    size_t result2 = solution(content, range_arr, id_arr, PART_2);

    printf("Part 1 Result: %zd\n", result1);
    printf("Part 2 Result: %ld\n", result2);

    return EXIT_SUCCESS;
}
