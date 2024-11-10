#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_cond_t condicao = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *esperar_sinal(void *id) {
    pthread_mutex_lock(&mutex);
    printf("Thread %ld aguardando sinal...\n", (long)id);
    pthread_cond_wait(&condicao, &mutex);
    printf("Thread %ld recebeu o sinal!\n", (long)id);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *enviar_sinal(void *id) {
    sleep(2);
    pthread_mutex_lock(&mutex);
    printf("Thread %ld enviando sinal...\n", (long)id);
    pthread_cond_signal(&condicao);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, esperar_sinal, (void *)1);
    pthread_create(&t2, NULL, enviar_sinal, (void *)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
