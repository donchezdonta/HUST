#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char date[12];
    int count;
    struct Node *next;
} Node;

Node *insert_sorted(Node *head, char *date)
{
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL)
    {
        int cmp = strcmp(current->date, date);
        if (cmp == 0)
        {
            current->count++;
            return head;
        }
        if (cmp > 0)
            break;
        prev = current;
        current = current->next;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->date, date);
    new_node->count = 1;
    new_node->next = current;

    if (prev == NULL)
    {
        return new_node;
    }
    prev->next = new_node;
    return head;
}

int main(int argc, char *argv[])
{
    FILE *input = stdin;
    FILE *output = stdout;

    if (argc >= 2)
    {
        input = fopen(argv[1], "r");
        if (input == NULL)
        {
            printf("Cannot open input file\n");
            return 1;
        }
    }

    if (argc >= 3)
    {
        output = fopen(argv[2], "w");
        if (output == NULL)
        {
            printf("Cannot open output file\n");
            fclose(input);
            return 1;
        }
    }

    char date[12], time[10], user[50], question[50];
    Node *head = NULL;

    while (fscanf(input, "%s", date) == 1 && date[0] != '*')
    {
        fscanf(input, "%s %s %s", time, user, question);
        head = insert_sorted(head, date);
    }

    Node *current = head;
    while (current != NULL)
    {
        fprintf(output, "%s %d\n", current->date, current->count);
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    if (input != stdin)
        fclose(input);
    if (output != stdout)
        fclose(output);

    return 0;
}