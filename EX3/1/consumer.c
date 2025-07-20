#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>  // for exit()

int main() {
    key_t key = 1234;
    int shmid = shmget(key, 100, 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    char *data = (char *) shmat(shmid, NULL, 0);
    if (data == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Read and display
    printf("Received message: %s\n", data);

    // Detach and remove
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
