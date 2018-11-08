#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int **x, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d\t", x[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void bankers(int **max, int **allocation, int *available, int numberOfProcesses,
             int numberOfResources) {
    int **need, *completed, *safeSequnece, currProcess = -1, count = 0;
    need = (int **)malloc(sizeof(int *) * numberOfProcesses);
    for (int i = 0; i < numberOfResources; i++)
        need[i] = (int *)malloc(sizeof(int) * numberOfResources);
    for (int i = 0; i < numberOfProcesses; i++) {
        for (int j = 0; j < numberOfResources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
    completed = (int *)malloc(sizeof(int) * numberOfProcesses);
    memset(completed, 0, sizeof(completed));
    safeSequnece = (int *)malloc(sizeof(int) * numberOfProcesses);
    memset(safeSequnece, -1, sizeof(safeSequnece));
    do {
        for (int i = 0; i < numberOfProcesses; i++) {
            currProcess = i;
            if (!completed[i]) {
                for (int j = 0; j < numberOfResources; j++) {
                    if (need[i][j] > available[j]) {
                        currProcess = -1;
                        break;
                    }
                }
                if (currProcess == i) {
                    printf("Process %d completed\n", i + 1);
                    safeSequnece[count++] = i + 1;
                    completed[i] = 1;
                    for (int k = 0; k < numberOfResources; k++) {
                        available[k] += allocation[i][k];
                    }
                }
            }
        }
    } while (count != numberOfProcesses && currProcess != -1);
    if (count == numberOfProcesses) {
        printf("The system is safe\n");
        printf("The safe sequence: ");
        for (int i = 0; i < numberOfProcesses; i++)
            printf("%d ", safeSequnece[i]);
        printf("\n");
    } else {
        printf("Deadlock detected\n");
    }
}

int main() {
    int **max, **allocation, *available;
    int numberOfProcesses, numberOfResources;
    printf("Enter the number of Processes: ");
    scanf("%d", &numberOfProcesses);
    printf("Enter the number of Resources: ");
    scanf("%d", &numberOfResources);
    printf("\n\n");
    // Generate input
    printf("Enter the Max allocation:\n");
    max = (int **)malloc(sizeof(int *) * numberOfProcesses);
    for (int i = 0; i < numberOfResources; i++)
        max[i] = (int *)malloc(sizeof(int) * numberOfResources);
    for (int i = 0; i < numberOfProcesses; i++) {
        for (int j = 0; j < numberOfResources; j++) scanf("%d", &max[i][j]);
    }
    printf("Enter the Allocation matrix: \n");
    allocation = (int **)malloc(sizeof(int *) * numberOfProcesses);
    for (int i = 0; i < numberOfResources; i++)
        allocation[i] = (int *)malloc(sizeof(int) * numberOfResources);
    for (int i = 0; i < numberOfProcesses; i++) {
        for (int j = 0; j < numberOfResources; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("Enter the availabe resources: ");
    available = (int *)malloc(sizeof(int) * numberOfResources);
    for (int i = 0; i < numberOfResources; i++) scanf("%d", &available[i]);
    printf("The max matrix:\n");
    print(max, numberOfProcesses, numberOfResources);
    printf("The allocation matrix:\n");
    print(allocation, numberOfProcesses, numberOfResources);
    bankers(max, allocation, available, numberOfProcesses, numberOfResources);
    return 0;
}

/*
Enter the number of Processes: 2
Enter the number of Resources: 2


Enter the Max allocation:
3 3
2 1
Enter the Allocation matrix:
3 2
0 0
Enter the availabe resources: 0 1
The max matrix:
3	3
2	1


The allocation matrix:
3	2
0	0


Process 1 completed
Process 2 completed
The system is safe
The safe sequence: 1 2

*/