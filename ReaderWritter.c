#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
int read_count = 0;         
sem_t mutex;               
sem_t wrt;                
void* reader(void* arg) {
    int id = *((int*)arg);
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt); 
    sem_post(&mutex);
    printf("Reader %d is reading\n", id);
    sleep(1); 
    printf("Reader %d finished reading\n", id);
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt); 
    sem_post(&mutex);
    return NULL;
}
void* writer(void* arg) {
    int id = *((int*)arg);
    sem_wait(&wrt); 
    printf("Writer %d is writing\n", id);
    sleep(2); 
    printf("Writer %d finished writing\n", id);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[5], w[5];
    int ids[5];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    for (int i = 0; i < 3; i++) {
        ids[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &ids[i]);
        pthread_create(&w[i], NULL, writer, &ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
