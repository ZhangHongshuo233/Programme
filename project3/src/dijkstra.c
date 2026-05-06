/*
 * =============================================================================
 * Normal-3: Dijkstra Sequence
 * =============================================================================
 * Problem:
 *   Given a weighted undirected connected graph with Nv vertices and Ne edges,
 *   and K query sequences (each a permutation of all vertices), determine for
 *   each query whether it can be produced by running Dijkstra's single-source
 *   shortest-path algorithm from the first vertex in that sequence.
 *
 * Key Insight:
 *   A sequence  s[0], s[1], ..., s[Nv-1]  is a valid Dijkstra sequence iff,
 *   after computing shortest distances dist[] from source s[0], for every
 *   position i the condition  dist[s[i]] <= dist[s[j]]  holds for all j > i.
 *   (Dijkstra always extracts the unvisited vertex with the globally minimum
 *   tentative distance; ties may be broken arbitrarily, so any tied vertex is
 *   an equally valid choice at that step.)
 *
 * Constraints:
 *   Nv <= 10^3,  Ne <= 10^5,  K <= 100,  edge weight <= 100
 *
 * Algorithm Complexity:
 *   Dijkstra (adjacency matrix, O(V^2)):  O(Nv^2) per query
 *   Sequence validation:                  O(Nv^2) per query
 *   Total:                                O(K * Nv^2)
 *                                       = O(100 * 10^6) = ~10^8  (acceptable)
 *
 * Space Complexity:
 *   Adjacency matrix adj[MAXV][MAXV]:     O(Nv^2)  ≈ 4 MB
 * =============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/* ---------- Compile-time constants ---------- */
#define MAXV 1005          /* Maximum number of vertices (1-indexed)        */
#define INF (INT_MAX >> 1) /* Sentinel for "infinite" distance               */

/* ---------- Global variables ----------
 * Using global scope to avoid stack overflow for large arrays.
 * (Local arrays of MAXV*MAXV size would exhaust the default stack.)       */
int adj[MAXV][MAXV];  /* Adjacency matrix: adj[u][v] = weight of edge u-v,
                         0 means no direct edge between u and v             */
int dist[MAXV];       /* Shortest distance from the current source vertex   */
int visited[MAXV];    /* visited[v] = 1 once v is finalized by Dijkstra     */
int Nv, Ne;           /* Number of vertices and edges                       */


/*
 * dijkstra(src)
 * -------------------------------------------------------------------------
 * Runs the classic O(V^2) Dijkstra algorithm on the adjacency matrix to
 * compute the single-source shortest paths from vertex 'src'.
 *
 * After the call, dist[v] holds the shortest distance from src to v for
 * every v in [1, Nv].  Unreachable vertices keep dist[v] = INF.
 *
 * Algorithm (greedy):
 *   1. Initialize dist[src]=0, all others = INF.
 *   2. Repeat Nv times:
 *      a. Among all unvisited vertices, pick u with minimum dist[u].
 *      b. Mark u as visited (finalized).
 *      c. For each unvisited neighbour v of u, relax:
 *         if dist[u] + adj[u][v] < dist[v], update dist[v].
 */
void dijkstra(int src)
{
    int u, v;

    /* -- Initialization -- */
    for (v = 1; v <= Nv; v++) {
        dist[v]    = INF;  /* All distances unknown initially    */
        visited[v] = 0;    /* No vertex finalized yet            */
    }
    dist[src] = 0;         /* Distance from source to itself = 0 */

    /* -- Main loop: finalize one vertex per iteration -- */
    for (int iter = 0; iter < Nv; iter++) {

        /* Step a: Find unvisited vertex u with the smallest dist[u] */
        u = -1;
        for (v = 1; v <= Nv; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u]))
                u = v;
        }

        /* If no reachable unvisited vertex remains, stop early */
        if (u == -1 || dist[u] == INF) break;

        visited[u] = 1;  /* Step b: Finalize u */

        /* Step c: Relax all edges from u */
        for (v = 1; v <= Nv; v++) {
            if (adj[u][v] != 0 && !visited[v]) {
                int new_dist = dist[u] + adj[u][v];
                if (new_dist < dist[v])
                    dist[v] = new_dist;  /* Found a shorter path to v */
            }
        }
    }
}


/*
 * is_dijkstra_sequence(seq)
 * -------------------------------------------------------------------------
 * Returns 1 if seq[0..Nv-1] is a valid Dijkstra sequence, 0 otherwise.
 *
 * Validation logic:
 *   After computing all shortest distances from seq[0], the sequence is
 *   valid iff at every step i the chosen vertex seq[i] has a distance no
 *   greater than the distance of any later vertex seq[j] (j > i).
 *   This mirrors the greedy choice property of Dijkstra's algorithm:
 *   "always pick the globally minimum-distance unvisited vertex."
 *
 * Note on ties:
 *   If dist[seq[i]] == dist[seq[j]] for j > i, either order is acceptable,
 *   so only a strict inequality (dist[seq[i]] > dist[seq[j]]) is a failure.
 */
int is_dijkstra_sequence(int *seq)
{
    int i, j;

    /* Step 1: Compute shortest distances from the source vertex seq[0] */
    dijkstra(seq[0]);

    /* Step 2: Check the greedy-minimum ordering constraint */
    for (i = 0; i < Nv; i++) {
        for (j = i + 1; j < Nv; j++) {
            /*
             * If a later vertex seq[j] has a strictly smaller distance than
             * seq[i], then seq[i] could NOT have been the greedy choice at
             * step i → the sequence is invalid.
             */
            if (dist[seq[i]] > dist[seq[j]])
                return 0;  /* Violation found */
        }
    }
    return 1;  /* All steps satisfy the greedy constraint */
}


/*
 * main()
 * -------------------------------------------------------------------------
 * Reads the graph and K query sequences; prints "Yes" or "No" for each.
 *
 * Input format:
 *   Line 1 : Nv Ne
 *   Lines 2..(Ne+1): u v w   (undirected edge with weight w)
 *   Line Ne+2 : K
 *   Lines Ne+3 .. end: each line contains Nv integers (a permutation)
 */
int main(void)
{
    int i, u, v, w, K;
    int seq[MAXV];  /* Buffer for one query sequence */

    /* -- Read graph dimensions -- */
    scanf("%d %d", &Nv, &Ne);

    /* -- Initialize adjacency matrix -- */
    memset(adj, 0, sizeof(adj));  /* 0 = no edge */

    /* -- Read edges -- */
    for (i = 0; i < Ne; i++) {
        scanf("%d %d %d", &u, &v, &w);
        /*
         * Handle parallel edges (multiple edges between same pair of
         * vertices) by keeping only the minimum weight, since Dijkstra
         * would always prefer the lighter edge.
         */
        if (adj[u][v] == 0 || adj[u][v] > w) adj[u][v] = w;
        if (adj[v][u] == 0 || adj[v][u] > w) adj[v][u] = w;
    }

    /* -- Answer each query -- */
    scanf("%d", &K);
    while (K--) {
        /* Read one permutation of Nv vertices */
        for (i = 0; i < Nv; i++)
            scanf("%d", &seq[i]);

        /* Validate and print result */
        printf("%s\n", is_dijkstra_sequence(seq) ? "Yes" : "No");
    }

    return 0;
}