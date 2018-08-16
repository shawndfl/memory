
#include "search.h"
#include <stdio.h>

extern int g_pid;

int main(int argc, char **argv)
{
  printf("args %d %s\n", argc, argv[0]);                      
                                                              
  if(argc > 1)                                                
  {                                                           
    g_pid = atoi(argv[1]);
  }
      
  int value=ReadM(0x21048);
  printf ("Value is %d\n", value);

  WriteM(0x21048, 99);
  printf ("Value is now 99\n");

  return 0;
}
