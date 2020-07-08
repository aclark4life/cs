#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

bg(char **tokenv, int *tokenc) {
  int i, j, pid;
  int table[10][2];

  free(tokenv[(*tokenc) - 1]);
  tokenv[(*tokenc) - 1] = NULL;
  if (tokenv[(*tokenc)] == NULL) {
    execvp(tokenv[0], tokenv);
  }

  /*	for( i=0; i<10; i++)
          {
                  table[i][0]=i+1;
          table[i][1]=0;
   printf("%d\n",table[i][0]);
          }

  */
  pid = fork();
  /*	table[0][1]=pid; */
  for (i = 0; i < 10; i++) {
    /*	printf("%d	%d\n",table[i][0],table[i][1]); */
  }
  switch (pid) {
  case 0:
    tokenv = tokenv + (*tokenc);
    printf("case 0\n");
    execvp(tokenv[0], tokenv);

    break;

  default:
    printf("default\n");
    /*				execvp(tokenv[0]); */
    perror(tokenv[0]);
    return (0);
    break;
  }
}
