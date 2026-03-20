#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {    
int Coefficient;    
int Exponent;    
PtrToNode Next;
};
typedef PtrToNode Polynomial;
Polynomial Add( Polynomial a, Polynomial b ){

    Polynomial res = (Polynomial)malloc(sizeof(struct Node));
    res->Next =NULL;

    if(a->Next == NULL && b->Next != NULL){
        res = b;
        return res;
    }
    if(a->Next != NULL && b->Next == NULL){
        res = a;
        return res;
    }
    if(a->Next == NULL && b->Next == NULL){
        return res;
    }else{
        Polynomial pa = a->Next;
        Polynomial pb = b->Next;

        Polynomial head,tail;
        head =(Polynomial)malloc(sizeof(struct Node));
        tail = head;
        tail->Next = NULL;
        
        while(pa != NULL && pb != NULL){
            Polynomial temp = (Polynomial)malloc(sizeof(struct Node));
            if(pa->Exponent > pb->Exponent){
                temp->Coefficient = pa->Coefficient;
                temp->Exponent = pa->Exponent;
                tail->Next = temp;
                tail = tail->Next;
                pa = pa->Next;
            }else if(pa->Exponent < pb->Exponent){
                temp->Coefficient = pb->Coefficient;
                temp->Exponent = pb->Exponent;
                tail->Next = temp;
                tail = tail->Next;
                pb = pb->Next;
            }else{
                int sum = pa->Coefficient + pb->Coefficient;
                if(sum != 0){
                    temp->Coefficient = sum;
                    temp->Exponent = pa->Exponent;
                    tail->Next = temp;
                    tail = tail->Next;
                }
                pa = pa->Next;
                pb = pb->Next;
            }
        }
        while(pa != NULL){
            Polynomial temp =(Polynomial)malloc(sizeof(struct Node));
            temp->Coefficient = pa->Coefficient;
            temp->Exponent = pa->Exponent;
            tail->Next = temp;
            tail = tail->Next;
            pa = pa->Next;
        }
        while(pb != NULL){
            Polynomial temp =(Polynomial)malloc(sizeof(struct Node));
            temp->Coefficient = pb->Coefficient;
            temp->Exponent = pb->Exponent;
            tail->Next = temp;
            tail = tail->Next;
            pb = pb->Next;
        }

        res = head;
        return res;
    }
}