#include <stdio.h>

int main() {
    int n, m, i, j, k;

    // Take user input for number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m];

    // Take user input for allocation matrix
    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Take user input for request matrix
    printf("Enter the request matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Take user input for available resources
    printf("Enter the available resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    int finish[n], safeSeq[n], work[m], flag;
    for (i = 0; i < n; i++) {
        finish[i] = 0; // Initially all processes are unfinished
    }

    // Copy available resources to work array
    for (j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    int count = 0;
    while (count < n) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canProceed = 1;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = 0;
                        break;
                    }
                }
                if (canProceed) {
                    for (k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    flag = 1;
                }
            }
        }
        if (flag == 0) {
            break;
        }
    }

    // Check for deadlock
    int deadlock = 0;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            deadlock = 1;
            printf("System is in a deadlock state.\n");
            printf("The deadlocked processes are: ");
            for (j = 0; j < n; j++) {
                if (finish[j] == 0) {
                    printf("P%d ", j);
                }
            }
            printf("\n");
            break;
        }
    }

    if (deadlock == 0) {
        printf("System is in safe state.\n");
        printf("Safe Sequence is: ");
        for (i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    }

    return 0;
}
