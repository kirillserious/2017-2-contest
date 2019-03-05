#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum
{
    TAGB = 10,
    PAGE_MAX = 1 << 10,
    PAGE_SIZE = 4096,
};

int get_page_num(int n)
{
    return (unsigned)n >> (sizeof(n) * 8 - TAGB);
}

int
main (int argc, char *argv[])
{
    char arr[PAGE_MAX];
    int num = 0;
    memset(arr, 0, sizeof(arr));

    int start, finish;
    while (scanf("%x-%x", &start, &finish) == 2) {
        int c; 
        do{
            c = fgetc(stdin);
        } while (c != EOF && c != '\n');

        finish = get_page_num(finish-1);
        for (int i = get_page_num(start); i <= finish; i++) {
            
            if (arr[i] == 0) {
                num++;
                arr[i]++;
            }
        }
    }

    num = !num ? 0 : num *PAGE_SIZE + PAGE_SIZE;
    printf("%d\n", num);

    return 0;
}