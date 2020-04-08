#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list_s {
    char *data;
    struct	list_s* next;
}node;

node * init(char * newString)
{
    node * newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->data = strdup(newString);

    if(newNode->data == NULL || newNode == NULL)
    {
	    fputs("Unable to allocate memory.\n", stdout);
	    exit(EXIT_FAILURE);
    }

    newNode->next = NULL;
    return(newNode);
}

node * addElement(node * previousNode, char * newString)
{
    if (previousNode == NULL)
    {
	    previousNode = init(newString);
	    return previousNode;
    }

    node* nextNode = (node*)malloc(sizeof(node));
    nextNode->data = strdup(newString);
    
    if(nextNode->data == NULL || nextNode == NULL)
    {
	    fputs("Unable to allocate memory.\n", stdout);
	    exit(EXIT_FAILURE);
    }

    nextNode->next = NULL;
    previousNode->next = nextNode;
    previousNode = nextNode;
    return previousNode;
}

void printList(node *head)
{
    node *p = head;
    while (p != NULL)
    {
	    fputs(p->data, stdout);
        p = p->next;
    }
}

void freeList(node * head)
{
    node *p = head, *t = NULL;
    while (p != NULL)
    {
	    t = p;
        p = p->next;
	    free(t->data);
	    free(t);
    }
}

int main()
{
    char string[BUFSIZ] = { '\0' };

    printf("Please enter something and then type \".\" at the next line.\n");
    char* check_fgets = fgets(string, BUFSIZ, stdin);

    if (check_fgets == NULL)
    {
	fputs("Error: cannot get string from stdin", stdout);
	exit(EXIT_FAILURE);
    }
    
    char endInput[BUFSIZ] = ".\n";
    if (strcmp(string, endInput) == 0)
    {
	    fputs("No input strings.\n", stdout);
	    exit(EXIT_FAILURE);
    }

    node * nodePtr = NULL;
    nodePtr = addElement(nodePtr, string);
    node * head = nodePtr;


    check_fgets = fgets(string, BUFSIZ, stdin);
    if (check_fgets == NULL)
    {
        fputs("Error: cannot get string from stdin.", stdout);
	    freeList(head);
        exit(EXIT_FAILURE);
    }
    
    while (strcmp(string, endInput) != 0)
    {
	    nodePtr = addElement(nodePtr, string);
	    check_fgets = fgets(string, BUFSIZ, stdin);
	    if (check_fgets == NULL)
	    {
	        fputs("Error: cannot get string from stdin", stdout);
	        freeList(head);
	        exit(EXIT_FAILURE);
	    }
    }
    printList(head);
    freeList(head);
    exit(EXIT_SUCCESS);
}
