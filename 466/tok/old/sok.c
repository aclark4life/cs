#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
sok()
{
	int domain, type, protocol, sv[2];
	socket(domain,type,protocol);	 
}
