/**
 * @brief It defines the inventory interface
 *
 * @file inventory.h
 * @author Alejandro Garcia  
 * @version 3.0
 * @date 17/03/2023
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H               

#include "types.h"
#include "set.h"

#define MAX_OBJS_INIT 4     /*!<Maximum initial number of objects in an inventory*/

/**
 * @brief Inventory struct 
 */
typedef struct _Inventory Inventory;

/**
 * @brief It creates a new inventory, allocating memory and initializing its members
 * @author Alejandro Garcia
 * @return A new inventory, initialized
 */
Inventory *inventory_create();

/**
 * @brief It destroys an inventory, freeing the allocated memory
 * @author Alejandro Garcia
 * @param inv A pointer to the inventory that must be destroyed
 */
void inventory_destroy(Inventory *inv);

/**
 * @brief Checks if a inventory is empty
 * @author Alejandro Garcia
 * @param inv A pointer to the inventory
 * @return True if the inventory is empty or False if not or in case of error
 */
BOOL inventory_is_empty(Inventory *inv);

/**
 * @brief It adds an id to the inventory
 * @author Alejandro Garcia
 * @param inv A pointer to the inventory
 * @param id Id to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS inventory_add_id(Inventory *inv, Id id);

/**
 * @brief It removes an id from the inventory
 * @author Alejandro Garcia
 * @param inv A pointer to the inventory
 * @param id Id to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS inventory_delete_id(Inventory *inv, Id id);

/**
 * @brief Number of ids currently in the inventory
 * @author Alejandro Garcia
 * @param inv A pointer to the inventory
 * @return Number of ids that the inventory contains or -1 in case of error
 */
int inventory_get_number_ids(Inventory *inv);

/**
 * @brief Checks if an id is in a inventory
 * @author Alejandro Garcia
 * @param inv A pointer to the inventory
 * @param id Id to be cheked
 * @return True if the Id is in the inventory or False if not or in case of error
 */
BOOL inventory_contains_id(Inventory *inv ,Id id);

/**
 * @brief Gets all the ids in a inventory
 * @author Alejandro Garcia
 * @param inv A pointer to the inventory
 * @param num Pointer to the variable that will hold the number of elements in the inventory
 * @return Returns the array of Ids that are contained or NULL in case of being empty or error (If empty num=0, in case of error num=-1)
 */
Id *inventory_get_all_ids(Inventory *inv, int *num);

/**
 * @brief It prints the inventory's information
 * @author Alejandro Garcia
 * This function shows the inventory's max number of objects, and all the information relative to the objects it contains.
 * @param inv a pointer to the inventory
 * @param f Output file where it will print
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS inventory_print(Inventory *inv, FILE *f);

/**
 * @brief It gets the inventory maximum
 * @author Alejandro Garcia
 * This function gets the inventory's max number of objects
 * @param inv a pointer to the inventory
 * @return the inventory's max number of objects , if everything goes well or -1 if there was some mistake
 */
int inventory_get_max_objs(Inventory *inv);

/**
 * @brief It sets a new maximum number of objects the inventory can hold
 * @author Alejandro Garcia
 * This function set a new inventory max number of objects
 * @param inv a pointer to the inventory
 * @param newMaxObjs the new maximum number of objects
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS inventory_set_max_objs(Inventory *inv, int newMaxObjs);


#endif