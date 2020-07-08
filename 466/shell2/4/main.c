#include <stdio.h>
#define PROMPT "* "

main() {
  char **tokenv;
  char *s;
  int tokenc;
  int i;

  s = prompt();
  while (s != NULL) {
    tokenv = tokenize(s, &tokenc);
    if (tokenv[0] != NULL) {
      dump_tokens(tokenv, &tokenc);
      handle_tokens(tokenv, &tokenc);
    }
    free(tokenv);
    free(s);
    s = prompt();
  }
}
