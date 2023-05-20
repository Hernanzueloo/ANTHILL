/**
 * @brief It defines the space interface
 *
 * @file space.h
 * @author Javier San Andres  
 * @version 3.0
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

/**
 * @brief Space structure
 *
 */
typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Javier San Andres  
 * @param id The identification number for the new space
 * @return A new space, initialized
 */
Space *space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Javier San Andres  
 * @param space A pointer to the space that must be destroyed
 */
void space_destroy(Space *space);

/**
 * @brief It gets the id of a space
 * @author Javier San Andres 
 * @param space A pointer to the space
 * @return The id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It sets the name of a space
 * @author Javier San Andres 
 * @param space A pointer to the space
 * @param name A string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS space_set_name(Space *space, char *name);

/**
 * @brief It gets the name of a space
 * @author Javier San Andres 
 * @param space A pointer to the space
 * @return  A string with the name of the space
 */
const char *space_get_name(Space *space);

/**
 * @brief It sets the light of a space
 * @author Alejandro García Hernando
 * @param space A pointer to the space
 * @param light A boolean with the value to store
 * @return  OK, if everything goes well or ERROR if there was some mistake
 */
STATUS space_set_light(Space *space, BOOL light);

/**
 * @brief It gets the light of a space
 * @author Alejandro García Hernando
 * @param space A pointer to the space
 * @return  The value of the light of the space
 */
BOOL space_get_light(Space *space);

/**
 * @brief It sets the light of a space
 * @author Alejandro García Hernando
 * @param space A pointer to the space
 * @param flooded A sstatus with the value to store
 * @return  OK, if everything goes well or ERROR if there was some mistake
 */
STATUS space_set_flooded(Space *space, SSTATUS flooded);

/**
 * @brief It gets the light of a space
 * @author Alejandro García Hernando
 * @param space A pointer to the space
 * @return  The sstatus of the space or 
 */
SSTATUS space_get_flooded(Space *space);

/**
 * @brief It adds an object to the space
 * @author Javier San Andres  
 * @param space A pointer to the space
 * @param id Object Id
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS space_add_object(Space *space, Id id);

/**
 * @brief It removes an object from the space
 * @author Javier San Andres 
 * @param space A pointer to the space
 * @param id Object Id
 * @return OK, if everything goes well or ERROR if there was some mistake
*/
STATUS space_remove_object(Space *space, Id id);

/**
 * @brief It checks if the space contains the object
 * @author Javier San Andres  
 * @param space A pointer to the space
 * @param id Object Id
 * @return True if it is contained or False if not ot in case of error
 */
BOOL space_contains_object(Space *space, Id id);

/**
 * @brief It gets an array that contains all the objects' ids in a space
 * @author Javier San Andres  
 * @param space A pointer to the space
 * @param num Pointer to the variable that will hold the number of elements in the set
 * @return A pointer to the array or NULL if error
 */
Id *space_get_objects(Space *space, int *num);

/**
 * @brief It gets the main description of a space
 * @author Javier San Andres 
 * @param space A pointer to the space
 * @return Returns a pointer to the textual descriptor (or NULL in case of error)
 */
char *space_get_tdesc(Space *space);

/**
 * @brief It sets the mian description of a space
 * @author Javier San Andres 
 * @param space A pointer to the object
 * @param tdescr Pointer to the description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS space_set_tdesc(Space *space, char *tdescr);

/**
 * @brief It gets the graphical descriptor of a space
 * @author Alejandro García
 * @param space A pointer to the space
 * @return Returns a pointer to the detailed textual descriptor (or NULL in case of error)
 */
char *space_get_idesc(Space *space);

/**
 * @brief It sets the detailed description of a space
 * @author Alejandro García
 * @param space A pointer to the object
 * @param idescr Pointer to the description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS space_set_idesc(Space *space, char *idescr);

/**
 * @brief It gets the graphical descriptor of a space
 * @author Javier San Andres 
 * @param space A pointer to the space
 * @return Returns a pointer to the graphical descriptor (or NULL in case of error)
 */
char **space_get_gdesc(Space *space);

/**
 * @brief It sets the graphical descriptor of a space
 * @author Javier San Andres 
 * @param space A pointer to the space
 * @param gdesc Pointer to the descriptor to be set
 * @return Returns OK if everything goes well or ERROR if there was some mistake
 */
STATUS space_set_gdesc(Space *space, char **gdesc);

/**
 * @brief It prints the space's information
 * @author Javier San Andres 
 * This function shows the id and name of the space, the spaces that surrounds it, whether it has an object or not and its graphical descriptor (if exists)
 * @param space a pointer to the space
 * @param file Output file where it will print
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS space_print(Space *space, FILE *file);

#endif
