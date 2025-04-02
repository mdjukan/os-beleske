#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

#define SEM_NAME "/TESTSEM"

int main() {
    sem_t *sem = sem_open(SEM_NAME, 0);
    if (sem==NULL) {
        perror("sem_open:");
    }

    while (1) {
        sem_wait(sem);
        printf("Hello!\n");
    }

    sem_close(sem);
}
