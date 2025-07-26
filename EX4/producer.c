#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    key_t key = 1234;  // fixed key
    int msgid;
    struct msg_buffer message;

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    message.msg_type = 1;

    printf("Producer: Enter a single word: ");
    if (scanf("%99s", message.msg_text) != 1) {
        printf("Failed to read input\n");
        return 1;
    }

    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd failed");
        return 1;
    }

    printf("Producer: Message sent successfully!\n");
    return 0;
}
