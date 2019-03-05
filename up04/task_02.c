#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char ALLRIGHTS[] = "rwxrwxrwx";

int
my_atoi(char ch);

int
main (int argc, char* argv[])
{
    int i, j, len, cur, prov;
    char line[10];
    for (i = 1; i < argc; i++) {
        //str to int
        len = strlen(argv[i]);
        cur = 0;
        for (j = 0; j < len; j++) {
                cur <<= 3;
                cur |= my_atoi(argv[i][j]);
        }
        //
        prov = 0400;
        for (j = 0; j < 9; j++) {
            if (cur & prov) {
                line[j] = ALLRIGHTS[j];
            } else {
                line[j] = '-';
            }
            prov >>= 1;
        }
        line[9] = '\0';
        printf("%s\n", line);
    }
}

int
my_atoi(char ch)
{
    return ch - '0';
}
