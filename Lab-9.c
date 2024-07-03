#include <stdio.h>

void Print(char *method, int PSize[], int Alloc[], int BSize[], int n, int m) {
    printf("\nMemory Management Scheme - %s\n", method);
    printf("File_no\tFile_size\tBlock_no\tBlock_size\tFragment\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t", i + 1, PSize[i]);
        if (Alloc[i] != -1)
            printf("%d\t\t%d\t\t%d\n", Alloc[i] + 1, BSize[Alloc[i]], BSize[Alloc[i]] - PSize[i]);
        else
            printf("Not Allocated\t-\t\t-\n");
    }
}

void firstFit(int BSize[], int m, int PSize[], int n, int Alloc[], int BSizeCopy[]) {
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

    Print("First Fit", PSize, Alloc, BSizeCopy, n, m);
}

void bestFit(int BSize[], int m, int PSize[], int n, int Alloc[], int BSizeCopy[]) {
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

    Print("Best Fit", PSize, Alloc, BSizeCopy, n, m);
}

void worstFit(int BSize[], int m, int PSize[], int n, int Alloc[], int BSizeCopy[]) {
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

    Print("Worst Fit", PSize, Alloc, BSizeCopy, n, m);
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

    printf("Enter number of files: ");
    scanf("%d", &n);
    int PSize[n];
    printf("Enter sizes of the files: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &PSize[i]);
    }

    int Alloc[n];

    firstFit(BSize, m, PSize, n, Alloc, BSize);
    bestFit(BSize2, m, PSize, n, Alloc, BSize2);
    worstFit(BSize3, m, PSize, n, Alloc, BSize3);

    return 0;
}
