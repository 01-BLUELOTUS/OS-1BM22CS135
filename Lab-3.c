#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
    char name[5];
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int isSystem; // 1 for system process, 0 for user process
};

void FCFS(struct process p[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].AT)
            current_time = p[i].AT;

        p[i].CT = current_time + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;

        current_time = p[i].CT;
    }
}

int main() {
    int n, sys_count = 0, user_count = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n], system_p[n], user_p[n];
    printf("Enter the arrival time, burst time and type (1 for system process, 0 for user process) for all the processes:\n");

    for (int i = 0; i < n; i++) {
        printf("\n\nProcess %d:\n", i + 1);
        sprintf(p[i].name, "p%d", i + 1);
        printf("Arrival time: ");
        scanf("%d", &p[i].AT);
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);
        printf("Type (1 for system, 0 for user): ");
        scanf("%d", &p[i].isSystem);

        if (p[i].isSystem) {
            system_p[sys_count++] = p[i];
        } else {
            user_p[user_count++] = p[i];
        }
    }

    for (int i = 0; i < sys_count - 1; i++) {
        for (int j = 0; j < sys_count - i - 1; j++) {
            if (system_p[j].AT > system_p[j + 1].AT) {
                struct process temp = system_p[j];
                system_p[j] = system_p[j + 1];
                system_p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < user_count - 1; i++) {
        for (int j = 0; j < user_count - i - 1; j++) {
            if (user_p[j].AT > user_p[j + 1].AT) {
                struct process temp = user_p[j];
                user_p[j] = user_p[j + 1];
                user_p[j + 1] = temp;
            }
        }
    }

    FCFS(system_p, sys_count);

    FCFS(user_p, user_count);

    int total_wt = 0, total_tat = 0;

    printf("\n\nProcess\tName\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tType\n");

    for (int i = 0; i < sys_count; i++) {
        printf("%d\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\tSystem\n", i + 1, system_p[i].name, system_p[i].AT, system_p[i].BT, system_p[i].CT, system_p[i].TAT, system_p[i].WT);
        total_wt += system_p[i].WT;
        total_tat += system_p[i].TAT;
    }

    for (int i = 0; i < user_count; i++) {
        printf("%d\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\tUser\n", i + 1 + sys_count, user_p[i].name, user_p[i].AT, user_p[i].BT, user_p[i].CT, user_p[i].TAT, user_p[i].WT);
        total_wt += user_p[i].WT;
        total_tat += user_p[i].TAT;
    }

    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    printf("\nAverage waiting time = %0.3f", avg_wt);
    printf("\nAverage turn around time = %0.3f\n", avg_tat);

    return 0;
}
