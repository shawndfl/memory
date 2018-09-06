/*
 * menu.h
 *
 *  Created on: Aug 25, 2018
 *      Author: shawn
 */

#include <linux/limits.h>

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

struct SearchContext;

/*
 * if -addr <file> go to menu Address file
 * if -pid <pid> go to menu First search
 *
 * Address file (filename: )
 * -reload file
 * -refresh data
 *
 * First search
 * -exact value
 * -unknown value
 * -set data type
 * -restart
 *
 * Set Data Type (current type: )
 * -u char
 * -char
 * -u short
 * -short
 * -u int
 * -int
 *
 * Next search
 * -exact value
 * -has changed
 * -has NOT changed
 * -has increased
 * -has decreased
 * -Poke 10 values
 * -refresh
 * -main menu
 *
 *
 */

/*
 * The first search. Given a pid this function will
 * guide the user through a menu to search memory for values.
 */
int FirstSearch(int pid);

/*
 * Edits a address file
 */
int EditAddress(int pid, const char* addressFile);


#endif /* SRC_MENU_H_ */
