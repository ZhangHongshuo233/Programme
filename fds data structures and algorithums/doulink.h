
#ifndef DOULINK_H
#define DOULINK_H
//自定义数据类型
typedef struct{
    int val;
    char name[20];
}datatype;

//双向链表节点结构
typedef struct DouLinkNode{
    datatype data;              //数据域
    struct DouLinkNode* prev;   //前驱指针
    struct DouLinkNode* next;   //后继指针
}Node;

//链表管理结构(存储链表头结点和长度)
typedef struct{
    Node* head;                 //头结点指针
    int clen;                   //链表实际节点个数 
}List;

//遍历方向枚举
typedef enum{
    SHOW_FORWARD =0,            //从头到尾
    SHOW_BACKWARD               //从尾到头
}SHOW_DIR;

//函数声明
// 1. 创建双向链表(初始化)
List* CreateDouLinkList();

// 2. 头部插入节点
int InsertHeadDouLinkList(List* list1, datatype* data);

// 3. 尾部插入节点
int InsertTailDouLinkList(List* list1, datatype* data);

// 4. 指定位置插入节点(pos从0开始)
int InsertPosDouLinkList(List* list1, int pos, datatype* data);

// 5. 删除指定位置节点(pos从0开始)
int DeletePosDouLinkList(List* list1, int pos);

//6.遍历链表
int ShowDouLinkList(List* list1, SHOW_DIR dir);

//7.按姓名查找数据(返回数据地址)
datatype* FindDouLinkList(List* list1, const char* name);

//8.按姓名修改数据
int ModifyDouLinkList(List* list1, const char* name, datatype* newdata);

//9.按姓名删除节点
int DeleteDouLinkNodeByName(List* list1, const char* name);

//10.反转链表
int ReverseDouLinkList(List* list1);    

//11.获取链表长度
int GetsizeDouLinkList(List* list1);

//12.判断链表是否为空
int IsEmptyDouLinkList(List* list1);

//13.销毁链表(释放内存)
int DestroyDouLinkList(List** list1);

//内部辅助函数：按姓名查找节点(返回节点指针)
static Node* FindDouLinkList2(List* list1, const char* name);
#endif // DOULINK_H