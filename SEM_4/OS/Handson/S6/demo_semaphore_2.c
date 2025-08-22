// Program to demonstrate semaphores

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *my_thread_1(void *arg)
{
   char s[] = "abcdefgh";
   int l = strlen(s);

   for(int i = 0; i < l; ++i)
   {
      putchar(s[i]);
      fflush(stdout); 
      sleep(2);
   }
}

void *my_thread_2(void *arg)
{
   char s[] = "ABCDEFGH";
   int l = strlen(s);

   for(int i = 0; i < l; ++i)
   {
      putchar(s[i]);
      fflush(stdout); 
      sleep(2);
   }
}

int main()
{
    pthread_t t1,t2;

    pthread_create(&t1, NULL, my_thread_1, NULL);
	
    //sleep(2);
	
    pthread_create(&t2, NULL, my_thread_2, NULL);
	
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	
    printf("\n");    
    return 0;
}	
