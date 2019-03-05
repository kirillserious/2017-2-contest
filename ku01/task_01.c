#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

enum
{
    MASKSEVEN = 0x7F,
    MASKEIGHT = 0x80,
    OFFSET = 7
};

int
main(int argc, char *argv[])
{
    uint32_t a;
    while(scanf("%" SCNu32, &a) == 1) {
        
        do {
            uint32_t cur = a & MASKSEVEN;
            if (a != cur) {
                cur |= MASKEIGHT;

            }
            printf("%02x ", cur);
            a >>= OFFSET;
        } while (a > 0);

        printf("\n");
    }

return 0;
}