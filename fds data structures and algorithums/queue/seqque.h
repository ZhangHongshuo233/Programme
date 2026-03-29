#ifndef SEQQUE_H
#define SEQQUE_H

typedef struct{
    int val;
    char name[20];
}datatype;

typedef struct {
    datatype* array;
    int head;
    int tail;
    int tlen;
}SeqQueue;

SeqQueue *CreateSeqQueue(int len);
int isEmptySeqQueue(SeqQueue* queue);
int isFullSeqQueue(SeqQueue *queue);
int EnterSeqQueue(SeqQueue *queue, datatype *data);
int QuitSeqQueue(SeqQueue *queue);
datatype *GetHeadSeqQueue(SeqQueue *queue);
int DestroySeqQueue(SeqQueue *queue);

#endif