#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
} Node;

int
search (int fd, off_t offset);

int
main (int argc, char* argv[])
{
    int fd;
    if ( (fd = open(argv[1], O_RDONLY)) == -1) {
        return 1;
    }

    if (search(fd, 0) == -1){
        return 2;
    }

    return 0;
}

int 
search (int fd, off_t offset)
{
    Node node;
    lseek(fd, offset * sizeof(node), SEEK_SET);

    //read a node
    
    ssize_t offs = 0;
    ssize_t cnt;
    while (offs < sizeof(node)) {
        cnt = read(fd, &node + offs, sizeof(node) - offs);
        if (cnt == -1){
            return -1;            
        }
        offs += cnt;

    }

    //search
    if ( node.right_idx && ( search(fd, node.right_idx) == -1)) {
        return -1;
    }    

    printf("%d\n", node.key);

    if ( node.left_idx && ( search(fd, node.left_idx) == -1)) {
        return -1;
    }

    return 0;
}

