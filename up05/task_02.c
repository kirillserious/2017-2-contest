#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

int
main (int argc, char* argv[])
{


    DIR *dfd;
    if( (dfd = opendir(argv[1])) == NULL ) {
        return 1;
    }

    uid_t id = getuid();
    long long int sum_size = 0;

    struct dirent *dd;
    struct stat bug;
    char path[PATH_MAX];
    while ((dd = readdir(dfd))) {
        if(!isupper((dd->d_name)[0])) {
            continue;
        }

        int slen;
        if (argv[1][strlen(argv[1])-1] == '/') {
            slen = snprintf(path, sizeof(path), "%s%s", argv[1], dd->d_name);
        } else {
            slen = snprintf(path, sizeof(path), "%s/%s", argv[1], dd->d_name);
        }
        if (slen + 1 > sizeof(path)) {
            continue;
        }

        if (stat(path, &bug) < 0) {
            continue;
        }

        if(!S_ISREG(bug.st_mode)) {
            continue;
        }

        if(bug.st_uid != id) {
            continue;
        }

        sum_size += bug.st_size;
    }
    printf("%lld\n", sum_size);
}