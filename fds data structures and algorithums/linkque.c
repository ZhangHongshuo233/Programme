#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkque.h"

LinkQueue* CreateLinkQueue(){
    LinkQueue* queue = (LinkQueue*)malloc(sizeof(LinkQueue));
    if(queue == NULL){
        printf("Memory allocation failed!\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->clen = 0;
    return queue;
}

int isEmpty(LinkQueue* queue){
    return queue->clen == 0;
}

int Enter(LinkQueue* queue,datatype* data){
    if(queue == NULL || data == NULL){
        printf("Invalid input!\n");
        return 1;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    memcpy(&newNode->data, data, sizeof(datatype));
    newNode->next = NULL;

    if(isEmpty(queue)){
        queue->front = newNode;
        queue->rear = newNode;
    }else{
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->clen++;
    return 0;
}

int Quit(LinkQueue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty!\n");
        return 1;
    }
    Node* temp = queue->front;
    queue->front =temp->next;
    free(temp);
    queue->clen--;
    // If the queue becomes empty after quitting, set rear to NULL
    if(isEmpty(queue)){
        queue->rear = NULL;
    }
    return 0;
}

datatype* GetHead(LinkQueue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty!\n");
        return NULL;
    }
    return &queue->front->data;
}

int GetSize(LinkQueue* queue){
    if(queue == NULL){
        printf("Invalid input!\n");
        return -1;
    }
    return queue->clen;
}

int DestroyLinkQueue(LinkQueue* queue){
    if(queue == NULL){
        return 1;
    }
    while(!isEmpty(queue)){
        Quit(queue);
    }
    free(queue);
    return 0;
    //another way to destroy the queue
    /*
    Node* temp = queue->front;
    while(temp != NULL){
        queue->front = queue->front->next;
        free(temp);
        temp = queue->front;
    }
    free(queue);
    return 0;
    */
}