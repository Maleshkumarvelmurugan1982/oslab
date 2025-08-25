#include<stdio.h>

int wrt, rc;  
char sharedData[100];  // shared variable

void startWrite() {
    if (wrt == 1) {   // only if no writer already writing
        wrt = 0;  // lock writer
        printf("Enter data to write (single word): ");
        scanf("%s", sharedData);
        printf("Writer started writing: %s\n", sharedData);
    } else {
        printf("Another writer is already writing → Wait.\n");
    }
}

void endWrite() {
    if (wrt == 0) {   // only if a writer is active
        wrt = 1;   // unlock writer
        printf("Writer finished and released lock.\n");
    } else {
        printf("No writer is currently writing.\n");
    }
}

void startRead() {
    rc++;
    printf("Reader entered → %d readers active\n", rc);
    printf("Reading data: %s\n", sharedData);
}

void endRead() {
    if (rc > 0) {
        rc--;
        printf("Reader exited → %d readers active\n", rc);
    } else {
        printf("No readers to exit!\n");
    }
}

int main() {
    wrt = 1;   // writer free initially
    rc = 0;
    sharedData[0] = '\0';  // initially empty
    
    int s;
    do {
        printf("\nSelect an Option\n");
        printf("1. Start Writing\n");
        printf("2. Stop Writing\n");
        printf("3. Start Reading\n");
        printf("4. Stop Reading\n");
        printf("5. Exit\n");
        scanf("%d", &s);
        switch(s) {
            case 1:
                startWrite();
                break;
            case 2:
                endWrite();
                break;
            case 3:
                startRead();
                break;
            case 4:
                endRead();
                break;
        }
    } while(s < 5);
    
    return 0;
}
