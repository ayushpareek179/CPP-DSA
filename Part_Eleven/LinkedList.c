//Linked-lists in C
/*
Version @1: 30/07/21 - three kinds of insertion, display and custom-creation using an array
Version @2: 01/08/21 - counting number of nodes, calculating sum of nodes' data, returning max/min elements and their indices, 
                       implementing linear search (iteratively and recursively, which return indices) and its bring-to-head facilitator
Version @3: 02/08/21 - integrated insert, correction in 'linear search improvement' if foundIndex is 0 and change in create
 */
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

/*insertion operations follow*/
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

void display(struct Node* ptr)
{
    while(ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}

int countNodes(struct Node* ptr)
{
    int count = 0;
    while(ptr != NULL)
    {
        ptr = ptr->next;
        count++;
    }
    return count;
}

int addNodes(struct Node* ptr)
{
    int sum = 0;
    while(ptr)
    {
        sum += ptr->data;
        ptr = ptr->next;
    }
    return sum;
}

int* maxMin(struct Node* ptr)
{
    int* ext = (int*)malloc(4*sizeof(int)), index = 0;
    ext[0] = INT_MIN; ext[2] = INT_MAX;
    ext[1] = ext[3] = -1; 
    while(ptr)
    {
        if(ptr->data < ext[2])
        {
            ext[2] = ptr->data;
            ext[3] = index;
        }
        else if(ptr->data > ext[0])
        {
            ext[0] = ptr->data;
            ext[1] = index;
        }
        index++;
        ptr = ptr->next;
    }
    return ext;
}

int search(struct Node** head, struct Node* ptr, int key, int choice)
{
    struct Node *last = NULL; //can assign last = ptr but that's against definition and anyway not needed if foundIndex = 0 
    int index = 0;
    while(ptr)
    {
        if(ptr->data == key)
        {
            if(choice)
            {
                if(*head != ptr) //if element is found at index 0, assignment leads to ptr->next = ptr (infinite linked list) 
                {
                    last->next = ptr->next;
                    ptr->next = *head;
                    *head = ptr; //magic - just like addHead's last line
                }
            }
            return index;
        }
        last = ptr;
        ptr = ptr->next;
        index++; 
    }
    return -1;
}

//integrated insertion function 
int insert(struct Node** head, int pos, int x)
{
    int flag = 0; //allocation unsuccessful
    if(pos < 0 || pos > countNodes(*head))
        return flag;
    if(pos == 0) //for head
    {
        struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = x;
        temp->next = *head;
        *head = temp;
        flag = 1;
    }
    else //every other position
    {
        struct Node* ptr = *head, *temp;
        int i = 1;
        for(; i <= pos-1 && ptr != NULL; i++) //stops at a node* n and not n->next
            ptr = ptr->next;
        if(ptr) //prevents accessing invalid position
        {
            temp = (struct Node*)malloc(sizeof(struct Node));
            temp->data = x;
            temp->next = ptr->next;
            ptr->next = temp;
            flag = 1;
        } //redundant now because of the return statement above
    }
    return flag;
}

//custom creation in a weird, roundabout manner with choice
void create(struct Node** head, int A[], int n, int choice)
{
    int i, f;
    if(!choice)
    {
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
    else //choice == 1
    {
        for(i = 0; i < 10; i++)
        {
            f = insert(head, i%2, A[i]); //can mimic the actions above
            if(!f)
            {
                printf("Node could not be allocated\n");
                //break;
            }
        }
    }
}

/*recursive equivalents follow*/
void rDisplay(struct Node* ptr)
{
    if(ptr != NULL)
    {
        printf("%d ", ptr->data); 
        rDisplay(ptr->next);
        printf("%d ", ptr->data); //prints the list in reverse
    }
    else
        printf("\nList displayed in reverse:\n");
}

int rCount(struct Node* ptr)
{
    if(ptr)
        return rCount(ptr->next)+1;
    return 0;
}

int rAdd(struct Node* ptr)
{
    if(ptr)
        return rAdd(ptr->next)+ptr->data;
    return 0;
}

int rMax(struct Node* ptr)
{//simplistic
    int x;
    if(!ptr)
        return INT_MIN;
    x = rMax(ptr->next);
    return x > ptr->data ? x:ptr->data;
}

int* rMinMax(struct Node* ptr)
{
    static int extremum[5] = {INT_MIN, -1, INT_MAX, -1, 0};
    if(ptr)
    {
        if(ptr->data < extremum[2])
        {
            extremum[2] = ptr->data;
            extremum[3] = extremum[4];
        }
        else if(ptr->data > extremum[0])
        {
            extremum[0] = ptr->data;
            extremum[1] = extremum[4];
        }
        extremum[4]++;
        rMinMax(ptr->next);
    }
    else
        return 0;
    return extremum;
}

int rSearch(struct Node* ptr, int key, int index)
{
    if(!ptr)
        return -1;
    if(ptr->data == key)
        return index;
    return rSearch(ptr->next, key, index+1); //may/mayn't write return
}

int main()
{
    int *p, arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, index, f;
    struct Node* first = NULL;
    create(&first, arr, 10, 1);
    
    printf("Linked list contents:\n");
    display(first);
    printf("\n");
    index = search(&first, first, 90, 1);
    if(index != -1)
        printf("Element %d was found at index: %d\n", 90, index);
    else
        printf("Element not found\n");
    index = search(&first, first, 10, 0);
    if(index != -1)
        printf("Element %d was found at index: %d\n", 10, index);
    else
        printf("Element not found\n");
    printf("Linked list contents:\n");
    display(first);
    printf("\n");

    printf("Program terminated\n");
    return 0;
}