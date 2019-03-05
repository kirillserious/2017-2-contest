#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

enum Constants
{
    BASE = 10
};

int
main (int argc, char* argv[])
{
    
    long unsigned int cur;
    uint32_t u_cur;
    char *ptr;

    int is_null, is_nonumber, is_x32overfl, is_x64overfl;

    int i;
    for (i = 1; i < argc; i++){
        errno = 0;
        cur = strtoul(argv[i], &ptr, BASE);

        is_null = ( argv[i][0] == '\0' );
        is_nonumber = ( *ptr != '\0');
        is_x32overfl = ( cur ==  ULONG_MAX && errno == ERANGE );
        is_x64overfl = ( cur > UINT32_MAX );
        
        if (is_null || is_nonumber || is_x32overfl || is_x64overfl) {
            printf("-1\n");
            
        } else {
            u_cur = (uint32_t)cur;

            int j;
            for (j = 0; u_cur > 0; j++) {
                u_cur >>= 1;

            }

            printf("%d\n", j);
        }
        
    }
}

