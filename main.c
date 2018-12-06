#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define POW_TWO 65537
#define LEN_OF_PAT_AND_BUF 17
#define UC const unsigned char
#define LEN_OF_DICT 256

void createShiftTable(int lenPat, int shifts[], UC pattern[]) {
    for (int i = 0; i < LEN_OF_DICT; i++) {
        shifts[i] = lenPat;
    }
    for (int i = 0; i < lenPat - 1; i++) {
        shifts[pattern[i]] = lenPat - 1 - i;
    }
}

int algorithm(UC *str, UC *pattern, int patLen, const int shifts[], int strLen, int *ind) {
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

    int shifts[LEN_OF_DICT] = {0};

    createShiftTable(lenPat, shifts, pattern);

    int strLen, ind = 0, indexStr = 0;

    while ((strLen = fread(&str[indexStr], sizeof(char), (size_t) (POW_TWO - 1 - indexStr), stdin)) != 0) {
        strLen += indexStr;

        indexStr = algorithm(str, pattern, lenPat, shifts, strLen, &ind);

        for (int i = 0; i < indexStr; i++)
            buffer[i] = str[strLen - indexStr + i];
        memset(str, '\0', POW_TWO);
        for (int i = 0; i < indexStr; i++)
            str[i] = buffer[i];
    }
    free(str);

    return 0;
}