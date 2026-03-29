#include "linkque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// 创建空队列
LinkQueue *CreateLinkQueue()
{
    LinkQueue *queue = (LinkQueue *)malloc(sizeof(LinkQueue));
    if (NULL == queue)
    {
        printf("CreateLinkQueue malloc error\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->clen = 0;
    return queue;
}
 
// 入队操作
int EnterLinkQueue(LinkQueue *queue, datatype newdata)
{
    LinkQueueNode *newnode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (NULL == newnode)
    {
        printf("EnterLinkQueue malloc error\n");
        return 1;
    }
    newnode->data = newdata;
    newnode->next = NULL;
 
    if (IsEmptyLinkQueue(queue))
    {
        // 空队列，头尾指针指向新结点
        queue->front = newnode;
        queue->rear = newnode;
    }
    else
    {
        // 新结点加入队尾
        queue->rear->next = newnode;
        queue->rear = newnode;
    }
    queue->clen++;
    return 0;
}
 
// 获取队列长度
int GetSizeLinkQueue(LinkQueue *queue)
{
    return queue->clen;
}
 
// 判断队列是否为空
int IsEmptyLinkQueue(LinkQueue *queue)
{
    return 0 == queue->clen;
}
 
// 销毁队列
int DestroyLinkQueue(LinkQueue *queue)
{
    int size = GetSizeLinkQueue(queue);
    int i = 0 ;
    for(i=0;i<size;i++)
    {
        QuitLinkQueue(queue);
    }
    free(queue);
    return 0;
}
 
// 获取队首元素
datatype *GetHeadLinkQueue(LinkQueue *queue)
{
    if(IsEmptyLinkQueue(queue))
    {
        return NULL;
    }
    return &queue->front->data;
}
 
// 出队操作
int QuitLinkQueue(LinkQueue *queue)
{
    if(IsEmptyLinkQueue(queue))
    {
        return 1;
    }
    LinkQueueNode* tmp = queue->front;
    queue->front = queue->front->next;
    // 队列为空时，尾指针置空
    if(NULL == queue->front)
    {
        queue->rear = NULL;
    }
    free(tmp);
    queue->clen--;
    return 0;
}