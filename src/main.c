#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <string.h>
#include "common.h"
#include "menu.h"
#include "search.h"

extern int g_pid;

/*
 * Prints the usage of this application
 */
void Usage();

int main(int argc, char **argv)
{

  char addrFile[PATH_MAX] = { 0 };
  g_pid = 0;

  // Process arguments
  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-h") == 0)
    {
      Usage();
      return 1;
    }
    else if (strcmp(argv[i], "-addr") == 0)
    {
      if (i + 1 >= argc)
      {
        Usage();
        printf("Expecting filename");
        return 1;
      }
      strcpy(addrFile, argv[i + 1]);
    }
    else
    {
      g_pid = atoi(argv[i]);
    }
  }

  if (g_pid == 0)
  {
    Usage();
    printf("Expecting pid.");
    return 1;
  }
  IntCollection ranges;

  GetRegions(&ranges);
  Search(&ranges, DT_INT, 0);

  //int currentValue = ReadM(address);
  //LOGI("Value is %d\n", value);

  //WriteM(address, 99);
  //LOGI("Value is now 99\n");

  return 0;
}

void Usage()
{
  printf("Usage\n");
  printf("  search [-addr <filename>] pid\n");
  printf("    addr <filename>] - The file name of an addr file. ");
  printf("                       This file is used to set value in");
  printf("                       memory of a given process \n");
  printf("    pid - The process id of the remote process. \n");
}
