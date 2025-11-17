#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void child_handler(int sig) {
    if(sig == SIGUSR1) {
        printf("자식: SIGUSR1 받음, 작업 수행 중...\n");
    } else if(sig == SIGTERM) {
        printf("자식: SIGTERM 받음, 종료합니다.\n");
        exit(0);
    }
}

int main() {
    pid_t pid = fork();
    if(pid < 0) {
        perror("fork 실패");
        return 1;
    }

    if(pid == 0) { // 자식 프로세스
        // 시그널 핸들러 등록
        signal(SIGUSR1, child_handler);
        signal(SIGTERM, child_handler);

        while(1) {
            printf("자식: 대기 중...\n");
            sleep(2);
        }
    } else { // 부모 프로세스
        sleep(3); // 자식이 준비될 시간을 줌
        printf("부모: SIGUSR1 보내기\n");
        kill(pid, SIGUSR1); // SIGUSR1 전송

        sleep(3);
        printf("부모: SIGTERM 보내기\n");
        kill(pid, SIGTERM); // SIGTERM 전송

        wait(NULL); // 자식 종료 대기
        printf("부모: 자식 종료, 프로그램 종료\n");
    }

    return 0;
}
