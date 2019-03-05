#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char* argv[])
{
    int count, low, high;
    unsigned seed;

    sscanf(argv[1], "%d", &count);
    sscanf(argv[2], "%d", &low);
    sscanf(argv[3], "%d", &high);
    sscanf(argv[4], "%u", &seed);

    srand(seed);



    for (int i = 0; i < count; i++) {
        printf("%d\n", (int)((double)rand() * (high-low) / (RAND_MAX+1.0)) + low);
    }
    return 0;
}