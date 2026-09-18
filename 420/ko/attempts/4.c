#include </usr/ucbinclude/sys/dir.h>
#include <stdio.h>
#include <sys/types.h>
#define NUM 100
main() {
  FILE *infile;
  char *buf = (char *)malloc(1024 * sizeof(char *));
  char **scruf = (char **)malloc(NUM * sizeof(char *));

  int i = 0;

  system("ls > foo");
  infile = fopen("foo", "r");

  /*
          for(i=0;i<NUM;i++)
          {
                  fgets(buf,NUM,infile);
                  scruf[i]=realloc(scruf[i],((strlen(buf))* sizeof (char )));
                  scruf[i]=buf;
                  printf("%s",scruf[i]);
                  printf("%s",buf);
          }

  */

  while (fgets(buf, 1024, infile) != NULL) {
    scruf[i] = realloc(scruf[i], ((strlen(buf)) * sizeof(char)));
    scruf[i] = buf;
    /*	printf("%s",buf); */
    printf("%s", scruf[i]);
    i++;
  }
}
