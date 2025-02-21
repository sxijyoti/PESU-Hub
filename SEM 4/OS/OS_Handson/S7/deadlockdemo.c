#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_t tid1, tid2;
pthread_mutex_t first_mutex, second_mutex;

void *do_work_one(void *param){
    pthread_mutex_lock(&first_mutex);
    sleep(5);
    pthread_mutex_lock(&second_mutex);
    printf("Entering thread 1\n");
    sleep(5);
    printf("Exiting thread 1\n");
    pthread_mutex_unlock(&second_mutex);
    sleep(5);
    pthread_mutex_unlock(&first_mutex);
    pthread_exit(0);
}

void *do_work_two(void *param){
    pthread_mutex_lock(&second_mutex);
    sleep(5);
    pthread_mutex_lock(&first_mutex);
    printf("Entering thread 2\n");
    sleep(5);
    printf("Exiting thread 2\n");
    pthread_mutex_unlock(&first_mutex);
    sleep(5);
    pthread_mutex_unlock(&second_mutex);
    pthread_exit(0);
}

int main(){
    int error;
    if (pthread_mutex_init(&first_mutex, NULL) != 0){
        printf("first mutex init has failed\n");
        return 1;
    }
    if (pthread_mutex_init(&second_mutex, NULL) != 0){
        printf("second mutex init has failed\n");
        return 1;
    }
    error=pthread_create(&tid1,NULL,&do_work_one,NULL);
    if(error!=0){
        printf("first thread can't be created : [%s]",strerror(error));
    }
    error=pthread_create(&tid2,NULL,&do_work_two,NULL);
    if(error!=0){
        printf("second thread can't be created : [%s]",strerror(error));
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&first_mutex);
    pthread_mutex_destroy(&second_mutex);

    return 0;
}