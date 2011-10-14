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
			printf("Unable to open blah blah\n");
			exit(-1);
		}
	}
	else exit(-1);
	path=argv[1];
	stat(path,buf);

	printf ( "st_mode>%d\n",buf->st_mode);
	printf ( "st_ino>%d\n",buf->st_ino);
	printf ( "st_dev>%d\n",buf->st_dev);
	printf ( "st_rdev>%d\n",buf->st_rdev);
	printf ( "st_nlink>%d\n",buf->st_nlink);
	printf ( "st_uid>%d\n",buf->st_uid);
	printf ( "st_gid>%d\n",buf->st_gid);
	printf ( "st_size>%d\n",buf->st_size);
	printf ( "st_atime>%d\n",buf->st_atime);
	printf ( "st_mtime>%d\n",buf->st_mtime);
	printf ( "st_ctime>%d\n",buf->st_ctime);

	buffer = (char*)malloc(sizeof(char)*(buf->st_size));

}
