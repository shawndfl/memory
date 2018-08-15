#include <stdio.h>
#include "input.h"

#define FAIL   1
#define SUCCED 0

int startTestApp();

int main() {
   
  startTestApp();
  printf("Test Passed\n");
  return SUCCED;
}

int startTestApp() {
  printf("Starting app...\n");
  char* line = inputLine ();
  printf("Line is %s\n", line);
  
  return 0;
}
