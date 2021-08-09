//Implementing a linked list in C++
#include <iostream>
using namespace std;

template <class T>
class Node
{
    public:
    T data;
    Node* next;
};

template <class T>
class LinkedList
{
    private:
    Node<T>* head;
    public:
    LinkedList()
    {
        head = NULL;
    }
    LinkedList(T*, int, int);
    void insert(T, int);
    void display();
    int countNodes();
    T deleteNode(int);
    ~LinkedList();
};

template <class T>
LinkedList<T>::LinkedList(T* arr, int n, int choice)
{
    head = NULL;
    for(int i = 0; i < n; i++)
    {
        if(choice == 1) //head
            insert(arr[i], 0);
        else if(choice == 2) //end
            insert(arr[i], i);
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* temp = head;
    while(head)
    {
        head = head->next;
        delete temp;
        temp = head;
    }
    cout<<"Object deleted\n";
}

template <class T>
void LinkedList<T>::insert(T newData, int position)
{
    if(position < 0 || position > countNodes())
        return;
    Node<T>* newNode = new Node<T>;
    newNode->data = newData;
    if(position == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node<T>* temp = head;
        for(int i = 1; i <= position - 1; i++)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

template <class T>
int LinkedList<T>::countNodes()
{
    Node<T>* temp = head;
    int count = 0;
    while(temp)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

template <class T>
void LinkedList<T>::display()
{
    Node<T>* temp = head;
    cout<<"Linked list elements are: "<<"\n";
    while(temp)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<"\n";
}

template <class T>
T LinkedList<T>::deleteNode(int position)
{
    if(position < 0 || position > countNodes())
        return 0;
    Node<T>* temp = head, *tempPtr; T var;
    if(position == 1)
    {
        head = head->next;
        var = temp->data;        
    }
    else
    {
        int c = 1;
        while(c != position)
        {
            tempPtr = temp;
            temp = temp->next;
            c++;
        }
        var = temp->data;
        tempPtr->next = temp->next; 
    }
    delete temp;
    return var;
}

int main()
{
    int n;
    while(true)
    {
        cout<<"Enter the number of elements you intend to insert: ";
        cin>>n; 
        if(n > 0)
            break;
        cout<<"Invalid input, retry with a positive number\n";
    }
    int arr[n];
    cout<<"Enter the elements: ";
    for(int i = 0; i < n; i++)
        cin>>arr[i];
    
    LinkedList<int> first(arr, n, 2);
    first.display();
    cout<<"Deleted element: "<<first.deleteNode(1)<<"\n";
    first.display();
    
    return 0;
}