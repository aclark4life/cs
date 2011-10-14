#include <stdio.h>

main(int argc,char *argv[])
{
	short port_num=atoi(argv[2]);
	int s=0;
	int t=0;
	char *buf=(char *)malloc(12 * sizeof(char));

	strcpy(buf,"hello world!");	
	s=create_socket(port_num); 
	s=open_socket(argv[1],port_num); 
	write(s,buf,12);
}	
