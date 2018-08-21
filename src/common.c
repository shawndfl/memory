/*
 * common.c
 *
 *  Created on: Aug 18, 2018
 *      Author: shawn
 */
#include "common.h"
#include <stdlib.h>

/**********************************************************/
void IntCollectionCreate(IntCollection* collection, int initializeSize)
{
  collection->count = 0;
  collection->i = malloc(sizeof(int) * initializeSize);
  collection->maxSize = initializeSize;
}

/**********************************************************/
void IntCollectionFree(IntCollection* collection)
{
  free(collection->i);
  collection->count = 0;
  collection->i = NULL;
  collection->maxSize = 0;
}

/**********************************************************/

void IntCollectionAdd(IntCollection* collection, int num)
{
  if (collection->count < collection->maxSize)
  {
    collection->i[collection->count++] = num;
  }

}
