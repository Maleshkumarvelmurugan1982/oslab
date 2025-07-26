#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    key_t key = 1234;  // same fixed key
    int msgid;
    struct msg_buffer message;

    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        return 1;
    }

    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv failed");
        return 1;
    }

    printf("Consumer: Received message: %s\n", message.msg_text);

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl (remove queue) failed");
        return 1;
    }

    return 0;
}
