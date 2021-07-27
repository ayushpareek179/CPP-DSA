//Implementing Sparse matrices in C
#include <stdio.h>
#include <stdlib.h>

struct Element
{
    int row;
    int col;
    int val; //data type of the matrix
};

struct Sparse
{
    int numRows;
    int numCols;
    int numNon0s;
    struct Element* arr; //pointer to heap
};

void reader(int* n, char s[])
{
    int inp;
    while(1)
    {
        printf("Enter the number of %s: ", s);
        scanf("%d", &inp);
        if(inp > 0)
            break;
        printf("Invalid input, try again\n");
    }
    *n = inp;
}

void allocator(struct Sparse* sp, int mag)
{
    if(mag == 0)
        sp->arr = (struct Element*)malloc((sp->numRows*sp->numCols)*sizeof(struct Element)); //worst-case - no zeroes
    else
        sp->arr = (struct Element*)realloc(sp->arr, sp->numNon0s*sizeof(struct Element)); //preventing wastage
}

void create(struct Sparse* sp)
{
    reader(&sp->numRows, "rows");
    reader(&sp->numCols, "columns");
    //illusion of 2D array
    printf("Enter the matrix elements:\n");
    int temp, i, j; sp->numNon0s = 0;
    allocator(sp, 0);
    for(i = 0; i < sp->numRows; i++)
    {
        for(j = 0; j < sp->numCols; j++)
        {
            scanf("%d", &temp);
            if(temp != 0)
            {
                sp->arr[sp->numNon0s].col = j;
                sp->arr[sp->numNon0s].row = i;
                sp->arr[sp->numNon0s].val = temp;
                sp->numNon0s++;
            }
        }
    }
    allocator(sp, 1);
}

void display(struct Sparse sp)
{
    int i, j, tracker = 0;
    printf("The matrix is:\n");
    for(i = 0; i < sp.numRows; i++)
    {
        for(j = 0; j < sp.numCols; j++)
        {
            if(i == sp.arr[tracker].row && j == sp.arr[tracker].col)
                printf("%d ", sp.arr[tracker++].val);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
}

void deallocate(struct Sparse* sp)
{
    free(sp->arr);
    sp->numRows = sp->numCols = sp->numNon0s = 0;
}

int main()
{
    struct Sparse S;
    create(&S);
    display(S);
    deallocate(&S);
    printf("Program terminated\n");
    return 0;
}