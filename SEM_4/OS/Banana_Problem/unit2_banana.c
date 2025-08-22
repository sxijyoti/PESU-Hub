#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int global_val = 0;
pthread_mutex_t lock;


void* data_modification() {
    int local_val = 0;
    static int static_val = 0;


    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        global_val++;
        static_val++; 
        pthread_mutex_unlock(&lock);

        local_val++;

        printf("Iteration: %d | Thread ID: %lu | Global: %d | Local: %d | Static: %d\n", 
            i + 1, pthread_self(), global_val, local_val, static_val);
        
        sleep(1);
    }

    return NULL;
}

void* data_modification_2() {
    int local_val = 0;
    static int static_val = 0;


    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&lock);
        global_val++;
        static_val++; 
        pthread_mutex_unlock(&lock);

        local_val++;

        printf("Iteration: %d | Thread ID: %lu | Global: %d | Local: %d | Static: %d\n", 
                i + 1, pthread_self(), global_val, local_val, static_val);
        
        sleep(1);
    }

    return NULL;
}


int main() {
    pthread_t thread1, thread2, thread3, thread4;

    pthread_mutex_init(&lock, NULL); // mutex initialization

    // thread creation
    pthread_create(&thread1, NULL, data_modification, NULL);
    pthread_create(&thread2, NULL, data_modification, NULL);

    // main thread waits for the created threads to terminate
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final Global Value after thread data modifications: %d\n", global_val);
    printf("\n");

    printf("To show difference between static and global variable:\n");
    printf("\n");

    pthread_create(&thread3, NULL, data_modification_2, NULL);
    pthread_create(&thread4, NULL, data_modification_2, NULL);

    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final Global Value after thread data modifications: %d\n", global_val);




    return 0;
}
