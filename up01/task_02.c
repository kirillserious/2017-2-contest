#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned int number;
    unsigned int MAX = 0xFFFFFF;
    while(scanf("%u", &number) != EOF)
    {
        if (number != 0){
            while((number&1) == 0) number>>=1;
            if(number <= MAX) printf("1\n");
                else printf("0\n");
        }else printf("1\n");
    }
}
