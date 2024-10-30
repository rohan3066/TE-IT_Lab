#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t empty, full;
pthread_mutex_t mutex;

int buffer[5];
int count = 0;

void *producer(void *arg) {
    long int num = (long int) arg;
    
    // Producer tries to produce data
    sem_wait(&empty);

    // Producer is allowed to produce data
    pthread_mutex_lock(&mutex);
    
    buffer[count] = rand() % 10;
    printf("\nProducer %ld produces: %d", num + 1, buffer[count]);
    count++;
    usleep(1000000);
    
    pthread_mutex_unlock(&mutex);
    
    sem_post(&full);
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    long int num = (long int) arg;
    
    // Consumer tries to consume data
    sem_wait(&full);

    // Consumer is allowed to consume data
    pthread_mutex_lock(&mutex);
    count--;
    int item = buffer[count];
    
    printf("\nConsumer %ld consumes: %d", num + 1, item);
    usleep(1000000);
    
    pthread_mutex_unlock(&mutex);
    
    sem_post(&empty);
    pthread_exit(NULL);
}

int main() {
    int np, nc;
    pthread_t p[10], c[10];
    unsigned long int i, j, k, l;
    
    printf("Enter number of producers and consumers: ");
    scanf("%d %d", &np, &nc);
    
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    
    for (i = 0; i < np; i++) {
        pthread_create(&p[i], NULL, producer, (void *)i);
    }
    
    for (j = 0; j < nc; j++) {
        pthread_create(&c[j], NULL, consumer, (void *)j);
    }
    
    for (k = 0; k < np; k++) {
        pthread_join(p[k], NULL);
    }
    
    for (l = 0; l < nc; l++) {
        pthread_join(c[l], NULL);
    }
    
    return 0;
}
