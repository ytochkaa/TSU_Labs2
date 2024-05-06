// 2 семестр лабораторная №1
// Выяснить, имеется ли в массиве С два идущих подряд нулевых элемента.
#include <stdio.h>
    int main() {
        int a[100], j, count;
        count = 0;
        printf("enter the power of the set");
        scanf("%d", &j);
        for (int i = 0; i < j; i++) {
            printf("%s%d%s", "a[", i, "]=");
            scanf("%d", &a[i]);
        }
        int *p = a;
        for (int i = 0; i < j - 1; i++) {
            if (0 == *(p + i) == *(p + i + 1)) {
                count++;
            }
        }
        if (count > 0) {
            printf("Two consecutive zeros found.\n");
        }else{
            printf("No consecutive zeros found.\n");
        }
    }
