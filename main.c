#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define POW_TWO 65537
#define LEN_OF_PAT_AND_BUF 17
#define UC const unsigned char

void createShiftTable(int lenPat, int shifts[], UC pattern[]) {
    for (int i = 0; i < 256; i++) {
        shifts[i] = lenPat;
    }
    for (int i = 0; i < lenPat - 1; i++) {
        shifts[pattern[i]] = lenPat - 1 - i;
    }
}

void algorithm(UC *str, UC *pattern, int patLen, const int shifts[], int strLen) {
    int k = 0;
    while (k + patLen <= strLen) {
        int i = patLen;
        do {
            printf("%d ", i + k);
            i--;
        } while (i > 0 && str[i + k] == pattern[i]);
        k += shifts[str[patLen - 1 + k]];
    }
}

int main() {
    unsigned char pattern[LEN_OF_PAT_AND_BUF] = {0};
    unsigned char buffer[LEN_OF_PAT_AND_BUF] = {0};
    unsigned char *str = (unsigned char *) malloc(sizeof(unsigned char) * POW_TWO);
    if (str == NULL) {
        printf("memory didn't give");
        return 0;
    }
    memset(str, '\0', POW_TWO);
    fgets((char *) pattern, LEN_OF_PAT_AND_BUF, stdin);
    int lenPat = (int) strlen((const char *) pattern);
    if (pattern[lenPat - 1] == '\n') {
        pattern[lenPat - 1] = '\0';
        lenPat--;
    } else {
        fgetc(stdin);
    }

    int shifts[256] = {0};

    createShiftTable(lenPat, shifts, pattern);

    /* str - строка для буферного считывания, длина - pow-two, занулена
     * pattern - считанная из stdin подстрока, которую нужно искать
     * lenPat - его длина
    */
    FILE *in = fopen("in.txt", "r");
    int strLen = (int) fread(str, 1, POW_TWO - 1, in);//stdin);
    algorithm(str, pattern, lenPat, shifts, strLen);

    return 0;
}