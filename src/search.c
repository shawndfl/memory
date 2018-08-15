
#include <stdio.h>
#include <sys/uio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  
  struct iovec local[2];
  struct iovec remote[1];
  char buf1[10];
  char buf2[10];
  ssize_t nread;
  pid_t pid = 10;             /* PID of remote process */

  printf("args %d %s\n", argc, argv[0]);

  if(argc > 1)
  {
    pid = atoi(argv[1]);
  }
  printf("Using pid %d\n", pid);

  local[0].iov_base = buf1;
  local[0].iov_len = 10;
  local[1].iov_base = buf2;
  local[1].iov_len = 10;
  remote[0].iov_base = (void *) 0x21044;
  remote[1].iov_len = 20;

  nread = process_vm_readv(pid, local, 2, remote, 1, 0);
  printf("Read %d bytes. Value is %s\n", nread, (char *)buf1);
  if (nread != 20)
      return 1;
  else
      return 0;
 
  printf ("Hello\n");
  return 0;
}
