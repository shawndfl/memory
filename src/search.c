
#include "search.h"

#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU
#include <sys/uio.h>

extern int g_pid;

/**********************************************************/
int ReadM(long address)
{
  
  struct iovec local[1];
  struct iovec remote[1];
  char buf1[10] = {0};
  ssize_t nread;

  local[0].iov_base = buf1;
  local[0].iov_len = 4;
  remote[0].iov_base = (void *)address;
  remote[0].iov_len = 4;

  printf("g_pid is %d\n", g_pid);
  nread = process_vm_readv(g_pid, local, 1, remote, 1, 0);
  printf("Read %d bytes. Value is %d\n", (int)nread, *buf1);
  if (nread != 20)
      return 1;
  else
      return 0;
}

/**********************************************************/
int WriteM(long address, int value)
{
  struct iovec local[1];                                       
  struct iovec remote[1];
  char buf1[4] = {0};
  *buf1 = value;                                          
  ssize_t nread;                                               
  
  local[0].iov_base = buf1;                                    
  local[0].iov_len = 4;
  remote[0].iov_base = (void *) address;     
  remote[0].iov_len = 4;
  
  printf("g_pid is %d\n", g_pid);
  nread = process_vm_writev(g_pid, local, 1, remote, 1, 0);
  printf("Write %d bytes. \n", (int)nread);
  return 0;
}
