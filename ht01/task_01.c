#include <stdint.h>

int32_t 
satsum(int32_t a, int32_t b)
{
    int32_t res;
    if (!__builtin_add_overflow(a, b, &res)) {
        return res;

    } else {
        uint32_t zero = 0;

        if (a > 0) {
            return ((~zero) >> 1);
        
        } else {
            return ~((~zero) >> 1);

        }
    }     
}



