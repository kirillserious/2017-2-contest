#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char const *argv[])
{
    setbuf (stdout, NULL);

    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {

        pid_t pid = fork();
        if (!pid) {
            if (i == n) {
                printf("%d\n", i);
                exit(0);
            } else {
                printf("%d ", i);
            }
        } else {
            while(waitpid(pid, NULL, 0) == -1);
            exit(0);
        }
    }
}