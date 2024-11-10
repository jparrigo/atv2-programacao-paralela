#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 4
pthread_barrier_t barreira;

void *tarefa(void *id) {
    printf("Thread %ld: antes da barreira\n", (long)id);
    pthread_barrier_wait(&barreira);
    printf("Thread %ld: após a barreira\n", (long)id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_barrier_init(&barreira, NULL, NUM_THREADS);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, tarefa, (void *)i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barreira);
    return 0;
}
