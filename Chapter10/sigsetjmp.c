#include "../include/apue.h"
#include "../include/error.h"
#include <setjmp.h>
#include <time.h>
#include <errno.h>

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

void pr_mask(const char* str)
{
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0)
	{
		err_sys("sigprocmaks error");
	}
	else
	{
		printf("%s", str);
		if(sigismember(&sigset, SIGINT))
			printf(" SIGINT");
		if(sigismember(&sigset, SIGQUIT))
			printf(" SIGQUIT");
		if(sigismember(&sigset, SIGUSR1))
			printf(" SIGUSR1");
		if(sigismember(&sigset, SIGALRM))
			printf(" SIGALRM");

		printf("\n");
	}
	errno = errno_save;
}

Sigfunc *signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if(signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
		act.sa_flags |= SA_RESTART;

	if(sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return (oact.sa_handler);
}

static void sig_usr1(int signo)
{
	time_t starttime;
	if(canjump == 0)
		return;
	pr_mask("starting sig_user");

	alarm(3);
	starttime = time(NULL);
	while(1)
	{
		if(time(NULL) > starttime + 5)
			break;
	}

	pr_mask("finish");

	canjump = 0;
	siglongjmp(jmpbuf, 1);	
}

static void sig_alrm(int signo)
{
	pr_mask("in sig_alrm:");
}

int main(void)
{
	if(signal(SIGUSR1, sig_usr1) == SIG_ERR)
		err_sys("signal error");
	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal error");

	pr_mask("starting main: ");

	if(sigsetjmp(jmpbuf, 1))
	{
		pr_mask("ending main: ");
		exit(0);
	}
	canjump = 1;

	while(1)
		pause();
}
