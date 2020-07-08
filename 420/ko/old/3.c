#include <stdio.h>
#define SEP " "

main() {

  FILE *dir_list;
  FILE *ran_nums;
  char *fil_nam = malloc(1024 * sizeof(char));
  char *buf = malloc(1024 * sizeof(char));
  /*	char **fil_nams=(char **)malloc(sizeof(char *));	 */

  int i = 0;
  int j = 0;
  do_ls();
  dir_list = fopen("foo", "r");
  while (fgets(buf, 1024, dir_list) != NULL) {
    fil_nam = strtok(buf, SEP);
    printf("%s", fil_nam);
  }
  /*
  while((dir_list)!=NULL)
  {
          fil_nam()
  }
  */

  /*
  while(fgets(fil_nam,1024,dir_list)!=NULL)
  {
          fil_nams[i]=(char *)malloc(1024*sizeof(char));
          fil_nams[i]=fil_nam;
          printf("%s",fil_nams[i]);
          i++;
  }
  */

  /*
  ran_nums=fopen(b[0],"r");
  while(fgets(buf,1024,ran_nums)!=NULL)
  {
          printf("%s",buf[j]);
          j++;

  }
  */
}
