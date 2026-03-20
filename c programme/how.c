#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main( int argc, char *argv[]){
    int len=0;
    printf("%c, ",*(*(argv+1)+1)+1);

    while (--argc > 0) 
        len += strlen( argv[argc]);
        
    printf("%d", len);
    return 0;
}
