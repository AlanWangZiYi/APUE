#include "../include/apue.h"
#include "../include/error.h"

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
	if(atexit(my_exit2) != 0 )
		err_sys("Can't register exit 2");
	
	if(atexit(my_exit1) != 0 )
		err_sys("Can't register exit 1");
	if(atexit(my_exit1) != 0 )
		err_sys("Can't register exit 1");

	printf("main is done\n");
	return 0;

}

static void my_exit1(void)
{
	printf("First exit handle\n");
}
static void my_exit2(void)
{
	printf("Second exit handle\n");
}
