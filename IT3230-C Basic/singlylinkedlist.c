#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* head = NULL;

Node* createNode(int k) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = k;
    newNode->next = NULL;
    return newNode;
}

int exists(int k) {
    for (Node* newNode = head; newNode; newNode = newNode->next)
        if (newNode->key == k) return 1;
    return 0;
}

void addlast(int k) {
    if (exists(k)) return;
    Node* newNode = createNode(k);
    if (!head) head = newNode;
    else {
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void addfirst(int k) {
    if (exists(k)) return;
    Node* newNode = createNode(k);
    newNode->next = head;
    head = newNode;
}

void addafter(int u, int v) {
    if (exists(u) || !exists(v)) return;
    for (Node* newNode = head; newNode; newNode = newNode->next) {
        if (newNode->key == v) {
            Node* temp = createNode(u);
            temp->next = newNode->next;
            newNode->next = temp;
            break;
        }
    }
}

void addbefore(int u, int v) {
    if (exists(u) || !exists(v)) return;
    if (head->key == v) {
        addfirst(u);
        return;
    }
    for (Node* newNode = head; newNode->next; newNode = newNode->next) {
        if (newNode->next->key == v) {
            Node* temp = createNode(u);
            temp->next = newNode->next;
            newNode->next = temp;
            break;
        }
    }
}

void removeKey(int k) {
    if (!head) return;
    if (head->key == k) {
        Node* newNode = head;
        head = head->next;
        free(newNode);
        return;
    }
    for (Node* newNode = head; newNode->next; newNode = newNode->next) {
        if (newNode->next->key == k) {
            Node* temp = newNode->next;
            newNode->next = temp->next;
            free(temp);
            break;
        }
    }
}

void reverse() {
    Node *prev = NULL, *curr = head, *next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

int main() {
    int n, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        addlast(k);
    }
    
    char cmd[20];
    while (scanf("%s", cmd) && cmd[0] != '#') {
        if (strcmp(cmd, "addlast") == 0) {
            scanf("%d", &k);
            addlast(k);
        } else if (strcmp(cmd, "addfirst") == 0) {
            scanf("%d", &k);
            addfirst(k);
        } else if (strcmp(cmd, "addafter") == 0) {
            int u, v;
            scanf("%d %d", &u, &v);
            addafter(u, v);
        } else if (strcmp(cmd, "addbefore") == 0) {
            int u, v;
            scanf("%d %d", &u, &v);
            addbefore(u, v);
        } else if (strcmp(cmd, "remove") == 0) {
            scanf("%d", &k);
            removeKey(k);
        } else if (strcmp(cmd, "reverse") == 0) {
            reverse();
        }
    }
    
    for (Node* newNode = head; newNode; newNode = newNode->next)
        printf("%d%c", newNode->key, newNode->next ? ' ' : '\n');
    
    return 0;
}