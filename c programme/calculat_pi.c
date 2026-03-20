#include<stdio.h>
double f(int n){
    static double fact=1;
    if(n==0){
        return fact;
    }
    if(n>0){
        return fact=fact*n;
    }
}
double g(int m){
    static double fact2 =1;
    if(m==0){
        return fact2;
    }
    if(m>0){
        return fact2=fact2*(2*m+1);
    }
}
int main(){
    double eps=0.0;
    scanf("%le", &eps);
    double sum=0.0;
    int i=0;
    double term=f(i)/g(i);
    while(term>eps){
        sum+=term;
        i++;
        term=f(i)/g(i);
    }
    sum+=term;
    printf("PI = %.5f",2*sum);
    return 0;
}