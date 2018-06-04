#include "../include/apue.h"
#include "../include/error.h"

static void sig_alrm(int signo)
{
	printf("Time out!");	
}

int main(void)
{
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal error");

	alarm(10);
	if( (n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");

	alarm(0);

	write(STDOUT_FILENO, line, n);
	exit(0);
}
