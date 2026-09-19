/* dave - here is my working version of the program. i left all of my mistakes
in it in comments so that i could see where i went wrong... alex */
#include <stdio.h>
#define BUF_SIZE 255

main() {
  int a[2], b[2], pid, i;
  FILE *infile, *fin;
  char *buf = (char *)malloc(sizeof(char) * BUF_SIZE);
  char **programv = (char **)malloc(sizeof(char *) * 2);
  char **stringv = (char **)malloc(sizeof(char *));
  char *string = (char *)malloc(sizeof(char));

  infile = fopen("infile", "r");
  pipe(a);
  pipe(b);
  programv[0] = "sort";
  programv[1] = NULL;
  pid = fork();
  switch (pid) {
  case 0:
    close(0);  /* stdin */
    dup(a[0]); /* to sort */

    close(1);  /*stdout */
    dup(b[1]); /* from sort */

    execvp(programv[0], programv); /* my gross way of execing sort  :( */

    break;

  default: /******close(1);  NO NEED TO CLOSE STDOUT
           dup(a[1]);
                                   MISTAKES!!!
           close(0);         NO NEED TO CLOSE STDIN
           dup(b[0]);

                   ||  THIS WAS A HIDEOUS MESS SO I DECIDED TO SCRAP IT
                   \/

           for(i=0;(string=fread_long(infile))!=NULL;i++)
           {
                   if (strlen(string) >= 50)
                   {
                           stringv=realloc(stringv,sizeof(char*)*(i+2));
                           stringv[i]=string;
                           write(a[1],stringv[i],strlen(string));
                   }
           }

           read(0,buf,BUF_SIZE);   THIS WAS MY ATTEMPT TO READ FROM SORT
           write(2,buf,BUF_SIZE);

           ******/

    while (fgets(string, 100, infile) != NULL) {
      if (strlen(string) >= 50) {
        write(a[1], string, strlen(string));
      }
    }
    fclose(infile);

    close(a[1]); /* this one is important */
                 /* done writing, close stuff then read results */
    /* THIS REALLY IS IMPORTANT. I TRIED IT WITHOUT AND IT 'HANGS' */

    fin = fdopen(b[0], "r"); /*THIS IS THE WAY BINKLEY READS FROM SORT */
    for (i = 0; i < 10; i++) /* MUCH NICER THAN MY WAY... */
    {
      if (fgets(buf, BUF_SIZE, fin) == NULL)
        printf("fgets returned NULL!\n"); /* so what ? */
      printf("%s", buf);
    }
    fclose(fin);

    break;
  }
}
