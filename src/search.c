#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <stdbool.h>

#define __USE_GNU
#include <sys/uio.h>

extern int g_pid;

/*
 * This hold the data found in /proc/<pid>/maps
 * example:
 *    7fa988062000-7fa98821b000 r-xp 00000000 fd:00 2232819  /usr/lib64/libc-2.23.so
 */
typedef struct Region
{
  unsigned int min;
  unsigned int max;
  char permissions[4];
  int offset;
  char device[6];
  int inode;
  char path[PATH_MAX];
} Region;

/**********************************************************/
bool CanReadWrite(Region* region)
{
  return region->permissions[0] == 'r' && region->permissions[1] == 'w';
}

/**********************************************************/
Region ParseRegion(char* line, int len)
{
  struct Region ret;
  char tmp[PATH_MAX] = { 0 };

  memset(&ret, 0, sizeof(ret));

  int column = 0;
  int tmpIndex = 0;
  for (int i = 0; i < len; i++)
  {
    if ((column == 0 && line[i] == '-') || line[i] == ' ' || line[i] == '\n'
        || line[i] == '\0')
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
void GetRegions(IntCollection* ranges)
{
  FILE *stream;         // Stream for opening /proc/<pid>/maps
  char *line = NULL;    // Each line of the output
  size_t len = 0;       // The length of the line
  ssize_t nread;        // The number of chars read
  char pidStr[20];      // Holds the pid in string format

  IntCollectionCreate(ranges, 10);

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
    LOGE("Cannot open %s", file);
    exit(EXIT_FAILURE);
  }

  while ((nread = getline(&line, &len, stream)) != -1)
  {
    Region reg = ParseRegion(line, len);
    if (CanReadWrite(&reg))
    {
      IntCollectionAdd(ranges, reg.min);
      IntCollectionAdd(ranges, reg.max);
    }

    //printf("[INFO]: %s\n", line);
    LOGI("min: %0x\n", reg.min);
    LOGI("max: %0x\n", reg.max);
    LOGI("perm: %s\n", reg.permissions);
    LOGI("path: %s\n", reg.path);
  }

  free(line);
  fclose(stream);
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

  LOGI("g_pid is %d\n", g_pid);
  nread = process_vm_readv(g_pid, local, 1, remote, 1, 0);
  LOGI("Read %d bytes. Value is %d\n", (int ) nread, *buf1);
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

  LOGI("g_pid is %d\n", g_pid);
  nwrite = process_vm_writev(g_pid, local, 1, remote, 1, 0);
  LOGI("Write %d bytes. \n", (int ) nwrite);
  return nwrite;
}

/**********************************************************/
void Search(IntCollection* addressRanges, int value)
{

}
