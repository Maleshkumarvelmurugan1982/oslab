#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];

    // Create the pipes once outside the loop
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
        // Child 1 process
        close(pipe1[1]); // Close write end

        while (1) {
            int x;
            read(pipe1[0], &x, sizeof(x));
            if (x == -1) break;

            if (x % 2 != 0)
                printf("Child 1: %d is an ODD number\n", x);
            else
                printf("Child 1: %d is NOT an odd number\n", x);
        }

        close(pipe1[0]);
        printf("Child 1: Exiting...\n");
        exit(0);
    }

    int pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        // Child 2 process
        close(pipe2[1]); // Close write end

        while (1) {
            int x;
            read(pipe2[0], &x, sizeof(x));
            if (x == -1) break;

            if (x % 2 == 0)
                printf("Child 2: %d is an EVEN number\n", x);
            else
                printf("Child 2: %d is NOT an even number\n", x);
        }

        close(pipe2[0]);
        printf("Child 2: Exiting...\n");
        exit(0);
    }

    // Parent process
    close(pipe1[0]); // Close read ends
    close(pipe2[0]);

    while (1) {
        int num;
        printf("Enter an integer (-1 to exit): ");
        scanf("%d", &num);

        // Send input to both children
        write(pipe1[1], &num, sizeof(num));
        write(pipe2[1], &num, sizeof(num));

        if (num == -1) {
            printf("Parent: Exit condition met. Goodbye!\n");
            break;
        }
    }

    // Close write ends in parent after done
    close(pipe1[1]);
    close(pipe2[1]);

    // Wait for both children to terminate
    wait(NULL);
    wait(NULL);

    return 0;
}

