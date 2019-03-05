#include <stdio.h>
#include <stdlib.h>

enum Constants
{
    STRSIZE = 3004
};

int 
main(int argc, char* argv[])
{
    int n, w;
    scanf("%d%d", &n, &w);

    int cur;
    int max = (1 << n);
    int sign_mask = (1 << (n-1));
    
    //create bit mask
    int i;
    int mask = 1;
    for (i = 0; i < n-1; i++) {
        mask <<= 1;
        mask++;
    }
    mask = (~mask);

    //print cycle
    for (cur = 0; cur < max; cur++) {
        printf("|%*d|%*x|%*d|\n", w, cur, w, cur, w, (cur & sign_mask) ? (cur | mask) : cur);
    }
}
