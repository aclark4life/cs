FYI, (hacked from alex's)

- dave


#include <stdio.h>
#include <sys/stat.h>

main(int argc, char *argv[])
{
    FILE *infile;
    char *string;
    struct stat buf;


    if (argc != 2)
    {
        printf("usage: %s file\n");
        exit(-1);
    }

    infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Unable to open input file.\n");
        exit(-1);
    }

    stat(argv[1], &buf);
    string = (char*)malloc(buf.st_size);
    fread(string, sizeof(char), buf.st_size, infile);
    printf("%s", string);
}
