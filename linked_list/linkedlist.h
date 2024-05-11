#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} LinkedListNode;

typedef struct {
    LinkedListNode *head;
    size_t size;
} LinkedList;

LinkedList initLinkedList();
void insertLinkedData(LinkedList *list, int index, int value);
void removeLinkedData(LinkedList *list, int index);
void printLinkedList(LinkedList *list);
void freeLinkedList(LinkedList *list);

#endif