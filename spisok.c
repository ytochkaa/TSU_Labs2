// 2 семестр лабораторная №10
// Дано число k(>0) и указатель P0 на один из элементов непустого двусвязного списка.
// Переместить в списке данный элемент на k позиций вперёд (если после данного элемента
// находится менее k элементов, то переместить его в конец списка). вывести указатель на первый и последний
// элементы преобразованного списка. Операции выделения и освобождения памяти не использовать.
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* moveNodeForward(Node* p0, int k) {
    // находим элемент, на который нужно переместить элемент p0
    Node* p1 = p0;
    for (int i = 0; i < k+1 && p1 -> next != NULL; i++) {
        p1 = p1->next;
    }

    // перемещаем элемент на его новую позицию
    if (p1->next == NULL) { // если элемент должен быть перемещен в конец списка
        p0->prev->next = p0->next; // связываем узлы перед и после перемещаемого узла
        if (p0->next != NULL) {
            p0->next->prev = p0->prev;
        }
        p0->prev = p1; // связываем перемещаемый узел и последний узел на новой позиции
        p0->next = NULL;
        p1->next = p0;
    }
    else { // если элемент должен быть перемещен на новую позицию
        p0->prev->next = p0->next;
        if (p0->next != NULL) {
            p0->next->prev = p0->prev;
        }
        p0->prev = p1->prev;
        p0->next = p1;
        p1->prev = p0;
        p0->prev->next = p0;
    }

    // находим первый и последний элементы списка
    Node* first = p0;
    while (first->prev != NULL) {
        first = first->prev;
    }
    Node* last = p1;
    while (last->next != NULL) {
        last = last->next;
    }

    // возвращаем указатель на первый элемент списка
    return first;
}

void printList(Node* head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    // вводим значение k и создаем указатель на первый элемент списка
    int k;
    printf("Enter k: ");
    scanf("%d", &k);
    Node* head = NULL;

    // добавляем элементы в список
    int n;
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid number of elements\n");
        return -1;
    }
    for (int i = 0; i < n; i++) {
        int data;
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        if (head == NULL) {
            head = newNode;
        }
        else {
            Node* curr = head;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newNode;
            newNode->prev = curr;
        }
    }

    // перемещаем элемент и выводим указатели на первый и последний элементы списка
    printList(head);
    Node* p0 = head->next->next; // указатель на элемент, который нужно переместить
    Node* newHead = moveNodeForward(p0, k);
    printList(newHead);
    Node* newLast = newHead;
    while (newLast->next != NULL) {
        newLast = newLast->next;
    }
    printf("First element: %p\n", (void*)newHead);
    printf("Last element: %p\n", (void*)newLast);

    // освобождаем выделенную память
    Node* curr = head;
    while (curr != NULL) {
        Node* tmp = curr->next;
        free(curr);
        curr = tmp;
    }

    return 0;
}