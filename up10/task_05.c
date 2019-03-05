#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main (int argc, char *argv[])
{

    setbuf(stdout, NULL);
    int first[2];
    int second[2];
    pipe(first);
    pipe(second);

    long int max = strtol(argv[1], NULL, 10);

    if (!fork()) {
        close(first[1]);
        close(second[0]);
        FILE *fin = fdopen(first[0], "r");
        FILE *fout = fdopen(second[1], "w");

        int cur;
        while(1){           
            if (fscanf(fin, "%d", &cur) != 1){
                close(first[0]);
                close(second[1]);
                exit(0);
            }

            if (cur >= max) {
                fprintf(fout, "%d ", cur);
                fflush(fout);
                close(first[0]);
                close(second[1]);
                exit(0);
            }
            printf("1 %d\n", cur);
            fflush(stdout);
            cur++;
            fprintf(fout, "%d ", cur);
            fflush(fout);

        } 
    }

    if (!fork()) {
        close(first[0]);
        close(second[1]);

        FILE *fin = fdopen(second[0], "r");
        FILE *fout = fdopen(first[1], "w");

        int cur = 1;
        while(1){
            fprintf(fout, "%d ", cur);
            fflush(fout);
            if (fscanf(fin, "%d", &cur) != 1){
                close(first[1]);
                close(second[0]);
                exit(0);
            }
            if (cur >= max) {
                fprintf(fout, "%d ", cur);
                fflush(fout);
                close(first[1]);
                close(second[0]);
                exit(0);

            }
            printf("2 %d\n", cur);
            fflush(stdout);
            cur++;

        } 
    }

    
    for (int i = 0; i < 2; i++) {
        while(wait(NULL) == -1);
    }
    printf("Done\n");
    fflush(stdout);
    
    return 0;
}