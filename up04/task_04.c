#include <stdio.h>
#include <stdlib.h>


/*void normalize_path(char *buf);

int main(int argc, char* argv[])
{
    char buf[] = "///a//bgjygjng//////////////";
    normalize_path(buf);
    printf("%s\n", buf);
}
*/
void normalize_path(char *buf)
{
    int slash_num = 0;

    char* i;

    for (; *buf != '\0'; buf++) {
        if (*buf == '/') {
            slash_num ++;

        } else if (slash_num > 0) {

            for (i = buf; *i != '\0'; i++){
                *(i - slash_num + 1) = *i;
            }
            *(i - slash_num + 1) = '\0';
            buf -= slash_num -1;
            slash_num = 0;           
        }
    }
    if (slash_num > 0) {
        *(buf - slash_num + 1) = '\0';
    }
}