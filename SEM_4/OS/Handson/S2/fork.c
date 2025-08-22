// program to demonstrate fork() 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t p1;

    int i = 0, y = 0;
   
    p1 = fork();

    if (p1 > 0) //parent process
    {
       for (i = 0; i < 5; i++)
       {
          sleep(i);

          y = y - 1;

          printf("This is parent. Process Id = %d, y = %d\n", getpid(), y);
       }
    }
    else if (p1 == 0) // child process 
    {
       for (i = 0; i < 5; i++)
       {
          sleep(i);

          y = y + 1;

          printf("This is child. Process Id = %d, Parent Process Id = %d, y = %d\n", getpid(), getppid(), y);
       }
    }
    else //fork failed
    {
        printf("fork creation failed!!!\n");
    }
}