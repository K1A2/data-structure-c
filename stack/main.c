#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

Stack initStack() {
    Stack stack;
    stack.top = -1;
    return stack;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int peak(Stack *stack) {
    if (isEmpty(stack)) return -1;
    return stack->items[stack->top];
}

void push(Stack *stack, int value) {
    if (stack->top + 1 == MAX_SIZE) return;
    stack->items[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) return -1;
    return stack->items[stack->top--];
}

void printStack(Stack *stack) {
    for (int i = 0;i < stack->top + 1;i++) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

int main() {
    Stack stack = initStack();

    char command[10];
    int number;

    printf("Commands: push <num>, pop, peak, exit\n");
    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "push") == 0) {
            scanf("%d", &number);
            push(&stack, number);
            printStack(&stack);
        } else if (strcmp(command, "pop") == 0) {
            printf("%d\n", pop(&stack));
            printStack(&stack);
        } else if (strcmp(command, "peak") == 0) {
            printf("%d\n", peak(&stack));
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}
