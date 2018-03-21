#include "../include/apue.h"
#include "../include/error.h"
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int val;

    if(argc != 2)
        err_quit("Usage out!");

    if( (val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0 )
        err_sys("error");

    switch(val & O_ACCMODE)
    {
        case O_RDONLY: 
            printf("read only");
            break;
        case O_WRONLY: 
            printf("write only");
            break;
        case O_RDWR: 
            printf("read write");
            break;
        default: 
            err_dump("Unknown");
            break;
    }
    if(val & O_APPEND)
        printf(", append");
    if(val & O_NONBLOCK)
        printf(", nonblocking");
    if(val & O_SYNC)
        printf(", sync");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if(val & O_FSYNC)
        printf(", sync write");
#endif

    putchar('\n');
    exit(0);

}