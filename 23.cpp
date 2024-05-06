// 2 семестр лабораторная №5
//Раделить число на 2. {0,1}

#include <stdio.h>
#include <stdlib.h>

int main() {
    int len = 2;
    char c;
    char *a = (char *) malloc(len * sizeof(char));
    a[0] = '*';
    while ((c = getchar()) != '\n') {
        a[len - 1] = c;
        len++;
        a = (char *) realloc(a, len);
    }
    a[len - 1] = '\0';
    for (int i = 0; i < len; ++i) {
        if ((a[i] == '*') && (a[i + 1] == '1')) {
            a[i] = '1';
            a[i + 1] = '*';
        } else if ((a[i] == '*') && (a[i + 1] == '0')) {
            a[i] = '0';
            a[i + 1] = '*';
        } else if ((a[i] == '*') && (a[i - 1] == '1')) {
            a[i] = '1';
            a[i - 1] = ' ';
        } else if ((a[i] == '*') && (a[i - 1] == '0')) {
            a[i] = '0';
            a[i - 1] = ' ';
        }
    }
    printf(a);
    free(a);
    return 0;

}