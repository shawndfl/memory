/*
 * common.c
 *
 *  Created on: Aug 18, 2018
 *      Author: shawn
 */
#include "common.h"
#include <stdlib.h>

/**********************************************************/
IntCollection IntCollectionCreate(int size)
{
  IntCollection collection = { malloc(sizeof(int) * size), size};
  return collection;
}

/**********************************************************/
void IntCollectionFree(IntCollection collection)
{
  free(collection.num);
  collection.count = 0;
  collection.num = NULL;
}

