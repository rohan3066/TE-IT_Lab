#include<stdio.h>
#include<stdlib.h>

int choice;
int finish[10];
int process_name[10];
int arrival_time[10];
int burst_time[10];
int waiting_time[10];
int turn_around_time[10];
int avg_wait_time;
int avg_turn_around_time;
int n, pending, remain_burst_time[10];
int count, time;

void input(){
    int i;
    printf("\nEnter number of process: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        process_name[i] = i;
        printf("\nEnter Burst time for process %d: ", process_name[i]);
        scanf("%d", &burst_time[i]);  // Corrected here
        remain_burst_time[i] = burst_time[i];
        printf("\nEnter arrival time for process %d: ", process_name[i]);
        scanf("%d", &arrival_time[i]);
    }
}

void round_robin(){
    int time_quantum, i;
    input();
    pending = n;

    printf("\nEnter time quantum: ");
    scanf("%d", &time_quantum);
    printf("\n\n\nGantt chart--> ");

    for(i = 0; i < n; i++){
        finish[i] = 0;
        waiting_time[i] = 0;
    }

    for(time = 0, count = 0; pending > 0;) {  // Corrected here
        if(finish[count] != 1 && arrival_time[count] <= time && remain_burst_time[count] <= time_quantum){
            time += remain_burst_time[count];
            pending--;
            finish[count] = 1;
            waiting_time[count] -= arrival_time[count];
            turn_around_time[count] = waiting_time[count] + burst_time[count];

            for(i = 0; i < remain_burst_time[count]; i++){
                printf("P%d ", process_name[count]);
            }

            for(i = 0; i < n; i++){
                if(i == count || finish[i] == 1){
                    continue;
                }
                waiting_time[i] += remain_burst_time[count];
            }
            remain_burst_time[count] = 0;
        }
        else if(finish[count] != 1 && arrival_time[count] <= time && remain_burst_time[count] >= time_quantum){
            time += time_quantum;
            remain_burst_time[count] -= time_quantum;
            for(i = 0; i < n; i++){
                if(i == count || finish[i] == 1){
                    continue;
                }
                waiting_time[i] += time_quantum;
            }
            for(i = 0; i < time_quantum; i++){
                printf("P%d ", process_name[count]);
            }
        }
        count = (count + 1) % n;  // Corrected here
    }
}

void sort(){
    int i,j,temp;

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(remain_burst_time[i]<remain_burst_time[j]){
                temp=burst_time[i];
                burst_time[i]=burst_time[j];
                burst_time[j]=temp;

                temp=remain_burst_time[i];
                remain_burst_time[i]=remain_burst_time[j];
                remain_burst_time[j]=temp;

                temp=arrival_time[i];
                arrival_time[i]=arrival_time[j];
                arrival_time[j]=temp;

                temp=waiting_time[i];
                waiting_time[i]=waiting_time[j];
                waiting_time[j]=temp;

                temp=process_name[i];
                process_name[i] = process_name[j];
                process_name[j]=temp;

                temp=finish[i];
                finish[i] = finish[j];
                finish[j]=temp;

            }
        }
    }
}

void sjf_preempt() {
    int i, time = 0, count;
    input();

    pending = n;

    printf("\n\n\nGantt Chart--> ");
    for (i = 0; i < n; i++) {
        finish[i] = 0;
        waiting_time[i] = 0;
    }

    while (pending > 0) {
        sort();  // Ensure processes are sorted by remaining burst time

        for (count = 0; count < n; count++) {
            if (finish[count] == 0 && arrival_time[count] <= time) {
                printf("P%d ", process_name[count]);

                // Simulate one unit time execution for the process
                remain_burst_time[count]--;
                time++;

                // Update waiting time for all other unfinished processes
                for (i = 0; i < n; i++) {
                    if (i != count && finish[i] == 0 && arrival_time[i] <= time) {
                        waiting_time[i]++;
                    }
                }

                // If process has completed
                if (remain_burst_time[count] == 0) {
                    pending--;
                    finish[count] = 1;
                    turn_around_time[count] = time - arrival_time[count];  // Calculate turnaround time
                    waiting_time[count] = turn_around_time[count] - burst_time[count];  // Calculate waiting time
                }

                break;  // Preempt and check next process in sorted order
            }
        }
    }
}


void display_output() {
    int i;
    printf("\n\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               process_name[i], 
               arrival_time[i], 
               burst_time[i], 
               turn_around_time[i], 
               waiting_time[i]);
    }
}


int main() {
    int choice;

    while (1) {
        printf("\nScheduling Algorithms Menu:");
        printf("\n1. Round Robin");
        printf("\n2. Shortest Job First (SJF) Preemptive");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nExecuting Round Robin Algorithm...\n");
                round_robin();
                display_output();
                break;

            case 2:
                printf("\nExecuting Shortest Job First (SJF) Preemptive Algorithm...\n");
                sjf_preempt();
                display_output();
                break;

            case 3:
                printf("\nExiting the program...\n");
                return 0;

            default:
                printf("\nInvalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
