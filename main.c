#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/wait.h>

#include "header.h"
#include "globl.h"

int listjobs=0;
sigjmp_buf buf_sig;
pid_t pid[MAXJOBS];



void handler1(int sig)
{
	siglongjmp(buf_sig,1);
}



void handler2(int sig)
{
	pid_t pid1;


	while((pid1=waitpid(-1,NULL,0))>0){
		deletejob(pid1);
		printf("process pid[%d] has terminated\n",(int)pid1);
		return;
	}

	if(errno != ECHILD){
		fprintf(stderr, "%s", strerror(errno));
		exit(0);
	}
	return;
}


int main()
{
	char cmdline[MAXLINE];


	if(signal(SIGINT,handler1) == SIG_ERR){
		fprintf(stderr, "signal error%s", strerror(errno));
		exit(0);
	}
	if(signal(SIGCHLD,handler2) == SIG_ERR){
		fprintf(stderr, "signal error %s", strerror(errno));
		exit(0);
	}

	if(sigsetjmp(buf_sig,1))
		printf("\n");



	while(1){
		printf(">");
		fgets(cmdline, MAXLINE,stdin);
		if(feof(stdin)){
			fprintf(stderr,"feof error\n");
			exit(0);
		}

		eval(cmdline);

	}
}


