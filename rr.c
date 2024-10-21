#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int wt;
    int tat;
    int bt_print;
    int bt;
    int ct;
    int scheduled;
} p[20], temp;

int n; // Number of processes
int tq; // Time quantum
float total_wt = 0, total_tat = 0;
float avg_wt, avg_tat;
int time_units = 0;

int tail = -1;
int ready_queue[20];

void push(int idx) {
    ready_queue[++tail] = idx;
}

int pop() {
    int idx;
    if (tail == -1) {
        return -1;
    }
    idx = ready_queue[0];
    for (int i = 1; i <= tail; ++i) {
        ready_queue[i - 1] = ready_queue[i];
    }
    --tail;
    return idx;
}

void display_item(int i) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
        p[i].pid, p[i].at, p[i].bt_print, p[i].ct, p[i].tat, p[i].wt);
}

void display() {
    printf("Time Quantum: %d\n", tq);
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        display_item(i);
    }
    avg_wt = total_wt / n;
    avg_tat = total_tat / n;
    printf("\nAverage Waiting Time: %f", avg_wt);
    printf("\nAverage Turnaround Time: %f\n", avg_tat);
}

void swap(int i, int j) {
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

void pid_sort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].pid > p[j + 1].pid) {
                swap(j, j + 1);
            }
        }
    }
}

void at_sort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                swap(j, j + 1);
            }
        }
    }
}

int execute(int i) {
    int time;
    if (p[i].bt > tq) {
        time = tq;
        p[i].bt -= tq;
    } else {
        time = p[i].bt;
        p[i].bt = 0;
    }
    time_units += time;
    p[i].ct = time_units;
    p[i].tat = p[i].ct - p[i].at;
    p[i].wt = p[i].tat - p[i].bt_print;
    total_tat += p[i].tat;
    total_wt += p[i].wt;
    return time;
}

void add_newly_arrived_tasks() {
    for (int i = 0; i < n; i++) {
        if (p[i].bt == 0 || p[i].scheduled == 1) {
            continue;
        }
        if (p[i].at <= time_units) {
            push(i);
            p[i].scheduled = 1;
        }
    }
}

void rr() {
    int current_task;
    int time;
    at_sort();
    push(0);
    p[0].scheduled = 1;
    while (1) {
        current_task = pop();
        if (current_task == -1) {
            break;
        }
        time = execute(current_task);
        add_newly_arrived_tasks();
        if (p[current_task].bt > 0) {
            push(current_task);
        }
    }
    pid_sort();
    printf("\nRR: \n");
    display();
}

int main() {
    printf("Kindly enter the number of processes: ");
    scanf("%d", &n);
    printf("Kindly enter the time quantum: ");
    scanf("%d", &tq);
    printf("\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt_print);
        p[i].bt = p[i].bt_print;
        p[i].scheduled = 0;
    }
    rr();
    return 0;
}
