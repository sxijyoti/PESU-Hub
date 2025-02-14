// Program to demonstrate semaphores

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

sem_t mutex;

void *my_thread_1(void *arg)
{
   char s[] = "abcdefgh";
   int l = strlen(s);

   for(int i = 0; i < l; ++i)
   {
      //wait
      sem_wait(&mutex);

      //critical section
      putchar(s[i]);
      fflush(stdout); 
      sleep(2);
					
      //signal
      sem_post(&mutex);
   }
}

void *my_thread_2(void *arg)
{
   char s[] = "ABCDEFGH";
   int l = strlen(s);

   for(int i = 0; i < l; ++i)
   {
      //wait
      sem_wait(&mutex);

      //critical section
      putchar(s[i]);
      fflush(stdout); 
      sleep(2);
					
      //signal
      sem_post(&mutex);
   }
}

int main()
{
    pthread_t t1,t2;

    sem_init(&mutex, 0, 1);

    pthread_create(&t1, NULL, my_thread_1, NULL);
	
    //sleep(2);
	
    pthread_create(&t2, NULL, my_thread_2, NULL);
	
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	
    sem_destroy(&mutex);

    printf("\n");    
    return 0;
}	
