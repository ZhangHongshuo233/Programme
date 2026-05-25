#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */

typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */

typedef struct VNode *PtrToVNode;

struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};

typedef struct GNode *Graph;

struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};
 
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){

}
