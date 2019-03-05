#include <stdlib.h>
#include <stdio.h>

enum Constants
{
    STANDA = 1103515245,
    STANDC = 12345,
    STANDMOD = 0x80000000
};

typedef struct RandomGenerator
{
    long long prev;
    long long a;
    long long c;
    long long mod;
    struct RandomOptions *ops;
} RandomGenerator;

struct RandomOptions
{
    int (*next)(RandomGenerator*);
    void (*destroy)(RandomGenerator*);
};

int 
next (RandomGenerator *rg)
{
    return (rg) ? rg->prev = (rg->a * rg->prev + rg->c) % rg->mod : -1;
}

void
destroy (RandomGenerator *rg)
{
    free(rg);
}

struct RandomOptions ro = {next, destroy};

RandomGenerator*
random_create (long long prev)
{   
    RandomGenerator *rg = NULL;
    rg = calloc(1, sizeof(RandomGenerator));
    if (rg) {
            rg->prev = prev;
            rg->a = STANDA;
            rg->c = STANDC;
            rg->mod = STANDMOD;
            rg->ops = &ro;
    }

    return rg;
}