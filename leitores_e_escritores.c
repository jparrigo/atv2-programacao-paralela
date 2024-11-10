#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex_recurso = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_leitor = PTHREAD_MUTEX_INITIALIZER;
int cont_leitores = 0;
int dado_compartilhado = 0;

void *leitor(void *id) {
    while (1) {
        pthread_mutex_lock(&mutex_leitor);
        cont_leitores++;
        if (cont_leitores == 1) pthread_mutex_lock(&mutex_recurso);
        pthread_mutex_unlock(&mutex_leitor);

        printf("Leitor %ld leu: %d\n", (long)id, dado_compartilhado);

        pthread_mutex_lock(&mutex_leitor);
        cont_leitores--;
        if (cont_leitores == 0) pthread_mutex_unlock(&mutex_recurso);
        pthread_mutex_unlock(&mutex_leitor);
        sleep(1);
    }
}

void *escritor(void *id) {
    while (1) {
        pthread_mutex_lock(&mutex_recurso);
        dado_compartilhado++;
        printf("Escritor %ld escreveu: %d\n", (long)id, dado_compartilhado);
        pthread_mutex_unlock(&mutex_recurso);
        sleep(2);
    }
}

int main() {
    pthread_t leitores[3], escritores[2];

    for (long i = 0; i < 3; i++) {
        pthread_create(&leitores[i], NULL, leitor, (void *)i);
    }
    for (long i = 0; i < 2; i++) {
        pthread_create(&escritores[i], NULL, escritor, (void *)i);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(leitores[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(escritores[i], NULL);
    }

    return 0;
}
