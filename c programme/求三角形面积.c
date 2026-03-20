#include<stdio.h>
#include<math.h>
int main(){
	int a, b, c;
	scanf("%d %d %d",&a,&b,&c);
	if(a + b > c && a + c > b && b + c > a){
		double s =(a+b+c)/2.0;
		double area =sqrt(s*(s-a)*(s-b)*(s-c));
		int perimeter = a + b + c;
		printf("area =%.2f, perimeter =%d",area,perimeter);
	}
	else{
		printf("These sides do not correspond to a valid triangle");
	}
    
    return 0;
}
