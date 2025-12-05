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

void preOrder(Node* r, char* buffer) {
    if (r == NULL) return;
    
    char temp[20];
    sprintf(temp, "%d ", r->id);
    strcat(buffer, temp);
    
    Node* p = r->leftMostChild;
    while (p != NULL) {
        preOrder(p, buffer);
        p = p->rightSibling;
    }
}

void inOrder(Node* r, char* buffer) {
    if (r == NULL) return;
    
    Node* p = r->leftMostChild;
    inOrder(p, buffer);
    
    char temp[20];
    sprintf(temp, "%d ", r->id);
    strcat(buffer, temp);
    
    if (p == NULL) return;
    
    p = p->rightSibling;
    while (p != NULL) {
        inOrder(p, buffer);
        p = p->rightSibling;
    }
}

void postOrder(Node* r, char* buffer) {
    if (r == NULL) return;
    
    Node* p = r->leftMostChild;
    while (p != NULL) {
        postOrder(p, buffer);
        p = p->rightSibling;
    }
    
    char temp[20];
    sprintf(temp, "%d ", r->id);
    strcat(buffer, temp);
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
    char outputs[10000] = "";
    
    while (scanf("%s", cmd) == 1) {
        if (cmd[0] == '*') break;
        
        if (strcmp(cmd, "MakeRoot") == 0) {
            scanf("%d", &u);
            root = makeNode(u);
        } else if (strcmp(cmd, "Insert") == 0) {
            scanf("%d %d", &u, &v);
            insert(root, u, v);
        } else if (strcmp(cmd, "PreOrder") == 0) {
            char buffer[10000] = "";
            preOrder(root, buffer);
            strcat(outputs, buffer);
            strcat(outputs, "\n");
        } else if (strcmp(cmd, "InOrder") == 0) {
            char buffer[10000] = "";
            inOrder(root, buffer);
            strcat(outputs, buffer);
            strcat(outputs, "\n");
        } else if (strcmp(cmd, "PostOrder") == 0) {
            char buffer[10000] = "";
            postOrder(root, buffer);
            strcat(outputs, buffer);
            strcat(outputs, "\n");
        }
    }
    
    printf("%s", outputs);
    
    freeTree(root);
    return 0;
}