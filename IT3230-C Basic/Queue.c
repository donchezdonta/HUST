#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int data;
    struct Node * prev;
    struct Node * next;
}Node;

Node * makeNode(int data){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Node * enQueue(Node * head, int data){ // sai
    if(head == NULL) return head;
    Node * newNode = makeNode(data);
    newNode -> prev = head;
    return newNode;
}

Node * deQueue(Node * tail){
    if(tail == NULL) return tail;
    Node * temp = tail;
    tail = tail->next;
    free(temp);
    return tail;
}

int main(){
    int t, k;
    char s[10];
    Node * head = NULL, * tail = NULL;
    scanf("%d", &t);
    while(t--){
        scanf("%s", s);
        if(strcmp(s, "enqueue") == 0){
            scanf("%d", &k);
            enQueue(head, k);
            if(tail == NULL) tail = head;
        }
        else{
            tail = deQueue(tail);
        }
    }
}