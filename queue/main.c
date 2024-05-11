#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int size;
} Queue;

Queue initQueue() {
    Queue queue;
    queue.size = 0;
    queue.front = queue.rear = NULL;
    return queue;
}

int isEmpty(Queue *queue) {
    return queue->size == 0;
}

void enqueue(Queue *queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

int dequeue(Queue *queue) {
    if (isEmpty(queue)) return -1;
    Node* target = queue->front;
    queue->front = target->next;
    int value = target->data;
    free(target);
    return value;
}

void freeQueue(Queue *queue) {
    Node* currentNode = queue->front;
    while (currentNode != NULL) {
        Node* tmp = currentNode->next;
        free(currentNode);
        currentNode = tmp;
    }
}

void printQueue(Queue *queue) {
    Node* currentNode = queue->front;
    while (currentNode != NULL) {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int main() {
    Queue queue = initQueue();

    char command[10];
    int number;

    printf("Commands: enqueue <num>, dequeue, exit\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "enqueue") == 0) {
            scanf("%d", &number);
            enqueue(&queue, number);
            printQueue(&queue);
        } else if (strcmp(command, "dequeue") == 0) {
            printf("%d\n", dequeue(&queue));
            printQueue(&queue);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    freeQueue(&queue);

    return 0;
}
