#include <sys/ipc.h> //interprocess communication
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    void *shared_mem;
    char buff[100];
    int shmid;
    shmid=shmget((key_t)1122,1024,0666|IPC_CREAT);
    printf("key of shared memory is %d\n",shmid);
    shared_mem=shmat(shmid,NULL,0);//atttaching the process, NULL-not prepresenting the address
    printf("process attached at %p\n",shared_mem);
    printf("enter some data to write to shared memory\n");
    read(0,buff,100);
    strcpy(shared_mem,buff);
    printf("data read from shared memory %s\n",(char *)shared_mem);


}