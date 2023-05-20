/**
 * @brief It implements the link' module
 *
 * @file link.c
 * @author Javier San Andrés
 * @version 3.0
 * @date 17/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link.h"

/**
 * @brief Link
 *
 * This struct stores all the information of a link.
 */
struct _Link
{
    Id id;                           /*!<Id of the link*/
    char name[WORD_SIZE + 1];        /*!<String with the name of the link*/ 
    Id origin;                       /*!<Id of the space of origin*/
    Id destination;                  /*!<Id of the space of destination*/
    DIRECTION direction;             /*!<Direction of the link*/
    LSTATUS status;                  /*!<Status of the link*/
};

Link *link_create(Id id)
{
    Link *link;

    if (id == NO_ID)
        return NULL;

    if ((link = (Link *)malloc(sizeof(Link))) == NULL)
        return NULL;

    link->id = id;
    link->name[0] = '\0';
    link->origin = NO_ID;
    link->destination = NO_ID;
    link->direction = NO_DIR;
    link->status = CLOSE;

    return link;
}

void link_destroy(Link *link)
{
    if(link)
        free(link);
}

STATUS link_set_name(Link *link, char *name)
{
    if (link == NULL || name == NULL)
        return ERROR;

    if (strcpy(link->name, name) == 0)
        return ERROR;

    return OK;
}

STATUS link_set_origin(Link *link, Id origin) 
{
    if (link == NULL || origin == NO_ID)
        return ERROR;

    link->origin = origin;
    return OK;
}

STATUS link_set_destination(Link *link, Id destination)
{
    if (link == NULL || destination == NO_ID)
        return ERROR;

    link->destination = destination;
    return OK;
}

STATUS link_set_direction(Link *link, DIRECTION direction)
{
    if (link == NULL || direction == NO_DIR)
        return ERROR;

    link->direction = direction;
    return OK;
}

STATUS link_set_status(Link *link, LSTATUS status)
{
    if (link == NULL)
        return ERROR;

    link->status = status;
    return OK;
}

Id link_get_id(Link *link)
{
    if (link == NULL)
        return NO_ID;
    
    return link->id;
}

char *link_get_name(Link *link)
{
    if (link == NULL)
        return NULL;

    return link->name;
}

Id link_get_origin(Link *link)
{
    if (link == NULL)
        return NO_ID;

    return link->origin;
}

Id link_get_destination(Link *link)
{
    if (link == NULL)
        return NO_ID;

    return link->destination;
}

DIRECTION link_get_direction(Link *link)
{
    if (link == NULL)
        return NO_DIR;

    return link->direction;
}

LSTATUS link_get_status(Link *link)
{
    if (link == NULL)
        return CLOSE;

    return link->status;
}

STATUS link_print(Link *link, FILE *file)
{
    if (link == NULL || file == NULL)
            return ERROR;

    /* 1. Prints the id, name, origin, destination, direction and status of the link*/

    fprintf(file, "--> Link (Id: %ld; Name: %s; Origin: %ld; Destination: %ld; Direction: %d; Status: %d)\n", link->id, link->name, link->origin, link->destination, link->direction, link->status);

    return OK;
}