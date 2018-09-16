#include "header.h"
#include "globl.h"

void sortlist()
{
	int a,b;

	for(a=0;a<listjobs;a++){
		for(b=0;b<listjobs;b++){
			if(pid[b] == 0)
				pid[b]=pid[b+1];
		}
	}
}

void addjob(pid_t pid1)
{
	pid[listjobs] = pid1;
	listjobs ++;

}

void deletejob(pid_t pid1)
{
	int c;

	for(c = 0; c <listjobs;c++){
		if(pid1 == pid[c]){
			pid[c] = 0;
			sortlist();
			listjobs--;
			return;
		}

	}
}

