#include <stdio.h>

int main() { FILE *fp = fopen("old.txt", "w"); fputs("파일 이름 변경\n", fp); fclose(fp);

    if (rename("old.txt", "new.txt") != 0) { perror("rename"); return 1; }
    printf("old.txt -> new.txt로 변경완료\n");
    return 0;
}
