#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int p2c[2], c2p[2];
    char buf[100];
    pipe(p2c);
    pipe(c2p);

    if (fork()) { // 부모
        close(p2c[0]); close(c2p[1]);
        while (1) {
            printf("부모: "); fgets(buf, 100, stdin);
            buf[strcspn(buf, "\n")] = 0;
            write(p2c[1], buf, strlen(buf)+1);
            if (!strcmp(buf,"exit")) break;
            read(c2p[0], buf, 100);
            printf("자식: %s\n", buf);
            if (!strcmp(buf,"exit")) break;
        }
    } else { // 자식
        close(p2c[1]); close(c2p[0]);
        while (1) {
            read(p2c[0], buf, 100);
            printf("부모: %s\n", buf);
            if (!strcmp(buf,"exit")) break;
            printf("자식: "); fgets(buf, 100, stdin);
            buf[strcspn(buf, "\n")] = 0;
            write(c2p[1], buf, strlen(buf)+1);
            if (!strcmp(buf,"exit")) break;
        }
    }
    return 0;
}
