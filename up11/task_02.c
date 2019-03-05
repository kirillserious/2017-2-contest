#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <signal.h>

volatile int fl = 0;

void
handler(int sig)
{
    switch (sig) {
        case SIGUSR1:
            signal(SIGUSR1, handler);
            fl = 0;
            break;
        case SIGUSR2:
            signal(SIGUSR2, handler);
            fl = 1;
            break;
        default:
            break;
    }
    return;
}


int
main (int argc, char *argv[])
{
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    pid_t pid = getpid();
    printf("%lld\n", (long long int)pid);
    fflush(stdout);


    long long int a;
    while (scanf("%lld", &a) == 1) {
        printf("%lld\n", (fl) ? a*a : -a);
        fflush(stdout);
    }

    return 0;
}