#include "../include/apue.h"
#include "../include/error.h"
#include <time.h>

int main(void)
{
	time_t t;
	struct tm *tmp;
	char buf1[16];
	char buf2[64];

	time(&t);
	tmp = localtime(&t);
	strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp);
	printf("%s\n",buf2);	
	return 0;	
}
