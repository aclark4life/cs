#include <stdio.h>
main() {
  FILE *dir;
  char c;
  dir = fopen("dir", "r");

  /*
  while(c=fgetc(dir)!=NULL)
  {
          printf("%c%d\n",c,c);


  }
  */
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c); /* this is gross, but when my
                            while loop above failed, i took
                            the easy way out...
                            */
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir); /*i'm wondering if the char pointer
                  gets updated when i call fgetc like
                  this. or am i just printing out
                  the first char over and over.
                  */
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
  c = fgetc(dir);
  printf("%c%d\n", c, c);
}
/*

        doesn't seem to be much in the output.
        output:

        purity:~/indep_study/dir>main
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1
        ÿ-1


        hmmm... when it prints to the screen it looks different
        than when i grab it with the mouse and put it in here.
        must be vi....


        what is this error:

        purity:~/os/dir>ccc main
        ld: fatal: getcwd call failed
        purity:~/os/dir>

*/
