#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
void *my_function(void *arg){
    sem_wait(&mutex);
    printf("\nEntered critical section\n");
    sleep(4);
    printf("\nExiting critical section\n");
    sem_post(&mutex);
    return NULL;
}
int main(){
    pthread_t t1,t2;
    sem_init(&mutex,0,1);
    pthread_create(&t1,NULL,my_function,NULL);
    sleep(2);
    pthread_create(&t2,NULL,my_function,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}