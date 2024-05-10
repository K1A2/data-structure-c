#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} LinkedList;

void insertData(LinkedList *list, int index, int value) {
    if (index > list->size) return;

    Node *target = list->head;
    for (int i = 0;i < index;i++) {
        target = target->next;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = target->next;
    target->next = newNode;
    list->size++;
}

void removeData(LinkedList *list, int index) {
    if (index >= list->size) return;

    Node *targetPrev = list->head;
    for (int i = 0;i < index;i++) {
        targetPrev = targetPrev->next;
    }

    Node *target = targetPrev->next;
    Node *targetNext = target->next;
    targetPrev->next = targetNext;
    free(target);
    list->size--;
}

void printList(LinkedList *list) {
    Node *currentNode = list->head->next;
    while (currentNode != NULL) {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

void freeList(LinkedList *list) {
    Node *nextNode = list->head;
    while (nextNode != NULL) {
        Node *tmp = nextNode->next;
        free(nextNode);
        nextNode = tmp;
    }
}

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = NULL;

    LinkedList list;
    list.head = head;
    list.size = 0;

    char command[10];
    int number;
    size_t index;

    printf("Commands: insert <index> <num>, del <index>, print, exit\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            scanf("%zu %d", &index, &number);
            insertData(&list, index, number);
        } else if (strcmp(command, "del") == 0) {
            scanf("%zu", &index);
            removeData(&list, index);
        } else if (strcmp(command, "print") == 0) {
            printList(&list);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    freeList(&list);

    return 0;
}
