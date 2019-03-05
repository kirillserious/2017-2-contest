#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/limits.h>

int
main (int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    if (!fork()) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        
        if (!fork()) {
            int file = open(argv[4], O_RDONLY);
            dup2(file, 0);
            close(file);
            execlp(argv[1], argv[1], (char*)NULL);
            _exit(1);
        }
        
        int st;
        wait(&st);
        if (WIFEXITED(st) && !WEXITSTATUS(st)) {
            if (!fork()) {
                execlp(argv[2], argv[2], (char*)NULL);
                _exit(1);
            }
        }
        wait(NULL);
        exit(0);
    }

    if (!fork()) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        if (!fork()) {
            int file = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
            dup2(file, 1);
            close(file);
            execlp(argv[3], argv[3], (char*)NULL);
            _exit(1);
        }
        wait(NULL);
        exit(0);
    }


    close(fd[1]);
    close(fd[0]);
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    return 0;
}