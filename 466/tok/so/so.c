#include <stdio.h>

main(int argc, char *argv[]) {
  short port_num = atoi(argv[1]);
  int s = 0;
  int t = 0;
  int n = 12;
  char *buf = (char *)malloc(12 * sizeof(char));

  s = create_socket(port_num);
  t = wait_for_connection(s);
  printf("connect.\n");
  read_data(t, buf, n);
  /*	read(t,buf,12);*/
  write(1, buf, 12);
  printf("\n");
}
