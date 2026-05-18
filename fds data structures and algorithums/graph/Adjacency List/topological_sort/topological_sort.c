#include <stdio.h>
#include <stdlib.h>
#include "../adj_list.h"

int TopologicalSort(Graph* graph, int* result) {
    int V = graph->V;
    int* in_degree = (int*)calloc(V, sizeof(int));
    if (!in_degree) return 0;

    for(int i = 0; i < V; i++) {
        AdjListNode* curr = graph->array[i].head;
        while(curr) {
            in_degree[curr->dest]++;
            curr = curr->next;
        }
    }

    int* queue = (int*)malloc(V * sizeof(int));
    if (!queue) {
        free(in_degree);
        return 0;
    }
    int front = 0, rear = 0;
    
    for(int i = 0; i < V; i++) {
        if(in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int count = 0;
    while(front < rear) {
        int u = queue[front++];
        result[count++] = u;

        AdjListNode* curr = graph->array[u].head;
        while(curr) {
            int v = curr->dest;
            in_degree[v]--;
            if(in_degree[v] == 0) {
                queue[rear++] = v;
            }
            curr = curr->next;
        }
    }

    free(in_degree);
    free(queue);

    if(count == V) {
        return 1;
    } else {
        return 0;
    }
}

int IsTopSort(Graph* graph, int* seq) {
    int V = graph->V;
    int* position = (int*)malloc(V * sizeof(int));
    if (!position) return 0;

    for(int i = 0; i < V; i++) {
        position[seq[i]] = i;
    }

    for(int i = 0; i < V; i++) {
        AdjListNode* curr = graph->array[i].head;
        while(curr) {
            int u = i;
            int v = curr->dest;
            if(position[u] > position[v]) {
                free(position);
                return 0;  
            }
            curr = curr->next;
        }
    }
    free(position);
    return 1;
}
