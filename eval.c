#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"
#include "globl.h"


void eval(char *cmdline)
{
	char *argv[MAXARGS];
	char buf[MAXLINE];
	int bg;
	pid_t currpid;

	strcpy(buf, cmdline);
	bg = parseline(buf, argv);

	if(argv[0] ==NULL)		    return;
	if(listjobs == MAXJOBS)		return;

	if(!commands(argv)){
		if((currpid =fork()) ==0){ 	/*[BUG] If child terminates before parent run, the child becomes a zombi*/
			if(execve(argv[0],argv,__environ)<0){
				printf("%s Command not found.\n", argv[0]);
				exit(0);
			}
		}
		if(!bg){
			int status;
			if( (currpid = waitpid( currpid, &status, 0) ) < 0){
				fprintf(stderr, "%s", strerror(errno));
				exit(0);
			}
			goto end;
		}else
			addjob(currpid);
			printf("bg\n[+]\tpid[%d]:%d argv:%s\n", listjobs,currpid,cmdline);
	}
end:
	printf("\n");
	return;
}
