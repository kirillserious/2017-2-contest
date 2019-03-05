#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int fd[2];
volatile long int max;
volatile pid_t pid1 = 0, pid2 = 0;
FILE *fin, *fout;

void
handler(int sig)
{
    signal(SIGUSR1, handler);

    if ((!pid1) && (!pid2)) {
        fscanf(fin, "%d", &pid2);
        fprintf(fout, "1 ");
        fflush(fout);
        kill(pid2, SIGUSR1);
    } else {
        int x;
        fscanf(fin, "%d", &x);
        if (x < max) {
            printf("%d %d\n", (pid1) ? 1 : 2, x);
            fflush(stdout);
        }
        fprintf(fout, "%d ", x+1);
        fflush(fout);
        kill((pid1) ? pid1 : pid2, SIGUSR1);
        if (x >= max){
            exit(0);
        }
    }

    return;
}


int
main (int argc, char *argv[])
{

    max = strtol(argv[1], NULL, 10);
    pipe(fd);
    fin = fdopen(fd[0], "r");
    fout = fdopen(fd[1], "w");

    signal(SIGUSR1, handler);
    
    pid1 = fork();
    if (!pid1) {    
        while (1) {
            pause();
        }
    }

    pid2 = fork();
    if (!pid2) {
        while (1) {
            pause();
        }
    }
    fprintf(fout, "%d ", pid2);
    fflush(fout);
    kill(pid1, SIGUSR1);

    close(fd[0]);
    close(fd[1]);
    fclose(fin);
    fclose(fout);

    wait(NULL);
    wait(NULL);

    printf("Done\n");
    fflush(stdout);

    return 0;
}