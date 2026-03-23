#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkque.h"

int main(){
    LinkQueue* queue = CreateLinkQueue(); 
    datatype d1,d2,d3;
    d1.val = 1;
    strcpy(d1.name, "Alice");
    d2.val = 2;
    strcpy(d2.name, "Bob");
    d3.val = 3;
    strcpy(d3.name, "Charlie");

    Enter(queue, &d1);
    Enter(queue, &d2);
    Enter(queue, &d3);

    printf("Queue size: %d\n", GetSize(queue));

    datatype* head = GetHead(queue);
    if(head != NULL){
        printf("Head of queue: %d, %s\n", head->val, head->name);
    }

    Quit(queue);
    
    head = GetHead(queue);
    if(head != NULL){
        printf("Head of queue: %d, %s\n", head->val, head->name);
    }
    
    DestroyLinkQueue(queue);

    return 0;    
}  