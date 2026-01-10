#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define M 10000

typedef struct Node {
    char key[MAX + 1];
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

Node* T[M];

Node* createNode(char* key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->leftChild = NULL; 
    newNode->rightChild = NULL;
    return newNode;
}

int hashCode(char *str, int mod) {
    int code = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        code = (code * 256 + str[i]) % mod;
    }
    return code;
}

Node* findBST(Node* r, char* k) {
    if (r == NULL)
        return NULL;
    int cmp = strcmp(k, r->key);
    if (cmp == 0)
        return r;
    if (cmp < 0)
        return findBST(r->leftChild, k);
    else 
        return findBST(r->rightChild, k);
}

int find(char* k) {
    int i = hashCode(k, M);
    Node* node = findBST(T[i], k);
    if (node == NULL) return 0;
    else return 1;
}

Node* insertBST(Node* r, char* k) {
    if (r == NULL) {
        return createNode(k);
    }
    int cmp = strcmp(k, r->key);
    if (cmp > 0)
        r->rightChild = insertBST(r->rightChild, k);
    else 
        r->leftChild = insertBST(r->leftChild, k);
    return r;
}

int insert(char* k) {
    int i = hashCode(k, M);
    if (findBST(T[i], k) != NULL) return 0;
    T[i] = insertBST(T[i], k);
    return 1;
}

int main() {
    /*
    char key[MAX + 1];
    
    for (int i = 0; i < M; i++) {
        T[i] = NULL;
    }

    while (1) {
        scanf("%s", key);
        if (strcmp(key, "*") == 0) break;
        insert(key);
    }
    
    char cmd[10];
    while (1) {
        scanf("%s", cmd);
        if (strcmp(cmd, "***") == 0) break;
        scanf("%s", key);
        if (strcmp(cmd, "find") == 0) {
            printf("%d\n", find(key));
        } else if (strcmp(cmd, "insert") == 0) {
            printf("%d\n", insert(key));
        }
    }
    */

    char s[10];
    fgets(s, sizeof(s), stdin);
    printf("%d", hashCode(s, 2));
    return 0;
}