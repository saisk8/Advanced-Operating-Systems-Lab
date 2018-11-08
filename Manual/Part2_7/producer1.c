#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHMSZ 1024

int main() {
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    sem_t *empty = sem_open("EMPTY", O_CREAT, 0666, 5);
    sem_unlink("EMPTY");
    sem_t *full = sem_open("FULL", O_CREAT, 0666, 0);
    sem_unlink("FULL");
    sem_t *mutex = sem_open("MUTEX", O_CREAT, 0666, 1);
    sem_unlink("MUTEX");
    s = shm;
    c = 'a';
    sleep(1);
    while (c <= 'z') {
        sem_wait(empty);
        sem_wait(mutex);
        printf("Producer 1 in CS\n");
        *s++ = c;
        sem_post(mutex);
        sem_post(full);
    }
    return 0;
}