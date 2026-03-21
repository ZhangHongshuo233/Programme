// 7-1 Queue Using Two Stacks
// A queue (FIFO structure) can be implemented by two stacks (LIFO structure) in the following way:

// Start from two empty stacks s 
// 1
// ​
//   and s 
// 2
// ​
//  .
// When element e is enqueued, it is actually pushed onto s 
// 1
// ​
//  .
// When we are supposed to dequeue, s 
// 2
// ​
//   is checked first. If s 
// 2
// ​
//   is empty, everything in s 
// 1
// ​
//   will be transferred to s 
// 2
// ​
//   by popping from s 
// 1
// ​
//   and immediately pushing onto s 
// 2
// ​
//  . Then we just pop from s 
// 2
// ​
//   -- the top element of s 
// 2
// ​
//   must be the first one to enter s 
// 1
// ​
//   thus is the first element that was enqueued.
// Assume that each operation of push or pop takes 1 unit of time.  You job is to tell the time taken for each dequeue.

// Input Specification:
// Each input file contains one test case. For each case, the first line gives a positive integer N (≤10 
// 3
//  ), which are the number of operations. Then N lines follow, each gives an operation in the format

// Operation Element
// where Operation being I represents enqueue and O represents dequeue.  For each I, Element is a positive integer that is no more than 10 
// 6
//  .  No Element is given for O operations.
// It is guaranteed that there is at least one O operation.

// Output Specification:
// For each dequeue operation, print in a line the dequeued element and the unites of time taken to do this dequeue.  The numbers in a line must be separated by 1 space, and there must be no extra space at the beginning or the end of the line.
// In case that the queue is empty when dequeue is called, output in a line ERROR instead.

// Sample Input:
// 10
// I 20
// I 32
// O
// I 11
// O
// O
// O
// I 100
// I 66
// O
// Sample Output:
// 20 5
// 32 1
// 11 3
// ERROR
// 100 5

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node* next;
} Node;

typedef struct{
    Node* top;
    int clen;
}Stack;

int main(){
    Stack *s1,*s2;
    s1 = (Stack*)malloc(sizeof(Stack));
    s2 = (Stack*)malloc(sizeof(Stack));
    s1->top = NULL;
    s1->clen = 0;
    s2->top = NULL;
    s2->clen = 0;

    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        char op;
        scanf("%c",&op);
        if(op == "I"){
            int val;
            scanf("%d",&val);
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->val = val;
            newNode->next = s1->top;
            s1->top = newNode;
            s1->clen++;
        }else if(op == "O"){
            int time = 0;
            if(s2->clen == 0){
                if(s1->clen == 0){
                    printf("ERROR\n");
                }else{
                    while(s1->clen > 0){
                        Node* temp = s1->top;
                        s1->top = temp->next;
                        s1->clen--;
                        time++;
                        temp->next = s2->top;
                        s2->top = temp;
                        s2->clen++;
                        time++;
                    }
                    int val = s2->top->val;
                    s2->top =s2->top->next;
                    s2->clen--;
                    time++;
                    printf("%d %d\n",val,time);
                }
            }else if(s2->clen > 0){
                int val = s2->top->val;
                s2->top =s2->top->next;
                s2->clen--;
                time++;
                printf("%d %d\n",val,time);
            }
            time = 0;
        }
    }
    return 0;
}