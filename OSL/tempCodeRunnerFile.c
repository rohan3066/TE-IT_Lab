#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t wr, mutex;
int a = 10, readCount = 0;

void *writer(void *arg) {
    long int num = (long int)arg;

    // Lock wr variable to enter critical section
    pthread_mutex_lock(&wr);
    printf("\n Writer %ld is in critical section ", num);
    printf("\n Writer %ld has written data as %d ", num, ++a);
    sleep(1);
    
    // Release the lock
    pthread_mutex_unlock(&wr);
    printf("\n Writer %ld left critical section ", num);
    
    return NULL;  // Return statement added
}

void *reader(void *arg) {
    long int num = (long int)arg;

    pthread_mutex_lock(&mutex);
    readCount++;
    pthread_mutex_unlock(&mutex);

    if (readCount == 1) {
        pthread_mutex_lock(&wr);
    }

    printf("\n Reader %ld is in critical section ", num);
    printf("\n Reader %ld is reading data %d ", num, a);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readCount--;
    pthread_mutex_unlock(&mutex);

    if (readCount == 0) {
        pthread_mutex_unlock(&wr);
    }

    printf("\n Reader %ld left critical section ", num);
    
    return NULL;  // Return statement added
}

int main() {
    pthread_t r[10], w[10];
    long int i, j;
    int nor, now;

    // Initialize mutex variables
    pthread_mutex_init(&wr, NULL);
    pthread_mutex_init(&mutex, NULL);
    
    printf("Enter number of writers and readers: ");
    scanf("%d %d", &nor, &now);  // Remove extra spaces

    for (i = 0; i < nor; i++) {
        pthread_create(&r[i], NULL, reader, (void *)i);
    }
    for (j = 0; j < now; j++) {
        pthread_create(&w[j], NULL, writer, (void *)j);  // Use w[j] instead of w[i]
    }

    for (i = 0; i < nor; i++) {
        pthread_join(r[i], NULL);
    }
    for (j = 0; j < now; j++) {
        pthread_join(w[j], NULL);
    }

    return 0;
}
