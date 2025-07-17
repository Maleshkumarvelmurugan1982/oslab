
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num;
    int pipe1[2], pipe2[2];

    while (1) {
        printf("Enter an integer (-1 to exit): ");
        scanf("%d", &num);

        if (num == -1) {
            printf("Exit condition met. Goodbye!\n");
            break;
        }

        if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
            perror("Pipe failed");
            exit(1);
        }

        int pid1 = fork();
        if (pid1 < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid1 == 0) {
            // Child 1
            close(pipe1[1]);
            int x;
            read(pipe1[0], &x, sizeof(x));
            close(pipe1[0]);

            if (x % 2 != 0)
                printf("Child 1: %d is an ODD number\n", x);
            else
                printf("Child 1: %d is NOT an odd number\n", x);

            exit(0);
        } else {
            int pid2 = fork();
            if (pid2 < 0) {
                perror("Fork failed");
                exit(1);
            }

            if (pid2 == 0) {
                // Child 2
                close(pipe2[1]);
                int x;
                read(pipe2[0], &x, sizeof(x));
                close(pipe2[0]);

                if (x % 2 == 0)
                    printf("Child 2: %d is an EVEN number\n", x);
                else
                    printf("Child 2: %d is NOT an even number\n", x);

                exit(0);
            } else {
                // Parent
                close(pipe1[0]);
                write(pipe1[1], &num, sizeof(num));
                close(pipe1[1]);

                close(pipe2[0]);
                write(pipe2[1], &num, sizeof(num));
                close(pipe2[1]);

                wait(NULL);
                wait(NULL);
            }
        }
    }

    return 0;
}
