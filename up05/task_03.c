#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <time.h>

int get_tm (struct tm*);

enum Constants
{
    LENGTH_MAX = 1000
};

FILE *fd;

int main(int argc, char* argv[])
{
    fd = fopen(argv[1], "r");

    struct tm time1, time2;
    time_t sec_time1, sec_time2;

    get_tm(&time1);

    sec_time1 = mktime(&time1);

    while (get_tm(&time2)) {
        sec_time2 = mktime(&time2);
        printf("%ld\n", sec_time2 - sec_time1);
        sec_time1 = sec_time2;
        time1 = time2;
    }
}

int get_tm(struct tm *time1)
{
    char line[LENGTH_MAX];
    memset(time1, 0, sizeof(*time1));
 
    if (fgets(line, sizeof(line), fd) == NULL || line[0] == '\n') {
        return 0;
    }

    sscanf(line, 
        "%d/%02d/%02d %02d:%02d:%02d", 
        &time1->tm_year,
        &time1->tm_mon,
        &time1->tm_mday,
        &time1->tm_hour,
        &time1->tm_min,
        &time1->tm_sec);


    time1->tm_isdst = -1;
    time1->tm_year -= 1900;
    time1->tm_mon  -= 1;

    return 1;
}