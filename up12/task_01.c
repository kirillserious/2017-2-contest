#include <stdlib.h>
#include <stdio.h>

#include <sys/sem.h>
#include <sys/shm.h>

#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int
main (int argc, char *argv[])
{
    int nproc, maxval;
    key_t key;

    sscanf(argv[1], "%d", &nproc);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%d", &maxval);

    int sem_id = semget(key, nproc, IPC_CREAT | 0666);
    int shm_id = shmget(key, sizeof(int), IPC_CREAT | 0666);
    
    int *ptr   = shmat(shm_id, NULL, 0);
    *ptr = 0;

    struct sembuf sem_buf;
    sem_buf.sem_flg = 0;

    for (int i = 0; i < nproc; ++i) {
        
        semctl(sem_id, i, SETVAL, 0);

        if (!fork()) {

            sem_buf.sem_num = i;
            sem_buf.sem_op = -1;
            while (!semop(sem_id, &sem_buf, 1)) {

                printf("%d: %d\n", i, *ptr);
                fflush(stdout);
                
                (*ptr)++;
                if (*ptr > maxval) {
                    shmctl(shm_id, IPC_RMID, NULL);
                    semctl(sem_id, 0, IPC_RMID, 0);
                } else {
                    sem_buf.sem_num = (*ptr) * (*ptr) % nproc;
                    sem_buf.sem_op = 1;
                    semop(sem_id, &sem_buf, 1);
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