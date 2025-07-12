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
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        exit(1);
    }
    printf("Enter a string: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = '\0'; 
    int pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid1 == 0) {
        close(pipe1[1]); 
        char buf[MAX_LEN];
        read(pipe1[0], buf, MAX_LEN);
        close(pipe1[0]);
        int vowel_count = 0;
        for (int i = 0; buf[i]; i++) {
            char ch = tolower(buf[i]);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                vowel_count++;
            }
        }
        printf("Child 1: Number of vowels = %d\n", vowel_count);
        exit(0);
    } else {
        int pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (pid2 == 0) {
            close(pipe2[1]); 
            char buf[MAX_LEN];
            read(pipe2[0], buf, MAX_LEN);
            close(pipe2[0]);
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
            exit(0);
        } else {
            close(pipe1[0]); 
            write(pipe1[1], input, strlen(input) + 1);
            close(pipe1[1]);
            close(pipe2[0]);
            write(pipe2[1], input, strlen(input) + 1);
            close(pipe2[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}
