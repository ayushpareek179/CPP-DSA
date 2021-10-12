#include <iostream>
using namespace std;

class BinNode
{
    public:
    int data;
    BinNode* lChild;
    BinNode* rChild;
    void newNode(int num)
    {
        data = num;
        lChild = rChild = NULL;
    }
};

class BinarySearchTree
{
    BinNode* root;
    void inOrder(BinNode*); //inorder traversal and node-wise display
    BinNode* rInsert(BinNode*, int); //recursively inserts new node
    BinNode* rSearch(BinNode*, int); //recursively looks for key
    /*Deletion criteria*/
    int height(BinNode*);
    int numNodes(BinNode*);
    /*Previous and Next InOrder element*/
    BinNode* predecessor(BinNode*);
    BinNode* successor(BinNode*);
    //Delete element
    BinNode* deleteEle(BinNode*, int);
    public:
    BinarySearchTree()
    {
        root = NULL;
    }
    void insert(int); //inserts new node
    void inOrder(); //helper
    void rInsert(int); //helper
    BinNode* search(int); //returns key address
    BinNode* rSearch(int); //helper
    void deleteEle(int); //helper
};

void BinarySearchTree::insert(int toInsert)
{
    BinNode* ptr = root, *tail;
    while(ptr)
    {
        tail = ptr;
        if(toInsert < ptr->data)
            ptr = ptr->lChild;
        else if(toInsert > ptr->data)
            ptr = ptr->rChild;
        else
            return; //toInsert is already a part of the tree
    }
    ptr = new BinNode;
    ptr->newNode(toInsert);
    if(!root)
        root = ptr;
    else
    {
        if(ptr->data < tail->data)
            tail->lChild = ptr;
        else
            tail->rChild = ptr; 
    }
}

void BinarySearchTree::inOrder()
{
    cout<<"Tree's inorder traversal: ";
    inOrder(root);
    cout<<"\n";
}

void BinarySearchTree::inOrder(BinNode* ptr)
{
    if(ptr)
    {
        inOrder(ptr->lChild);
        cout<<ptr->data<<" ";
        inOrder(ptr->rChild);
    }
}

void BinarySearchTree::rInsert(int toInsert)
{
    root = rInsert(root, toInsert);
}

BinNode* BinarySearchTree::rInsert(BinNode* ptr, int toInsert)
{
    if(!ptr)
    {
        ptr = new BinNode;
        ptr->newNode(toInsert);
        return ptr;
    }
    if(toInsert < ptr->data)
        ptr->lChild = rInsert(ptr->lChild, toInsert);
    else if(toInsert > ptr->data)
        ptr->rChild = rInsert(ptr->rChild, toInsert);
    return ptr;
}

BinNode* BinarySearchTree::search(int key)
{
    BinNode* ptr = root;
    while(ptr)
    {
        if(key == ptr->data)
            break;
        else if(key < ptr->data)
            ptr = ptr->lChild;
        else
            ptr = ptr->rChild;
    }
    return ptr;
}

BinNode* BinarySearchTree::rSearch(int key)
{
    return rSearch(root, key);
}

BinNode* BinarySearchTree::rSearch(BinNode* ptr, int key)
{
    if(!ptr || ptr->data == key)
        return ptr;
    else if(key < ptr->data)
        return rSearch(ptr->lChild, key);
    else
        return rSearch(ptr->rChild, key);
}

int BinarySearchTree::height(BinNode* ptr)
{
    if(!ptr)
        return 0;
    int x = height(ptr->lChild);
    int y = height(ptr->rChild);
    return (x > y)?x+1:y+1;
}

int BinarySearchTree::numNodes(BinNode* ptr)
{
    if(!ptr)
        return 0;
    return numNodes(ptr->lChild) + numNodes(ptr->rChild) + 1;
}

BinNode* BinarySearchTree::predecessor(BinNode* ptr)
{
    while(ptr && ptr->rChild)
        ptr = ptr->rChild;
    return ptr;
}

BinNode* BinarySearchTree::successor(BinNode* ptr)
{
    while(ptr && ptr->lChild)
        ptr = ptr->lChild;
    return ptr;
}

BinNode* BinarySearchTree::deleteEle(BinNode* ptr, int key)
{
    if(!ptr) //not found
        return NULL;
    /*---physical deletion of a leaf node---*/
    if(ptr && ptr->data == key && !ptr->lChild && !ptr->rChild) //first condition is redundant
    {
        if(!root->lChild && !root->rChild)
            root = NULL; //if there's only root node
        delete ptr;
        return NULL;
    }
    /*Deletion algorithm*/
    //Search for the element to be deleted
    if(key < ptr->data)
        ptr->lChild = deleteEle(ptr->lChild, key);
    else if(key > ptr->data)
        ptr->rChild = deleteEle(ptr->rChild, key);
    else
    {//found
        BinNode* q = NULL;
        //Using height as deletion criteria
        if(height(ptr->lChild) > height(ptr->rChild))
        {
            /*finding element previous to the one 
            to be deleted (in inOrder), in left subtree*/
            q = predecessor(ptr->lChild);
            ptr->data = q->data; //deleted node effectively replaced
            ptr->lChild = deleteEle(ptr->lChild, q->data); //go and delete the node from which we copied
        }
        else
        {
            /*finding element next to the one 
            to be deleted (in inOrder), in right subtree*/
            q = successor(ptr->rChild);
            ptr->data = q->data;
            ptr->rChild = deleteEle(ptr->rChild, q->data);
        }
    }
    return ptr; //redundant, just like rInsert (had no explicit task)
}

void BinarySearchTree::deleteEle(int key)
{
    root = deleteEle(root, key);
}

int main()
{
    BinarySearchTree b;
    b.rInsert(10);
    b.insert(5);
    b.rInsert(20);
    b.insert(7);
    b.rInsert(15);
    b.insert(4);
    b.rInsert(30);
    b.deleteEle(7);
    b.deleteEle(0); //element is not in tree
    cout<<"4 found at address: "<<b.rSearch(4)<<"\n";
    cout<<"20 found at address: "<<b.search(20)<<"\n";
    b.inOrder();
    return 0;
}