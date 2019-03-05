#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main (int argc, char* argv[])
{
    setbuf(stdout, NULL);

    pid_t main_pid = getpid();

    int a, b;
    if (scanf("%d", &a) == EOF) {
        return 0;
    }
    
    
    while(1) {
        if (scanf("%d", &b) == EOF) {
            printf("%d\n", a);
            exit(0);
        }

        pid_t pid = fork();
        if (pid == -1) {
            exit(1);
        }
        if (!pid) {
            a = b;
        } else {
            int status;
            while(waitpid(pid, &status, 0) == -1);
            if ( WEXITSTATUS(status) == 0 ) {
                printf("%d\n", a);
                exit(0);
            } else if (getpid() != main_pid){
                exit(1);
            } else {
                printf("-1\n");
                exit(0);
            }
        }
    }
    


}