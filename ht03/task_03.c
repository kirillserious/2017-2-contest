#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

const char libpath[] = "/lib/libm.so.6";

int
main (int argc, char* argv[])
{
    void *handle;
    if ( (handle = dlopen(libpath, RTLD_NOW)) == NULL) {
        printf("err 1\n");
        return 1;
    }

    double (*func)(double) = NULL;
    if ( (func = dlsym(handle, argv[1])) == NULL) {
        printf("err 2\n");
        return 2;
    }

    double cur;
    while ( scanf("%lf", &cur) != EOF) {
        printf("%.10g\n", (*func)(cur));
    }

    dlclose(handle);
    return 0;
}