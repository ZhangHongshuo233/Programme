#include<stdio.h>
#include<stdlib.h>
// Define a structure to hold student information
struct student{
    int id;
    char name[10];
    int computer_score,math_score,english_score;
    double average_score;
};

// Function declarations
void sort_average(struct student* students,int n);
int update_score(struct student*p,int n,int search_id,int certain_course,int new_score);

// Main function
int main(){
    int n,i;
    // 1.Read the number of students
    scanf("%d",&n);

    //2.check whether n is within valid range
    if(n<=0){
        printf("Invalid number of students.\n");
        return 1; // Exit if n is out of range
    }

    //3. Dynamically allocate memory for n students
    struct student* students =(struct  student*)malloc(n * sizeof(struct student));
    if(students == NULL){
        printf("Memory allocation failed.\n");
        return 1; // Exit if memory allocation fails
    }

    //4. Read student data
    for(i=0;i<n;i++){
        scanf("%d %s %d %d %d",&students[i].id,students[i].name,
              &students[i].computer_score,&students[i].math_score,
              &students[i].english_score);
        // Calculate average score
        students[i].average_score=(students[i].computer_score+
                                   students[i].math_score+
                                   students[i].english_score)/3.0;
    }

    // //1-1.按照学生的个人平均成绩从高到低输出他们的信息
    // //5.sort students by average score in descending order
    // sort_average(students,n);
    // //6.output student's average scores
    // for (i = 0; i < n; i++ ){
    // printf("%d\t%s\t %.2lf\n", students[i].id, students[i].name, 
    //         students[i].average_score);
    // }

    // // 1-2.输入一个学生的学号、课程以及成绩，在自定义函数中修改该学生指定课程的成绩。
    // int search_id,certain_course,new_score;
    // scanf("%d %d %d",&search_id,&certain_course,&new_score);
    // // 默认certain_course为1对应computer,2、3同理
    // int pos=update_score(students,n,search_id,certain_course,new_score);
    // if(pos==-1){
    //     printf("Student ID %d not found.\n",search_id);
    // }else{
    //     printf("Updated student info: %d\t%s\t%d\t%d\t%d\t%.2lf\n",
    //            students[pos].id,students[pos].name,
    //            students[pos].computer_score,
    //            students[pos].math_score,
    //            students[pos].english_score,
    //            students[pos].average_score);
    // }
    
    
    //7.free allocated memory
    free(students);
    return 0;
}

//函数sort_average按照学生的个人平均成绩从高到低输出他们的信息
void sort_average(struct student* students,int n){
    int i,j,index;
    struct student temp;
    //apply Selection_sort
    for(i=0;i<n-1;i++){
        index=i;
        for(j=i+1;j<n;j++){
            if(students[j].average_score>students[index].average_score){
                index=j;
            }
        }
        //swap students[i] and students[index]
        temp=students[i];
        students[i]=students[index];
        students[index]=temp;

    }
}

//函数update_score修改指定学生的指定课程成绩
int update_score(struct student*p,int n,int search_id,int certain_course,int new_score){
    int pos,i;
    //find the student by id
    for(i=0;i<n;i++,p++){
        if(p->id==search_id){
            pos=i;
            break;
        }
    }
    if(i==n) pos=-1; //not found

    //if found, update the score
    else{
        int course_invalid=0;
        //update the certain course score
        switch(certain_course){
            case 1:
                p->computer_score=new_score;
                break;
            case 2:
                p->math_score=new_score;
                break;
            case 3:
                p->english_score=new_score;
                break;
            default:
                printf("Invalid course number.\n");
                course_invalid=1;
        }
        //recalculate average score
        if(!course_invalid){
        p->average_score=(p->computer_score+
                              p->math_score+
                              p->english_score)/3.0;
        }
    }
    return pos;
}