#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
    a->array = (int*)malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void insertArray(Array *a, int element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (int*)realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void insertAtIndexArray(Array *a, size_t index, int element) {
    if (index > a->used) return;

    if (a->used == a->size) {
        a->size *= 2;
        a->array = (int*)realloc(a->array, a->size * sizeof(int));
    }
    memmove(&a->array[index + 1], &a->array[index], (a->used - index) * sizeof(int));
    a->array[index] = element;
    a->used++;
}

void removeAtIndexArray(Array *a, size_t index) {
    if (index >= a->used) return;

    memmove(&a->array[index], &a->array[index + 1], (a->used - index - 1) * sizeof(int));
    a->used--;
}

void printArray(Array *a) {
    for (size_t i = 0; i < a->used; i++) {
        printf("%d ", a->array[i]);
    }
    printf("\n");
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

int main() {
    Array array;

    char command[10];
    int number;
    size_t index;

    initArray(&array, 5);

    printf("Commands: add <num>, insert <index> <num>, del <index>, print, exit\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%d", &number);
            insertArray(&array, number);
        } else if (strcmp(command, "insert") == 0) {
            scanf("%zu %d", &index, &number);
            insertAtIndexArray(&array, index, number);
        } else if (strcmp(command, "del") == 0) {
            scanf("%zu", &index);
            removeAtIndexArray(&array, index);
        } else if (strcmp(command, "print") == 0) {
            printArray(&array);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    freeArray(&array);

    return 0;
}