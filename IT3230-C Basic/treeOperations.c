#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    struct Node* leftMostChild;
    struct Node* rightSibling;
    struct Node* parent;
} Node;

Node* root = NULL;

Node* makeNode(int u) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->id = u;
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    p->parent = NULL;
    return p;
}

Node* find(Node* r, int u) {
    if (r == NULL) return NULL;
    if (r->id == u) return r;
    
    Node* p = r->leftMostChild;
    while (p != NULL) {
        Node* q = find(p, u);
        if (q != NULL) return q;
        p = p->rightSibling;
    }
    return NULL;
}

void insert(Node* r, int u, int v) {
    if (find(r, u) != NULL) return;
    
    Node* p = find(r, v);
    if (p == NULL) return;
    
    Node* q = makeNode(u);
    q->parent = p;
    
    if (p->leftMostChild == NULL) {
        p->leftMostChild = q;
        return;
    }
    
    Node* h = p->leftMostChild;
    while (h->rightSibling != NULL) {
        h = h->rightSibling;
    }
    h->rightSibling = q;
}

int depth(Node* r) {
    int d = 0;
    Node* p = r;
    while (p != NULL) {
        d++;
        p = p->parent;
    }
    return d;
}

int height(Node* r) {
    if (r == NULL) return 0;
    
    int maxH = 0;
    Node* p = r->leftMostChild;
    while (p != NULL) {
        int h = height(p);
        if (h > maxH) maxH = h;
        p = p->rightSibling;
    }
    return maxH + 1;
}

void freeTree(Node* r) {
    if (r == NULL) return;
    Node* p = r->leftMostChild;
    while (p != NULL) {
        Node* np = p->rightSibling;
        freeTree(p);
        p = np;
    }
    free(r);
}

int main() {
    char cmd[20];
    int u, v;
    int results[1000];
    int resultCount = 0;
    
    while (scanf("%s", cmd) == 1) {
        if (cmd[0] == '*') break;
        
        if (strcmp(cmd, "MakeRoot") == 0) {
            scanf("%d", &u);
            root = makeNode(u);
        } else if (strcmp(cmd, "Insert") == 0) {
            scanf("%d %d", &u, &v);
            insert(root, u, v);
        } else if (strcmp(cmd, "Height") == 0) {
            scanf("%d", &u);
            Node* node = find(root, u);
            results[resultCount++] = height(node);
        } else if (strcmp(cmd, "Depth") == 0) {
            scanf("%d", &u);
            Node* node = find(root, u);
            results[resultCount++] = depth(node);
        }
    }
    
    for (int i = 0; i < resultCount; i++) {
        printf("%d\n", results[i]);
    }
    
    freeTree(root);
    return 0;
}