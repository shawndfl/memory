#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

#define __USE_GNU
#include <sys/uio.h>

extern int g_pid;

/*
 * This hold the data found in /proc/<pid>/maps
 * example:
 *    7fa988062000-7fa98821b000 r-xp 00000000 fd:00 2232819  /usr/lib64/libc-2.23.so
 */
struct Region
{
  unsigned int min;
  unsigned int max;
  char permissions[4];
  int offset;
  char device[6];
  int inode;
  char path[PATH_MAX];
};

struct Region Region(char* line, int len)
{
  struct Region ret;
  char tmp[PATH_MAX] = { 0 };

  memset(&ret, 0, sizeof(ret));

  int column = 0;
  int tmpIndex = 0;
  for (int i = 0; i < len; i++)
  {
    if ((column == 0 && line[i] == '-') || line[i] == ' ' || line[i] == '\n' || line[i] == '\0')
    {
      tmp[tmpIndex] = '\0';
      //printf("[INFO]: col: %d -->|%s|\n", column, tmp);
      switch (column)
      {
      case 0:
        ret.min = strtol(tmp, NULL, 16);
        break;
      case 1:
        ret.max = strtol(tmp, NULL, 16);
        break;
      case 2:
        memcpy(ret.permissions, tmp, sizeof(ret.permissions));
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        memcpy(ret.path, tmp, PATH_MAX);
        break;
      }
      column++;
      tmpIndex = 0;

      // Eat white space
      while (line[i + 1] == ' ' || line[i + 1] == '\t' || line[i + 1] == '\n'
          || line[i + 1] == '\0')
        i++;
    }
    else
    {
      tmp[tmpIndex++] = line[i];
    }

  }
  return ret;
}

/**********************************************************/
IntCollection GetRegions()
{
  FILE *stream;         // Stream for opening /proc/<pid>/maps
  char *line = NULL;    // Each line of the output
  size_t len = 0;       // The length of the line
  ssize_t nread;        // The number of chars read
  char pidStr[20];      // Holds the pid in string format
  IntCollection intCollection = IntCollectionCreate(10);  // The first range found

// Get the string value of pid
  sprintf(pidStr, "%d", g_pid);

// Get the path for maps
  char file[PATH_MAX] = { 0 };
  strcat(file, "/proc/");
  strcat(file, pidStr);
  strcat(file, "/maps");

// Open the stream
  stream = fopen(file, "r");
  if (stream == NULL)
  {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  while ((nread = getline(&line, &len, stream)) != -1)
  {
    struct Region reg = Region(line, len);
    //printf("[INFO]: %s\n", line);
    printf("[INFO]: min: %0x\n", reg.min);
    printf("[INFO]: max: %0x\n", reg.max);
    printf("[INFO]: perm: %s\n", reg.permissions);
    printf("[INFO]: path: %s\n", reg.path);
  }

  free(line);
  fclose(stream);
  return intCollection;
}

/**********************************************************/
int ReadM(long address)
{

  struct iovec local[1];
  struct iovec remote[1];
  char buf1[10] = { 0 };
  ssize_t nread;

  local[0].iov_base = buf1;
  local[0].iov_len = 4;
  remote[0].iov_base = (void *) address;
  remote[0].iov_len = 4;

  printf("g_pid is %d\n", g_pid);
  nread = process_vm_readv(g_pid, local, 1, remote, 1, 0);
  printf("Read %d bytes. Value is %d\n", (int) nread, *buf1);
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
  char buf1[4] = { 0 };
  *buf1 = value;
  ssize_t nwrite;

  local[0].iov_base = buf1;
  local[0].iov_len = 4;
  remote[0].iov_base = (void *) address;
  remote[0].iov_len = 4;

  printf("g_pid is %d\n", g_pid);
  nwrite = process_vm_writev(g_pid, local, 1, remote, 1, 0);
  printf("Write %d bytes. \n", (int) nwrite);
  return nwrite;
}
