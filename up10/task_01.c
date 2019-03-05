#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(int argc, char const *argv[])
{
    int fd[2];
    pipe(fd);
    
    time_t t;
    struct tm *st_t;

    if(!fork()) {
        if(!fork()) {
            if(!fork()) {
                read(fd[0], &t, sizeof(t));
                st_t = localtime(&t);
                printf("S:%02d\n", st_t->tm_sec);
                exit(0);
            }
            wait(NULL);
            read(fd[0], &t, sizeof(t));
            st_t = localtime(&t);
            printf("M:%02d\n", st_t->tm_min);
            exit(0);
        }
        wait(NULL);
        read(fd[0], &t, sizeof(t));
        st_t = localtime(&t);
        printf("H:%02d\n", st_t->tm_hour);
        exit(0);
    }

    t = time(NULL);
    write(fd[1], &t, sizeof(t));
    write(fd[1], &t, sizeof(t));
    write(fd[1], &t, sizeof(t));

    wait(NULL);
    return 0;
}