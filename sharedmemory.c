#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

void main(){
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;
    const char*file_path="/home/S5IT/shm1.c";
    key_t key=ftok(file_path, 65);
    shmid=shmget(key, 1024, 0666|IPC_CREAT);
    printf("Key of shared memory is: %d\n", shmid);
    shared_memory=shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);
    printf("Enter data to write to shared memory: ");
    fgets(buff, 100, stdin);
    strcpy(shared_memory, buff);
    printf("The data written is: %s",(char*)shared_memory);
}
