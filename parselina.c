#include <string.h>

int parseline(char *buf, char **argv)
{
	int bg;
	char *delim;
	int c;

	buf[strlen(buf)-1] = ' ';
	while(*buf &&(*buf == ' '))
		buf++;

	c=0;
	while((delim = strchr(buf,' '))){
		argv[c++]=buf;
		*delim='\0';
		buf=delim+1;
		while(*buf &&(*buf==' '))
			buf++;
	}

	argv[c]=NULL;

	if(c==0)
		return 1;

	if((bg = (*argv[c-1] == '&')) !=0)
		argv[--c] = NULL;

	return bg;
}
