#ifndef DAY02_H
    #define DAY02_H

    #include <stdbool.h>
    #include "lib.h"

// Function prototypes
bool repeats(const char *buff, int len, int p);
bool is_invalid_id(long long num, enum PART part);
void invalid_id(
    long long num_1,
    long long num_2,
    unsigned long long *total,
    enum PART part
);
void handle_reset(long long *num, char *buf, int buf_size, int *i);
long solution(char *content, enum PART part);

#endif // DAY02_H
