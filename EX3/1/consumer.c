#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main() {
    key_t key = 1234;

    // Try to get the same shared memory segment
    int shmid = shmget(key, 100, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    char *data = (char *) shmat(shmid, NULL, 0);
    if (data == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Read and display the message
    printf("Received message: %s\n", data);

    // Detach from and remove the shared memory
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
