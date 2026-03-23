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
int isEmptyLinkQueue(LinkQueue *queue);
int EnterLinkQueue(LinkQueue *queue, datatype *data);
int QuitLinkQueue(LinkQueue *queue);
datatype* GetHeadLinkQueue(LinkQueue *queue);
int DestroyLinkQueue(LinkQueue *queue);
#endif