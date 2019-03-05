#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <signal.h>

volatile int num = 0;

void
handler(int sig)
{
    signal(SIGINT, handler);
    if (num < 4) {
        printf("%d\n", num);
        fflush(stdout);
        num++;
        return;
    } else {
        exit(0);
    }

}


int
main (int argc, char *argv[])
{
    signal(SIGINT, handler);

    pid_t pid = getpid();
    printf("%lld\n", (long long int)pid);
    fflush(stdout);

    while (1) {
        pause();
    }

    return 0;
}