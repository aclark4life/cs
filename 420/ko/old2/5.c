#include </usr/ucbinclude/sys/dir.h>
#include <stdio.h>
#include <sys/types.h>
main() {
  FILE *infile;
  char *buf = (char *)malloc(1024 * sizeof(char *));

  /*char **scruf=(char **)malloc(1024 * sizeof(char *));*/

  char **scruf = (char **)malloc(sizeof(char *));

  int i = 0;
  int j = 0;
  int n = 0;

  system("ls -1 > foo");
  infile = fopen("foo", "r");

  while (fgets(buf, 1024, infile) != NULL) {
    n++;

    /*		printf("---------->%s\n",buf); */

    /*scruf[i]=realloc(scruf[i],((strlen(buf)+1)*sizeof(char *)));    */

    scruf = (char **)realloc(scruf, sizeof(char *) + n + 1);
    scruf[n - 1] = (char *)malloc((strlen(buf) + 1) * sizeof(char));

    /*scruf[i]=buf; 	<----- a big mistake 	*/

    strcpy(scruf[n - 1], buf);
    scruf[n - 1][strlen(buf)] = '\0';
    /*		scruf[i][strlen(buf)]='a';
                    scruf[i][strlen(buf)+1]=' ';
                    */

    /*		printf ("%d\n",(strlen(buf))); */

    /*		for(i=(strlen(buf));i<1024;i++)
                    {
                            scruf[i]='a';
                    }
                    */

    printf("%s", scruf[i]);
    i++;
  }

  /*        for(j=0;j<i;j++)
          {
                  printf("%s",scruf[j]);
          }
          */

  open(scruf, n);
}
