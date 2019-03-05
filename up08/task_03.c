#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

enum
{
    BUFFSIZE = 8,
    NPROC = 3
};

int
main (int argc, char* argv[])
{
    setbuf(stdout, NULL);

    pid_t son;
    for (int i = 1; i <= NPROC; i++) {
        son = fork();
        if (!son) {
            char line[BUFFSIZE];
            long long int num;
            read(STDIN_FILENO, line, sizeof(line));
            line[BUFFSIZE - 1] = '\0';
            sscanf(line, "%lld", &num);
            printf("%d %lld\n", i, num*num);
            fflush(stdout);
            exit(0);
        }
    }

    for (int i = 1; i <= NPROC; i++) {
        while (wait(NULL) == -1);
    }
    exit(0);

}