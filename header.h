#ifndef __header_h__
#define __header_h__

#include <unistd.h>

#define MAXARGS 64
#define MAXLINE 128
#define MAXJOBS 15


void eval(char *cmdline);
int commands(char **argv);
int parseline(char *buf,char **argv);
void deletejob(pid_t pid1);
void addjob(pid_t pid1);
void sortlist();


#endif
