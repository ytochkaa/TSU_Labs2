// 2 семестр лабораторная №7
// Hanoi Towers
#include <stdio.h>
#include <malloc.h>

void printmat(int **a, int size){ // вывод матрицы на экран
    printf("\n");
    for(int i=0; i<size; i++){
        for(int j=0; j<3; j++){
            printf("%d ", a[j][i]);
        }
        printf("\n");
    }

}

int get_empty_row(int **a, int k, int size){ // возвращение позиции свободного элемента в столбце
    for(int i = size-1; i>=0; i--){
        if(!a[k][i]){
            return i;
        }
        //  k
        // [0]0 0
        //  2 0 0
        //  3 0 1
    }
    return -1;
}


void hanoi(int n, char A, char B, char C, int **a, int N) // сама рекурсия
{
    if (n == 1){

        printf("1 From %c to %c\n", A, C);

        int from_i = abs('A'-A);
        int from_j = get_empty_row(a, from_i, N);

        if(from_j>0 && from_j<N-1) {
            from_j++;
        }else if(from_j!=N-1){
            from_j++;
        }
        int to_i = 3-abs('C'-C)-1;
        int to_j = get_empty_row(a,to_i,N);
        printf("[%d,%d] -> [%d,%d]\n", from_i, from_j, to_i, to_j);
        int t = a[from_i][from_j];
        a[from_i][from_j] = a[to_i][to_j];
        a[to_i][to_j] = t;
        printmat(a,N);

        // verified "to" 2-abs('C'-C)
        // verified "from" abs('A'-A);

        return;
    }
    hanoi(n-1,A,C,B, a,N);
    printf("%d From %c to %c  ------   %d\n", n, A, C, N);
    // промежуточный B
    // verified "to" 2-abs('C'-C)
    // verified "from" abs('A'-A);

    int from_i = abs('A'-A);
    int from_j = get_empty_row(a, from_i, N);

    if (from_j>0 && from_j<N-1) {
        from_j++;
    }else if(from_j!=N-1){
        from_j++;
    }

    int to_i = 3-abs('C'-C)-1;
    int to_j = get_empty_row(a,to_i,N);
    printf("[%d,%d] -> [%d,%d]\n", from_i, from_j, to_i, to_j);

    int t = a[from_i][from_j];
    a[from_i][from_j] = a[to_i][to_j];
    a[to_i][to_j] = t;

    printmat(a,N);
    hanoi(n-1,B,A,C, a, N);

}

int main() {
    int n=0;
    scanf("%d", &n);
    int **a = (int**) malloc(3*sizeof(int*));
    for(int i=0; i<3; i++){
        a[i] = (int*) malloc(n*sizeof(int));
        for(int j=0; j<n; j++){
            a[i][j] = 0;
        }
    }
    for(int i=0; i<n; i++)a[0][i] = i+1;
    printmat(a, n);

    hanoi(n, 'A','B','C',a,n);
    return 0;
}