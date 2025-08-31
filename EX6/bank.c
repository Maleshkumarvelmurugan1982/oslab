#include <stdio.h>
#include <stdbool.h>
int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    int total[m];
    printf("Enter total instances of each resource:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &total[i]);
    int max[n][m];
    printf("Enter maximum resource demand for each process:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    int allot[n][m];
    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allot[i][j]);
    int avail[m];
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += allot[i][j];
        avail[j] = total[j] - sum;
    }
    printf("Calculated available resources: ");
    for (int j = 0; j < m; j++)
        printf("%d ", avail[j]);
    printf("\n");
    int need[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allot[i][j];
    bool finish[n];
    for (int i = 0; i < n; i++) finish[i] = false;
    int work[m];
    for (int i = 0; i < m; i++) work[i] = avail[i];
    int safeSeq[n];
    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == m) {  // Process can be executed
                    for (int k = 0; k < m; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }
    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    return 0;
}
