#include <stdio.h>

void findwtTime(int processes[],int n, int wt[],int bt[]){
    wt[0] = 0;
    for(int i = 1; i<n; i++){
        wt[i]=bt[i-1] + wt[i-1];
    }
}

void findtatTime(int processes[], int n, int wt[], int bt[], int tat[]){
    for(int i = 0; i<n ;i++){
        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime(int processes[], int n, int bt[]){
    int wt[n], tat[n], tot_wt = 0, tot_tat = 0;
    findwtTime(processes,n,wt,bt);
    findtatTime(processes,n,wt,bt,tat);
    printf("Processes Bursttime waitingtime turnaroundtime\n");
    for(int i = 0; i<n; i++){
        tot_wt = tot_wt + wt[i];
        tot_tat = tot_tat + tat[i];
        printf("%d %d %d %d \n", processes[i], bt[i], wt[i], tat[i]);
    }
    float avg_wt = (float) tot_wt/ (float) n;
    float avg_tat = (float) tot_tat/ (float) n;
    printf("Avg waiting time = %f\n", avg_wt);
    printf("Avg turnaround time = %f\n", avg_tat);

}

int main(){
    int processess[]={1,2,3};
    int n = sizeof processess / sizeof processess[0];
    int burst_time[] = {10,5,8};
    findavgTime(processess,n,burst_time);
}