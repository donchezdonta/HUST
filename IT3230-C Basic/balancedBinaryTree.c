#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50001

typedef struct TNode {
    int id;
    struct TNode* left;
    struct TNode* right;
} Node;

Node* root = NULL;
Node* nodes[N] = {NULL};

typedef struct TINFO {
    int balanced;
    int h;
} INFO;

Node* makeNode(int id) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->id = id;
    p->left = NULL;
    p->right = NULL;
    return p;
}

int addLeft(int u, int v) {
    if (nodes[u] != NULL || nodes[v] == NULL) 
        return 0;
    
    if (nodes[v]->left != NULL) return 0;

    Node* p = makeNode(u);
    nodes[v]->left = p;
    nodes[u] = p;
    return 1;
}

int addRight(int u, int v) {
    if (nodes[u] != NULL || nodes[v] == NULL) 
        return 0;
    
    if (nodes[v]->right != NULL) return 0;

    Node* p = makeNode(u);
    nodes[v]->right = p;
    nodes[u] = p;
    return 1;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int abs_val(int x) {
    return (x < 0) ? -x : x;
}

INFO visit(Node* r) {
    INFO i;
    
    if (r == NULL) {
        i.balanced = 1;
        i.h = 0;
        return i;
    }

    INFO i1 = visit(r->left);
    INFO i2 = visit(r->right);
    
    i.h = max(i1.h, i2.h) + 1;

    if (i1.balanced == 0 || i2.balanced == 0) {
        i.balanced = 0;
        return i;
    }

    if (abs_val(i1.h - i2.h) >= 2) 
        i.balanced = 0;
    else 
        i.balanced = 1;

    return i;
}

int main() {
    char command[20];
    int u, v;

    while (scanf("%s", command) == 1) {
        if (strcmp(command, "*") == 0) {
            break;
        }
        else if (strcmp(command, "MakeRoot") == 0) {
            scanf("%d", &u);
            root = makeNode(u);
            nodes[u] = root;
        }
        else if (strcmp(command, "AddLeft") == 0) {
            scanf("%d %d", &u, &v);
            addLeft(u, v);
        }
        else if (strcmp(command, "AddRight") == 0) {
            scanf("%d %d", &u, &v);
            addRight(u, v);
        }
    }

    INFO result = visit(root);
    printf("%d %d\n", result.balanced, result.h);

    return 0;
}