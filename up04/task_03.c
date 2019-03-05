#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char RIGHTS[] = "rwxrwxrwx";

int
parse_rwx_permissions(const char *str)
{
    if ((str == NULL)||(strlen(str) != sizeof(RIGHTS)-1)){
        return -1;
    }

    int cur = 0;

    int i;
    for (i = 0; i < sizeof(RIGHTS)-1; i++) {
        if(str[i] == RIGHTS[i]) {
            cur <<= 1;
            cur |= 1;

        } else if (str[i] == '-') {
            cur <<= 1;

        } else {
            return -1;

        }
    }

    return cur;
}
