#include "../include/apue.h"
#include "../include/error.h"

int main(void)
{
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}
