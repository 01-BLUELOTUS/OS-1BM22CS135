#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>

struct Process {
    char name[5]; // Process name
    int AT, BT, ST[20], WT, FT, TAT, pos, CT, RT;
};

int quant;

int main() {
    int n, temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter the arrival time and burst time for all the processes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("\n\nProcess %d:\n", i + 1);
        sprintf(p[i].name, "p%d", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].AT);
        printf("Burst Time: ");
        scanf("%d", &p[i].BT);
        p[i].pos = i + 1;
    }

    printf("Enter the quantum: ");
    scanf("%d", &quant);

    // Initializing variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];

    // Initializing burst and arrival time arrays
    int index = -1;
    for(int i = 0; i < n; i++) {
        b[i] = p[i].BT;
        a[i] = p[i].AT;
        for(int j = 0; j < 20; j++) {
            s[i][j] = -1;
        }
    }

    int tot_wt = 0, tot_tat = 0, tot_rt = 0;
    bool flag = false;

    while(c != 0) {
        mini = INT_MAX;
        flag = false;

        for(int i = 0; i < n; i++) {
            float p = time + 0.1;
            if(a[i] <= p && mini > a[i] && b[i] > 0) {
                index = i;
                mini = a[i];
                flag = true;
            }
        }

        // If no process is available at this moment
        if(!flag) {
            time++;
            continue;
        }

        // Calculating start time
        int j = 0;
        while(s[index][j] != -1) {
            j++;
        }

        if(s[index][j] == -1) {
            s[index][j] = time;
            p[index].ST[j] = time;
        }

        if(b[index] <= quant) {
            time += b[index];
            b[index] = 0;
        }
        else {
            time += quant;
            b[index] -= quant;
        }

        if(b[index] > 0) {
            a[index] = time + 0.1;
        }

        // Calculating arrival, burst, final times
        if(b[index] == 0) {
            c--;
            p[index].FT = time;
            p[index].WT = p[index].FT - p[index].AT - p[index].BT;
            tot_wt += p[index].WT;
            p[index].TAT = p[index].BT + p[index].WT;
            tot_tat += p[index].TAT;
            p[index].CT = time;
            p[index].RT = p[index].ST[0] - p[index].AT;
            tot_rt += p[index].RT;
        }
    } // end of while loop

    // Printing output
    printf("\n\nProcess\tName\tArrival Time\tBurst Time\tStart time\tFinal time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t\t%d\t\t", p[i].pos, p[i].name, p[i].AT, p[i].BT);
        int j = 0;
        while(s[i][j] != -1) {
            printf("%d ", p[i].ST[j]);
            j++;
        }
        printf("\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].FT, p[i].CT, p[i].TAT, p[i].WT, p[i].RT);
    }

    // Calculating average wait time, turnaround time, and response time
    double avg_wt = (double) tot_wt / n;
    double avg_tat = (double) tot_tat / n;
    double avg_rt = (double) tot_rt / n;

    // Printing average wait time, turnaround time, and response time
    printf("\nThe average wait time is : %lf\n", avg_wt);
    printf("The average Turnaround time is : %lf\n", avg_tat);
    printf("The average Response time is : %lf\n", avg_rt);

    return 0;
}
