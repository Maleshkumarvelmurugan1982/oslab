#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: sum second half
        close(fd[0]); // Close read end

        int sum = 0;
        for (int i = n / 2; i < n; i++) {
            sum += arr[i];
        }

        printf("Child: Sum of second half = %d\n", sum);

        write(fd[1], &sum, sizeof(sum));  // Send sum to parent
        close(fd[1]);  // Close write end

        exit(0);
    } else {
        // Parent process: sum first half
        close(fd[1]); // Close write end

        int sum = 0;
        for (int i = 0; i < n / 2; i++) {
            sum += arr[i];
        }

        int child_sum;
        read(fd[0], &child_sum, sizeof(child_sum));  // Read child's sum
        close(fd[0]); // Close read end

        wait(NULL); // Wait for child to finish

        printf("Parent: Sum of first half = %d\n", sum);
        printf("Total sum = %d\n", sum + child_sum);
    }

    return 0;
} 
