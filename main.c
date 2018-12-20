#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define POW_TWO 65536
#define LEN_OF_PAT_AND_BUF 17
typedef unsigned char UC;

static void createShiftTable(int lenPat, int shifts[], const UC *pattern) {
    for (int i = 0; i < UCHAR_MAX; i++) {
        shifts[i] = lenPat;
    }
    for (int i = 0; i < lenPat - 1; i++) {
        shifts[pattern[i]] = lenPat - 1 - i;
    }
}

static int loggingOfBM(const UC *str, const UC *pattern, int patLen, const int shifts[], int strLen, int *ind) {
    int k = 0;
    while (k + patLen <= strLen) {
        int i = patLen;
        do {
            printf("%d ", i + k + *ind);
            i--;
        } while (i > 0 && str[i + k] == pattern[i]);
        k += shifts[str[patLen - 1 + k]];
    }
    *ind += k;
    return strLen - k;
}

int main() {
    UC pattern[LEN_OF_PAT_AND_BUF] = {0};
    UC buffer[LEN_OF_PAT_AND_BUF] = {0};
    UC *str = (UC *) malloc(sizeof(UC) * POW_TWO);
    if (str == NULL) {
        printf("memory didn't give");
        return -1;
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

    int shifts[UCHAR_MAX] = {0};

    createShiftTable(lenPat, shifts, pattern);

    int strLen, ind = 0, indexStr = 0;

    while ((strLen = fread(&str[indexStr], sizeof(char), (size_t) (POW_TWO - 1 - indexStr), stdin)) != 0) {
        strLen += indexStr;

        indexStr = loggingOfBM(str, pattern, lenPat, shifts, strLen, &ind);

        memmove(buffer, &str[strLen - indexStr], (size_t) indexStr);
        memset(str, '\0', POW_TWO);
        memmove(str, buffer, (size_t) indexStr);
    }
    free(str);

    return 0;
}