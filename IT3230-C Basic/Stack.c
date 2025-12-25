#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node * next;
}Node;
Node * makeNode(int val){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode -> val = val;
    newNode -> next = NULL;
    return newNode;
}
Node * push(Node * head, int val){
    Node * newNode = makeNode(val);
    newNode -> next = head;
    return newNode;
}

Node * pop(Node * head){
    if(head == NULL) return head;
    Node * temp = head;
    printf("pop %d\n", head->val);
    head = head->next;
    free(temp);
    return head;
}

int main(){
    int t, k;
    char s[10];
    Node * head = NULL;
    scanf("%d", &t);
    while(t--){
        scanf("%s %d", s, &k);
        if(strcmp(s, "push") == 0){
            head = push(head, k);
        }
        else{
            head = pop(head);
        }
    }
    Node * temp = head;
    while(temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
}
}