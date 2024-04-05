#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *array;
    size_t used;
    size_t size;
    size_t elemSize;
} Array;

void initArray(Array *a, size_t initialSize, size_t elemSize) {
    a->array = (int*)malloc(initialSize * elemSize);
    a->used = 0;
    a->size = initialSize;
    a->elemSize = elemSize;
}

void insertArray(Array *a, void *element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, a->size * a->elemSize);
    }
    memcpy((char*)a->array + (a->used * a->elemSize), element, a->elemSize);
    a->used++;
}

void insertAtIndexArray(Array *a, size_t index, void *element) {
    if (index > a->used) return;

    if (a->used == a->size) {
        a->size *= 2;
        a->array = realloc(a->array, a->size * a->elemSize);
    }
    memmove((char*)a->array + ((index + 1) * a->elemSize), 
            (char*)a->array + (index * a->elemSize), 
            (a->used - index) * a->elemSize);
    memcpy((char*)a->array + (index * a->elemSize), element, a->elemSize);
    a->used++;
}

void removeAtIndexArray(Array *a, size_t index) {
    if (index >= a->used) return;

    memmove((char*)a->array + (index * a->elemSize),
            (char*)a->array + ((index + 1) * a->elemSize),
            (a->used - index - 1) * a->elemSize);
    a->used--;
}

void printArray(Array *a) {
    for (size_t i = 0;i < a->used;i++) {
        printf("%d ", *((int*)a->array + i));
    }
    printf("\n");
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = a->elemSize = 0;
}

int main() {
    Array array;

    char command[10];
    int number;
    size_t index;

    initArray(&array, 5, sizeof(int));

    printf("Commands: add <num>, insert <index> <num>, del <index>, print, exit\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%d", &number);
            insertArray(&array, &number);
        } else if (strcmp(command, "insert") == 0) {
            scanf("%zu %d", &index, &number);
            insertAtIndexArray(&array, index, &number);
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