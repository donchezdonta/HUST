#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact_t {
    char name[50];
    char tel[15];
    char email[30];
} contact;

typedef struct list_el {
    contact el;
    struct list_el *next;
} node;

node *root = NULL, *cur = NULL, *prev = NULL;

node* makeNewNode(contact ct) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->el = ct;
    new_node->next = NULL;
    return new_node;
}

contact readNode() {
    contact tmp;
    printf("Name:");
    getchar();
    fgets(tmp.name, 50, stdin);
    tmp.name[strcspn(tmp.name, "\n")] = 0;
    printf("Phone number:");
    scanf("%s", tmp.tel);
    printf("Email:");
    scanf("%s", tmp.email);
    return tmp;
}

void displayNode(node* p) {
    if (p == NULL) return;
    printf("%-20s\t%-15s\t%-25s%-p\n", p->el.name, p->el.tel, p->el.email, p->next);
}

void insertAtHead(contact ct) {
    node* new_item = makeNewNode(ct);
    new_item->next = root;
    root = new_item;
    cur = root;
    prev = NULL;
}

void insertAfterCurrent(contact ct) {
    node* new_node = makeNewNode(ct);
    if (root == NULL) {
        root = new_node;
        cur = root;
        prev = NULL;
    } else if (cur == NULL) {
        return;
    } else {
        new_node->next = cur->next;
        cur->next = new_node;
        prev = cur;
        cur = new_node;
    }
}

void insertBeforeCurrent(contact ct) {
    node *new_node = makeNewNode(ct);
    if (root == NULL) {
        root = new_node;
        cur = root;
        prev = NULL;
    } else {
        new_node->next = cur;
        if (cur == root) {
            root = new_node;
            prev = NULL;
        } else {
            prev->next = new_node;
        }
        cur = new_node;
    }
}

void insertAtTail(contact ct) {
    node* new_node = makeNewNode(ct);
    if (root == NULL) {
        root = new_node;
        cur = root;
        prev = NULL;
    } else {
        node* temp = root;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        prev = temp;
        cur = new_node;
    }
}


void traversingList() {
    node* p;
    for (p = root; p != NULL; p = p->next)
        displayNode(p);
}

void deleteFirstElement() {
    if (root == NULL) return;
    node* del = root;
    root = root->next;
    free(del);
    cur = root;
    prev = NULL;
}

void deleteCurrentElement() {
    if (cur == NULL) return;
    if (cur == root) {
        deleteFirstElement();
    } else {
        prev->next = cur->next;
        free(cur);
        cur = prev->next;
    }
}

void reverseList() {
    node *curr = root, *p = NULL, *next;
    while (curr != NULL) {
        next = curr->next;
        curr->next = p;
        p = curr;
        curr = next;
    }
    root = p;
    cur = root;
    prev = NULL;
}

void freeList() {
    node* tmp;
    while (root != NULL) {
        tmp = root;
        root = root->next;
        free(tmp);
    }
    cur = prev = NULL;
}

int main() {
    int choice;
    contact ct;
    
    while (1) {
        printf("\n1.Insert at head\n2.Insert after current\n3.Insert before current\n");
        printf("4.Insert at tail\n5.Display list\n6.Delete first\n7.Delete current\n8.Reverse\n9.Exit");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                ct = readNode();
                insertAtHead(ct);
                traversingList();
                break;
            case 2:
                printf("Testing for the insertion after current position of pointer.Before insert..\n");
                traversingList();
                ct = readNode();
                insertAfterCurrent(ct);
                traversingList();
                break;
            case 3:
                printf("Testing for the insertion before current position of pointer.Before insert..\n");
                traversingList();
                ct = readNode();
                insertBeforeCurrent(ct);
                traversingList();
                break;
            case 4:
                printf("Testing for the insertion at the tail position of pointer.Before insert..\n");
                traversingList();
                ct = readNode();
                insertAtTail(ct);
                traversingList();
                break;
            case 5:
                printf("Displaying list....\n");
                traversingList();
                printf("\nPress any key to continue...");
                getchar();
                getchar();
                break;
            case 6:
                printf("Testing for the deletion of the first element..\n");
                deleteFirstElement();
                traversingList();
                break;
            case 7:
                printf("Testing for the deletion of the middle element..\n");
                deleteCurrentElement();
                traversingList();
                break;
            case 8:
                printf("Testing for the reverse list operation..\n");
                reverseList();
                traversingList();
                break;
            case 9:
                freeList();
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}