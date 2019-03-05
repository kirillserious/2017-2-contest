#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <signal.h>

volatile int num = 0;
volatile int cnt = 0;

void
handler(int sig)
{
    switch (sig) {
        case SIGINT:
            signal(SIGINT, handler);
            if (cnt < 3) {
                cnt++;
                printf("%d\n", num);
                fflush(stdout);
                break;
            } 
        case SIGTERM:
            exit(0);
        default:
            break;
    }
    return;
}


int
main (int argc, char *argv[])
{
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    int low, high;
    scanf("%d%d", &low, &high);

    pid_t pid = getpid();
    printf("%lld\n", (long long int)pid);
    fflush(stdout);   

    for (int i = low; i < high; i++) {
        int j = 2;
        int fl = 1;
        while (j * j <= i) {
            if(i % j == 0) {
                fl = 0;
                break;
            }
            j++;
        }
        if (fl) {
            num = i;
        }
    }

    printf("-1\n");    
    fflush(stdout);
    return 0;
}