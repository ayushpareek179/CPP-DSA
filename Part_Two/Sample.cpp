//Structres and ways in which parameters are passed
#include <iostream>
using namespace std;

struct Rectangle 
{
    double length;
    double breadth;
};

bool validator(double, string);
void initialize(Rectangle* rect) //pass by address
{//setter
    double a,b; bool x,y;
    while(true)
    {
        cout<<"Enter the length and breadth\n";
        cin>>a;
        x = validator(a, "Length");
        if(!x)
            continue;
        cin>>b;
        y = validator(b, "Breadth");
        if(!y)
            continue; 
        
        rect->length = a;
        rect->breadth = b;
        break;
    }
}
bool validator(double n, string s) //facilitator for initialize(Rectangle*, double, double)
{
    if(n <= 0)
        cout<<s<<" has to be non-negative\nPlease try again\n";
    return (n>0);
}

double area(Rectangle rect) //pass by value
{//returns area
    return rect.length*rect.breadth;
}

void mutator(Rectangle& rect) //pass by reference
{//makes the rectangle a square
    double max = rect.length > rect.breadth ? rect.length : rect.breadth;
    rect.length = rect.breadth = max; 
}

int main()
{
    Rectangle r; initialize(&r);
    printf("Area of rectangle is: %lf units\n",area(r));
    
    if(r.length != r.breadth)
    {
        mutator(r);
        cout<<"The rectangle has been converted into a square\nIts sides are equal now\n";
        printf("Area of rectangle is: %lf units\n",area(r));
    }
    return 0;
}