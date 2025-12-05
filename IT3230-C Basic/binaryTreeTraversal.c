#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

Node* root = NULL;

Node* makeNode(int u) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->id = u;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node* find(int u, Node* r) {
    if (r == NULL) return NULL;
    if (r->id == u) return r;
    
    Node* p = find(u, r->leftChild);
    if (p != NULL) return p;
    
    return find(u, r->rightChild);
}

void addLeft(int u, int v, Node* r) {
    Node* p = find(v, r);
    if (p == NULL) return;
    if (p->leftChild != NULL) return;
    
    Node* q = find(u, r);
    if (q != NULL) return;
    
    p->leftChild = makeNode(u);
}

void addRight(int u, int v, Node* r) {
    Node* p = find(v, r);
    if (p == NULL) return;
    if (p->rightChild != NULL) return;
    
    Node* q = find(u, r);
    if (q != NULL) return;
    
    p->rightChild = makeNode(u);
}

void preOrder(Node* r, char* output) {
    if (r == NULL) return;
    char temp[20];
    sprintf(temp, "%d ", r->id);
    strcat(output, temp);
    preOrder(r->leftChild, output);
    preOrder(r->rightChild, output);
}

void inOrder(Node* r, char* output) {
    if (r == NULL) return;
    inOrder(r->leftChild, output);
    char temp[20];
    sprintf(temp, "%d ", r->id);
    strcat(output, temp);
    inOrder(r->rightChild, output);
}

void postOrder(Node* r, char* output) {
    if (r == NULL) return;
    postOrder(r->leftChild, output);
    postOrder(r->rightChild, output);
    char temp[20];
    sprintf(temp, "%d ", r->id);
    strcat(output, temp);
}

int main() {
    char command[20];
    int u, v;
    char outputs[100000] = "";
    
    while (scanf("%s", command) == 1) {
        if (strcmp(command, "*") == 0) {
            break;
        }
        else if (strcmp(command, "MakeRoot") == 0) {
            scanf("%d", &u);
            root = makeNode(u);
        }
        else if (strcmp(command, "AddLeft") == 0) {
            scanf("%d %d", &u, &v);
            addLeft(u, v, root);
        }
        else if (strcmp(command, "AddRight") == 0) {
            scanf("%d %d", &u, &v);
            addRight(u, v, root);
        }
        else if (strcmp(command, "PreOrder") == 0) {
            preOrder(root, outputs);
            strcat(outputs, "\n");
        }
        else if (strcmp(command, "InOrder") == 0) {
            inOrder(root, outputs);
            strcat(outputs, "\n");
        }
        else if (strcmp(command, "PostOrder") == 0) {
            postOrder(root, outputs);
            strcat(outputs, "\n");
        }
    }
    
    printf("%s", outputs);
    
    return 0;
}