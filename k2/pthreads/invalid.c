#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>

#define N 10
#define MIL 1000000

int x = 0;

sem_t* mutex;

void *worker(void *arg) {
    for (int i=0; i<MIL; i++) {
        sem_wait(mutex);
        x += 1;
        sem_post(mutex);
    }

    return NULL;
}

#define SEM_NAME "/SEM"

int main() {
    mutex = sem_open(SEM_NAME, O_CREAT, O_RDWR, 1);
    /* printf("mutex=%p\n", mutex); */

    pthread_t thrs[N];
    for (int i=0; i<N; i++) {
        pthread_create(&thrs[i], NULL, worker, NULL);
    }

    for (int i=0; i<N; i++) {
        pthread_join(thrs[i], NULL);
    }

    sem_close(mutex);
    sem_unlink(SEM_NAME);

    printf("x=%d\n", x);
}
