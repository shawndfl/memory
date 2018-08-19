#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include "input.h"

int startTestApp();

int myFavoriteNumber=10; 

int main() {
    
  startTestApp();

  printf("Test Passed\n");
  return EXIT_SUCCESS;
}

int startTestApp() {
  int pid = getpid();
  printf("Starting app (%d)...\n", pid);

  while( myFavoriteNumber != 0 ) 
  {
    printf("Number is %d address is %p. Enter a new number or 0 to quit or -1 to refresh: ", myFavoriteNumber, &myFavoriteNumber);
    char* line = inputLine ();
    if( strcmp (line, "-1") != 0)
    {
      myFavoriteNumber = atoi (line);
    }
    free (line);
  }
  return EXIT_FAILURE;
}
