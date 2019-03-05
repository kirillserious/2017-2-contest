#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum Constants
{
    BUFFER_SIZE = 4096
};

void 
copy_file(int in_fd, int out_fd)
{
    char buffer[BUFFER_SIZE];

    ssize_t rcnt, wcnt, offset;
    while ((rcnt = read(in_fd, buffer, sizeof(buffer))) > 0) {
        offset = 0;
        while(offset < rcnt){
            if ( (wcnt = write(out_fd,  buffer + offset, rcnt - offset)) == -1) {
                break;
            }
            offset += wcnt;
        }
                
    }
  
}