#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main (int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    if (!fork()) {
        close(fd[1]);
        if (!fork()) {
            //Внук
            int cur;
            long long sum =  0;

            while(read(fd[0], &cur, sizeof(cur))) {
                sum += cur;
            }
            printf("%lld\n", sum);
            close(fd[0]);
            exit(0);
        }

        //Child
        close(fd[0]);
        wait(NULL);
        exit(0);
    }

    close(fd[0]);
    //Parent
    int cur;
    while (scanf("%d", &cur) != EOF) {
    
        write(fd[1], &cur, sizeof(cur));
    }

    close(fd[1]);
    wait(NULL);
    return 0;
}