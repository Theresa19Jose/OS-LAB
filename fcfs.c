#include<stdio.h>
#include<stdlib.h>

struct process{
    int pid;
    int at;
    int wt;
    int tat;
    int bt;
    int ct;
}p[20],temp;

int  n;

void asort(){
    for(int i=0; i<n-1; i++){
        for(int j=i+1;j<n;j++){
            if(p[i].at>p[j].at){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
   
    }
}

void fcfs(){
    float sum1=0,sum2=0;
    asort();
    p[0].ct=p[0].at+p[0].bt;
    for(int i=0;i<n;i++){
        p[i+1].ct=p[i].ct+p[i+1].bt;
        p[i].tat=p[i].ct-p[i].at;
        sum1=sum1+p[i].tat;
        p[i].wt=p[i].tat-p[i].bt;
        sum2=sum2+p[i].wt;
       
    }
   
    printf("FCFS:\n");
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\t\tTurn Around Time\t\tWait Time\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t",p[i].pid);
        printf("%d\t\t",p[i].at);
        printf("%d\t\t",p[i].bt);
        printf("%d\t\t\t",p[i].ct);
        printf("%d\t\t\t",p[i].tat);
        printf("%d\t\t\t\t",p[i].wt);
        printf("\n");
   
    }
    printf("Average Turn Around Time: %f \n",(sum1/n));
    printf("Average Wait Time: %f \n",(sum2/n));
}

void main(){
    printf("Enter the number of processes:");
    scanf("%d",&n);
   
    for(int i=0;i<n;i++){
        printf("Enter process id:");
        scanf("%d",&p[i].pid);
        printf("Enter Arrival Time for %d:",p[i].pid);
        scanf("%d",&p[i].at);
        printf("Enter Burst Time for %d:",p[i].pid);
        scanf("%d",&p[i].bt);
   
    }
    fcfs();
}
