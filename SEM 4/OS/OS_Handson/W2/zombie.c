// Program to demonstrate Zombie Process. 
// Child becomes Zombie as parent is sleeping when child process exits.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid > 0) //Parent process
    {
       sleep(50);
       printf("In parent\n");
    }
    else if (pid == 0) //Child process          
    {
       printf("In child\n");
       exit(0);
    }

    return 0;
}