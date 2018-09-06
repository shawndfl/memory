/*
 * menu.c
 *
 *  Created on: Sep 4, 2018
 *      Author: shawn
 */
#include <stdbool.h>

#include "common.h"
#include "input.h"
#include "menu.h"
#include "search.h"

/*
 * The first search menu. This is called
 * from FirstSearch function.
 *
 * pid - The process id
 * searchContext - The context of the search. This will get
 *                 edited by this function.
 * returns - true if success else false.
 */
bool FirstSearchMenu(int pid, SearchContext* searchContext);

/*
 * Sets the data type for the search.
 * returns - true if success else false.
 */
bool SetDataTypeMenu(SearchContext* context);

/**********************************************************/
int FirstSearch(int pid)
{
  SearchContext context;
  FirstSearchMenu(pid, &context);

  return 0;
}

/**********************************************************/
int EditAddress(int pid, const char* addressFile)
{
  return 0;
}

/**********************************************************/
bool FirstSearchMenu(int pid, SearchContext* context)
{
  bool valid = false;
  while (!valid)
  {
    if (context == NULL)
    {
      LOGE("Context can not be null");
      valid = false;
      break;
    }

    printf("\nFirst Search\n");
    printf("------------\n");

    printf("[e]xact value\n");
    printf("[u]nknown value\n");
    printf("set [d]ata type\n");
    printf("[r]estart\n");
    printf("[s]earch\n");
    char* line = inputLine();

    switch (line[0])
    {
    case 'e':
      context->SearchType = ST_Excat;
      valid = true;
      break;
    case 'u':
      context->SearchType = ST_Unknown;
      valid = true;
      break;
    case 'd':
      valid = SetDataTypeMenu(context);
      break;
    case 'r':
      valid = true;
      break;
    case 's':
      SearchEx(context);
    default:
      printf("Expecting: e,u,s, or r\n");
    }
  }
  return valid;
}

bool SetDataTypeMenu(SearchContext* context)
{
  bool valid = false;
  while (!valid)
  {
    if (context == NULL)
    {
      LOGE("Context can not be null");
      valid = false;
      break;
    }

    printf("\nSet Data Type\n");
    printf("------------\n");

    printf("[c]har\n");
    printf("[u]char\n");
    printf("[s]hort\n");
    printf("us[h]ort\n");
    printf("[i]nt\n");
    printf("ui[n]t\n");
    char* line = inputLine();
    switch (line[0])
    {
    case 'c':
      break;
    case 'u':
      break;
    case 's':
      break;
    case 'h':
      break;
    case 'i':
      break;
    case 'n':
      break;
    default:
      break;
    }
  }

  return valid;
}
