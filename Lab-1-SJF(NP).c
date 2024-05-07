#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
    char name[5]; // Process name
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int executed; // Flag to mark if the process has been executed
};

// Function to find the process with the shortest burst time among the arrived processes
int findShortestJob(struct process p[], int n, int current_time) {
    int SJ_index = -1;
    int SJ_burst = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (p[i].AT <= current_time && p[i].executed == 0 && p[i].BT < SJ_burst) {
            SJ_index = i;
            SJ_burst = p[i].BT;
        }
    }

    return SJ_index;
}

int main() {
    int n, temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    printf("Enter the arrival time and burst time for all the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("\n\nProcess %d:\n", i + 1);
        sprintf(p[i].name, "p%d", i + 1);
        printf("Arrival time: ");
        scanf("%d", &p[i].AT);
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);
        p[i].executed = 0;
    }

    // Sort processes based on arrival time (FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].AT > p[j + 1].AT) {
                // Swap
                temp = p[j].AT;
                p[j].AT = p[j + 1].AT;
                p[j + 1].AT = temp;

                temp = p[j].BT;
                p[j].BT = p[j + 1].BT;
                p[j + 1].BT = temp;

                char temp_name[5];
                strcpy(temp_name, p[j].name);
                strcpy(p[j].name, p[j + 1].name);
                strcpy(p[j + 1].name, temp_name);
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        int SJ_index = findShortestJob(p, n, current_time);
        if (SJ_index == -1) {
            // No process available to execute, move to the next arrival time
            current_time = p[i].AT;
            SJ_index = findShortestJob(p, n, current_time);
        }

        // Execute the shortest job
        p[SJ_index].CT = current_time + p[SJ_index].BT;
        p[SJ_index].TAT = p[SJ_index].CT - p[SJ_index].AT;
        p[SJ_index].WT = p[SJ_index].TAT - p[SJ_index].BT;
        p[SJ_index].executed = 1;

        current_time = p[SJ_index].CT;
    }

    // Calculate average waiting time and average turnaround time
    int total_wt=0, total_tat=0;

    for(int i=0;i<n;i++)
    {
        total_wt+=p[i].WT;
        total_tat+=p[i].TAT;
    }

    float s=(float)total_wt / (float)n;
    float t=(float)total_tat / (float)n;


    // Print the details of each process
    printf("\n\nProcess\tName\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, p[i].name, p[i].AT, p[i].BT,
               p[i].CT, p[i].TAT, p[i].WT);
    }
    
    printf("\n");
    printf("Average waiting time = %0.3f",s);
    printf("\n");
    printf("Average turn around time = %0.3f ",t);


    return 0;
}
