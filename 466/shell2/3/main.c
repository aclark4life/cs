#include <stdio.h>

extern void prompt();
extern char *read_long();
extern char **tokenize(char *, int *);
extern int check_for_exit(char **);

main() {
  char **tokenv;
  char *s;
  int tokenc;
  int i;

  prompt();
  for (s = read_long(); s != NULL; s = read_long()) {
    tokenv = tokenize(s, &tokenc);
    if (!(tokenv[0] == NULL)) {
      check_for_exit(tokenv);
      bust_a_fork(tokenv, &tokenc);
    }
    prompt();
  }
}
