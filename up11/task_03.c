#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/limits.h>

int
my_wait(void)
{
    int status;
    wait(&status);
    if (WIFEXITED(status) && !WEXITSTATUS(status)) {
        return 1;    
    }
    return 0;
}

void
new_proc(char *str)
{
    if (!fork()) {
        char path[PATH_MAX+1];

        FILE *file = fopen(str, "r");
        fgets(path, sizeof(path), file);
        path[strlen(path) - 1] = '\0';
        fclose(file);

        execlp(path, path, (char*) NULL);
        _exit(1);
    }
}



int
main (int argc, char *argv[])
{
    long int n = strtol(argv[1], NULL, 10);
    n = (n > argc - 2) ? argc - 2 : n;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        new_proc(argv[2 + i]);
    }
    for (int j = 0; j < n; j++){
        cnt += my_wait();
    }

    for (int j = 0; j < argc - 2- n; j++) {
        new_proc(argv[j + n + 2]);
        cnt += my_wait();
    }
    
    printf("%d\n", cnt);
    return 0;
}