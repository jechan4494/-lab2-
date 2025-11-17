#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSIZE 100

struct msgbuf {
    long mtype;
    char mtext[MSGSIZE];
};

int main() {
    key_t key = 1234; // 메시지 큐 키
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msgbuf msg;
    char buf[MSGSIZE];

    if (fork()) { // 부모
        while (1) {
            printf("부모: "); fgets(buf, MSGSIZE, stdin);
            buf[strcspn(buf, "\n")] = 0;
            msg.mtype = 1;
            strcpy(msg.mtext, buf);
            msgsnd(msgid, &msg, strlen(msg.mtext)+1, 0);
            if (!strcmp(buf, "exit")) break;

            msgrcv(msgid, &msg, MSGSIZE, 2, 0);
            printf("자식: %s\n", msg.mtext);
            if (!strcmp(msg.mtext, "exit")) break;
        }
    } else { // 자식
        while (1) {
            msgrcv(msgid, &msg, MSGSIZE, 1, 0);
            printf("부모: %s\n", msg.mtext);
            if (!strcmp(msg.mtext, "exit")) break;

            printf("자식: "); fgets(buf, MSGSIZE, stdin);
            buf[strcspn(buf, "\n")] = 0;
            msg.mtype = 2;
            strcpy(msg.mtext, buf);
            msgsnd(msgid, &msg, strlen(msg.mtext)+1, 0);
            if (!strcmp(buf, "exit")) break;
        }
    }

    if (fork() == 0) exit(0); // 자식 종료
    msgctl(msgid, IPC_RMID, NULL); // 메시지 큐 제거
    return 0;
}
