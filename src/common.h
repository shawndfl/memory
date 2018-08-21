/*
 * common.h
 *
 *  Created on: Aug 18, 2018
 *      Author: shawn
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

/*************************************************************
 *        Collection functions
 *************************************************************/

/*
 * A collection of integers
 * Use IntCollectionCreate to create the collection then use
 * IntCollectionFree to release the memory
 */
typedef struct IntCollection
{
  int* num;
  int count;
}IntCollection;

/*
 * Creates a collection of integers. Use IntCollectionFree to
 * free memory.
 * Param: size - The size of the collection.
 * Returns:  IntCollection allocated with the given size
 */
IntCollection IntCollectionCreate(int size);

/*
 * Frees a IntCollection and sets the size to zero.
 * Param: collection - The IntCollection that will be freed.
 */
void IntCollectionFree(IntCollection collection);


/*************************************************************
 *          Logging functions
 *************************************************************/
#define LOGD(...) fprintf(stdout,"[DEBUG] %s %s (%d): ", __TIME__, __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__);
#define LOGI(...) fprintf(stdout,"[INFO]  %s %s (%d): ", __TIME__, __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__);
#define LOGW(...) fprintf(stdout,"[WARN]  %s %s (%d): ", __TIME__, __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__);
#define LOGE(...) fprintf(stdout,"[ERROR]  %s %s (%d): ", __TIME__, __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__);

#endif /* SRC_COMMON_H_ */
