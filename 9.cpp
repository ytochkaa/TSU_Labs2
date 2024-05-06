// 2 семестр лабораторная №4
// Дан массив из n строк. Удалить все строки, оканчивающиеся группой букв ing или ed.
// Массив описать как указатель на указатель.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n = 0;
    printf("%s", "number of rows");//сторока j
    scanf("%d", &n);
    char **a = (char **) malloc(n * sizeof(char *)); // выделение ячеек под указатели
    getchar();
    for (int i = 0; i < n; i++) {// указатель <=> строка
        int len = 1;
        char c;
        a[i] = (char *) malloc(n * sizeof(char)); // создаём массив размерностью n
        while ((c = getchar()) != '\n') {
            a[i][len - 1] = c;
            len++;
            a[i] = (char *) realloc(a[i], len); // увеличиваем на len усли не \n
        }
        a[i][len - 1] = '\0';
    }

    for (int i = 0; i < n; i++) {
        int len = strlen(a[i]);
        if (((len >= 3) && (strcmp(a[i] + len - 3, "ing") == 0)) || ((len >= 2) && (strcmp(a[i] + len - 2, "ed") == 0))) {
            free(a[i]);
            for (int k = i; k < n; k++) {
                a[k] = a[k+1];
            }
            n--;
            i--;
        }
    }

    printf("\nthe remaining rows of the array\n");
    for (int i = 0; i < n; ++i) {
        printf( "%s\n", a[i]);
        free(a[i]);
    }
    free(a);
}

