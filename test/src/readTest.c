#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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
    printf("Number is %d address is %p. Enter a new number or 0 to quit: ", myFavoriteNumber, &myFavoriteNumber);
    char* line = inputLine ();
    myFavoriteNumber = atoi (line);
  }
  return EXIT_FAILURE;
}
