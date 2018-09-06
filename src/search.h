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


/*
 * Data types used in a search
 */
typedef enum DataType
{
  DT_CHAR, DT_UCHAR, DT_SHORT, DT_USHORT, DT_INT, DT_UINT
} DataType;


/*
 * The context of the search. This will provide the search
 * with every thing it needs to find a value in memory.
 */
typedef struct SearchContext
{
  // Search path to save found files.
  char currentFile[PATH_MAX];
  // The path of the last search.
  // Can be null if this is the first search.
  char lastFile[PATH_MAX];
  // The type of search
  SearchType SearchType;
  // A value to compare to. This only applies
  // to ST_Excat value.
  Data compareValue;
  // The type of data to search for.
  DataType type;
  // The pid of the process to search.
  int pid;

} SearchContext;

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

/*
 * Searches a collection of address ranges for a given value.
 *
 */
void SearchEx(SearchContext* context);

#endif
