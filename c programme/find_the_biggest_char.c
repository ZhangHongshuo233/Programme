#include <stdio.h>
//find the biggest char in a string and move it to the front
int main()
{
    char max, str[80], *p, *q;
        
    p = str; 
    gets(p); 
    max = *p;
    p++;
    while ( *p != '\0' ){
        if ( max < *p ){ 
            max = *p; 
            q=p; 
        }
        p++;
    }
    p = q;
    while ( p>str){
        *p = *(p-1);
        p--; 
    }
    *p = max;
    puts(p);
    return 0;
}