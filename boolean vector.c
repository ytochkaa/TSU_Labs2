// 2 семестр лабораторная №9
// Даны булевы вектора a и b длины n.
// Если возможно, упорядочить их, или вывести сообщение "Векторы несравнимы"
// через строки

// Два булевых вектора называются сравнимыми, если они имеют одинаковую длину
// и каждый элемент одного вектора больше или равен соответствующему элементу другого вектора.
// Другими словами, если у нас есть два булевых вектора A и B длины n, то они сравнимы,
// если и только если для любого i от 1 до n выполняется условие Ai >= Bi.

// Например, если даны векторы A = 1010 и B = 1100, то они являются сравнимыми,
// потому что для каждой позиции i выполняется условие A[i] >= B[i]:

#include <stdio.h>
#include <stdlib.h>

int compare(unsigned int A, unsigned int B, int size) {
    unsigned int e = 1;     //используются для создания битовой маски с единичным битом.
    unsigned int a = A;
    unsigned int b = B;
    int f = 1;              // f - флаг, который определяет, отношение.

    // a_1 и b_1 - первые биты чисел a и b.
    unsigned int a_1 = a & e;
    unsigned int b_1 = b & e;

    //A предшественник B?
    //Если A больше либо равен B, то флаг f устанавливается в 0, иначе цикл продолжается.
    for (int i = 0; i < size && f; i++) {   // a_n >= b_n   <=>   a V (ab V (-a)(-b))   <=>   a V (-a)(-b)   <=>   a V ~(a V b)
        if (!(a_1 || !(a_1 | b_1)))f = 0;
            a = a >> 1;
            b = b >> 1;
            a_1 = a & e;
            b_1 = b & e;
    }

    // возвращаем значения
    a = A;
    b = B;
    a_1 = a & e;
    b_1 = b & e;

    // аналогично только другое отношение и флаг 2
    for (int i = 0; i < size && !f; i++) {    // a_n >= b_n   <=>   a V (ab V (-a)(-b))   <=>   a V (-a)(-b)   <=>   a V ~(a V b)
        if (!(b_1 || !(b_1 | a_1)))f = 2;
        a = a >> 1;
        b = b >> 1;
        a_1 = a & e;
        b_1 = b & e;
    }
    //отношение
    return f;

}

int main() {     // выполнить операцию определения предшествования двух булевых векторов

    char *a = malloc(0);
    char *b = malloc(0);
    int len_a = 0;
    int len_b = 0;
    char c = ' ';

    printf("Enter a:");
    while ((c = getchar()) != '\n') {
        len_a++;
        a = (char *) realloc(a, len_a * sizeof(char));
        a[len_a - 1] = c;
    }

    printf("\n");
    c = ' ';


    printf("Enter b:");
    while ((c = getchar()) != '\n') {
        len_b++;
        b = (char *) realloc(b, len_b * sizeof(char));
        b[len_b - 1] = c;
    }

    if (len_a == 0 || len_b == 0 || len_a != len_b) {
        printf("Error size");
        return 0;
    }

    unsigned int vec_a = 0;
    unsigned int vec_b = 0;
    unsigned int e = 1;
    for (int i = 0; i < len_a; i++) {
        if (a[i] - 48) {
            vec_a = vec_a << 1;
            vec_a = vec_a | e;
        } else { vec_a = vec_a << 1; }

        if (b[i] - 48) {
            vec_b = vec_b << 1;
            vec_b = vec_b | e;
        } else { vec_b = vec_b << 1; }
    }

    int result = compare(vec_a, vec_b, len_a);

    if (result==1) {
        printf("%u is predshestvuet to %u", vec_a, vec_b);
        return 0;
    }else if(!result){
        printf("%u is not predshestvuet to %u", vec_a, vec_b);
        return 0;
    }else{
        printf("%u is not sravnimiy to %u", vec_a, vec_b);
        return 0;
    }

}
