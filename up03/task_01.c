#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
    double sum = atof(argv[1]);
    double proc_dep = (atof(argv[2]) + 100) / 100;
    double proc_crd = (atof(argv[3]) + 100) / 100;

    int i;
    for (i = 4; i < argc; i++) {
        sum += atof(argv[i]);
        if (sum >= 0) {
            sum *= proc_dep;
        } else {
            sum *= proc_crd;
        }
    } 

    printf("%.10g\n", sum);
    return 0;
}