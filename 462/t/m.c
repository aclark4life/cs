#include <stdio.h>


void main(int argc, char *argv[])
{
	FILE *file;
	char *string ; 
	int d;
	if (argc != 1)
	{
		printf ( "Sorry, I don't take command line arguments.\n");
	} 
	else 
	{
		//file = fopen("file","r");
		//fscanf (file,"%s",&string);
		//fprintf ("%s",string );
		scanf ("%d",&d);
		printf ("%d",d);
	}
}
