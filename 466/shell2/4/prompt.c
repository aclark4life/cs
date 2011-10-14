#include<stdio.h>
#define PROMPT "* "
prompt()
{
	printf(PROMPT);
	return(read_long());
}
