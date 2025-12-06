#ifndef DAY04_H
    #define DAY04_H

    #include <limits.h>
    #include "lib.h"

// Function prototypes
int count_neighbors(
    char (*content)[LINE_MAX],
    int i,
    int j,
    int rows,
    int cols,
    enum PART part
);

#endif // DAY04_H
