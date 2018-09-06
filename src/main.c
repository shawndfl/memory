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
    // Help
    if (strcmp(argv[i], "-h") == 0)
    {
      Usage();
      return 1;
    }
    // Address file
    else if (strcmp(argv[i], "-addr") == 0)
    {
      if (i + 1 >= argc)
      {
        Usage();
        printf("Expecting filename.\n");
        return 1;
      }
      strcpy(addrFile, argv[i + 1]);
    }
    // Search expect a pid
    else
    {
      g_pid = atoi(argv[i]);
    }
  }

  if (g_pid == 0)
  {
    Usage();
    printf("Expecting pid.\n");
    return 1;
  }

  if(strlen(addrFile) > 0)
  {
    EditAddress(g_pid, addrFile);
  }
  else
  {
    FirstSearch(g_pid);
  }
  //IntCollection ranges;
  //GetRegions(&ranges);
  //Search(&ranges, DT_INT, 105);



  return 0;
}

void Usage()
{
  printf("Usage\n");
  printf("  search [-addr <filename>] pid\n");
  printf("    addr <filename>] - The file name of an addr file.\n");
  printf("                       This file is used to set value in\n");
  printf("                       memory of a given process. \n");
  printf("    pid - The process id of the remote process.\n\n");
}
