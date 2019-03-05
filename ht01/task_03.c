#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int
compare (const void *aIn, const void *bIn, void *thunk)
{
    int a = *((int*)aIn);
    int b = *((int*)bIn);
    int *data = (int*)thunk;

    if (data[a] > data[b]) {
        return 1;

    } else if (data[a] == data[b]) {
        if (a > b) {
            return 1;

        } else {
            return -1;
            
        }

    } else {
        return -1;

    }
}

void
process (size_t count, int *data, int *order)
{
    for (int i = 0; i < count; i++) {
        order[i] = i;
    }

    qsort_r(order, count, sizeof(int), compare, data);
}

