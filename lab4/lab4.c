#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct list_s {
    char *data;
    struct	list_s* next;
}node;

node * initList(char * newString)
{
    node * newNode;
    newNode = (node*)malloc(sizeof(node));
    newNode->data = strdup(newString);
    if(newNode == NULL)
    {
	return NULL;
    }
    newNode->data = strdup(newString);
    if(newNode == NULL)
    {
	free(newNode);
	return NULL;
    }

    newNode->next = NULL;
    return(newNode);
}

node * addElement(node * previousNode, char * newString)
{
    if (previousNode == NULL)
    {
	previousNode = initList(newString);
	return previousNode;
    }

    node* nextNode = (node*)malloc(sizeof(node));
    
    if(nextNode == NULL)
    {
	return NULL;
    }
    nextNode->data = strdup(newString);
    if(nextNode == NULL)
    {
	free(nextNode);
	return NULL;
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

    node * nodePtr = initList(string);
    if(nodePtr == NULL)
    {
	perror(strerror(errno));
	exit(EXIT_FAILURE);
    }
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
	if(nodePtr == NULL)
	{
	    perror(strerror(errno));
	    freeList(head);
	    exit(EXIT_FAILURE);
        }
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
