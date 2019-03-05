#include <stdio.h>
#include <stdlib.h>

enum Constants 
{
    BUFFER_SIZE = 16384
};

typedef struct Elem
{
    double fval;
    int ival;
    int pos;
} Elem;

int 
compare(const Elem *, const Elem *);

Elem arr[BUFFER_SIZE];

int 
main(void)
{
    int num = 0;
    while (scanf("%lf%d", &(arr[num].fval), &(arr[num].ival)) != EOF){
        arr[num].pos = num;
        num++;
    }

    qsort(arr, num, sizeof(Elem), (int(*) (const void *, const void *))compare);

    int j;
    for(j = 0; j < num; j++){
        printf("%.10g %d\n", arr[j].fval, arr[j].ival);
    }
    
}

int 
compare(const Elem *a, const Elem *b)
{
    if ( a->fval > b->fval ) {
        return 1;
    }
    if ( a->fval < b->fval ) {
        return -1;
    }
    if ( a->pos > b->pos) {
        return 1;
    }
    return -1;
}
