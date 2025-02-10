#include <stdio.h>
#include <pthread.h>

void *computation();

int main(){
    pthread_t thread1;
    pthread_t thread2;
    long value = 5;
    long value1 = 1;
    pthread_create(&thread1, NULL, computation, (void *)value);
    pthread_create(&thread2, NULL, computation, (void *)value1);
    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
    return 0;
}

void *computation(void *add){
    long *add_num = (long *)add;
    printf("Add: %ld\n",add_num);
    return 0;
}