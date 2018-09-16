#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include "header.h"
#include "globl.h"


int ps_comm(char **argv);
int q_comm(char **argv);
int cd_comm(char **argv);
int astr_comm(char **argv);
int help_comm(char **argv);
int kill_comm(char **argv);

const char *commands_ptr[] = {
				"help",
				"cd",
				"quit",
				"ps",
				"kill",
				"&"};
int (*commands_fun[])(char **) = {
			     help_comm,
			     cd_comm,
			     q_comm,
			     ps_comm,
			     kill_comm,
			     astr_comm
};
int fun_num_comm()
{
	return sizeof(commands_ptr)/sizeof(char*);
}



int ps_comm(char **argv)
{
	int index =0;
	while(index<listjobs)
		printf("\tpid[%d]:%d\n",++index,pid[index]);

	return 1;
}
int q_comm(char **argv)
{
	exit(0);
//	return 1;
}
int cd_comm(char **argv)
{
	if(argv[1] == NULL)
		fprintf(stderr,"[USAGE] cd <dir> \n");
		goto end;

	if(chdir(argv[1]) !=0 )
		fprintf(stderr, "%s", strerror(errno));
end:
	return 1;
}
int kill_comm(char **argv)
{
	unsigned int kill_pid;

	if(argv[1] == NULL){
		fprintf(stderr, "[USAGE] kil <pid>");
		goto end;
	}
	if(!(kill_pid = atoi(argv[1])) ){
		fprintf(stderr, "[USAGE] kil <pid>");		/*[BUG] If user tape bigger then unsigned int */
		goto end;
	}
	
	// Search for pid and kill it
	for(int c; c <listjobs; c++){
		if(kill_pid == pid[c]){
			kill(pid[c],9);
			deletejob(pid[c]);
		}
	}

end:
	return 1;
}
int astr_comm(char **argv)
{
	if(argv[0] == "&")
		return 1;
}
int help_comm(char **argv)
{
	int c;
	printf(" SHELL commands:\n");

	for(c = 0;c<fun_num_comm();c++)
		printf("\t%d. %s\n", c,commands_ptr[c]);

	return 1;
}


int commands(char **argv)
{
	int i;

	for(i = 0; i< fun_num_comm(); i++){
		if(!strcmp(argv[0],commands_ptr[i]))
		return (*commands_fun[i])(argv);

	}

	return 0;
}

