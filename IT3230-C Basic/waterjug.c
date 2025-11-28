#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct Node {
    int x;
    int y;
    struct Node* next;
} Node;

Node* front = NULL;
Node* rear = NULL;

int a, b, c;
int m[MAX][MAX];
int num[MAX][MAX];
Node lstNext1Step[6];

Node* makeNode(int x, int y) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->x = x;
    p->y = y;
    p->next = NULL;
    return p;
}

void initQueue() {
    front = NULL;
    rear = NULL;
}

int queueEmpty() {
    return front == NULL;
}

void push(int x, int y) {
    Node* p = makeNode(x, y);
    if (queueEmpty()) {
        front = rear = p;
    } else {
        rear->next = p;
        rear = p;
    }
}

Node* pop() {
    if (queueEmpty()) return NULL;
    Node* x = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    return x;
}

void init() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            m[i][j] = 0;
            num[i][j] = 0;
        }
    }
}

int target(Node* t) {
    return (t->x == c || t->y == c);
}

void mark(Node* t) {
    m[t->x][t->y] = 1;
}

int is_mark(Node* t) {
    return m[t->x][t->y] == 1;
}

void next_steps(Node* t) {
    int x = t->x;
    int y = t->y;
    int nx, ny;
    
    lstNext1Step[0].x = a;
    lstNext1Step[0].y = y;
    
    lstNext1Step[1].x = x;
    lstNext1Step[1].y = b;
    
    lstNext1Step[2].x = 0;
    lstNext1Step[2].y = y;
    
    lstNext1Step[3].x = x;
    lstNext1Step[3].y = 0;
    
    if (x + y > b) {
        nx = x + y - b;
        ny = b;
    } else {
        nx = 0;
        ny = x + y;
    }
    lstNext1Step[4].x = nx;
    lstNext1Step[4].y = ny;
    
    if (x + y > a) {
        nx = a;
        ny = x + y - a;
    } else {
        nx = x + y;
        ny = 0;
    }
    lstNext1Step[5].x = nx;
    lstNext1Step[5].y = ny;
}

int solve() {
    initQueue();
    init();
    
    push(0, 0);
    mark(makeNode(0, 0));
    
    while (!queueEmpty()) {
        Node* t = pop();
        
        next_steps(t);
        
        for (int i = 0; i < 6; i++) {
            Node* ti = &lstNext1Step[i];
            
            if (target(ti)) {
                int result = num[t->x][t->y] + 1;
                free(t);
                return result;
            }
            
            if (!is_mark(ti)) {
                push(ti->x, ti->y);
                mark(ti);
                num[ti->x][ti->y] = num[t->x][t->y] + 1;
            }
        }
        
        free(t);
    }
    
    return -1;
}

int main() {
    scanf("%d %d %d", &a, &b, &c);
    printf("%d\n", solve());
    return 0;
}