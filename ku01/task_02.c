#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int
main (int argc, char* argv[])
{
    int32_t a, place, cur_place;
    long long int tmp;
    for (int i = 1; i < argc; i++) {
        cur_place = 0, place = 0;
        
        int32_t loc_max = INT32_MIN, loc_min = INT32_MAX; 
        
        while(cur_place < strlen(argv[i])){
            sscanf(argv[i]+cur_place, "%d%n", &a, &place);
            cur_place += place + 1;
            if (a > loc_max) {
                loc_max = a;
            }
            if (a < loc_min) {
                loc_min = a;
            }
        }
        tmp = (long long)loc_max - (long long)loc_min + 1;
        printf("%lld\n", tmp);
    }
    
}