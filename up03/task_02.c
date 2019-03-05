#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int
main(int argc, char* argv[])
{
    int fd = open(argv[1], (O_WRONLY|O_CREAT|O_TRUNC), 0600);

    unsigned short num;
    while(scanf("%hu", &num) != EOF) {

        num = (num << 8) | (num >> 8);

        write(fd, &num, sizeof(num));
    }
    
}