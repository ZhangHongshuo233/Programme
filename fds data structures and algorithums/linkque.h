#ifndef LINKQUE_H
#define LINKQUE_H

typedef struct{
    int val;
    char name[20];
}datatype;

typedef struct Node{
    datatype data;
    struct Node* next;
}Node;

typedef struct {
    Node* front;
    Node* rear;
    int clen;
}LinkQueue;

LinkQueue* CreateLinkQueue();
int isEmpty(LinkQueue *queue);
int Enter(LinkQueue *queue, datatype *data);
int Quit(LinkQueue *queue);
datatype* GetHead(LinkQueue *queue);
int GetSize(LinkQueue *queue);
int DestroyLinkQueue(LinkQueue *queue);
#endif