#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void fifo(int F[], int n, int P[], int m) 
{
    int index = 0;
    int p_fault = 0;

    for (int i = 0; i < m; i++) 
    {
        bool found = false;
        for (int j = 0; j < n; j++) 
        {
            if (F[j] == P[i]) 
            {
                found = true;
                break;
            }
        }

        if (!found) 
        {
            F[index] = P[i];
            index = (index + 1) % n;
            p_fault++;
        }
    }

    printf("FIFO Page Faults: %d\n", p_fault);
}

void lru(int F[], int n, int P[], int m) 
{
    int LU[n];
    int p_fault = 0;
    int count = 0;

    for (int i = 0; i < n; i++) 
    {
        F[i] = -1;
        LU[i] = -1;
    }

    for (int i = 0; i < m; i++) 
    {
        int j;
        bool found = false;

        for (j = 0; j < n; j++) 
        {
            if (F[j] == P[i]) 
            {
                found = true;
                LU[j] = count++;
                break;
            }
        }

        if (!found) 
        {
            int lru_index = 0;
            for (j = 1; j < n; j++) 
            {
                if (LU[j] < LU[lru_index]) 
                {
                    lru_index = j;
                }
            }
            F[lru_index] = P[i];
            LU[lru_index] = count++;
            p_fault++;
        }
    }

    printf("LRU Page Faults: %d\n", p_fault);
}

void optimal(int F[], int n, int P[], int m) 
{
    int p_fault = 0;

    for (int i = 0; i < n; i++) 
    {
        F[i] = -1;
    }

    for (int i = 0; i < m; i++) 
    {
        bool found = false;
        for (int j = 0; j < n; j++) 
        {
            if (F[j] == P[i]) 
            {
                found = true;
                break;
            }
        }

        if (!found) 
        {
            int replace_i = -1;
            int far = i + 1;

            for (int j = 0; j < n; j++) 
            {
                int k;
                for (k = i + 1; k < m; k++) 
                {
                    if (F[j] == P[k]) 
                    {
                        if (k > far) 
                        {
                            far = k;
                            replace_i = j;
                        }
                        break;
                    }
                }

                if (k == m) 
                {
                    replace_i = j;
                    break;
                }
            }

            if (replace_i == -1) 
            {
                replace_i = 0;
            }

            F[replace_i] = P[i];
            p_fault++;
        }
    }

    printf("Optimal Page Faults: %d\n", p_fault);
}

int main() 
{
    int n; 
    int m; 

    printf("Enter the number of Frames: ");
    scanf("%d", &n);

    printf("Enter the length of reference string: ");
    scanf("%d", &m);

    int P[m];
    printf("Enter the reference string: ");
    for (int i = 0; i < m; i++) 
    {
        scanf("%d", &P[i]);
    }

    int F[n];
    for (int i = 0; i < n; i++)
    {
        F[i] = -1;
    }

    fifo(F, n, P, m);
    lru(F, n, P, m);
    optimal(F, n, P, m);

    return 0;
}
