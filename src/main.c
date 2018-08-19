
#include "search.h"
#include <stdio.h>
#include <stdlib.h>

extern int g_pid;

int main(int argc, char **argv)
{
  printf("args %d %s\n", argc, argv[0]);                      

  int address = 0;
  if(argc > 1)                                                
  {                                                           
    g_pid = atoi(argv[1]);
    if( argc > 2)
    {
      address=(int)strtol(argv[2], NULL, 16);
    }
  }

  GetRegions();
      
  int value=ReadM(address);
  printf ("Value is %d\n", value);

  WriteM(address, 99);
  printf ("Value is now 99\n");

  return 0;
}
