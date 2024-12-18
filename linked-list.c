#include <stdio.h>
#include <stdlib.h>

// Linked List düyün strukturu
struct Node {
    int data;             // Düyünün məlumatı
    struct Node *link;    // Növbəti düyünə pointer
};


void appendNode(struct Node **head, int data) {
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->link = NULL;

    if (*head == NULL) { // Əgər siyahı boşdursa
        *head = temp;
        return;
    }

    struct Node *ptr = *head;
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }
    ptr->link = temp;
}

void printList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int sumNodes(struct Node *head) {
    int sum = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        sum += temp->data;
        temp = temp->link;
    }
    return sum;
}

int main() {
    struct Node *L = NULL;
    struct Node *M = NULL;
    FILE *file = fopen("text.txt", "r");

    if (file == NULL) {
        printf("Faylı açmaq mümkün olmadı.\n");
        return 1;
    }

    int number;
    while (fscanf(file, "%d", &number) != EOF) {
        if (number > 0) {
            appendNode(&L, number);
        } else if (number < 0) {
            appendNode(&M, number);
        }
    }

    fclose(file);

    int sumL = sumNodes(L);
    int sumM = sumNodes(M);

    printf("\nMüsbət ədədlər (L siyahısı):\n");
    printList(L);
    printf("Elementlərin sayı: %d, Cəm: %d\n", sumNodes(L), sumL);

    printf("\nMənfi ədədlər (M siyahısı):\n");
    printList(M);
    printf("Elementlərin sayı: %d, Cəm: %d\n", sumNodes(M), sumM);

    return 0;
}
