#ifndef DAY05_H
    #define DAY05_H

    #include <stdio.h>

// Function prototypes
void convert(size_t *num, char *buf, int buf_size, int *i);
int get_range(char *content, size_t (*arr)[2]);
void get_id(char *content, size_t *arr, int blank);
int cmp(const void *a, const void *b);

#endif // DAY05_H
