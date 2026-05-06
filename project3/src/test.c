#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define INF (INT_MAX >> 1)  /* Sentinel for "infinite" distance */

/* ==========================================
 * 1. Adjacency List Data Structure Definitions
 * ========================================== */

/* Linked list node: represents an edge */
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

/* Adjacency list header for a vertex */
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

/* Main Graph structure */
typedef struct Graph {
    int V;          /* Number of vertices */
    AdjList* array; /* Dynamic array storing the list headers for all vertices */
} Graph;

/* ==========================================
 * 2. Adjacency List Basic Operations
 * ========================================== */

/* Internal helper function: create a new edge node */
static AdjListNode* CreateNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) return NULL;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

/* Create graph (Note: to accommodate 1-based indexing (1~Nv), the array size is V + 1) */
Graph* CreateGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;
    graph->V = V;
    /* Allocate V + 1 headers so indices 1~V map directly to vertex numbers */
    graph->array = (AdjList*)malloc((V + 1) * sizeof(AdjList));
    if (!graph->array) {
        free(graph);
        return NULL;
    }
    for (int i = 0; i <= V; i++) {
        graph->array[i].head = NULL;
    }   
    return graph;
}

/* Add an undirected weighted edge */
void AddEdge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src > graph->V || dest > graph->V) return;

    /* src -> dest */
    AdjListNode* newNode = CreateNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    /* dest -> src (undirected graph) */
    newNode = CreateNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

/* Destroy the graph and free memory */
void DestroyGraph(Graph* graph) {
    if (!graph) return;
    for (int v = 0; v <= graph->V; v++) {
        AdjListNode* curr = graph->array[v].head;
        while (curr) {
            AdjListNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

/* ==========================================
 * 3. Core Algorithm: Check Dijkstra Sequence
 * ========================================== */

/* Check if the given sequence is a valid Dijkstra sequence */
bool IsDijkstraSequence(Graph* graph, int seq[]) {
    int V = graph->V;
    int *dist = (int*)malloc((V + 1) * sizeof(int));
    bool *known = (bool*)malloc((V + 1) * sizeof(bool));
    
    /* Step 1: Initialize all distances and known status */
    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        known[i] = false;
    }

    /* The first vertex in the sequence is the source */
    dist[seq[1]] = 0;

    /* Step 2: Simulate and strictly verify according to the sequence order */
    for (int i = 1; i <= V; i++) {
        int currVertex = seq[i];

        /* Action 1: Find the minimum distance among all "unknown" vertices */
        int minDist = INF;
        for (int v = 1; v <= V; v++) {
            if (!known[v] && dist[v] < minDist) {
                minDist = dist[v];
            }
        }

        /* Action 2: Verify the greedy choice property!
         * If the required vertex in the sequence has a distance > the actual minimum distance available, it is invalid */
        if (dist[currVertex] > minDist) {
            free(dist);
            free(known);
            return false;
        }

        /* Verification passed, mark as known */
        known[currVertex] = true;

        /* Action 3: Relaxation (traverse the adjacency list of the current vertex) */
        AdjListNode* currNode = graph->array[currVertex].head;
        while (currNode) {
            int w = currNode->dest;
            int weight = currNode->weight;
            
            /* If the neighbor is unknown, and the path through the current vertex is shorter, update it */
            if (!known[w] && dist[currVertex] + weight < dist[w]) {
                dist[w] = dist[currVertex] + weight;
            }
            currNode = currNode->next;
        }
    }

    free(dist);
    free(known);
    return true;
}

/* ==========================================
 * 4. Main Function: Handle Input and Output
 * ========================================== */
int main() {
    int Nv, Ne;
    if (scanf("%d %d", &Nv, &Ne) != 2) return 0;

    /* Build the graph */
    Graph* graph = CreateGraph(Nv);

    /* Read all edges */
    for (int i = 0; i < Ne; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        AddEdge(graph, u, v, weight);
    }

    /* Read the number of queries */
    int K;
    scanf("%d", &K);

    /* Allocate memory for the sequence array (1-based index) */
    int* seq = (int*)malloc((Nv + 1) * sizeof(int));

    /* Process each query */
    for (int i = 0; i < K; i++) {
        for (int j = 1; j <= Nv; j++) {
            scanf("%d", &seq[j]);
        }

        /* Verify and print the result */
        if (IsDijkstraSequence(graph, seq)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    /* Free resources */
    free(seq);
    DestroyGraph(graph);

    return 0;
}