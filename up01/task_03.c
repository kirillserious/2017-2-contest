#include <ctype.h>

int mystrspccmp(const char *str1, const char *str2)
{
    while(1)
    {
        if(isspace(*str1))
        {
            str1++;
            continue;
        }

        if(isspace(*str2))
        {
            str2++;
            continue;
        }

        if((*str1 == '\0') && (*str2 != '\0')) return -1;
        if((*str1 != '\0') && (*str2 == '\0')) return 1;
        if((*str1 == '\0') && (*str2 == '\0')) return 0;

        if((unsigned char)*str1 > (unsigned char)*str2) return 1;
        if((unsigned char)*str1 < (unsigned char)*str2) return -1;
        if((unsigned char)*str1 == (unsigned char)*str2)
        {
            str1++;
            str2++;
            continue;
        }
    }
}
