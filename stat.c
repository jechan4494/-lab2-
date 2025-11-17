#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat st;
    if (stat("example.txt", &st) != 0) { perror("stat"); return 1; }

    printf("파일 크기: %ld bytes\n", st.st_size);
    printf("마지막 수정 시간: %ld\n", st.st_mtime);
    return 0;
}
