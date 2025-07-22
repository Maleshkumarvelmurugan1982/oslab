#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_LEN 100

int main() {
    int pipe1[2], pipe2[2];
    char input[MAX_LEN];

    // Create pipes once
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    // Fork child 1
    int pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        // Child 1: Count vowels
        close(pipe1[1]); // Close write end

        while (1) {
            char buf[MAX_LEN];
            read(pipe1[0], buf, MAX_LEN);
            if (strcmp(buf, "-1") == 0) break;

            int vowel_count = 0;
            for (int i = 0; buf[i]; i++) {
                char ch = tolower(buf[i]);
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                    vowel_count++;
                }
            }
            printf("Child 1: Number of vowels = %d\n", vowel_count);
        }

        close(pipe1[0]);
        printf("Child 1: Exiting...\n");
        exit(0);
    }

    // Fork child 2
    int pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        // Child 2: Check palindrome
        close(pipe2[1]); // Close write end

        while (1) {
            char buf[MAX_LEN];
            read(pipe2[0], buf, MAX_LEN);
            if (strcmp(buf, "-1") == 0) break;

            int is_palindrome = 1;
            int len = strlen(buf);
            for (int i = 0, j = len - 1; i < j; i++, j--) {
                if (tolower(buf[i]) != tolower(buf[j])) {
                    is_palindrome = 0;
                    break;
                }
            }

            if (is_palindrome)
                printf("Child 2: The string is a palindrome\n");
            else
                printf("Child 2: The string is not a palindrome\n");
        }

        close(pipe2[0]);
        printf("Child 2: Exiting...\n");
        exit(0);
    }

    // Parent process
    close(pipe1[0]); // Close read ends in parent
    close(pipe2[0]);

    while (1) {
        printf("Enter a string (-1 to exit): ");
        scanf("%s", input);

        // Send input to both children
        write(pipe1[1], input, MAX_LEN);
        write(pipe2[1], input, MAX_LEN);

        if (strcmp(input, "-1") == 0) {
            printf("Parent: Exit condition met. Goodbye!\n");
            break;
        }
    }

    close(pipe1[1]);
    close(pipe2[1]);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    return 0;
}

