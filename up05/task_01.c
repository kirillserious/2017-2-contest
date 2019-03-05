#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main (int argc, char* argv[])
{
    time_t now_time = time(NULL);

    int days;
    time_t res_time;
    struct tm *timeinfo;

    while (scanf("%d", &days) != EOF) {
        if (__builtin_mul_overflow(days, 24*60*60, &res_time)) {
            printf("OVERFLOW\n");
            continue;
        }

        if (__builtin_add_overflow(now_time, res_time, &res_time)) {
            printf("OVERFLOW\n");
            continue;
        }

        timeinfo = localtime(&res_time);
        printf("%d-", timeinfo->tm_year+1900);
        if (timeinfo->tm_mon+1 < 10) {
            printf("0%d-", timeinfo->tm_mon+1);
        } else {
            printf("%d-", timeinfo->tm_mon+1);
        }
        if(timeinfo->tm_mday < 10) {
            printf("0%d\n", timeinfo->tm_mday);
        } else {
            printf("%d\n", timeinfo->tm_mday);
        }
    }
}
