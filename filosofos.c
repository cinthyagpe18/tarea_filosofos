#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define VECES 3

sem_t tenedor[N];

void *filosofo(void *arg) {
    int i = *(int *)arg;
    int primero, segundo;

    if (i == N - 1) {
        primero = 0;
        segundo = N - 1;
    } else {
        primero = i;
        segundo = i + 1;
    }

    for (int v = 1; v <= VECES; v++) {
        printf("Filosofo %d esta pensando\n", i);
        usleep(rand() % 100000);

        sem_wait(&tenedor[primero]);
        sem_wait(&tenedor[segundo]);

        printf("Filosofo %d empieza a comer\n", i);
        usleep(rand() % 100000);
        printf("Filosofo %d termina de comer\n", i);

        sem_post(&tenedor[primero]);
        sem_post(&tenedor[segundo]);
    }
    return NULL;
}

int main() {
    pthread_t hilo[N];
    int ids[N];

    for (int i = 0; i < N; i++)
        sem_init(&tenedor[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&hilo[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(hilo[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&tenedor[i]);

    printf("\nTermino el programa\n");
    return 0;
}
