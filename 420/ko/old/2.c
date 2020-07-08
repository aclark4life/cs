#include <stdio.h>

main() {

  FILE *dir_list;
  FILE *ran_nums;
  char *fil_nam = malloc(1024 * sizeof(char));
  char **b = (char **)malloc(sizeof(char *));
  char *buf = malloc(1024 * sizeof(char));

  int i = 0;
  int j;
  struct foo {
    char **a;
  };

  /*	b[0]=(char *)malloc(10*sizeof(char));
          b[0]="foo";
          b[1]="ass";
          printf("%s%s",b[0],b[1]);
          for(j=0;j<10;j++)
          {

                  b[i]=(char *)malloc(10*sizeof(char));
                  b[j]="ass";
                  printf("%s",b[j]);

          }
          */
  make_array_o_fp();
  do_ls();
  dir_list = fopen("foo", "r");
  while (fgets(fil_nam, 1024, dir_list) != NULL) {
    /*printf("%s",file_name); */
    b[i] = (char *)malloc(1024 * sizeof(char));
    b[i] = fil_nam;
    printf("%s", b[i]);
    i++;
  }
  ran_nums = fopen(b[0], "r");
  while (fgets(buf, 1024, ran_nums) != NULL) {
    printf("%s", buf[i]);
    i++;
  }
}
