#include <stdio.h>
#include <unistd.h>

int main() {
    if (access("example.txt", F_OK) == 0)
        printf("example.txt 존재함\n");
    else
        printf("example.txt 없음\n");

    if (access("example.txt", R_OK) == 0)
        printf("읽기 가능\n");
    else
        printf("읽기 불가\n");

    return 0;
}
