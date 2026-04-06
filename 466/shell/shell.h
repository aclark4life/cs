#ifndef SHELL_H
#define SHELL_H

char *prompt(void);
char **tokenize(char *s, int *tokenc);
void dump_tokens(char **tokenv, int *tokenc);
void handle_tokens(char **tokenv, int *tokenc);
void handle_pipe(char **tokenv, int *tokenc);
void handle_less_than(char **tokenv, int *tokenc);
void handle_greater_than(char **tokenv, int *tokenc);

#endif
