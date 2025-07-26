#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main() {
    key_t key = 1234;
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

    // Write message to shared memory
    printf("Enter a single word: ");
    scanf("%99s", data);  // reads only one word

    // Detach from shared memory
    shmdt(data);

    return 0;
}

