#include "doulink.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Getsize of list
int GetsizeDouLinkList(List* list1) {
    return (list1 != NULL) ? list1->clen : 0;
}

//Check if list is empty
int IsEmptyDouLinkList(List* list1) {
    return (list1 == NULL || list1->clen == 0) ? 1 : 0;
}

//Create and initialize a  new doubly linked list
List* CreateDouLinkList() { 
    List* list = (List*)malloc(sizeof(List));
    if(list==NULL){
        printf("Memory allocation failed!\n");
        return NULL;
    }
    list->head = NULL;  //初始时无节点，头指为NULL
    list->clen =0;      //初始长度为0
    return list;
}

//Insert node at head
int InsertHeadDouLinkList(List* list1, datatype* data) {
    if(list1 ==NULL || data == NULL){
        printf("invalid parameter!\n");
        return 1;
    }

    //create new node
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode == NULL){
        printf("memory allocation failed!\n");
        return 1;  
    }

    //copy data to new node
    memcpy(&(newnode->data),data,sizeof(datatype));
    newnode->prev = NULL;
    newnode->next = NULL;  

    //insert at head
    newnode->next = list1-> head;
    if(list1->head != NULL){   //若原链表非空，原头节点的prev指向新节点
        list1->head->prev = newnode;
    }
    list1->head = newnode;     //更新头节点指针
    list1->clen++;             //更新链表长度
    return 0;
}
  
//Insert node at tail
int InsertTailDouLinkList(List* list1, datatype* data) {
    if(list1 ==NULL || data == NULL){
        printf("invalid parameter!\n");
        return 1;
    }

    //if list is empty,directly insert at head
    if(IsEmptyDouLinkList(list1)){
        return InsertHeadDouLinkList(list1, data);
    }   

    //create new node
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode == NULL){
        printf("memory allocation failed!\n");
        return 1;  
    }

    //copy data to new node
    memcpy(&(newnode->data),data,sizeof(datatype));
    newnode->prev = NULL;
    newnode->next = NULL;  

    //find tail node
    Node* temp = list1->head;
    while(temp->next != NULL){
        temp = temp->next;
    }
   
    //insert at tail
    newnode->prev =temp;
    temp->next = newnode;
    list1->clen++;             //update list length

    return 0;
}

//Insert node at specified position(pos starts from 0)
int InsertPosDouLinkList(List* list1, int pos, datatype* data) {
    if(list1 == NULL || data ==NULL){
        printf("invalid parameter!\n");
        return 1;
    }

    int size = GetsizeDouLinkList(list1);
    //check position validity
    if(pos<0 || pos>=size){
        printf("position out of range!\n");
        return 1;
    }

    //insert at head
    if(pos == 0){
        return InsertHeadDouLinkList(list1,data);
    }
    //insert at tail
    else if(pos == size-1){
        return InsertTailDouLinkList(list1,data);
    }
    else{
        //create new node
        Node* newnode = (Node*)malloc(sizeof(Node));
        if(newnode == NULL){
            printf("memory allocation failed!\n");
            return 1;  
        }

        //copy data to new node
        memcpy(&(newnode->data),data,sizeof(datatype));
        newnode->prev = NULL;
        newnode->next = NULL;  

        //find position to insert
        Node* temp = list1->head;
        for(int i=0;i<pos-1;i++){   //move to the node before the position(pos-1)
            temp = temp->next;
        }


        //insert at position
        newnode->next = temp->next;
        newnode->prev = temp;
        temp->next->prev = newnode;
        temp->next =newnode;
        list1->clen++;             //update list length

        return 0;
    }
}

//Delete node at specified position(pos starts from 0)
int DeletePosDouLinkList(List* list1, int pos) {
    if(list1 ==NULL){
        printf("The list is invalid!\n");
        return 1;
    }

    int size = GetsizeDouLinkList(list1);
    //check position validity
    if(pos<0 || pos>=size){
        printf("position out of range!\n");
        return 1;
    }
    Node* temp = list1->head;

    //delete head node
    if(pos == 0){  
        list1->head =list1->head->next;
        if(list1->head !=NULL){
            list1->head->prev =NULL;
        }
    }
    else if(pos == size-1){
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->prev->next=NULL;
    }
    else{
        for(int i=0;i<pos;i++){
            temp=temp->next;
        }
        temp->prev->next=temp->next;    //前驱节点的next指向后继节点
        temp->next->prev=temp->prev;    //后继节点的prev指向前驱节点
    }
    free(temp);
    temp = NULL;
    list1->clen--;
    return 0;
}

//show list
int ShowDouLinkList(List* list1, SHOW_DIR dir) {
    if(list1 ==NULL || IsEmptyDouLinkList(list1)){
        printf("list is empty or invalid!\n");
        return 1;
    }

    Node* temp =list1->head;
    if(dir == SHOW_FORWARD){
        printf("Showing list from head to tail:\n");
        while(temp != NULL){
            printf("Value: %d, Name: %s\n", temp->data.val, temp->data.name);
            temp = temp->next;
        }
    }else if(dir == SHOW_BACKWARD){
        printf("Showing list from tail to head:\n");

        //move to tail
        while(temp->next !=NULL){
            temp = temp->next;
        }
        while(temp != NULL){
            printf("Value: %d, Name: %s\n", temp->data.val, temp->data.name);
            temp = temp->prev;
        }
    }else{
        printf("invalid direction!\n");
        return 1;
    }
    printf("\n");
    return 0;
}

//find double linked list node by name
datatype* FindDouLinkList(List* list1, const char* name) {
    if(list1 ==NULL || IsEmptyDouLinkList(list1) || name ==NULL){
        return NULL;
    }
    Node* temp = FindDouLinkList2(list1,name);
    return temp ? &(temp->data) : NULL;
}

//全局辅助函数：按姓名查找节点(返回节点地址)
static Node* FindDouLinkList2(List* list1, const char* name) {
    if(list1 ==NULL || IsEmptyDouLinkList(list1) || name ==NULL){
        return NULL;
    }

    Node* temp = list1->head;
    while(temp != NULL){
        if(strcmp(temp->data.name, name) ==0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;    //if not found,return NULL
}

//Modify data by name
int ModifyDouLinkList(List* list1, const char* name, datatype* newdata) {
    if(list1 ==NULL || IsEmptyDouLinkList(list1) || name ==NULL || newdata ==NULL){
        printf("invalid parameter!\n");
        return 1;
    }

    datatype* target = FindDouLinkList(list1,name);
    if(target == NULL){
        printf("data with name %s not found!\n",name);
        return 1;
    }

    //modify data
    memcpy(target,newdata,sizeof(datatype));
    return 0;

}

//Delete node by name
int DeleteDouLinkNodeByName(List* list1,const char* name) {
    if(list1 == NULL || IsEmptyDouLinkList(list1) || name == NULL){
        printf("invalid parameter!\n");
        return 1;
    }

    Node* target = FindDouLinkList2(list1,name);
    if(target == NULL){
        printf("node with name %s not found!\n",name);
        return 1;
    }

    //delete node at head
    if(target == list1->head){
        list1->head = list1->head->next;
        if(list1->head !=NULL){
            list1->head->prev =NULL;
        }
    }
    //delete node at tail
    else if(target->next == NULL){
        target->prev->next =NULL;
    }
    else{
        target->next->prev = target->prev;
        target->prev->next = target->next;
    }

    free(target);
    target = NULL;
    list1->clen--;
    return 0;
}

//Reverse the doubly linked list
int  ReverseDouLinkList(List* list1){
    if(list1 == NULL || GetsizeDouLinkList(list1) < 2){
        printf("list is invalid or too short to reverse!\n");
        return 1;
    }

//Version 1: 
//使用双指针遍历法：cur和next同步移动
// 逐个交换每个节点的prev和next指针
// 最后处理尾节点并更新头指针
    // Node* cur = list1->head;
    // Node* next = cur->next;
    // while(next != NULL){
    //     cur->next = cur->prev;
    //     cur->prev = next;
    //     cur =next;
    //     next = next->next;
    // }
    // cur->next = cur->prev;
    // cur->prev = NULL;
    // list1->head = cur;

//Version 2: 
// 使用单指针遍历法：通过temp暂存next节点
// 交换当前节点的prev和next指针后向前移动
// 当temp为NULL时更新头指针为当前节点（原尾节点）
    // Node* temp = NULL;
    // Node* cur = list1->head;
    // while (cur != NULL) {
    //     temp = cur->next;
    //     cur->next =cur->prev;
    //     cur->prev = temp;
    //     if(temp != NULL){
    //         cur = temp ; 
    //     }else{
    //         list1->head = cur; //update head pointer
    //         break;
    //     }
    // }

//Version 3:
    Node* cur = list1->head;
    Node* prev = NULL;
    Node* next = NULL;
    while(cur != NULL){
        next = cur->next;
        cur->next = prev;
        cur->prev = next;
        prev = cur;
        cur = next;
    }
    list1->head = prev; //update head pointer


    return 0;
}

int DestroyDouLinkList(List** list1){
    if(list1 ==NULL || *list1 == NULL){
        printf("invalid parameter!\n");
        return 1;
    }
    Node* temp = (*list1)->head;
    Node* next = NULL;
    while(temp != NULL){
        next = temp->next;
        free(temp);
        temp =next;
    }
    free(*list1);
    *list1 = NULL;
    return 0;   
}