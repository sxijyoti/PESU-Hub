#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    int res,n;
    char buffer[100];
    res = open("fifo1",O_WRONLY);
    
    n=read(res,buffer,100);
    printf("Reader process %d sent the data\n", getpid());
    printf("Data read from fifo %d is : %s\n",getpid(), buffer);

    return 0;
}