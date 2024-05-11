#include "linkedlist.h"
#include <stdio.h>
#include <string.h>

LinkedList initLinkedList() {
    LinkedListNode* head = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    head->next = NULL;

    LinkedList list;
    list.head = head;
    list.size = 0;
    return list;
}

void insertLinkedData(LinkedList *list, int index, int value) {
    if (index > list->size) return;

    LinkedListNode *target = list->head;
    for (int i = 0;i < index;i++) {
        target = target->next;
    }

    LinkedListNode *newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->data = value;
    newNode->next = target->next;
    target->next = newNode;
    list->size++;
}

void removeLinkedData(LinkedList *list, int index) {
    if (index >= list->size) return;

    LinkedListNode *targetPrev = list->head;
    for (int i = 0;i < index;i++) {
        targetPrev = targetPrev->next;
    }

    LinkedListNode *target = targetPrev->next;
    LinkedListNode *targetNext = target->next;
    targetPrev->next = targetNext;
    free(target);
    list->size--;
}

void printLinkedList(LinkedList *list) {
    LinkedListNode *currentNode = list->head->next;
    while (currentNode != NULL) {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

void freeLinkedList(LinkedList *list) {
    LinkedListNode *nextNode = list->head;
    while (nextNode != NULL) {
        LinkedListNode *tmp = nextNode->next;
        free(nextNode);
        nextNode = tmp;
    }
}