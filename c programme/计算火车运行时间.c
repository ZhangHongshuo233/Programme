#include<stdio.h>
int main(){
	int departure,arrival;
	scanf("%d %d",&departure,&arrival);
	
	int d_a=departure/100;
	int d_b=departure%100;
	
	int a_a=arrival/100;
	int a_b=arrival%100;
	
	int d_total=d_a*60+d_b;
	int a_total=a_a*60+a_b;
	
	int dif=a_total-d_total;
	
	int a=dif/60;
	int b=dif%60;
	
	printf("%02d:%02d",a,b);
	
	return 0;
} 
