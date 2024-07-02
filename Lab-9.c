#include <stdio.h>

void Print(char *method, int PSize[], int Alloc[], int n) {
    printf("\n%s Allocation:\nProcess No.\tProcess Size\tBlock no.\n", method);
    for (int i = 0; i < n; i++) {
        printf(" %i\t\t%i\t\t", i + 1, PSize[i]);
        if (Alloc[i] != -1)
            printf("%i", Alloc[i] + 1);
        else
            printf("Not Allocated, waiting");
        printf("\n");
    }
}

void firstFit(int BSize[], int m, int PSize[], int n, int Alloc[]) {
    for (int i = 0; i < n; i++)
        Alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (BSize[j] >= PSize[i]) {
                Alloc[i] = j;
                BSize[j] -= PSize[i];
                break;
            }
        }
    }
}

void bestFit(int BSize[], int m, int PSize[], int n, int Alloc[]) {
    for (int i = 0; i < n; i++)
        Alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (BSize[j] >= PSize[i] && (bestIdx == -1 || BSize[j] < BSize[bestIdx])) {
                bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            Alloc[i] = bestIdx;
            BSize[bestIdx] -= PSize[i];
        }
    }
}

void worstFit(int BSize[], int m, int PSize[], int n, int Alloc[]) {
    for (int i = 0; i < n; i++)
        Alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (BSize[j] >= PSize[i] && (worstIdx == -1 || BSize[j] > BSize[worstIdx])) {
                worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            Alloc[i] = worstIdx;
            BSize[worstIdx] -= PSize[i];
        }
    }
}

int main() {
    int m, n;
    printf("Enter number of blocks: ");
    scanf("%d", &m);
    int BSize[m], BSize2[m], BSize3[m];
    printf("Enter sizes of the blocks: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &BSize[i]);
        BSize2[i] = BSize[i];
        BSize3[i] = BSize[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int PSize[n];
    printf("Enter sizes of the processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &PSize[i]);
    }

    int Alloc[n];

    firstFit(BSize, m, PSize, n, Alloc);
    Print("First Fit", PSize, Alloc, n);

    bestFit(BSize2, m, PSize, n, Alloc);
    Print("Best Fit", PSize, Alloc, n);

    worstFit(BSize3, m, PSize, n, Alloc);
    Print("Worst Fit", PSize, Alloc, n);

    return 0;
}
