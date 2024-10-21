#include<stdio.h>
#include<stdlib.h>

struct process {
    int pid;
    int at;  // Arrival Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
    int bt;  // Burst Time
    int ct;  // Completion Time
} p[20], temp;

int n;

void asort() {
    // Sort the processes by their arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void swap(int a, int b, struct process p[20]) {
    // Swap function to swap two processes
    temp = p[a];
    p[a] = p[b];
    p[b] = temp;
}

void btsort(struct process p[20], int i, int n, int ict) {
    // Sort based on burst time for processes that have arrived and are ready to execute
    for (int a = i + 1; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            if ((p[a].at <= ict) && (p[b].at <= ict)) {
                if (p[a].bt > p[b].bt) {
                    swap(a, b, p);
                }
            }
        }
    }
}

void sjf() {
    asort();
    int ict = p[0].at; // Initial current time set to the arrival time of the first process

    for (int i = 0; i < n; i++) {
        if (ict < p[i].at) {
            p[i].ct = p[i].at + p[i].bt;
            ict = p[i].ct; // Update current time after process completion
        } else {
            p[i].ct = ict + p[i].bt;
            ict = p[i].ct; // Update current time after process completion
        }

        p[i].tat = p[i].ct - p[i].at; // Calculate Turnaround Time
        p[i].wt = p[i].tat - p[i].bt; // Calculate Waiting Time

        btsort(p, i, n, ict); // Sort remaining processes by burst time
    }
}

void main() {
    float sum1 = 0, sum2 = 0; // Declare sum1 and sum2 to accumulate WT and TAT

    printf("Enter number of processes:\n");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter PID for process %d:\n", i + 1);
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time for process %d:\n", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for process %d:\n", i + 1);
        scanf("%d", &p[i].bt);
    }

    sjf(); // Execute Shortest Job First scheduling

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        sum1 += p[i].wt;
        sum2 += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", sum1 / n);
    printf("\nAverage Turnaround Time: %.2f", sum2 / n);
}

