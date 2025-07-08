#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t p2 = fork();

    if (p2 == 0) {
        // P2 process
        pid_t p4 = fork();
        if (p4 == 0) {
            // P4 process
            pid_t p6 = fork();
            if (p6 == 0) {
                // P6 process
                printf("P6: PID = %d, PPID = %d — Child of P4\n", getpid(), getppid());
                exit(0);
            } else {
                wait(NULL); // wait for P6
                printf("P4: PID = %d, PPID = %d — Child of P2\n", getpid(), getppid());
                exit(0);
            }
        } else {
            wait(NULL); // wait for P4
            printf("P2: PID = %d, PPID = %d — Child of P1\n", getpid(), getppid());
            exit(0);
        }

    } else {
        wait(NULL); // wait for P2, P4, P6

        pid_t p3 = fork();
        if (p3 == 0) {
            // P3 process
            pid_t p5 = fork();
            if (p5 == 0) {
                // P5 process
                pid_t p7 = fork();
                if (p7 == 0) {
                    // P7 process
                    printf("P7: PID = %d, PPID = %d — Child of P5\n", getpid(), getppid());
                    exit(0);
                } else {
                    wait(NULL); // wait for P7

                    pid_t p8 = fork();
                    if (p8 == 0) {
                        // P8 process
                        printf("P8: PID = %d, PPID = %d — Child of P5\n", getpid(), getppid());
                        exit(0);
                    } else {
                        wait(NULL); // wait for P8
                        printf("P5: PID = %d, PPID = %d — Child of P3\n", getpid(), getppid());
                        exit(0);
                    }
                }

            } else {
                wait(NULL); // wait for P5 (P7, P8)
                printf("P3: PID = %d, PPID = %d — Child of P1\n", getpid(), getppid());
                exit(0);
            }

        } else {
            wait(NULL); // wait for P3 and its children
            printf("P1: PID = %d, PPID = %d — Root process\n", getpid(), getppid());
        }
    }

    return 0;
}
