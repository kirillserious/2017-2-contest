#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum Constants
{
    BUFFER_SIZE = 16,
    INT_LENGTH = 16
};

int
is_num(char);
int
my_atoi(char);

int
main(void)
{
    int minus_fl = 0; 

    char buf[BUFFER_SIZE];
    long long sum = 0;
    long long cur_num = 0;
    ssize_t cnt, i;

    while ((cnt = read(0, buf, BUFFER_SIZE)) > 0) {

        for (i = 0; i < cnt; i++) {

            if (buf[i] == '-') {
                minus_fl = 1;

            } else if (is_num(buf[i])) {
                cur_num = 10 * cur_num + my_atoi(buf[i]);

            } else if (cur_num > 0) {
                if (!minus_fl) {
                    sum += cur_num;

                } else {
                    sum -= cur_num;
                    minus_fl = 0;

                }
                cur_num = 0;
            }
        }
    }
    
    if (!minus_fl) {
        sum += cur_num;
    } else {
        sum -= cur_num;
    }

    printf("%lld\n", sum);
}

int
is_num(char ch)
{
    if((ch >= '0') && (ch <= '9')) {
        return 1;
    }
    return 0;
}

int
my_atoi(char ch)
{
    return ch - '0';
}