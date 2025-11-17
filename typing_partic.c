#include <stdio.h>
#include <string.h>
#include <time.h>

int count_errors(const char* orig, const char* typed) {
    int errors = 0;
    int len_orig = strlen(orig), len_typed = strlen(typed);
    int min_len = len_orig < len_typed ? len_orig : len_typed;
    for (int i = 0; i < min_len; i++)
        if (orig[i] != typed[i]) errors++;
    errors += len_orig > len_typed ? len_orig - len_typed : len_typed - len_orig;
    return errors;
}

double wpm(int chars, double sec) {
    return sec > 0 ? (chars / 5.0) / (sec / 60.0) : 0;
}

int main() {
    const char *sentence = "저의 이름은 OO입니다." // 검사할 문장;
    char typed[1024];

    printf("%s\n", sentence);
    printf("입력: ");
    fflush(stdout);

    time_t start = time(NULL);
    fgets(typed, sizeof(typed), stdin);
    time_t end = time(NULL);

    // 개행 제거
    typed[strcspn(typed, "\n")] = 0;

    int errors = count_errors(sentence, typed);
    double speed = wpm(strlen(typed), difftime(end, start));

    printf("입력 글자: %zu\n", strlen(typed));
    printf("걸린 시간: %.0f초\n", difftime(end, start));
    printf("오타 수: %d\n", errors);
    printf("WPM: %.1f\n", speed);
    return 0;}
