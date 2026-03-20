#include<stdio.h>
#include"doulink.h"

int main(){

    //1.创建链表
    List* d1 = CreateDouLinkList();
    if(d1 == NULL){
        return 1;
    }

    //2.定义测试数据
    datatype data1 = {10, "Alice"};
    datatype data2 = {20, "Bob"};
    datatype data3 = {30, "Charlie"};
    datatype data4 = {40, "Diana"};
    datatype newdata = {25, "Bob"};

    //3.尾部插入
    InsertTailDouLinkList(d1,&data1);
    InsertTailDouLinkList(d1,&data2);
    InsertTailDouLinkList(d1,&data3);   
    ShowDouLinkList(d1, SHOW_FORWARD);

    //4.头部插入
    InsertHeadDouLinkList(d1,&data4);
    ShowDouLinkList(d1, SHOW_FORWARD);

    //5.指定位置插入
    datatype data5 = {15, "Eve"};
    InsertPosDouLinkList(d1,2,&data5);
    ShowDouLinkList(d1, SHOW_FORWARD);

    //6.查找节点
    datatype* found = FindDouLinkList(d1, "Bob");
    printf("Found node: Value=%d, Name=%s\n", found->val, found->name);

    //7.修改节点
    ModifyDouLinkList(d1,"Bob",&newdata);
    ShowDouLinkList(d1, SHOW_FORWARD);

    //8.反转链表
    ReverseDouLinkList(d1);
    ShowDouLinkList(d1, SHOW_FORWARD);

    //9.从尾到头遍历
    ShowDouLinkList(d1, SHOW_BACKWARD);

    //10.按姓名删除节点
    DeleteDouLinkNodeByName(d1,"Charlie");
    ShowDouLinkList(d1, SHOW_FORWARD);

    //11.销毁链表
    DestroyDouLinkList(&d1);
    ShowDouLinkList(d1, SHOW_FORWARD);  
    
    return 0;
}   