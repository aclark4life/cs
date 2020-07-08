#include <stdio.h>
void do_token(char **tokenv, int *tokenc) {
  int pid, status;
  pid = fork();
  switch (pid) {
  case 0:
    redir(tokenv, &tokenc);
    if (execvp(tokenv[0], tokenv) == -1) {
      perror(tokenv[0]);
      exit(0);
    }
    break;

  default:
    if (wait(&status) == -1) {
      perror("wait error...");
    }
    break;
  }
}
