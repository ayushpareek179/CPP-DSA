// Performing BFS and DFS on graphs represented using adjacent matrices
# include <iostream>
# include <queue>

using namespace std;

class Graph
{
    private:
    int** adj;
    int n;
    void fill(int*);
    int* init();
    void BreadthFirstSearch(int);
    void DFS(int*, int);
    public:
    Graph(int*, int);
    void BFS(int);
    void DFS(int);
    ~Graph();
};
void Graph::fill(int* arr)
{
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < n; j++)
            adj[i][j] = *(arr+(i-1)*(n-1)+(j-1));
    }
}
int* Graph::init()
{
    int* arr = new int[n];
    for(int i = 0; i < n; i++)
        arr[i] = 0;
    return arr;
}
void Graph::BreadthFirstSearch(int start)
{
    queue<int> que; int* visit= init();
    cout << start << " ";
    visit[start] = 1;
    que.push(start);
    while(!que.empty())
    {
        start = que.front(); que.pop();
        for(int i = 1; i < n; i++)
        {
            if(adj[start][i] == 1 && visit[i] == 0)
            {
                cout << i << " ";
                visit[i] = 1;
                que.push(i);
            }
        }
    }
    delete[] visit;
}
void Graph::DFS(int* visit, int start)
{
    if(visit[start] == 0)
    {
        cout << start << " ";
        visit[start] = 1;
        for(int i = 1; i < n; i++)
            if(adj[start][i] == 1)
                DFS(visit, i);
    }
}
Graph::Graph(int* arr, int x)
{
    n = (x > 0) ? x + 1 : 6;
    adj = new int*[n];
    for(int i = 0; i < n; i++)
        adj[i] = new int[n];
    fill(arr);
}
void Graph::BFS(int start)
{
    cout << "Graph in breadth-first search: ";
    BreadthFirstSearch(start); cout << "\n";
}
void Graph::DFS(int start)
{
    int* visit = init();
    cout << "Graph in depth-first search: ";
    DFS(visit, start); cout << "\n";
    delete[] visit;
}
Graph::~Graph()
{
    for(int i = 0; i < n; i++)
        delete[] adj[i];
    delete[] adj;
    cout << "Graph destructed\n";
}

int main()
{
    // int s[7][7] = {{0, 1, 1, 1, 0, 0, 0},
    //                {1, 0, 1, 0, 0, 0, 0},
    //                {1, 1, 0, 1, 1, 0, 0},
    //                {1, 0, 1, 0, 1, 0, 0},
    //                {0, 0, 1, 1, 0, 1, 1},
    //                {0, 0, 0, 0, 1, 0, 0},
    //                {0, 0, 0, 0, 1, 0, 0}};
    int n = 6, k = 4;
    int s[n][n] = {{0, 1, 1, 0, 0, 0},
                   {1, 0, 0, 1, 0, 0},
                   {1, 0, 0, 1, 0, 0},
                   {0, 1, 1, 0, 1, 1},
                   {0, 0, 0, 1, 0, 0},
                   {0, 0, 0, 1, 0, 0}};
    Graph g((int*)s, n);
    g.BFS(k);
    g.DFS(k);
    return 0;
}