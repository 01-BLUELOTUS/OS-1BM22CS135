#include <stdio.h>
#include <stdbool.h>

void Need(int n, int m, int max[n][m], int alloc[n][m], int need[n][m])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe(int n, int m, int avai[m], int alloc[n][m], int need[n][m], int safeSequence[n])
{
    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = avai[i];

    bool finish[n];
    for (int i = 0; i < n; i++)
        finish[i] = false;

    int count = 0;

    while (count < n)
    {
        bool found = false;
        for (int p = 0; p < n; p++)
        {
            if (!finish[p])
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[p][j] > work[j])
                        break;
                }
                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[p][k];
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void printTable(int n, int m, int alloc[n][m], int max[n][m], int need[n][m], int avai[m], int safeSequence[n], bool is_safe)
{
    printf("\nProcess\tAllocation\tMaximum\t\tNeed\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) printf("%-2d ", alloc[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%-2d ", max[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%-2d ", need[i][j]);
        printf("\n");
    }

    if (is_safe)
    {
        int work[m];
        for (int i = 0; i < m; i++) work[i] = avai[i];

        for (int count = 0; count < n; count++)
        {
            int p = safeSequence[count];
            for (int j = 0; j < m; j++)
            {
                work[j] += alloc[p][j];
            }
            printf("After P%d execution, available: ", p);
            for (int j = 0; j < m; j++)
            {
                printf("%-2d ", work[j]);
            }
            printf("\n");
        }
    }
}

int main()
{
    int n, m;

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int avai[m];
    int max[n][m];
    int alloc[n][m];
    int need[n][m];
    int safeSequence[n];

    printf("Enter the available m (R1 R2 ... Rn):\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &avai[i]);
    }

    printf("Enter the maximum resource matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    Need(n, m, max, alloc, need);

    bool is_safe = isSafe(n, m, avai, alloc, need, safeSequence);

    printTable(n, m, alloc, max, need, avai, safeSequence, is_safe);

    if (is_safe)
    {
        printf("\nThe system is in a safe state.\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}
