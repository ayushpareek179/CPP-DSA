/*
Implementing a binary tree with following operations: 
1. Initialization and deletion using a queue
2. Traversal with and without recursion, using stacks for the latter
3. COunting number of nodes, leaf nodes, non-leaf nodes, degree-1 and degree-2 nodes
*/

#include "Queue.h"
#include "Stacks.h"

template <typename T>
class BinNode
{
    public:
    T data;
    BinNode* left;
    BinNode* right;
};

template <typename T>
class BinTree
{
    private:
    BinNode<T>* root;
    void preOrder(BinNode<T>*);
    void postOrder(BinNode<T>*);
    void inOrder(BinNode<T>*);
    int countNodes(BinNode<T>*);
    int treeHeight(BinNode<T>*);
    int countLeaf(BinNode<T>*);
    int countDeg2(BinNode<T>*);
    int countNLeaf(BinNode<T>*);
    int countDeg1(BinNode<T>*);
    public:
    BinTree()
    {
        root = NULL;
    }
    void create();
    void preOrder();
    void inOrder();
    void postOrder();
    void iterPreOrder();
    void iterInOrder();
    void iterPostOrder();
    void levelOrder();
    int countNodes();
    int treeHeight(); //displays number of levels
    int countLeaf();
    int countNLeaf();
    int countDeg2();
    int countDeg1();
    ~BinTree();
};

template <typename T>
void BinTree<T>::preOrder()
{
    cout<<"Tree in preorder traversal: ";
    preOrder(root);
    cout<<"\n";
}

template <typename T>
void BinTree<T>::inOrder()
{
    cout<<"Tree in inorder traversal: ";
    inOrder(root);
    cout<<"\n";
}

template <typename T>
void BinTree<T>::postOrder()
{
    cout<<"Tree in postorder traversal: ";
    postOrder(root);
    cout<<"\n";
}

template <typename T>
void BinTree<T>::create()
{
    Queue<BinNode<T>*> address; T var; char choice;
    BinNode<T>* newNode, *ptr;
    //Root
    cout<<"Enter the value for root node: "; cin>>var;
    root = new BinNode<T>; root->data = var;
    root->left = root->right = NULL;
    address.enqueue(root);
    //Non-root
    while(!address.isEmpty())
    {
        ptr = address.dequeue();
        cout<<"----------Node value = "<<ptr->data<<"----------\n";
        cout<<"Press Y/y to enter the left node: "; cin>>choice;
        if(choice == 'Y' || choice == 'y')
        {
            cout<<"Enter the value for left child: "; cin>>var; 
            newNode = new BinNode<T>; newNode->data = var;
            newNode->left = newNode->right = NULL;
            ptr->left = newNode;
            address.enqueue(newNode);
        }
        cout<<"Press Y/y to enter the right node: "; cin>>choice;
        if(choice == 'Y' || choice == 'y')
        {
            cout<<"Enter the value for right child: "; cin>>var; 
            newNode = new BinNode<T>; newNode->data = var; 
            newNode->left = newNode->right = NULL;
            ptr->right = newNode;
            address.enqueue(newNode);
        }
    }
}

template <typename T>
void BinTree<T>::preOrder(BinNode<T>* ptr)
{
    if(ptr)
    {
        cout<<ptr->data<<" ";
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

template <typename T>
void BinTree<T>::inOrder(BinNode<T>* ptr)
{
    if(ptr)
    {
        inOrder(ptr->left);
        cout<<ptr->data<<" ";
        inOrder(ptr->right);
    }
}

template <typename T>
void BinTree<T>::postOrder(BinNode<T>* ptr)
{
    if(ptr)
    {
        postOrder(ptr->left);
        postOrder(ptr->right);
        cout<<ptr->data<<" ";
    }
}

template <typename T>
void BinTree<T>::iterPreOrder()
{
    Stack<BinNode<T>*> stk;
    BinNode<T>* ptr = root;
    cout<<"Tree in iterative preorder traversal: ";
    while(ptr != NULL || !stk.isEmpty())
    {
        if(ptr)
        {
            cout<<ptr->data<<" ";
            stk.push(ptr);
            ptr = ptr->left;
        }
        else
        {
            ptr = stk.pop();
            ptr = ptr->right;
        }
    }
    cout<<"\n";
}

template <typename T>
void BinTree<T>::iterInOrder()
{
    Stack<BinNode<T>*> stk;
    BinNode<T>* ptr = root;
    cout<<"Tree in iterative inorder traversal: ";
    while(ptr != NULL || !stk.isEmpty())
    {
        if(ptr)
        {
            stk.push(ptr);
            ptr = ptr->left;
        }
        else
        {
            ptr = stk.pop();
            cout<<ptr->data<<" ";
            ptr = ptr->right;
        }
    }
    cout<<"\n";
}

template <typename T>
void BinTree<T>::iterPostOrder()
{
    Stack<BinNode<T>*> stk1, stk2; BinNode<T>* ptr;
    cout<<"Tree in iterative postorder traversal: ";
    stk1.push(root);
    while(!stk1.isEmpty())
    {
        ptr = stk1.pop();
        stk2.push(ptr);
        if(ptr->left)
            stk1.push(ptr->left);
        if(ptr->right)
            stk1.push(ptr->right);
    }
    while(!stk2.isEmpty())
    {
        ptr = stk2.pop();
        cout<<ptr->data<<" ";
    }
    cout<<"\n";
}

template <typename T>
void BinTree<T>::levelOrder()
{
    Queue<BinNode<T>*> q; BinNode<T>* ptr = root;
    q.enqueue(root);
    cout<<"Tree in level order traversal: "<<ptr->data<<" ";
    while(!q.isEmpty())
    {
        ptr = q.dequeue();
        if(ptr->left)
        {
            cout<<ptr->left->data<<" ";
            q.enqueue(ptr->left);
        }
        if(ptr->right)
        {
            cout<<ptr->right->data<<" ";
            q.enqueue(ptr->right);
        }
    }
    cout<<"\n";
}

template <typename T>
int BinTree<T>::countNodes(BinNode<T>* ptr)
{
    if(ptr)
    {
        int x = countNodes(ptr->left);
        int y = countNodes(ptr->right);
        return x+y+1;
    }
    return 0;
}

template <typename T>
int BinTree<T>::countNodes()
{
    return countNodes(root);
}

template <typename T>
int BinTree<T>::treeHeight(BinNode<T>* ptr)
{
    if(ptr)
    {
        int x = treeHeight(ptr->left);
        int y = treeHeight(ptr->right);
        return (x > y)? x+1:y+1;
    }
    return 0;
}

template <typename T>
int BinTree<T>::treeHeight()
{
    return treeHeight(root);
}

template <typename T>
int BinTree<T>::countLeaf(BinNode<T>* ptr)
{
    if(ptr)
    {
        int x = countLeaf(ptr->left);
        int y = countLeaf(ptr->right);
        return (!ptr->left && !ptr->right)?x+y+1:x+y;
    }
    return 0;
}

template <typename T>
int BinTree<T>::countLeaf()
{
    return countLeaf(root);
}

template <typename T>
int BinTree<T>::countDeg2()
{
    return countDeg2(root);
}

template <typename T>
int BinTree<T>::countDeg2(BinNode<T>* ptr)
{
    if(ptr)
    {
        int x = countDeg2(ptr->left);
        int y = countDeg2(ptr->right);
        return (ptr->left && ptr->right)?x+y+1:x+y;
    }
    return 0;
}

template <typename T>
int BinTree<T>::countNLeaf()
{
    return countNLeaf(root);
}

template <typename T>
int BinTree<T>::countNLeaf(BinNode<T>* ptr)
{
    if(ptr)
    {
        int x = countNLeaf(ptr->left);
        int y = countNLeaf(ptr->right);
        return (ptr->left || ptr->right)?x+y+1:x+y; //even if one is true, ide est node both deg1 and deg2 considered
    }
    return 0;
}

template <typename T>
int BinTree<T>::countDeg1()
{
    return countDeg1(root);
}

template <typename T>
int BinTree<T>::countDeg1(BinNode<T>* ptr)
{
    if(ptr)
    {
        int x = countDeg1(ptr->left);
        int y = countDeg1(ptr->right);
        return (ptr->left != NULL ^ ptr->right != NULL)?x+y+1:x+y; //translates to ((ptr->left && !ptr->right)||(!ptr->left && ptr->right))
    }
    return 0;
}

template <typename T>
BinTree<T>::~BinTree()
{
    Queue<BinNode<T>*> q; q.enqueue(root);
    BinNode<T>* ptr = root;
    while(!q.isEmpty())
    {
        ptr = q.dequeue();
        if(ptr->left)
            q.enqueue(ptr->left);
        if(ptr->right)
            q.enqueue(ptr->right);
        //cout<<"Deleted node with value "<<ptr->data<<"\n";
        delete ptr;
    }
    root = NULL; //not necessary but let it be
    cout<<"Binary tree destructed\n";
}

int main()
{
    BinTree<int> b;
    b.create();
    b.levelOrder();
    cout<<"Tree Height: "<<b.treeHeight()<<"\n";
    cout<<"Number of nodes: "<<b.countNodes()<<"\n";
    cout<<"Number of leaf nodes: "<<b.countLeaf()<<"\n";
    cout<<"Number of non-leaf nodes: "<<b.countNLeaf()<<"\n";
    cout<<"Number of degree two nodes: "<<b.countDeg2()<<"\n";
    cout<<"Number of degree one nodes: "<<b.countDeg1()<<"\n";
    cout<<"Program terminated\n";
    return 0;
}