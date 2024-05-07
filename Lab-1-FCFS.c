#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct process
{
    char name[5]; // Process name
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

int main()
{
    int n, temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    printf("Enter the arrival time and burst time for all the processes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("\n\nProcess %d:\n", i + 1);
        sprintf(p[i].name, "p%d", i + 1);
        printf("Arrival time: ");
        scanf("%d", &p[i].AT);
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);
    }

    // Sorting processes based on arrival time (FCFS)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].AT > p[j + 1].AT)
            {
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

    // Calculate completion time, waiting time, and turnaround time
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].AT)
            current_time = p[i].AT;

        p[i].CT = current_time + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;

        current_time = p[i].CT;
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
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, p[i].name, p[i].AT, p[i].BT,
               p[i].CT, p[i].TAT, p[i].WT);
    }
    printf("\n");
    printf("Average waiting time = %0.3f",s);
    printf("\n");
    printf("Average turn around time = %0.3f ",t);

    return 0;
}
