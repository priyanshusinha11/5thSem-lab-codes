#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node
{
    int vertex;
    struct Node *next;
};

// Structure to represent the adjacency list of a graph
struct Graph
{
    int numVertices;
    struct Node **adjLists;
};

// Create a new node
struct Node *createNode(int v)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with 'n' vertices
struct Graph *createGraph(int n)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = n;
    graph->adjLists = (struct Node **)malloc(n * sizeof(struct Node *));
    for (int i = 0; i < n; i++)
    {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Add an edge to the graph
void addEdge(struct Graph *graph, int src, int dest)
{
    // Add an edge from src to dest
    struct Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src - 1];
    graph->adjLists[src - 1] = newNode;

    // Add an edge from dest to src (since it's an undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest - 1];
    graph->adjLists[dest - 1] = newNode;
}

// Perform BFS traversal and calculate distances
void BFS(struct Graph *graph, int start, int *distances)
{
    int *visited = (int *)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++)
    {
        visited[i] = 0;
        distances[i] = -1;
    }

    // Create a queue for BFS
    int *queue = (int *)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    visited[start - 1] = 1;
    queue[rear++] = start;
    distances[start - 1] = 0;

    while (front < rear)
    {
        int current = queue[front++];
        struct Node *temp = graph->adjLists[current - 1];
        while (temp)
        {
            int neighbor = temp->vertex;
            if (!visited[neighbor - 1])
            {
                visited[neighbor - 1] = 1;
                queue[rear++] = neighbor;
                distances[neighbor - 1] = distances[current - 1] + 2;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue);
}

int main()
{
    int n, m;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &m);

    struct Graph *graph = createGraph(n);

    printf("Enter the edges:\n");
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int start;
    printf("Enter the starting node: ");
    scanf("%d", &start);

    int *distances = (int *)malloc(n * sizeof(int));

    BFS(graph, start, distances);

    printf("BFS Traversal: ");
    for (int i = 0; i < n; i++)
    {
        if (distances[i] != -1)
        {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    printf("Distance: ");
    for (int i = 0; i < n; i++)
    {
        printf("[%d] ", distances[i]);
    }
    printf("\n");

    free(distances);
    return 0;
}
