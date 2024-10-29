#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

    int pid=fork();

    if(pid>0){
        sleep(2);
        printf("\nParent procces is terminated!!");
    }

    else{

        printf("\nChild Before Sleep!!");
        printf("\nChild process id:%d",getpid());
        printf("\Parent process id:%d",getppid());

        sleep(5);
        
        printf("\nChild After Sleep!!");
        printf("\nChild process id:%d",getpid());
        printf("\Parent process id:%d",getppid());
    }
    return 0;

}