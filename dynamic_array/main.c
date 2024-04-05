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

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = a->elemSize = 0;
}

int main() {
    Array array;
    initArray(&array, 5, sizeof(int));

    int numbers[] = {1,2,3,4,5,6,7,8,9,10};
    for (int i = 0;i < 10;i++) {
        insertArray(&array, &numbers[i]);
    }

    printf("array elements:\n");
    for (size_t i = 0;i < array.used;i++) {
        printf("%d ", *((int*)array.array + i));
    }
    printf("\n");

    freeArray(&array);

    return 0;
}