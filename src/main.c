#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

extern int g_pid;

int main(int argc, char **argv)
{
  LOGI("args %d %s\n", argc, argv[0]);

  int address = 0;
  if (argc > 1)
  {
    g_pid = atoi(argv[1]);
    if (argc > 2)
    {
      address = (int) strtol(argv[2], NULL, 16);
    }
    else
    {
      LOGE("Missing address to edit of remote program.\n");
      return 1;

    }
  }
  else
  {
    LOGE("Missing pid of remote program.\n");
    return 1;
  }
  IntCollection ranges;

  GetRegions(&ranges);
  Search(&ranges, 10);

  int value = ReadM(address);
  LOGI("Value is %d\n", value);

  WriteM(address, 99);
  LOGI("Value is now 99\n");

  return 0;
}
