#include<stdio.h>

void sort(int proc_id[], int p[], int at[], int bt[], int b[], int n, int priority_type)
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((priority_type == 1 && p[i] > p[j]) || (priority_type == 2 && p[i] < p[j]))
            {
                // Swap priorities
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;

                // Swap arrival times
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap backup burst times
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;

                // Swap process IDs
                temp = proc_id[i];
                proc_id[i] = proc_id[j];
                proc_id[j] = temp;
            }
        }
    }
}

void main()
{
    int n, c = 0, priority_type;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int proc_id[n], at[n], bt[n], ct[n], tat[n], wt[n], m[n], b[n], rt[n], p[n];
    double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;

    printf("Enter priorities (1 for higher number means higher priority, 2 for lower number means higher priority): ");
    scanf("%d", &priority_type);

    for (int i = 0; i < n; i++)
    {
        proc_id[i] = i + 1;
        m[i] = 0;
    }

    printf("Enter priorities:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &at[i]);

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
        b[i] = bt[i];
        m[i] = -1;
        rt[i] = -1;
    }

    sort(proc_id, p, at, bt, b, n, priority_type);

    int count = 0, x = 0;
    c = 0;
    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= c && b[i] > 0 && m[i] != 1)
            {
                if (!found || (priority_type == 1 && p[i] > p[x]) || (priority_type == 2 && p[i] < p[x]))
                {
                    x = i;
                    found = 1;
                }
            }
        }
        if (found && b[x] > 0)
        {
            if (rt[x] == -1)
                rt[x] = c - at[x];
            b[x]--;
            c++;
            if (b[x] == 0)
            {
                count++;
                ct[x] = c;
                m[x] = 1;
            }
        }
        else
        {
            c++;
        }
    }

    for (int i = 0; i < n; i++)
        tat[i] = ct[i] - at[i];

    for (int i = 0; i < n; i++)
        wt[i] = tat[i] - bt[i];

    printf("Priority scheduling (Pre-Emptive):\n");
    printf("PID\tPrior\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

    for (int i = 0; i < n; i++)
    {
        ttat += tat[i];
        twt += wt[i];
    }
    avg_tat = ttat / (double)n;
    avg_wt = twt / (double)n;
    printf("\nAverage turnaround time: %lfms\n", avg_tat);
    printf("\nAverage waiting time: %lfms\n", avg_wt);
}
