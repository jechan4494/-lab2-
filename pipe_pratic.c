#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "메시지를 보냅니다!";
    char read_msg[100];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) { // 부모 프로세스
        close(fd[0]); // 읽기용 닫기
        write(fd[1], write_msg, strlen(write_msg)+1);
        close(fd[1]);
    } else { // 자식 프로세스
        close(fd[1]); // 쓰기용 닫기
        read(fd[0], read_msg, sizeof(read_msg));
        printf("자식프로세스가  받은 메시지: %s\n", read_msg);
        close(fd[0]);
    }

    return 0;
}
