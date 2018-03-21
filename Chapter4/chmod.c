#include "../include/apue.h"
#include "../include/error.h"

int main()
{
    struct stat statbuf;

    if(stat("foo", &statbuf) < 0)
        err_sys("error");

    if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        err_sys("error");

    if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        err_sys("error");

    exit(0);
}