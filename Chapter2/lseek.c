#include "../include/apue.h"
#include "../include/error.h"

int main()
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("Can't seek\n");
    else
        printf("seek OK\n");
    
    exit(0);
}