#include<stdio.h>
// void month_day(int year,int yearday,int *pday,int *pmonth);{
//     int daytab[2][13]={
//         {0,31,28,31,30,31,30,31,31,30,31,30,31},
//         {0,31,29,31,30,31,30,31,31,30,31,30,31}
//     };
//     int leap;
//     if((year%4==0&&year%100!=0)||year%400==0){
//         leap=1; 
//     }else{
//         leap=0;
//     }
//     int month;
//     for(month=1;yearday>daytab[leap][month];month++){
//         yearday-=daytab[leap][month];
//     }
//     *pmonth=month;
//     *pday=yearday;
// }
// int main(){
//     int year,yearday,day,month;
//     printf("请输入年份和该年的第几天：");
//     scanf("%d %d",&year,&yearday);
//     month_day(year,yearday,&day,&month);
//     printf("对应的月份和日期是：%d月%d日\n",month,day);
//     return 0;
// }


int main(){
    int year,yearday,day,month;
    void month_day(int year, int yearday,int*pday,int*pmonth);
    printf("请输入年份和该年的第几天：");
    scanf("%d %d",&year,&yearday);
    month_day(year,yearday,&day,&month);
    printf("%d-%d-%d\n",year,month,day);
    return 0;
}
void month_day(int year,int yearday,int *pday,int *pmonth){
    int k;
    int tab[2][13]={
        {0,31,28,30,31,30,31,30,31,31,30,31,30,31},
        {0,31,29,30,31,30,31,30,31,31,30,31,30,31}
    };
    //判断闰年
    int leap=(year%4==0&&year%100!=0)||(year%400==0);
    for(k=0;yearday>tab[leap][k];k++){
        yearday-=tab[leap][k];  
    }
    *pmonth=k;
    *pday=yearday;
}