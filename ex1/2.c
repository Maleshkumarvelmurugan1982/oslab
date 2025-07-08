#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork(); // fork P2

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // P2 process
        sleep(1);
        printf("P2: PID = %d, PPID = %d (child of P1)\n", getpid(), getppid());
        exit(0);
    } else {
        // P1 waits for P2
        wait(NULL);

        pid_t pid2 = fork(); // fork P3

        if (pid2 < 0) {
            perror("Second fork failed");
            exit(1);
        }

        if (pid2 == 0) {
            // P3 process
            sleep(1);
            printf("P3: PID = %d, PPID = %d (child of P1)\n", getpid(), getppid());
            exit(0);
        } else {
            // P1 waits for P3
            wait(NULL);
            // Now print P1 info after both children are done
            printf("P1: PID = %d, PPID = %d (root process)\n", getpid(), getppid());
        }
    }

    return 0;
}
