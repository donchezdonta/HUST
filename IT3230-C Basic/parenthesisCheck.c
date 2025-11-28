#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000001

typedef struct Node {
    char value;
    struct Node* next;
} Node;

Node* top = NULL;

Node* makeNode(char x) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->value = x;
    p->next = NULL;
    return p;
}

void initStack() {
    top = NULL;
}

int stackEmpty() {
    return top == NULL;
}

Node* pop() {
    if (top == NULL) return NULL;
    Node* x = top;
    top = top->next;
    return x;
}

void push(char x) {
    Node* p = makeNode(x);
    p->next = top;
    top = p;
}

char getTop() {
    if (top == NULL) return '\0';
    return top->value;
}

int match(char a, char b) {
    return (a == '(' && b == ')') || 
           (a == '[' && b == ']') || 
           (a == '{' && b == '}');
}

int check(char *s) {
    initStack();
    
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            push(s[i]);
        } else {
            if (stackEmpty() || !match(getTop(), s[i])) {
                return 0;
            }
            Node* temp = pop();
            free(temp);
        }
    }
    
    return stackEmpty() ? 1 : 0;
}

int main() {
    char s[MAX_LEN];
    scanf("%s", s);
    printf("%d\n", check(s));
    return 0;
}