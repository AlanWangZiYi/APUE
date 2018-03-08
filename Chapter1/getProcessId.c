#include "../include/apue.h"
#include "../include/error.h"

int main(void)
{
	printf("hello world from process ID %ld\n", (long)getpid());
	exit(0);
}
