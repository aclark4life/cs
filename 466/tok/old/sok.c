#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
sok() {
  int domain, type, protocol, sv[2];
  socket(domain, type, protocol);
}
