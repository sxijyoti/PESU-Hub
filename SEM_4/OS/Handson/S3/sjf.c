#include <stdio.h>

void findtatTime(int processes[], int n, int wt[], int bt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findwtTime(int processes[], int n, int wt[], int bt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i-1] + wt[i-1];
    }
}

void sortByBurstTime(int processes[], int n, int bt[]) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (bt[i] > bt[j]) {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void findavgtim(int processes[], int n, int bt[]) {
    int wt[n], tat[n], tot_wt = 0, tot_tat = 0;

    sortByBurstTime(processes, n, bt);
    findwtTime(processes, n, wt, bt);
    findtatTime(processes, n, wt, bt, tat);

    printf("Processes BurstTime WaitingTime TurnAroundTime\n");

    for (int i = 0; i < n; i++) {
        tot_wt += wt[i];
        tot_tat += tat[i];
        printf("    %d\t   %d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    float avg_wt = (float)tot_wt / n;
    float avg_tat = (float)tot_tat / n;
    printf("Avg Waiting Time = %f\n", avg_wt);
    printf("Avg Turn Around Time = %f\n", avg_tat);
}

int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {10, 5, 8};

    findavgtim(processes, n, burst_time);
    return 0;
}