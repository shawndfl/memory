#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "input.h"

int startTestApp();

char* num1;
unsigned char num2;

short* num3;
unsigned short num4;

int main()
{

  num1 = malloc(sizeof(char));
  *num1 = 1;

  num2 = 2;

  num3 = malloc(sizeof(short));
  *num3 = 3;

  num4 = 4;

  time_t t;
  /* Initializes the random number generator */
  srand((unsigned) time(&t));

  startTestApp();

  free(num1);
  free(num3);
  return EXIT_SUCCESS;
}

int startTestApp()
{
  int pid = getpid();
  printf("--------------------------------------------\n");
  printf("Starting Test App. Run the following to search memory:\n");
  printf("bin/search %d \n", pid);
  printf("--------------------------------------------\n\n");

  int num5 = 0;
  unsigned int num6 = 0;

  while (1)
  {
    printf("My numbers are\n1)%d\n2)%d\n3)%d\n4)%d\n5)%d\n6)%d\n", *num1, num2, *num3, num4, num5, num6);
    printf("[r]efresh; [c]hange numbers; [q]uit\n");
    char* line = inputLine ();

    // Anthing other than 2 or 3 will just refresh
    if( strcmp (line, "c") == 0)
    {
      *num1 = (char)rand();
      num2 = (unsigned char)rand();
      *num3 = (short)rand();
      num4 = (unsigned short)rand();
      num5 = rand();
      num6 = rand();
    }
    else if(strcmp (line, "q") == 0)
    {
      free(line);
      break;
    }

    free(line);
  }
  return EXIT_FAILURE;
}
