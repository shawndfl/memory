#ifndef SRC_SEARCH_H_
#define SRC_SEARCH_H_

#include "common.h"

/*
 * The global pid used by all the memory access functions.
 * Like ReadM and WriteM
 */
int g_pid;

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
void Search(IntCollection* addressRanges, int value);

#endif
