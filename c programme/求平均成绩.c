#include<stdio.h>
int main(void){
	int count,i,n;			/*count记录成绩不合格学生人数*/ 
	double score,average,total;			 	/*score存放输入的成绩，total保存成绩之和*/ 		
	printf("Enter n:");				/*提示输入学生数*/ 
	scanf("%d",&n);
	count = 0;			
	total = 0;	
	for(i=1;i<=n;i++){
		printf("Enter score #%d:",i);		/*提示输入第i个成绩*/ 
		scanf("%lf",&score);			/*输入第i个成绩，注意score的类型是double，故应为"lf"*/ 
		total = total + score;			/*累加成绩*/ 
		if(score<60){				/*统计不合格学生人数*/ 
			count++;
		}
	}
	if(n!=0){
		average = total/n;			/*分母不能为0*/ 
		
		printf("Average = %.2f\n",average);
	}	
	else{
		printf("Average = %.2f\n",0.0);	/*当n为0时，平均分为0*/	
	}
	printf("Number of failure is %d\n",count);
	return 0;
} 
