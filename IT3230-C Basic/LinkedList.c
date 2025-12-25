#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
Node* insertLast(Node* head, int value) {
    Node* newNode = createNode(value);
    if(head == NULL) {
        return newNode;
    }
    Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}
void printList(Node* head) {
    Node* temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}
Node * findNode(Node* head, int value) {
    Node* temp = head;
    while(temp != NULL) {
        if(temp->data == value) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Node * insertFirst(Node* head, int value) {
    Node* newNode = createNode(value);
    if(head == NULL) {
        head = newNode;
        return head;
    }
    newNode->next = head;
    head = newNode;
    return head;
}
void addAfter(Node* head, int afterVal, int value){
    Node * newNode = findNode(head, afterVal);
    if(newNode !=  NULL){
        Node* temp = createNode(value);
        temp->next = newNode->next;
        newNode->next = temp;
    }
}
Node * addBefore(Node * head, int beforeVal, int value){
    if(head == NULL) return head;
    if(head->data == beforeVal){
        head = insertFirst(head, value);
        return head;
    }
    Node* temp = head;
    while(temp->next != NULL){
        if(temp->next->data == beforeVal){
            Node* newNode = createNode(value);
            newNode->next = temp->next;
            temp->next = newNode;
            return head;
        }
        temp = temp->next;
    }
    return head;
}
Node* deleteNode(Node * head, int value){
    if(head == NULL) return head;
    if(head->data == value){
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    Node* temp = head;
    while(temp->next != NULL){
        if(temp->next->data == value){
            Node* delNode = temp->next;
            temp->next = delNode->next;
            free(delNode);
            return head;
        }
        temp = temp->next;
    }
    return head;
}
Node * reverseList(Node * head){
    if(head == NULL || head->next == NULL) return head;
    Node * prev = NULL;
    Node * curr = head;
    Node * next;
    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
int main() {
    int n;
    scanf("%d", &n);
    Node* head = NULL, *temp;
    for(int i = 0; i < n;i++){
        int value;
        scanf("%d", &value);
        Node* newNode = createNode(value);

        if(head == NULL) head = newNode;
        else {
            temp->next = newNode;
        }
        temp = newNode;
    }
    char command[20];
    while(1){
        scanf("%s", command);
        if(command[0] == '#') break;
        if(strcmp(command, "addfirst") == 0){
            int value;
            scanf("%d", &value);
            if(findNode(head, value) == NULL){
                head = insertFirst(head, value);
            }
        }
        else if(strcmp(command, "addlast") == 0){
            int value;
            scanf("%d", &value);
            if(findNode(head, value) == NULL){
                head = insertLast(head, value);
            }
        }
        else if(strcmp(command, "addafter") == 0){
            int afterVal, value;
            scanf("%d %d", &value, &afterVal);
            if(findNode(head, value) == NULL){
                addAfter(head, afterVal, value);
            }
        }
        else if(strcmp(command, "addbefore") == 0){
            int beforeVal, value;
            scanf("%d %d", &value, &beforeVal);
            if(findNode(head, value) == NULL){
                head = addBefore(head, beforeVal, value);
            }
        }
        else if(strcmp(command, "remove") == 0){
            int value;
            scanf("%d", &value);
            head = deleteNode(head, value);
        }
        else{
            head = reverseList(head);
        }
    }
    printList(head);
    Node * current = head;
    while(current != NULL) {
        Node * next = current->next;
        free(current);
        current = next;
    }
    return 0;
}
