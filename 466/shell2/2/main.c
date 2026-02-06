#include <stdio.h>
#include <stdlib.h>

extern void prompt(void);
extern char *read_long(void);
extern char **tokenize(char *, int *);
extern int no_token(char **);
extern int check_for_exit(char **);
extern void do_token(char **, int *);

int main(void) {
  char **tokenv;
  char *s;
  int tokenc;

  prompt();
  for (s = read_long(); s != NULL; s = read_long()) {
    tokenv = tokenize(s, &tokenc);
    if (!no_token(tokenv)) /* if there is a token */
    {
      check_for_exit(tokenv);
      do_token(tokenv, &tokenc);
    }
    prompt();
  }

  return EXIT_SUCCESS;
}
