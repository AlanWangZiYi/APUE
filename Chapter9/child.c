#include "../include/apue.h"
#include "../include/error.h"

static void sig_hup(int signo)
{
	printf("SIGHUP, pid = %ld\n", (long)getpid());
}

static void pr_ids(char* name)
{
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n", name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(void)
{
	char c;
	pid_t pid;

	pr_ids("parent");
	if((pid = fork()) > 0)
		sleep(5);
	else if(pid == 0)
	{
		pr_ids("child");
		signal(SIGHUP, sig_hup);
		kill(getpid(), SIGTSTP);
		pr_ids("child");
		if(read(STDIN_FILENO, &c, 1) != 1)
			printf("raed error %d on tty\n", errno);
	}
	exit(0);
}
