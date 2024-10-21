#include <stdio.h>
#include <unistd.h>

int main(){
    int fd[2], n;
    char buffer[100], as[100];
    pid_t p;
    p=fork();
    if(p>0){
        printf("Parent pass value to child\n");
        printf("Enter Data:");
        fgets(as, 100, stdin);
        write(fd[1],as,100);    
    }
    read(fd[0], buffer,100);
    printf("Child receives data");
    printf("\nBuffer: %s", buffer);
}



