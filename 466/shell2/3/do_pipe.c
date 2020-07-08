#include <stdio.h>
#include <unistd.h>

do_pipe(char **tokenv, int *tokenc) {
  int fd[2];
  int pid;

  free(tokenv[(*tokenc) - 1]);
  tokenv[(*tokenc) - 1] = NULL;
  if (tokenv[(*tokenc)] == NULL) {
    execvp(tokenv[0], tokenv);
  } else {
    if (pipe(fd) == -1) {
      perror(tokenv[0]);
      exit(0);
    }
    pid = fork();
    switch (pid) {
    case 0:
      tokenv = tokenv + (*tokenc);
      close(0);
      dup(fd[1]);
      /*close(fd[1]);   */
      execvp(tokenv[0], tokenv);
      perror(tokenv[0]);
      break;
    default:
      close(1);
      dup(fd[0]);
      /*close(fd[0]);*/
      execvp(tokenv[0], tokenv);
      perror(tokenv[0]);
      break;
    }
  }
}
