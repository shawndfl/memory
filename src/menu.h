/*
 * menu.h
 *
 *  Created on: Aug 25, 2018
 *      Author: shawn
 */

#include <linux/limits.h>

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

/*
 * if -addr <file> go to menu Address file
 * if -pid <pid> go to menu First search
 *
 * Address file (filename: )
 * -reload file
 * -refresh data
 * -main menu
 *
 * First search
 * -exact value
 * -unknown value
 * -set data type
 * -main menu
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

typedef struct MenuContext
{
  int pid;
  char addrFile[PATH_MAX];
}MenuContext;

typedef enum MenuId
{
  MENU_FIRST,
  MENU_NEXT,

}MenuId;

typedef struct MenuState
{

}MenuState;

/*
 * Go back to the previous menu
 */
#define MENU_BACK       1

/*
 * Used to set the data type of the search
 */
#define MENU_SET_TYPE   1

#define MENU_SEARCH     3


int FirstSearch();


#endif /* SRC_MENU_H_ */
