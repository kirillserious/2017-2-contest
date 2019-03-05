#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int
main(int argc, char const *argv[])
{
    char line[PATH_MAX];
    long long sum = 0;
    while( fgets(line, PATH_MAX, stdin) != NULL) {
        long long start, finish;
        sscanf(line, "%llx-%llx", &start, &finish);
        sum += finish - start;
    }
    printf("%lld\n", sum);
    return 0;
}