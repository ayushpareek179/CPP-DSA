//Linked-lists in C
/*
Version @1: 30/07/21 - three kinds of insertion, display and custom-creatin using an array
 */
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

void atEnd(struct Node** head, int n)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* tempLast = *head;
    newNode->data = n;
    newNode->next = NULL;

    if(*head == NULL)
    {
        *head = newNode;
        return;
    }

    while(tempLast->next != NULL) //using tempLast != NULL does not link the node as expected
            tempLast = tempLast->next;
    tempLast->next = newNode;
}

void atHead(struct Node** head, int n)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = n;
    if(*head == NULL)
        newNode->next = NULL; //list was empty
    else 
        newNode->next = *head;
    *head = newNode;
}

void afterN(struct Node* aNode, int n)
{
    if(aNode != NULL)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = n;
        newNode->next = aNode->next;
        aNode->next = newNode;
    }
}

void create(struct Node** head, int A[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(i%3 == 0 || i == 1)
            atEnd(head, A[i]);
        else if(i%3 == 2)
            atHead(head, A[i]);
        else
        {
            struct Node* someNode = *head;
            while(someNode->data != A[2])
                someNode = someNode->next;
            afterN(someNode, A[i]);
        }
    }
}

void display(struct Node* ptr)
{
    while(ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}

void rDisplay(struct Node* ptr)
{
    if(ptr != NULL)
    {
        printf("%d ", ptr->data); 
        rDisplay(ptr->next);
        printf("%d ", ptr->data); //prints the list in reverse
    }
    else
        printf("\n");
}

int main()
{
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150};
    struct Node* first = NULL;
    create(&first, arr, 15);  
    printf("Linked list contents:\n");
    rDisplay(first);
    printf("\n");
    printf("Program terminated\n");
    return 0;
}