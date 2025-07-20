#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    key_t key = 9999;
    int *mat;

    // Wait for producer to create the memory
    int shmid;
    while ((shmid = shmget(key, 0, 0666)) < 0) {
        printf("Waiting for producer...\n");
        sleep(1);
    }

    // Attach
    mat = (int *) shmat(shmid, NULL, 0);
    if (mat == (int *) -1) {
        perror("shmat failed in consumer");
        exit(1);
    }

    int n = mat[0];

    int total = 3 * n * n + 1;
    shmid = shmget(key, total * sizeof(int), 0666);
    if (shmid < 0) {
        perror("shmget failed in consumer");
        exit(1);
    }

    // Compute remaining rows
    for (int i = n / 2; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[1 + 2 * n * n + i * n + j] = 0;
            for (int k = 0; k < n; k++) {
                mat[1 + 2 * n * n + i * n + j] +=
                    mat[1 + i * n + k] * mat[1 + n * n + k * n + j];
            }
        }
    }

    // Print result
    printf("Product Matrix (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[1 + 2 * n * n + i * n + j]);
        }
        printf("\n");
    }

    shmdt(mat);
    shmctl(shmid, IPC_RMID, NULL); // remove shared memory

    return 0;
}
