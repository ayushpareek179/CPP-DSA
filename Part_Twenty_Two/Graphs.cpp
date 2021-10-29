// Performing BFS and DFS on graphs represented using adjacent matrices
// Displaying edges of the minimum-cost spanning tree using Prim's algorithm
# include <iostream>
# include <queue>

using namespace std;
#define inf INT_MAX

void del2D(int** ar, int x)
{
    for(int i = 0; i < x; i++)
        delete[] ar[i];
    delete[] ar;
}
class Graph
{
    private:
    int** adj;
    int n;
    void fill(int*);
    int* init(int);
    void BreadthFirstSearch(int);
    void DFS(int*, int);
    public:
    Graph(int*, int);
    void BFS(int);
    void DFS(int);
    int** MSTPrims();
    ~Graph();
};
void Graph::fill(int* arr)
{
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < n; j++)
            adj[i][j] = *(arr+(i-1)*(n-1)+(j-1)) == 0 ? inf : *(arr+(i-1)*(n-1)+(j-1));
    }
}
int* Graph::init(int toFill)
{
    int* arr = new int[n];
    for(int i = 0; i < n; i++)
        arr[i] = toFill;
    return arr;
}
void Graph::BreadthFirstSearch(int start)
{
    queue<int> que; int* visit = init(0);
    cout << start << " ";
    visit[start] = 1;
    que.push(start);
    while(!que.empty())
    {
        start = que.front(); que.pop();
        for(int i = 1; i < n; i++)
        {
            if(adj[start][i] != inf && visit[i] == 0)
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
            if(adj[start][i] != inf)
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
    int* visit = init(0);
    cout << "Graph in depth-first search: ";
    DFS(visit, start); cout << "\n";
    delete[] visit;
}
int** Graph::MSTPrims()
{
    int* near = init(inf), **result = new int*[2];
    result[0] = new int[n-2]; result[1] = new int[n-2]; 
    // one-time procedure
    int min = inf, u, v;
    for(int i = 1; i < n; i++) // minimum in upper triangle
    {
        for(int j = i; j < n; j++)
        {
            if(adj[i][j] < min)
            {
                min = adj[i][j];
                u = i, v = j;
            }
        }
    }
    result[0][0] = u, result[1][0] = v; // push the edge
    near[u] = near[v] = 0; // zero out the indices
    for(int i = 1; i < n; i++) // set the least costliest
    {
        if(near[i] != 0)
        {
            if(adj[i][u] < adj[i][v])
                near[i] = u;
            else
                near[i] = v;
        }
    }
    // repeating procedure
    for(int res = 1; res < n-2; res++)
    {
        min = inf;
        for(int i = 1; i < n; i++)
        {
            if(near[i] != 0 && adj[i][near[i]] < min)
            {
                min = adj[i][near[i]];
                u = i; // min cost index
            }
        }
        result[0][res] = u, result[1][res] = near[u]; // push the edge
        near[u] = 0; // zero out the vertex's index
        for(int i = 1; i < n; i++) // rejig the least costliest
        {
            if(near[i] != 0 && adj[i][u] < adj[i][near[i]])
                near[i] = u;
        }
    }
    return result;
}
Graph::~Graph()
{
    del2D(adj, n);
    cout << "Graph destructed\n";
}

int main()
{
    int n = 7, k = 4;
    int s[7][7] = {{0, 25, 0, 0, 0, 5, 0},
                   {25, 0, 12, 0, 0, 0, 10},
                   {0, 12, 0, 8, 0, 0, 0},
                   {0, 0, 8, 0, 16, 0, 14},
                   {0, 0, 0, 16, 0, 20, 18},
                   {5, 0, 0, 0, 20, 0, 0},
                   {0, 10, 0, 14, 18, 0, 0}};
    // int s[n][n] = {{0, 6, 9, 0, 0, 0},
    //                {6, 0, 0, 11, 0, 0},
    //                {9, 0, 0, 24, 0, 0},
    //                {0, 11, 24, 0, 7, 5},
    //                {0, 0, 0, 7, 0, 0},
    //                {0, 0, 0, 5, 0, 0}};
    Graph g((int*)s, n);
    g.BFS(k);
    g.DFS(k);
    int** mst = g.MSTPrims();
    cout << "Minimum-cost spanning tree edges:\n";
    for(int i = 0; i < n-1; i++)
        cout << "(" << mst[0][i] << ", " << mst[1][i] << ")\t";
    cout << "\n";
    del2D(mst, 2);
    return 0;
}