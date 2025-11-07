#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXP 1024

struct Stack {
    int size;
    int top;
    char *arr;
};

int isEmpty(struct Stack *ptr) {
    return ptr->top == -1;
}

int isFull(struct Stack *ptr) {
    return ptr->top == ptr->size - 1;
}

void push(struct Stack *ptr, char val) {
    if (isFull(ptr)) {
        printf("Stack overflow! Cannot push %c to the stack!\n", val);
        return;
    }
    ptr->top++;
    ptr->arr[ptr->top] = val;
}

char pop(struct Stack *ptr) {
    if (isEmpty(ptr)) {
        printf("Stack underflow!\n");
        return '\0';
    }
    char val = ptr->arr[ptr->top];
    ptr->top--;
    return val;
}

int parenthesisMatch(char *exp) {
    struct Stack *sp = malloc(sizeof *sp);
    if (!sp) return 0;
    sp->size = 100;
    sp->top = -1;
    sp->arr = malloc(sp->size * sizeof(char));
    if (!sp->arr) {
        free(sp);
        return 0;
    }

    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] == '(') {
            push(sp, '(');
        } else if (exp[i] == ')') {
            if (isEmpty(sp)) {
                free(sp->arr);
                free(sp);
                return 0;
            }
            pop(sp);
        }
    }

    int result = isEmpty(sp);
    free(sp->arr);
    free(sp);
    return result;
}

int main() {
    char exp[MAX_EXP];
    if (fgets(exp, sizeof(exp), stdin) == NULL) {
        fprintf(stderr, "No input\n");
        return 1;
    }
    size_t len = strlen(exp);
    if (len > 0 && exp[len - 1] == '\n') exp[len - 1] = '\0';

    if (parenthesisMatch(exp))
        printf("Matching!\n");
    else
        printf("Not matching!\n");

    return 0;
}