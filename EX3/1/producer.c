#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = 1234;
    int shmid = shmget(key, 100, 0666 | IPC_CREAT);
    char *data = (char *) shmat(shmid, NULL, 0);

    // Write message to shared memory
    printf("Enter message: ");
    scanf("%s", data);

    // Detach
    shmdt(data);

    return 0;
}
