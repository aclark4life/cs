#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(int argc, char *argv[])
{
	FILE *infile;
	const char *path;
	struct stat *buf;
	char *buffer;

	buf=(struct stat*)(malloc(sizeof(struct stat)));
	if (argc == 2)
	{
		infile = fopen(argv[1],"r");
		if (infile == NULL)
		{
			printf("Unable to open input file.\n");
			exit(-1);
		}
	}
	else exit(-1);
	path=argv[1];
	stat(path,buf);
	buffer = (char*)malloc(sizeof(char)*(buf->st_size));
	fread(buffer,sizeof(char),buf->st_size,infile);

	printf ( "buffer > %s",buffer);
}

