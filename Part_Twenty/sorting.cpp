// Sorting algorithms
# include <iostream>
using namespace std;

template <typename T>
class Node
{
    public:
    T data;
    Node* next;
    void createNew(T x)
    {
        data = x;
        next = NULL;
    }
};
template <typename T>
class LinkedList
{
    private:
    Node<T>* head;
    Node<T>* tail;
    public:
    LinkedList()
    {
        head = tail = NULL;
    }
    void InsertEnd(int x)
    {
        if(!tail)
        {
            head = new Node<T>;
            head->createNew(x);
            tail = head;
        }
        else
        {
            tail->next = new Node<T>;
            tail->next->createNew(x);
            tail = tail->next;
        }
    }
    T DelHead()
    {
        T toDel;
        if(!head)
            return toDel;
        Node<T>* temp = head;
        head = head->next;
        toDel = temp->data;
        delete temp;
        return toDel;
    }
    bool isEmpty()
    {
        return head == NULL;
    }
};

template <typename T>
class sorts
{
    private:
    void swap(T&, T&);
    int partition(T*, int, int);
    void quickSort(T*, int, int);
    void merge(T*, int, int, int); // merges two sorted lists in the same array
    void mergeSort(T*, int, int);
    int maxEle(T*, int);
    int minEle(T*, int);
    void setZero(T*, int); // memSet equivalent
    public:
    void bubbleSort(T*, int);
    void insertionSort(T*, int);
    void selectionSort(T*, int);
    void quickSort(T* arr, int n)
    {
        quickSort(arr, 0, n-1);
    }
    void mergeSort(T* arr, int n)
    {
        mergeSort(arr, 0, n-1);
    }
    void countSort(T*, int); // only for int and char
    void bucketSort(T*, int); // only for int and char
    void radixSort(T*, int); // only for positive numbers/characters
    void shellSort(T*, int);
    void display(T*, int);
};
template <typename T>
void sorts<T>::swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
template <typename T>
void sorts<T>::bubbleSort(T* arr, int n)
{
    int flag;
    for(int i = 0; i < n-1; i++) // number of passes
    {
        flag = 0;
        for(int j = 0; j < n-1-i; j++) // unsorted array keeps getting smaller
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                flag = 1;
            }
        }
        if(!flag) // no swaps in the pass
            break;
    }
}
template <typename T>
void sorts<T>::display(T* arr, int n)
{
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}
template <typename T>
void sorts<T>::insertionSort(T arr[], int n)
{
    for(int i = 1; i < n; i++) // the empty cell
    {
        int j = i-1; 
        T x = arr[i]; // since arr[i] changes, we should take out the value
        while(j > -1 && arr[j] > x) // not out of range and greater
        {
            arr[j+1] = arr[j]; // shift
            j--;
        }
        arr[j+1] = x; // virtually empty index, for insertion
    }
}
template <typename T>
void sorts<T>::selectionSort(T* arr, int n)
{
    for(int i = 0; i < n-1; i++) // n-1 passes
    {
        int k = i;
        for(int j = i; j < n; j++) // both j and k upon i
        {
            if(arr[k] > arr[j])
                k = j;
        }
        swap(arr[i], arr[k]); // 1 swap per pass
    }
}
template <typename T>
int sorts<T>::partition(T* arr, int l, int h)
{
    // pivot = arr[h]
    int i = l-1;
    for(int j = l; j <= h-1; j++)
    {
        if(arr[j] < arr[h])
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[h]);
    return i+1;
}
template <typename T>
void sorts<T>::quickSort(T* arr, int l, int h)
{
    if(l < h)
    {
        int ind = partition(arr, l, h);
        quickSort(arr, l, ind-1);
        quickSort(arr, ind+1, h);
    }
}
template <typename T>
void sorts<T>::mergeSort(T* arr, int l, int h)
{
    if(l < h)
    {
        int mid = (l+h)/2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid+1, h);
        merge(arr, l, mid, h);
    }
}
template <typename T>
void sorts<T>::merge(T* arr, int low, int mid, int high)
{
    int i = low, j = mid+1, k = 0;
    int* aux = new int[high-low+1];
    while(i <= mid && j <= high)
    {
        if(arr[i] < arr[j])
            aux[k++] = arr[i++];
        if(arr[j] < arr[i])
            aux[k++] = arr[j++];
    }
    for(; i <= mid; i++)
        aux[k++] = arr[i];
    for(; j <= high; j++)
        aux[k++] = arr[j];
    for(int i = 0; i < k; i++)
        arr[low+i] = aux[i];
    delete aux;
}
template <typename T>
int sorts<T>::maxEle(T* arr, int n)
{
    T max = arr[0];
    for(int i = 1; i < n; i++)
        if(arr[i] > max)
            max = arr[i];
    return max;
}
template <typename T>
int sorts<T>::minEle(T* arr, int n)
{
    T min = arr[0];
    for(int i = 1; i < n; i++)
        if(arr[i] < min)
            min = arr[i];
    return min;
}
template <typename T>
void sorts<T>::setZero(T* arr, int n)
{
    for(int i = 0; i < n; i++)
        arr[i] = 0;
}
template <typename T>
void sorts<T>::countSort(T* arr, int n)
{
    int min = minEle(arr, n); 
    int cSize = maxEle(arr, n) - min + 1; // accounting for signs and reducing memory consumption
    T* count = new T[cSize]; setZero(count, cSize);
    for(int i = 0; i < n; i++)
        count[arr[i]-min]++; 
    int i = 0, j = 0;
    while(i < cSize)
    {
        if(count[i])
        {
            arr[j++] = i+min;
            count[i]--;
        }
        else
            i++;
    }
    delete count;
}
template <typename T>
void sorts<T>::bucketSort(T* arr, int n)
{
    int min = minEle(arr, n), bSize = maxEle(arr, n) - min + 1;
    LinkedList<T>** bins = new LinkedList<T>*[bSize]; // just like countSort
    for(int i = 0; i < bSize; i++)
        bins[i] = NULL;
    for(int i = 0; i < n; i++)
    {
        if(!bins[arr[i] - min]) // in case no list existed before
            bins[arr[i] - min] = new LinkedList<T>;
        bins[arr[i] - min]->InsertEnd(arr[i]);
    }
    int i = 0, j = 0;
    while(j < bSize)
    {
        while(bins[j])
        {
            arr[i++] = bins[j]->DelHead(); // copying
            if(bins[j]->isEmpty()) // ensuring that the cell starts pointing to NULL again
            {
                delete bins[j];
                bins[j] = NULL;
            }
        }
        j++;
    }
}
template <typename T>
void sorts<T>::radixSort(T* arr, int n)
{
    int max = maxEle(arr, n), nDig, i, j, divisor = 1; // for number of repetitions
    LinkedList<T>** bins = new LinkedList<T>*[10]; // decimal number system - 10 digits
    for(int i = 0; i < 10; i++)
        bins[i] = NULL;
    while(max > 0) // repeats for as many times as the number of digits in the greatest number
    {
        for(int i = 0; i < n; i++)
        {
            nDig = (arr[i]/divisor)%10; // insertion as per the nth digit from right
            if(!bins[nDig])
                bins[nDig] = new LinkedList<T>;
            bins[nDig]->InsertEnd(arr[i]);
        }
        i = j = 0;
        while(j < 10)
        {
            while(bins[j])
            {
                arr[i++] = bins[j]->DelHead(); // copying
                if(bins[j]->isEmpty()) // ensuring that the cell starts pointing to NULL again
                {
                    delete bins[j];
                    bins[j] = NULL;
                }
            }
            j++;
        }
        max /= 10;
        divisor *= 10; // enabling proper indexing
    }
}
template <typename T>
void sorts<T>::shellSort(T* arr, int n)
{ // mirrors insertion sort
    int j;
    for(int gap = n/2; gap >= 1; gap /= 2) // gaps help decrease the time complexity
    {
        for(int i = gap; i < n; i++)
        {
            j = i - gap;
            T temp = arr[i];
            while(j > -1 && arr[j] > temp)
            {
                arr[j+gap] = arr[j];
                j -= gap;
            }
            arr[j+gap] = temp;
        }
    }
}

int main()
{
    sorts<int> S; 
    int a[] = {15, 36, 187, 2, 40, 326, 2, 4007, 36, 40, 47};
    int size = sizeof(a)/sizeof(a[0]);
    S.shellSort(a, size);
    S.display(a, size);
    return 0;
}