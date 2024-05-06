// 2 семестр лабораторная №3
// Даны вектора x и квадратная матрица A. в матрице заменить все чётные строки на x
#include <stdio.h>
#include <time.h>
#include <cstdlib>

int main() {

    int m, a[20][20], r, x[20];
    printf("%s", "number of rows and colums ");
    scanf("%d", &m);
    srand(time(0));
    for (int i = 0; i < m; i++) {       // строка i
        printf("\n");
        for (int j = 0, k=0; j < m; j++, k++) {   // столбец j
            a[i][j] = rand()%1000;
            x[k]= rand()%1000;
            printf("%d ", a[i][j]);
        }
    }

    printf("\n\n");
    for (int k = 0; k < m; k++) {
        printf("%d ", x[k]);
    }

    printf("\n");

    for (int i = 0; i < m; i++) {
        printf(("\n"));
        for (int j = 0; j < m; j++) {
            if (i % 2 == 0) {
                printf("%d ", a[i][j]);
            } else {
                printf("%d ", x[j]);
            }
        }
    }
}