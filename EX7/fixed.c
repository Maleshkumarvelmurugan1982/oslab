#include <stdio.h>
#include <limits.h>

// Function prototypes
void firstFit(int n, int partitions[], int m, int processes[], int allocated[], int frag[]);
void bestFit(int n, int partitions[], int m, int processes[], int allocated[], int frag[]);
void worstFit(int n, int partitions[], int m, int processes[], int allocated[], int frag[]);

int main() {
    int n, m, i, choice;

    printf("Enter number of partitions: ");
    scanf("%d", &n);

    int originalPartitions[n];
    printf("Enter size of each partition:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &originalPartitions[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &m);
    int processes[m];
    printf("Enter size of each process:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &processes[i]);
    }

    while (1) {
        printf("\nSelect Allocation Method:\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        // Reset partitions for fresh allocation
        int partitions[n], allocated[m], frag[m];
        for (i = 0; i < n; i++) partitions[i] = originalPartitions[i];
        for (i = 0; i < m; i++) {
            allocated[i] = -1; 
            frag[i] = -1;
        }

        if (choice == 1)
            firstFit(n, partitions, m, processes, allocated, frag);
        else if (choice == 2)
            bestFit(n, partitions, m, processes, allocated, frag);
        else if (choice == 3)
            worstFit(n, partitions, m, processes, allocated, frag);
        else {
            printf("Invalid Choice!\n");
            continue;
        }

        // Display allocation result
        printf("\nProcess\tSize\tPartition\tInternal Frag.\n");
        int totalExternalFrag = 0;
        for (i = 0; i < m; i++) {
            if (allocated[i] != -1) {
                printf("P%d\t%d\t%d\t\t%d\n", i+1, processes[i], allocated[i]+1, frag[i]);
            } else {
                printf("P%d\t%d\tNot Allocated\t-\n", i+1, processes[i]);
            }
        }

        // Calculate total external fragmentation
        for (i = 0; i < n; i++)
            if (partitions[i] > 0) totalExternalFrag += partitions[i];

        printf("Total External Fragmentation: %d\n", totalExternalFrag);
    }

    return 0;
}

// First Fit Allocation
void firstFit(int n, int partitions[], int m, int processes[], int allocated[], int frag[]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (processes[i] <= partitions[j]) {
                allocated[i] = j;
                frag[i] = partitions[j] - processes[i]; // store fragmentation
                partitions[j] = 0; // block partition reuse
                break;
            }
        }
    }
}

// Best Fit Allocation
void bestFit(int n, int partitions[], int m, int processes[], int allocated[], int frag[]) {
    for (int i = 0; i < m; i++) {
        int idx = -1, min = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (processes[i] <= partitions[j] && partitions[j] - processes[i] < min) {
                min = partitions[j] - processes[i];
                idx = j;
            }
        }
        if (idx != -1) {
            allocated[i] = idx;
            frag[i] = partitions[idx] - processes[i];
            partitions[idx] = 0; // partition can't be reused
        }
    }
}

// Worst Fit Allocation
void worstFit(int n, int partitions[], int m, int processes[], int allocated[], int frag[]) {
    for (int i = 0; i < m; i++) {
        int idx = -1, max = -1;
        for (int j = 0; j < n; j++) {
            if (processes[i] <= partitions[j] && partitions[j] - processes[i] > max) {
                max = partitions[j] - processes[i];
                idx = j;
            }
        }
        if (idx != -1) {
            allocated[i] = idx;
            frag[i] = partitions[idx] - processes[i];
            partitions[idx] = 0; // partition can't be reused
        }
    }
}
