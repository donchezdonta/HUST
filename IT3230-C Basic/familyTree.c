#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 30

typedef struct Node {
    char name[MAX_LEN];
    struct Node* leftMostChild;
    struct Node* rightSibling;
    struct Node* parent;
} Node;

Node* listNodes[10000];
int TotalNodes = 0;

Node* makeNode(const char* name) {
    Node* p = (Node*)malloc(sizeof(Node));
    strcpy(p->name, name);
    p->leftMostChild = NULL;
    p->rightSibling = NULL;
    p->parent = NULL;
    return p;
}

void addChild(Node* child, Node* parent) {
    child->parent = parent;
    if (parent->leftMostChild == NULL) 
        parent->leftMostChild = child;
    else {
        Node* p = parent->leftMostChild;
        while (p->rightSibling != NULL)
            p = p->rightSibling;
        p->rightSibling = child;
    }
}

Node* findNode(char* name) {
    for (int i = 0; i < TotalNodes; i++) {
        if (strcmp(listNodes[i]->name, name) == 0)
            return listNodes[i];
    }
    return NULL;
}

Node* getOrCreateNode(char* name) {
    Node* node = findNode(name);
    if (node == NULL) {
        node = makeNode(name);
        listNodes[TotalNodes++] = node;
    }
    return node;
}

int countDescendants(Node* node) {
    if (node == NULL) return 0;

    Node* p = node->leftMostChild;
    int cnt = 0;

    while (p != NULL) {
        cnt += 1 + countDescendants(p);
        p = p->rightSibling;
    }
    return cnt;
}

int generation(Node* r) {
    if (r == NULL) return 0;
    
    int maxH = 0;
    Node* p = r->leftMostChild;
    
    if (p == NULL) return 0;
    
    while (p != NULL) {
        int h = generation(p);
        if (h > maxH) maxH = h;
        p = p->rightSibling;
    }
    return maxH + 1;
}

void freeTree() {
    for (int i = 0; i < TotalNodes; i++) {
        free(listNodes[i]);
    }
}

int main() {
    char child[MAX_LEN], parent[MAX_LEN];
    char results[10000][50];
    int resultCount = 0;
    
    while (1) {
        scanf("%s", child);
        if (strcmp(child, "***") == 0) break;
        scanf("%s", parent);
        
        Node* childNode = getOrCreateNode(child);
        Node* parentNode = getOrCreateNode(parent);
        addChild(childNode, parentNode);
    }
    
    char cmd[MAX_LEN], param[MAX_LEN];
    while (1) {
        scanf("%s", cmd);
        if (strcmp(cmd, "***") == 0) break;
        scanf("%s", param);
        
        Node* node = findNode(param);
        
        if (strcmp(cmd, "descendants") == 0) {
            int count = countDescendants(node);
            sprintf(results[resultCount++], "%d", count);
        } else if (strcmp(cmd, "generation") == 0) {
            int gen = generation(node);
            sprintf(results[resultCount++], "%d", gen);
        }
    }
    
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", results[i]);
    }
    freeTree();
    return 0;
}