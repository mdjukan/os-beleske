#include <pthread.h>
#include <stdio.h>

#define N 10
int M[N][N];

void *worker(void *arg) {
    int i = (int)arg;
    int s = 0;
    for (int j=0; j<N; j++) {
        s += M[i][j];
    }

    return (void*)s;
}

int main() {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            M[i][j] = i * j;
            /* M[i][j] = 1; */
        }
    }

    pthread_t thrs[N];
    for (int i=0; i<N; i++) {
        pthread_create(&thrs[i], NULL, worker, (void*)i);
    }

    int s = 0, rs;
    for (int i=0; i<N; i++) {
        pthread_join(thrs[i], (void**)(&rs));
        s += rs;
    }

    printf("s=%d\n", s);
}
