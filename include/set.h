/**
 * @brief It defines the set interface
 *
 * @file set.h
 * @author David Brenchley
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/**
 * @brief Set structure
 *
 */
typedef struct _Set Set;

/**
 * @brief It creates a new set, allocating memory and initializing its members
 * @author David Brenchley 
 * @return A new set, initialized
 */
Set *set_create();

/**
 * @brief It destroys a set, freeing the allocated memory
 * @author David Brenchley 
 * @param s A pointer to the set that must be destroyed
 */
void set_destroy(Set *s);

/**
 * @brief Checks if a set is empty
 * @author David Brenchley 
 * @param s A pointer to the set
 * @return True if the set is empty or False if not or in case of error
 */
BOOL set_is_empty(Set *s);

/**
 * @brief It adds an id to the set
 * @author David Brenchley 
 * @param s A pointer to the set
 * @param id Id to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS set_add_id(Set *s, Id id);

/**
 * @brief It adds several id to the set
 * @author David Brenchley 
 * @param s A pointer to the set
 * @param ids Pointer to an array containing the ids to be added
 * @param num_ids Number of ids in the array that are to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS set_massive_add(Set *s, Id *ids, int num_ids);

/**
 * @brief It removes an id from the set
 * @author David Brenchley 
 * @param s A pointer to the set
 * @param id Id to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS set_delete_id(Set *s, Id id);

/**
 * @brief Number of ids currently in the set
 * @author David Brenchley
 * @param s A pointer to the set
 * @return Number of ids that the set contains or -1 in case of error
 */
int set_get_number_ids(Set *s);

/**
 * @brief Checks if an id is in a set
 * @author David Brenchley
 * @param s A pointer to the set
 * @param id Id to be cheked
 * @return True if the Id is in the set or False if not or in case of error
 */
BOOL set_contains_id(Set *s ,Id id);

/**
 * @brief Gets all the ids in a set
 * @author David Brenchley
 * @param s A pointer to the set
 * @param num Pointer to the variable that will hold the number of elements in the set
 * @return Returns the array of Ids that are contained or NULL in case of being empty or error (If empty num=0, in case of error num=-1)
 */
Id *set_get_all_ids(Set *s, int *num);

/**
 * @brief It prints the set's information
 * @author David Brenchley 
 * This function shows the set's size, the current number of ids, and all the ids that are contained.
 * @param s a pointer to the set
 * @param f Output file where it will print
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS set_print(Set *s, FILE *f);



#endif





