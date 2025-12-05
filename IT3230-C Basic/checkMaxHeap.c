#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 100001

typedef struct TNode {
    int id;
    struct TNode* left;
    struct TNode* right;
} Node;

Node* root = NULL;
Node* nodes[N] = {NULL};

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

bool isMaxHeap(Node* node) {
    if (node == NULL) return true;

    if (node->left != NULL) {
        if (node->id < node->left->id) 
            return false;
        if (isMaxHeap(node->left) == false)
            return false;
    }

    if (node->right != NULL) {
        if (node->id < node->right->id) 
            return false;
        if (isMaxHeap(node->right) == false)
            return false;
    }

    return true;
}

int countNodesWithTwoChildren(Node* node) {
    if (node == NULL) return 0;
    
    int count = 0;
    if (node->left != NULL && node->right != NULL) 
        count = 1;

    return count + countNodesWithTwoChildren(node->left) + countNodesWithTwoChildren(node->right);
}

int main() {
    char command[50];
    int u, v;
    char results[100000] = "";
    
    while (scanf("%s", command) == 1) {
        if (strcmp(command, "*") == 0) {
            break;
        }
        else if (strcmp(command, "make-root") == 0) {
            scanf("%d", &u);
            root = makeNode(u);
            nodes[u] = root;
        }
        else if (strcmp(command, "add-left") == 0) {
            scanf("%d %d", &u, &v);
            addLeft(u, v);
        }
        else if (strcmp(command, "add-right") == 0) {
            scanf("%d %d", &u, &v);
            addRight(u, v);
        }
    }
    
    while (scanf("%s", command) == 1) {
        if (strcmp(command, "***") == 0) {
            break;
        }
        else if (strcmp(command, "is-max-heap") == 0) {
            scanf("%d", &u);
            int result = isMaxHeap(nodes[u]) ? 1 : 0;
            char temp[20];
            sprintf(temp, "%d\n", result);
            strcat(results, temp);
        }
        else if (strcmp(command, "count-nodes-having-2-children") == 0) {
            scanf("%d", &u);
            int result = countNodesWithTwoChildren(nodes[u]);
            char temp[20];
            sprintf(temp, "%d\n", result);
            strcat(results, temp);
        }
    }
    
    printf("%s", results);
    
    return 0;
}