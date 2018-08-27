#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define __USE_GNU
#include <sys/uio.h>

extern int g_pid;
/*
 * The filename of the current search
 */
#define CURRENT_SEARCH "current.search"

/*
 * The file name of the last search
 */
#define LAST_SEARCH "last.search"

/*
 * How many bytes to read at
 * a time from the remote process
 */
#define BLOCK_SIZE 1024


/*
 * The file handle to the last
 * search
 */
FILE* lastSearch;
/*
 * The file handle for the current
 * search
 */
FILE* currentSeach;

/*
 * Opens a file handle for read only
 */
FILE* OpenLastSearch(const char* filename);

/*
 * Open a file handle for write
 */
FILE* OpenCurrentSearch(const char* filename);

/*
 * Close the file handle.
 * Param: file - The file pointer that was created by OpenCurrentSearch
 *               or OpenLastSearch.
 */
void CloseSearch(FILE* file);

/*
 * Writes a line when an entry is found. This entry
 * will be used in the next search.
 * Param: file - The file pointer that was created by OpenCurrentSearch
 *        address - The memory address of the remote address found in the search.
 *        value   - The value of data that when the match was found.
 */
void WriteSearchEntry(FILE* file, int address, DataType type, Data value);

void ReadLine(FILE* file, char * line, int len);

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
      //LOGI("min: %0x\n", reg.min);
      //LOGI("max: %0x\n", reg.max);
      //LOGI("perm: %s\n", reg.permissions);
      //LOGI("path: %s\n", reg.path);
    }
  }

  //LOGI("---------------------------\n");
  //for(int i = 0; i< ranges->count; i++)
  //{
  //  LOGI("%d: %0x\n", i, ranges->i[i]);
  //}

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

bool ReadM2(long startAddress, char* outBuffer, int size)
{

  struct iovec local[1];
  struct iovec remote[1];
  ssize_t nread;

  local[0].iov_base = outBuffer;
  local[0].iov_len = size;
  remote[0].iov_base = (void *) startAddress;
  remote[0].iov_len = size;

  //LOGI("g_pid is %d\n", g_pid);
  nread = process_vm_readv(g_pid, local, 1, remote, 1, 0);
  if (nread != size)
    return false;
  else
    return true;
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

  //LOGI("g_pid is %d\n", g_pid);
  nwrite = process_vm_writev(g_pid, local, 1, remote, 1, 0);
  //LOGI("Write %d bytes. \n", (int ) nwrite);
  return nwrite;
}

/**********************************************************/
void Search(IntCollection* addressRanges, DataType type, int value)
{
  LOGI("Searching for %d...\n", value);

  FILE* file = OpenCurrentSearch(CURRENT_SEARCH);
  for (int region = 0; region < addressRanges->count; region += 2)
  {
    int min = addressRanges->i[region];
    int max = addressRanges->i[region + 1];
    char buffer[BLOCK_SIZE] = { 0 };

    //LOGI("min: %0x\n", min);
    //LOGI("max: %0x\n", max);

    if ((max - min) % BLOCK_SIZE != 0)
    {
      LOGW("Not aligned to %d \n", BLOCK_SIZE);
    }

    for (int address = min; address < max; address += BLOCK_SIZE)
    {
      float done = ((float) (address - min + 1) / (float) (max - min)) * 100.0f;
      LOGI("processing ... %0.00f%%\r", done);
      ReadM2(address, buffer, BLOCK_SIZE);
      for (int i = 0; i < BLOCK_SIZE; i += 4)
      {
        int realAddress = address + i;
        union Data data;
        data.data[0] = buffer[i];
        data.data[1] = buffer[i + 1];
        data.data[2] = buffer[i + 2];
        data.data[3] = buffer[i + 3];
        if (data.i == value)
        {
          //LOGI("\n");
          //LOGI("Found %d %0x\n", data.i, realAddress);
          WriteSearchEntry(file, realAddress, type, data);
        }
      }
    }
    LOGI("Done       ... 100.00%%                     \n");
  }
  CloseSearch(file);
}

FILE* OpenCurrentSearch(const char* filename)
{
  FILE* file = fopen(filename, "w");
  return file;
}

void CloseSearch(FILE* file)
{
  fclose(file);
}

/*
 * Writes a line when an entry is found. This entry
 * will be used in the next search.
 * Param: file - The file pointer that was created by OpenCurrentSearch
 *        address - The memory address of the remote address found in the search.
 *        value   - The value of data that when the match was found.
 */
void WriteSearchEntry(FILE* file, int address, DataType type, Data value)
{
  char data[30] = { 0 };

  switch (type)
  {
  case DT_CHAR:
    sprintf(data, "char:  %0x %d\n", address, value.c);
    break;
  case DT_UCHAR:
    sprintf(data, "uchar: %0x %d\n", address, value.uc);
    break;
  case DT_SHORT:
    sprintf(data, "short: %0x %d\n", address, value.s);
    break;
  case DT_USHORT:
    sprintf(data, "ushort: %0x %d\n", address, value.us);
    break;
  case DT_INT:
    sprintf(data, "int: %0x %d\n", address, value.i);
    break;
  case DT_UINT:
    sprintf(data, "uint: %0x %d\n", address, value.ui);
    break;
  }
  //sprintf(data, "%s %0x %d\n", type )
  //int len = strlen(data);
  //LOGI("string length %d\n", len);
  fwrite(data, strlen(data), 1, file);
}
