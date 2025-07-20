#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main() {
    key_t key = 9999;
    int n;

    printf("Enter size of matrix (n x n): ");
    scanf("%d", &n);

    int total = 3 * n * n + 1; // for A, B, result, and size
    int shmid = shmget(key, total * sizeof(int), 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed in producer");
        exit(1);
    }

    int *mat = (int *) shmat(shmid, NULL, 0);
    if (mat == (int *) -1) {
        perror("shmat failed in producer");
        exit(1);
    }

    mat[0] = n;

    printf("Enter matrix A (%dx%d):\n", n, n);
    for (int i = 0; i < n * n; i++) {
        scanf("%d", &mat[1 + i]);
    }

    printf("Enter matrix B (%dx%d):\n", n, n);
    for (int i = 0; i < n * n; i++) {
        scanf("%d", &mat[1 + n * n + i]);
    }

    // Compute first half of product
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            mat[1 + 2 * n * n + i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                mat[1 + 2 * n * n + i * n + j] +=
                    mat[1 + i * n + k] * mat[1 + n * n + k * n + j];
            }
        }
    }

    shmdt(mat);
    return 0;
}
