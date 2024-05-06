// 2 семестр лабораторная №6
// Поиск подстроки в страке
#include <stdio.h>
#include <stdlib.h>

char *vvod(int *len) {// Динамического расширения памяти
    char c;
    char *a = (char *) malloc((*len) * sizeof(char)); // Выделяем память под строку размера len
    int i = 0;
    while ((c = getchar()) != '\n') {
        a[i] = c;
        i++;
        if (i == (*len)) { // Если достигли конца массива, увеличиваем его размер
            (*len)++;
            a = (char *) realloc(a, (*len) * sizeof(char)); // перевыделение памяти
        }
    }
    a[i] = '\0'; // Добавляем символ конца строки
    return a;
}

int len_p(char *a, char *b, int lena, int lenb) { // Функция для поиска подстроки в строке
    int j;
    for (int i = 0; i < lena - lenb + 1; ++i) {
        for (j = 0; j < lenb; ++j) {
            if (a[i+j] != b[j]) {
                j = lenb;
            }
        }
        if (j == lenb) {
            return i;
        }
    }
    return -1;
}


int main() {
    int len_s = 1, len_po = 1;
    char *stroka = vvod(&len_s); // Считываем строку
    char *podstroka = vvod(&len_po); // Считываем подстроку
    printf("%d", len_p(stroka, podstroka, len_s - 1, len_po - 1));

    free(stroka); // Освобождаем память, выделенную под строку
    free(podstroka); // Освобождаем память, выделенную под подстроку

}