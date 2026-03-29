#ifndef LINKQUE_H
#define LINKQUE_H
#include "tree.h"

typedef TreeNode* datatype;

typedef struct LinkQueueNode{
    datatype data;
    struct LinkQueueNode* next;
} LinkQueueNode;

typedef struct LinkQueue{
    LinkQueueNode* front;
    LinkQueueNode* rear;
    int clen;
} LinkQueue;


LinkQueue * CreateLinkQueue();
int EnterLinkQueue(LinkQueue *queue, datatype newnode);
int QuitLinkQueue(LinkQueue *queue);
datatype* GetHeadLinkQueue(LinkQueue *queue);
int GetSizeLinkQueue(LinkQueue *queue);
int IsEmptyLinkQueue(LinkQueue *queue);
int DestroyLinkQueue(LinkQueue * queue);


#endif //LINKQUE_H
