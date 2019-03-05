#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char const *argv[])
{
    long long w_sum = 0;
    long long x_sum = 0;
    while (1) {
        long long start = 0;
        long long finish = 0;
        
        scanf("%llx-%llx", &start, &finish);

        int c;
        c = fgetc(stdin);
        c = fgetc(stdin);
        c = fgetc(stdin);
        if (c == 'w') {

            w_sum += finish - start;
        }
        
        c = fgetc(stdin);
        if (c == 'x') {
            x_sum += finish - start;
        }
        while (((c = fgetc(stdin)) != EOF) && (c != '\n'));
        if (c == EOF) {
            break;
        }

    }
    printf("%lld\n%lld\n", w_sum, x_sum);
    return 0;
}