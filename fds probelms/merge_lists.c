#include<stdio.h>
struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *mergelists(struct ListNode *list1, struct ListNode *list2) {
    struct ListNode *head, *tail, *p;
    
    // 创建一个虚拟头节点，简化操作
    head = (struct ListNode*)malloc(sizeof(struct ListNode));
    tail = head;

    while(list1!=NULL&& list2!=NULL){
        if(list1->data<=list2->data){
            tail->next=list1;
            list1=list1->next;
        }else{
            tail->next=list2;
            list2=list2->next;
        }
        tail=tail->next;
    }

    // 将剩余的节点连接到结果链表
    if(list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }
    
    // 保存真正的头节点，释放虚拟头节点
    p = head->next;
    free(head);
    
    return p;
}