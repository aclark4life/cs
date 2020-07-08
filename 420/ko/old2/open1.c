#include <stdio.h>
void open(char **scruf, int n) {
  int i;
  char *buf = (char *)malloc(1024 * sizeof(char *));
  char **file = (char **)malloc(1024 * sizeof(char *));
  char *temp = (char *)malloc(1024 * sizeof(char *));
  char *test = (char *)malloc(1024 * sizeof(char *));

  FILE *infile;

  /*	test[0]='"';
          test[1]='1';
          test[2]='.';
          test[3]='c';
          test[4]='"';
          */

  for (i = 0; i < 1; i++) {
    /*printf("%s",scruf[i]); */
    /*		printf("\n\n\n\n\n%s\n",test); */

    printf("%s", scruf[i]);
    infile = fopen(scruf[i], "r");
    printf("%i\n", infile);
    printf("%i\n", NULL);

    /*    		while(fgets(buf,1024,infile)!=NULL)
                    {
                            file[i]=realloc(scruf[i],((strlen(buf))*sizeof(char)));
                            strcpy(file[i],buf);
                            printf("%s",file[i]);
                            i++;
                    }
                    */
  }
}
