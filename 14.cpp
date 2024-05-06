// 2 семестр лабораторная №2
// Задан числовой массив А подсчитать число различных чисел.
#include <stdio.h>
#include <malloc.h>
int main() {
    int j;
    printf("enter the power of the set");
    scanf("%d", &j);
    int *a=(int*) malloc(j* sizeof(int ));
    for (int i = 0; i < j; i++) {
        printf("%s%d%s", "a[", i, "]=");
        scanf("%d", &a[i]);
    }
    int count = 0;
    int *p = a;
    int un[1000];
    int flag;
    int c;
    for (int i = 0; i < j; i++) {
        flag = 0;
        for (int k = 0; k < j; k++) {
            if (*(p + i) == *(un + k)) {
                flag = 1;
                c = k;
            }
        }
        if (flag == 0) {
            *(un + c) = *(p + i);
            count++;
        }

    }
    printf("Number of different numbers in the array: %d\n", count);
    free(a);
}

