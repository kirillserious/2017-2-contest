#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int
is_ok (int st)
{
    return (WIFEXITED(st) && (WEXITSTATUS(st) == 0)) ? 1 : 0;
}

int
st_proc (const char* str)
{
    int st;
    pid_t child = fork();
    switch (child) {
        case -1:
            _exit(1);
        case 0:
            execlp(str, str, NULL);
            return 0;
        default:
            while(wait(&st) == -1);
            return is_ok(st);
    }
} 

int
main (int argc, char *argv[])
{
    exit(!((st_proc(argv[1]) || st_proc(argv[2])) && st_proc(argv[3])));
}