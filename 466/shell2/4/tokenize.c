#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPARATOR " \t"

char **tokenize(char *s, int *tokenc) {
  char *token;
  char *temp;
  char **tokenv = (char **)malloc(sizeof(char *));
  char **temp_v;

  if (tokenv == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  (*tokenc) = 0;
  token = strtok(s, SEPARATOR);
  if (token != NULL) {
    (*tokenc)++;
    temp = (char *)malloc((strlen(token) + 1) * sizeof(char));
    if (temp == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    strcpy(temp, token);
    tokenv[(*tokenc) - 1] = temp;
  } else {
    tokenv[0] = NULL;
    return (tokenv);
  }

  while ((token = strtok(NULL, SEPARATOR)) != NULL) {
    (*tokenc)++;
    temp_v = (char **)realloc(tokenv, (sizeof(char *) * (*tokenc)));
    if (temp_v == NULL) {
      perror("realloc");
      exit(EXIT_FAILURE);
    }
    tokenv = temp_v;
    temp = (char *)malloc((strlen(token) + 1) * sizeof(char));
    if (temp == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    strcpy(temp, token);
    tokenv[(*tokenc) - 1] = temp;
  }
  temp_v = (char **)realloc(tokenv, (sizeof(char *) * ((*tokenc) + 1)));
  if (temp_v == NULL) {
    perror("realloc");
    exit(EXIT_FAILURE);
  }
  tokenv = temp_v;
  tokenv[(*tokenc)] = NULL;
  return (tokenv);
}
