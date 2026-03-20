#include "seqque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SeqQueue* CreateSeqQueue(int len){
    SeqQueue *sq = (SeqQueue* )malloc(sizeof(SeqQueue));
    if(sq == NULL){
        printf("CreateSeqQueue: malloc1 failed!\n");
        return NULL;
    }
    sq->array = (datatype* )malloc(sizeof(datatype) * len);
    if(sq->array ==NULL){
        printf("CreateSeqQueue: malloc2 failed!\n");
        free(sq);
        return NULL;
    }
    sq->head = 0;
    sq->tail = 0;
    sq->tlen = len; 
    return sq;
}

int isEmptySeqQueue(SeqQueue* queue){
    return queue->head == queue->tail;
}

int isFullSeqQueue(SeqQueue *queue){
    return (queue->tail + 1) % queue->tlen == queue->head;
}

int EnterSeqQueue(SeqQueue *queue,datatype *data){
    if(isFullSeqQueue(queue)){
        printf("EnterSeqQueue: queue is full!\n");
        return 1; 
    }
    memcpy(&queue->array[queue->tail],data,sizeof(datatype));
    queue->tail = (queue->tail + 1) % queue->tlen;
    return 0;
}

int QuitSeqQueue(SeqQueue *queue){
    if(isEmptySeqQueue(queue)){
        printf("QuitSeqQueue: queue is empty!\n");
        return 1; 
    }
    queue->head = (queue->head + 1) % queue->tlen;
    return 0;
}

datatype *GetHeadSeqQueue(SeqQueue *queue){
    if(isEmptySeqQueue(queue)){
        printf("GetHeadSeqQueue: queue is empty!\n");
        return NULL; 
    }
    return &queue->array[queue->head];
}

int DestroySeqQueue(SeqQueue *queue){
    if(isEmptySeqQueue(queue)){
        return 1; 
    }
    free(queue->array);
    free(queue);  
    return 0;
}