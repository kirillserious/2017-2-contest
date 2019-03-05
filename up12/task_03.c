#include <stdlib.h>
#include <stdio.h>

#include <sys/sem.h>
#include <sys/shm.h>

#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

enum
{
    MY_KEY = 10
};

int
main (int argc, char *argv[])
{
    setvbuf(stdin, 0, _IONBF, 0);
    int count;
    sscanf(argv[1], "%d", &count);
    
    int sem_id = semget(MY_KEY, count, IPC_CREAT | 0666);
    
    struct sembuf sem_buf;
    sem_buf.sem_flg = 0;

    for (int i = 0; i < count; ++i) {
        
        semctl(sem_id, i, SETVAL, 0);

        if (!fork()) {

            sem_buf.sem_num = i;
            sem_buf.sem_op = -1;
            while (!semop(sem_id, &sem_buf, 1)) {

                int a;
                if (scanf("%d", &a) != EOF) {
                    printf("%d %d\n", i, a);
                    fflush(NULL);
                    sem_buf.sem_num = (a % count) + ((a%count < 0)?count:0);
                    sem_buf.sem_op = 1;
                    semop(sem_id, &sem_buf, 1);
                } else {
                    semctl(sem_id, 0, IPC_RMID, 0);
                }

                sem_buf.sem_num = i;
                sem_buf.sem_op = -1;
            }
            exit(0);
        }
    }

    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    semop(sem_id, &sem_buf, 1);

    while (wait(NULL) != -1);
    exit(0);
}