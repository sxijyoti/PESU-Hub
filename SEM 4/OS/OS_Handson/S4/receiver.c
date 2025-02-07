#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(){
    void *shared_mem;
    char buff[100];
    int shmid;
    shmid=shmget((key_t)1122,1024,0066);
    printf("key of shared memory is %d\n",shmid);
    shared_mem=shmat(shmid,NULL,0);
    printf("process attached at %p\n",shared_mem);
    printf("data read from shared memory is : %s\n", (char*)shared_mem);
}