#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main (int argc, char *argv[])
{
    int fin = open(argv[2], O_RDONLY);
    int fout = open(argv[3], O_WRONLY|O_TRUNC|O_CREAT, 0666);

    switch (fork()) {
        case -1:
            break;
        case 0:
            if (dup2(fin, 0) == -1) {
                break;
            }
            if (dup2(fout, 1) == -1) {
                break;
            }
            close(fin);
            close(fout);
            execlp(argv[1], argv[1], NULL);
            break;
        default:
            while (wait(NULL) == -1);
    }

    return 0;

}