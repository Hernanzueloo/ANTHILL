/**
 * @brief It defines the link interface
 *
 * @file link.h
 * @author Javier San Andrés
 * @version 3.0
 * @date 17/03/2023
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H


#include "types.h"

/**
 * @brief Link struct 
 */
typedef struct _Link Link;

/**
 * @brief It creates a new link, initializing its members
 * @author Javier San Andrés
 * @param id Id of the link to be created
 * @return A new link, initialized
 */
Link *link_create(Id id);


/**
 * @brief It destroys a link
 * @author Javier San Andrés
 * @return A new link, initialized
 */
void link_destroy(Link *link);

/**
 * @brief It gets the link's id
 * @author Javier San Andrés
 * @param link pointer to the link
 * @return id of the link
 */
Id link_get_id(Link *link);


/**
 * @brief It sets the link's name
 * @author Javier San Andrés
 * @param link pointer to the link
 * @param name pointer to the string name to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS link_set_name(Link *link, char *name);


/**
 * @brief It gets the link's name
 * @author Javier San Andrés
 * @param link pointer to the link
 * @return pointer to the string of the link's name
 */
char *link_get_name(Link *link);


/**
 * @brief It sets a link's origin
 * @author Javier San Andrés
 * @param link pointer to the link
 * @param origin id of the origin to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS link_set_origin(Link *link, Id origin);


/**
 * @brief It sets a link's destination
 * @author Javier San Andrés
 * @param link pointer to the link
 * @param destination id of the destination to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS link_set_destination(Link *link, Id destination);


/**
 * @brief It sets a link's direction
 * @author Javier San Andrés
 * @param link pointer to the link
 * @param direction direction to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS link_set_direction(Link *link, DIRECTION direction);


/**
 * @brief It sets a status to the link
 * @author Javier San Andrés
 * @param link pointer to the link
 * @param status status of the link to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS link_set_status(Link *link, LSTATUS status);


/**
 * @brief It gets the link's origin
 * @author Javier San Andrés
 * @param link pointer to the link
 * @return Id of the link's origin
 */
Id link_get_origin(Link *link);


/**
 * @brief It gets the link's destination
 * @author Javier San Andrés
 * @param link pointer to the link
 * @return Id of the link's destination
 */
Id link_get_destination(Link *link);


/**
 * @brief It gets the link's direction
 * @author Javier San Andrés
 * @param link pointer to the link
 * @return direction of the link
 */
DIRECTION link_get_direction(Link *link);


/**
 * @brief It gets the link's status
 * @author Javier San Andrés
 * @param link pointer to the link
 * @return status of the link
 */
LSTATUS link_get_status(Link *link);


/**
 * @brief It prints the link's information
 * @author Javier San Andres 
 * This function shows the link's id, name, origin, destination, direction and status
 * @param link A pointer to the link
 * @param file Output file where it will be printed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS link_print(Link *link, FILE *file);

#endif