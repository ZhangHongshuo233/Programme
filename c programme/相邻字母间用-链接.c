#include<stdio.h>
int main(){
	char ch;
	int first = 1,k;
	printf("Enter 8 charactors:");
	for(k=1;k<=8;k++){
		ch = getchar();
		if(first==1){
			putchar(ch);
			first = 0;
		}
		else{
			putchar('-');
			putchar(ch); 
		}
	}
	return 0;
}
