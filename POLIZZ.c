#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR_LEN 100// обьявление максимальной длины выражения

// Структура стека для хранения операторов
typedef struct{
    char *stack;
    int top;
    int maxSize;
}Stack;

// Создание и удаление стека
Stack *createStack(int size);
void deleteStack(Stack *stack);

//операции со стеком
void push(Stack *stack, char data);//добавление
char pop(Stack *stack);//удаление
char peek(Stack *stack);// получение верхнего элемента
int isEmpty(Stack *stack);//пустой?
int isFull(Stack *stack);//заполненный?

//функции для преобразования в ПОЛИЗ
void infixToPostfix(char *infixExpr, char *postfixExpr, int postfixSize);
int getPrecedence(char op);//приоретет
int isOperator(char ch);//оператор?
void evaluatePostfix(char *postfixExpr, double *result);//вычисление

//функция создания стека.
Stack *createStack(int size) {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    stack->stack = (char*) malloc(size * sizeof(char));
    stack->maxSize = size;//кол-во ячеек в входной строке
    stack->top = -1;
    return stack;
}

//функция удаление из стека
void deleteStack(Stack *stack) {
    free(stack->stack);
    free(stack);
}

//функция добавления элемента в стек.
void push(Stack *stack, char data) {
    if (!isFull(stack)) {
        stack->top++;
        stack->stack[stack->top] = data;
    }
}

//функция удаления элемента из стека.
char pop(Stack *stack) {
    if (!isEmpty(stack)) {
        char data = stack->stack[stack->top];
        stack->top--;
        return data;//запоминаем последний симол
    }
    return '\0';//если пустой
}

//получаем верхний элемент.
char peek(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->stack[stack->top];//запоминаем вершину стека
    }
    return '\0';
}

//функция проверки стека на пустоту.
int isEmpty(Stack *stack) {
    return (stack->top == -1);
}

//функция проверки стека на заполненность.
int isFull(Stack *stack) {
    return (stack->top == stack->maxSize - 1);//T если предел
}

// стек
void infixToPostfix(char *infixExpr, char *postfixExpr, int postfixSize) {
    int i, j = 0;
    char ch, top;
    Stack *operatorStack = createStack(postfixSize);

    // Проверка каждого символа в инфиксном выражении
    for (i = 0; i < strlen(infixExpr); i++) {//идём по длинне строки
        ch = infixExpr[i];

        // Если операнд, добавляем его в постфиксную форму
        if (isdigit(ch) || ch == '.') {
            while (isdigit(infixExpr[i]) || infixExpr[i] == '.') {
                postfixExpr[j++] = infixExpr[i++];
            }
            postfixExpr[j++] = ' ';
            i--;
        }

        // Если открывающая скобка, добавляем его в стек операторов
        else if (ch == '(') {
            push(operatorStack, ch);
        }

        // Если символ - закрывающая скобка, добавляем все операторы до соответствующей открывающей скобки в постфиксную форму
        else if (ch == ')') {
            while (peek(operatorStack) != '(') {
                postfixExpr[j++] = pop(operatorStack);
                postfixExpr[j++] = ' ';
            }
            pop(operatorStack);
        }

        // Если символ - оператор, добавляем его в стек операторов с учетом приоритет
        else if (isOperator(ch)) {
            while (!isEmpty(operatorStack) && getPrecedence(ch) <= getPrecedence(peek(operatorStack))) {
                postfixExpr[j++] = pop(operatorStack);
                postfixExpr[j++] = ' ';
            }
            push(operatorStack, ch);
        }


        // Если недопустимый
        else {
            printf("Error: %c \n", ch);
            exit(1);    // завершение программы
        }
    }

    // Добавляем все оставшиеся операторы из стека в постфиксную форму
    while (!isEmpty(operatorStack)) {
        top = pop(operatorStack);
        if (top != '(') {
            postfixExpr[j++] = top;
            postfixExpr[j++] = ' ';
        }
    }

    // Завершаем нулевым символом
    postfixExpr[j] = '\0';

    // Освобождаем память, выделенную под стек операторов
    deleteStack(operatorStack);
}

//функция получения приоритета оператора. На вход подается символ оператора, на выходе возвращается его приоритет.
int getPrecedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '~':
            return 10;
        default:
            return 0;
    }
}

//функция проверки, является ли символ оператором.
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/'|| ch =='~');
}
//подсчёт значения через СТЕК операндов
void evaluatePostfix(char *postfixExpr, double *result) {
    int i;
    double operand, op1, op2;
    char ch;
    Stack *operandStack = createStack(MAX_EXPR_LEN);

    // Обрабатываем каждый символ в постфиксном выражении
    for (i = 0; i < strlen(postfixExpr); i++) {
        ch = postfixExpr[i];

        // Если операнд, добавляем его в стек операндов
        if (isdigit(ch) || ch == '.') {
            operand = atof(&postfixExpr[i]);// преобразуем в double
            push(operandStack, operand);
            while (isdigit(postfixExpr[i]) || postfixExpr[i] == '.') {
                i++;
            }
            i--;
        }

        // Если оператор, извлекаем два операнда из стека и выполняем операцию
        else if (isOperator(ch)) {
            if (ch=='~') {
                op2 = pop(operandStack);
                operand = -op2;
            }else{
                op2 = pop(operandStack);
                op1 = pop(operandStack);
            switch (ch) {
                case '+':
                    operand = op1 + op2;
                    break;
                case '-':
                    operand = op1 - op2;
                    break;
                case '*':
                    operand = op1 * op2;
                    break;
                case '/':
                    if (op2 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    operand = op1 / op2;
                    break;
            }
            }
            push(operandStack, operand);
        }
    }

    // Вычисляем окончательный результат
    *result = pop(operandStack);

    // Освобождаем память, выделенную под стек операндов
    deleteStack(operandStack);
}

int main() {
    char infixExpr[MAX_EXPR_LEN];
    char postfixExpr[MAX_EXPR_LEN];
    double result;

    // Ввод инфиксного выражения
    printf("Enter: ");
    fgets(infixExpr, MAX_EXPR_LEN, stdin);
    infixExpr[strcspn(infixExpr, "\n")] = '\0';

    // Преобразование в постфиксную форму
    infixToPostfix(infixExpr, postfixExpr, MAX_EXPR_LEN);

    // Вывод постфиксной формы
    printf("POLIZ: %s\n", postfixExpr);

    // Вычисление результата
    evaluatePostfix(postfixExpr, &result);

    // Вывод результата
    printf("Result: %.2f\n", result);

    // Освобождение памяти
    free(infixExpr);
    free(postfixExpr);

    return 0;
}