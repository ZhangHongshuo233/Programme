#include "node.h"
#include <stdio.h>
#include <stdlib.h>

// typedef struct _node{
//     int value;
//     struct _node* next;
// } Node;

// Define a List structure to hold the head of the linked list
typedef struct _list{
    Node* head;
    Node* tail;
}List;

void add(List* List_ref,int number);
void print(List* List_ref);

int main(int argc, char const *argv[])
{
    List list;
    list.head = list.tail = NULL;
    int number;
    do{
        scanf("%d",&number);
        if(number!=-1){
            add(&list,number);
        }  
    }while(number!=-1);

    return 0;

}

void add(List* List_ref,int number){
    //add to linked-list
    Node* p=(Node*)malloc(sizeof(Node));
    p->value=number;
    p->next=NULL;
    if(List_ref->head=NULL){
        // 情况1：链表为空 → head 和 tail 都指向新节点
        List_ref->head=List_ref->tail=p;
    }else{
        // 情况2：链表非空 → 尾指针直接挂载新节点，然后更新 tail
        List_ref->tail->next=p;
        List_ref->tail=p;
    }
}
//事实上最初的版本是引入临时变量 temp 来保存 tail 指向的位置，然后通过 temp 来进行操作，最后再更新 tail 指针
// void add(List* List_ref,int number){
//     //add to linked-list
//     Node* p=(Node*)malloc(sizeof(Node));
//     p->value=number;
//     p->next=NULL;
//     Node* temp=List_ref->head;
//     if(temp!=NULL){
//         while(temp->next!=NULL){
//             temp=temp->next;
//         }
//         temp->next=p;
//     }else{
//         List_ref->head=p;
//     }
// } 

void print(List* List_ref){
    Node* p=List_ref->head;
    while(p!=NULL){
        printf("%d ", p->value);
        p = p->next;
    }

    // Alternative using for loop
    //for(p=List_ref->head;p;p=p->next){
    //    printf("%d ", p->value);}

    printf("\n");
}
 
void delete(List* List_ref,int number){
    Node* p;
    Node* q;
    for(q=NULL,p=List_ref->head;p;q=p,p=p->next){
        if(p->value==number){
            
            if(!q){    
                //删除的是头节点
                List_ref->head=p->next;
            }else{
                q->next=p->next;
            }
            free(p);
            break;
        }
    }
}

void freeList(List* List_ref){
    //边界检查1：避免空指针解引用
    if(!List_ref){
        return;
    }
    Node* p=List_ref->head,*q=NULL;
    for(;p;){
        q=p;
        p=p->next;
        free(q);
        q=NULL;
    }
    //边界检查2：将头指针置为空，避免悬空指针
    List_ref->head=NULL;
}