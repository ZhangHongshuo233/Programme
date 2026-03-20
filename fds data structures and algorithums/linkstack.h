#ifndef LINKSTACK_H
#define LINKSTACK_H

typedef struct data{
    int val;
    char name[20];
}datatype;

typedef struct node{
    datatype data;
    struct node* next;
}node;

typedef struct{
    node* top;
    int count;
}LinkStack;

LinkStack* CreateLinkStack();
int push(LinkStack* stack, datatype* data);
int pop(LinkStack* stack, datatype* data);
datatype* getTop(LinkStack* stack);
int IsEmpty(LinkStack* stack);
int GetSize(LinkStack* stack);
int clearStack(LinkStack* stack);

#endif // LINKSTACK_H