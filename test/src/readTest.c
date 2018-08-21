#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#include "input.h"

int startTestApp();
int* myFavoriteNumber; 

int main() {
    
  myFavoriteNumber=malloc(sizeof(int));
  *myFavoriteNumber=10;
  startTestApp();

  free(myFavoriteNumber);
  return EXIT_SUCCESS;
}

int startTestApp() {
  int pid = getpid();
  printf("--------------------------------------------\n");
  printf("Starting Test App. Run the following to search memory:\n");
  printf("search %d %p\n", pid, myFavoriteNumber);
  printf("--------------------------------------------\n\n");


  while( *myFavoriteNumber != 0 ) 
  {
    printf("My favorite number is %d. Enter a new number or 0 to quit or -1 to refresh: ", *myFavoriteNumber);
    char* line = inputLine ();
    if( strcmp (line, "-1") != 0)
    {
      *myFavoriteNumber = atoi (line);
    }
    free (line);
  }
  return EXIT_FAILURE;
}
