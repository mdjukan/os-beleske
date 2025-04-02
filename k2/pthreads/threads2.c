#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>

#define N 100
int M[N][N];
int max;

sem_t* mutex;

void *worker(void *arg) {
    int i = (int)arg;
    int lmax = M[i][0];
    for (int j=1; j<N; j++) {
        if (M[i][j] > lmax) {
            lmax = M[i][j];
        }
    }

    sem_wait(mutex);
    if (lmax > max) {
        max = lmax;
    }
    sem_post(mutex);

    return NULL;
}

#define SEM_NAME "/SEM"

int main() {
    mutex = sem_open(SEM_NAME, O_CREAT, O_RDWR, 1);
    printf("mutex=%p\n", mutex);

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            M[i][j] = i * j;
        }
    }
    max = M[0][0];

    pthread_t thrs[N];
    for (int i=0; i<N; i++) {
        pthread_create(&thrs[i], NULL, worker, (void*)i);
    }

    for (int i=0; i<N; i++) {
        pthread_join(thrs[i], NULL);
    }
    sem_close(mutex);
    sem_unlink(SEM_NAME);

    printf("max=%d\n", max);
}
