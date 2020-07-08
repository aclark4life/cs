/* socket.c - socket support code */
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/types.h>

int create_socket(u_short portnum) {
  char myname[MAXHOSTNAMELEN + 1];
  int s;
  struct sockaddr_in sa;
  struct hostent *hp;

  bzero(&sa, sizeof(struct sockaddr_in));
  gethostname(myname, MAXHOSTNAMELEN);
  hp = gethostbyname(myname);
  if (hp == NULL) {
    printf("I don't exist \n");
    return (-1);
  }

  sa.sin_family = hp->h_addrtype;
  sa.sin_port = htons(portnum);

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("socket failed\n");
    return (-2);
  }

  if (bind(s, &sa, sizeof sa) < 0) {
    close(s);
    return (-3);
  }

  if (listen(s, 3) < 0) {
    perror("listen");
    return (-1);
  }
  return (s);
}

int wait_for_connection(int s) {
  struct sockaddr_in isa;
  int i;
  int t;

  errno = 0;
  i = sizeof(struct sockaddr_in);
  do {
    if ((t = accept(s, &isa, &i)) >= 0)
      break;
  } while (errno == EINTR);

  /*printf("end of wait_for_connection\n");*/
  return (t);
}
int open_socket(char *hostname, u_short portnum) {
  struct sockaddr_in sa;
  struct hostent *hp;
  int s;
  int hold;

  if ((hp = gethostbyname(hostname)) == NULL) {
    errno = ECONNREFUSED;
    return (-1);
  }

  bzero(&sa, sizeof(sa));
  bcopy(hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
  sa.sin_family = hp->h_addrtype;
  sa.sin_port = htons((u_short)portnum);

  if ((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0)
    return (-2);

  if (connect(s, &sa, sizeof sa) < 0) {
    hold = errno;
    close(s);
    errno = hold;
    return (-3);
  }
  return (s);
}

int read_data(int s, char *buf, int n) {
  int bcount;
  int br;

  bcount = 0;
  br = 0;
  while (bcount < n) {
    br = read(s, buf, n - bcount);
    if (br < 0) {
      return (-1);
    } else {
      bcount += br;
      buf += br;
    }
  }
  return (bcount);
}
