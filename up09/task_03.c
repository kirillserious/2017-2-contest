#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#include <stdio.h>

int
mysys (const char *str)
{
    // Is bash is working?
    if (str == NULL) {
        return mysys(":") == 0;
    }


    pid_t child = fork();
    int status;
    switch (child) {
        case -1: //fork failed
            return -1;

        case 0: // Child: exec command
            execl("/bin/sh", "sh", "-c", str, (char*) NULL);
            _exit(-1); // execl failed
            break;

        default: //Parent
            
            while (waitpid(child, &status, 0) == -1) {
                if (errno != EINTR) {
                    return -1;
                }
            }

            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            }

            if (WIFSIGNALED(status)) {
                return 128 + WTERMSIG(status);
            }

            

            return 0;
    }
}