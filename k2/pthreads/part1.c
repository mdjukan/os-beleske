#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

#define ILEN 100
#define SEM_NAME "/TESTSEM"

int main() {
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0777, 0);

    char instr[ILEN];
    while (scanf("%s", instr)!=EOF) {
        if (strcmp(instr, "post")==0) {
            sem_post(sem);
        }
    }

    sem_close(sem);
    sem_unlink(SEM_NAME);
}
