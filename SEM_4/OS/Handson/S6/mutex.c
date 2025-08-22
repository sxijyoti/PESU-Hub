#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// pthread_t tid[2];
// int counter;
// thread_mutex_t lock;

// void *thread_function(void *arg){
//     pthread_mutex_lock(&lock);
//     unsigned long i = 0;
//     counter += 1;
//     printf("\n Job %d has started\n", counter);
//     for(i=0; i<(0xFFFFFFFF); i++);
//     printf("\n Job %d has finished\n", counter);
//     pthread_mutex_unlock(&lock);
//     return NULL;
// }

// int main(){
//     int i = 0;
//     int threadcrea;
//     if(pthread_mutex_init(&lock, NULL) != 0){
//         printf("\n mutex init has failed\n");
//         return 1;
//     }
//     while(i<2){
//         threadcrea = pthread_create(&(tid[i]), NULL, &thread_function, NULL);
//         if(threadcrea != 0){
//             printf("\nThread creation failed: %s\n", strerror(threadcrea));
//         }
//         i++;
//     }
//     pthread_join(tid[0], NULL);
//     pthread_join(tid[1], NULL);

//     return 0;
// }

pthread_t tid[2];
int counter;
pthread_mutex_t lock;
void *thread_function(void *arg){
    pthread_mutex_lock(&lock);
    unsigned long i=0;
    counter+=1;
    printf("\n Job %d has started\n",counter);
    for(i=0;i<(0xFFFFFFFF);i++);
    printf("\njob %d has finished\n",counter);
    pthread_mutex_unlock(&lock);//lock released for the next thread togo in
    return NULL;
}
int main(){
    int i=0;
    int threadcrea;
    if(pthread_mutex_init(&lock,NULL)!=0){
        printf("\n mutex init has failed\n");
        return 1;
    }
    while(i<2){
        threadcrea=pthread_create(&tid[i],NULL,&thread_function,NULL);//thread created
        i++;
        
    }
    pthread_join(tid[0],NULL);//thread is joined to the process using the thread id(tid[i])
    pthread_join(tid[1],NULL);
    return 0;

}