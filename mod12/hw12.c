// name: Anastasia Yakauleva
// email: yakauleva.a@northeastern.edu
// Compile with:
//
// gcc -lpthread hw12.c -o hw12
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // provides pthread_mutex_t data type

#define NTHREADS 100

// shared variable
int counter = 0;

pthread_mutex_t lock;

// thread to be executed - unspecified variable arguments
void* thread1 (void* vargp) {
    pthread_mutex_lock(&lock);
    counter = counter + 1;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* thread2 (void* vargp) {
    pthread_mutex_lock(&lock);
    // add 5 to counter
    counter = counter + 5;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* thread3 (void* vargp) {
    pthread_mutex_lock(&lock);
    // subtract 2 from counter
    counter = counter - 2;
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* thread4 (void* vargp) {
    pthread_mutex_lock(&lock);
    // subtract 10 from counter
    counter = counter - 10;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    // array to keep Pthread IDs of created threads
    pthread_t tid[NTHREADS*4];
    int i;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    printf("Counter starts at %d\n", counter);

    // create and run the threads
    for (i = 0; i < NTHREADS; ++i) {
        pthread_create(&(tid[i]), NULL, thread1, NULL);
        pthread_create(&(tid[i + NTHREADS]), NULL, thread2, NULL);
        pthread_create(&(tid[i + 2 * NTHREADS]), NULL, thread3, NULL);
        pthread_create(&(tid[i + 3 * NTHREADS]), NULL, thread4, NULL);
    }

    // wait until all threads are done
    for (i = 0; i < NTHREADS*4; ++i){
        pthread_join(tid[i], NULL);
    }

    printf("Counter ends at %d\n", counter);

    // Destroy the mutex object
    pthread_mutex_destroy(&lock);

    return 0;
}