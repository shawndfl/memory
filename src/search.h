#ifndef SRC_SEARCH_H_
#define SRC_SEARCH_H_

#include "common.h"

/*
 * The global pid used by all the memory access functions.
 * Like ReadM and WriteM
 */
int g_pid;

/*
 * Data types used in a search
 */
typedef enum DataType
{
  D_CHAR, D_UCHAR, D_SHORT, D_USHORT, D_INT, D_UINT
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
