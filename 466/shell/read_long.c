/* read-long.c: read a string of indeterminate length */
static char *cr = "copyright (c) David Binkley 1993";

/*char *realloc(), *check_malloc(); */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

char *read_long() {
  int c;
  char *buff;
  int len;

  buff = malloc(1);
  *buff = '\0';

  for (len = 0; ((c = getchar()) != EOF); len++) {
    if (c == '\n') {
      buff[len] = '\0';
      return (buff);
    }
    buff = realloc(buff, len + 2);
    if (buff == NULL) {
      fprintf(stderr, "No Core\n");
      exit(-1);
    }

    buff[len] = c;
  }

  if (len == 0) {
    free(buff);
    return (NULL);
  } else
    return (buff);
}
