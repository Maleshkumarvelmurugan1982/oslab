#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork(); // P1 forks P2

    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        // This is P2
        pid2 = fork(); // P2 forks P3

        if (pid2 < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid2 == 0) {
            // This is P3
            printf("P3: PID = %d, PPID = %d (child of P2)\n", getpid(), getppid());
        } else {
            // P2 waits for P3 to finish
            wait(NULL);
            printf("P2: PID = %d, PPID = %d (child of P1)\n", getpid(), getppid());
        }
    } else {
        // P1 waits for P2 to finish
        wait(NULL);
        printf("P1: PID = %d, PPID = %d (original process)\n", getpid(), getppid());
    }

    return 0;
}
