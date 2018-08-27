#ifndef SRC_SEARCH_H_
#define SRC_SEARCH_H_

#include "common.h"
#include <linux/limits.h>

/*
 * The global pid used by all the memory access functions.
 * Like ReadM and WriteM
 */
int g_pid;

/*
 * Data union used to convert 4 bytes to
 * other data types for comparison
 */
typedef union Data
{
  char c;
  unsigned char uc;
  short s;
  unsigned short us;
  int i;
  unsigned int ui;
  char data[4];
} Data;

/*
 * Search type used in searches and Search Context
 */
typedef enum SearchType
{
  ST_Excat,
  ST_HasIncreased,
  ST_HasDecreased,
  ST_Unknown,
  ST_HasNotChanged,
  ST_HasChanged

} SearchType;

typedef struct SearchContext
{
  char currentFile[PATH_MAX];
  char lastFile[PATH_MAX];
  SearchType SearchType;
  Data compareValue;

} SearchContext;


/*
 * Data types used in a search
 */
typedef enum DataType
{
  DT_CHAR, DT_UCHAR, DT_SHORT, DT_USHORT, DT_INT, DT_UINT
} DataType;

/*
 * Reads a given address.
 * NOTE: The g_pid must be set.
 * Param: address - The address where we want to read from.
 * Return: The int value at the address.
 */
int ReadM(long address);

/*
 * Writes an int to a given address.
 * NOTE: The g_pid must be set.
 * Param: address - The address where we want to write to.
 *        value   - The int value we are writing to memory.
 * Return: the number of bytes written to the address.
 */
int WriteM(long address, int value);

/*
 * Get a memory regions
 */
void GetRegions(IntCollection* ranges);

/*
 * Searches a collection of address ranges for a given value.
 *
 */
void Search(IntCollection* addressRanges, DataType type, int value);

#endif
