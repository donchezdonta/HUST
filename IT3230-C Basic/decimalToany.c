#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void push(Stack *s, int val) {
    s->data[++s->top] = val;
}

int pop(Stack *s) {
    return s->data[s->top--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void convertBase(int num, int base) {
    Stack s = {{0}, -1};
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    if (num == 0) {
        printf("0\n");
        return;
    }
    
    while (num > 0) {
        push(&s, num % base);
        num /= base;
    }
    
    printf("Result: ");
    while (!isEmpty(&s)) {
        printf("%c", digits[pop(&s)]);
    }
    printf("\n");
}

int main() {
    int num, base;
    
    printf("Enter decimal number: ");
    scanf("%d", &num);
    printf("Enter base (2-36): ");
    scanf("%d", &base);
    
    if (base < 2 || base > 36) {
        printf("Invalid base!\n");
        return 1;
    }
    
    convertBase(num, base);
    return 0;
}