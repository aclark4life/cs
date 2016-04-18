#include <unistd.h>
#include <stdio.h>

do_something()

{
  int fd[2];
  char *buf = (char *)malloc(1024 * sizeof(char *));
  pipe(fd);

  /*	close(1);
          dup(fd[1]);
          */

  execlp("ls", "ls", (char *)0);

  /*	read(fd[0],buf,1);
          write(fd[1],buf,1);
          */
}
