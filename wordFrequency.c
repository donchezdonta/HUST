#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 21
#define N 1000001

typedef struct Node {
    char word[MAX];
    int occ;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

Node* root = NULL;
char T[N];
int n;

void input() {
    n = 0;
    while(!feof(stdin)) {
        char c = fgetc(stdin);
        if (feof(stdin)) break;
        T[n] = c;
        n++;
    }
    T[n] = '\0'; 
}

Node* createNode(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->occ = 1;
    newNode->leftChild = NULL; 
    newNode->rightChild = NULL;
    return newNode;
}

Node* insert(Node* r, char* word) {
    if (r == NULL) 
        return createNode(word);
    int cmp = strcmp(word, r->word);
    if (cmp == 0)
        r->occ++;
    else if (cmp < 0) 
        r->leftChild = insert(r->leftChild, word);
    else 
        r->rightChild = insert(r->rightChild, word);
    return r;
}

int legal(char c) {
    return isalnum(c);
}

void extractWords() {
    root = NULL;
    int end = -1;
    char word[MAX];
    
    for (int i = 0; i < n; i++) {
        if (legal(T[i])) {
            end++;
            word[end] = T[i];
        } else {
            if (end != -1) {
                word[end + 1] = '\0';
                root = insert(root, word);
            }
            end = -1;
        }
    }
    
    if (end != -1) {
        word[end + 1] = '\0';
        root = insert(root, word);
    }
}

void inOrder(Node* r) {
    if (r == NULL) return;
    inOrder(r->leftChild);
    printf("%s %d\n", r->word, r->occ);
    inOrder(r->rightChild);
}

int main() {
    input();
    extractWords();
    inOrder(root);
    return 0;
}