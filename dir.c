#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    if (mkdir("mydir", 0755) != 0) { perror("mkdir"); return 1; }
    printf("testdir 생성\n");

    if (rmdir("mydir") != 0) { perror("rmdir"); return 1; }
    printf("testdir 삭제\n");
    return 0;
}

