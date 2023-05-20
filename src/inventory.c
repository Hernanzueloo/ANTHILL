/**
 * @brief It implements the inventory module
 *
 * @file inventory.c
 * @author Alejandro Garcia
 * @version 3.0
 * @date 17/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"

/**
 * @brief Inventory
 *
 * This struct stores all the information of a inventory.
 */
struct _Inventory
{
    Set *objs;        /*!<Pointer to the set which contains the objects of the inventory*/
    int max_objs;     /*!<Maximum number of objects which the inventory can have*/
};


/**
 * @brief Tells if the inventory is full
 * @author Alejandro García Hernando
 * @param inv Pointer to the inventory
 * @return True if the inventory is full or NULL, False if the inventory is not full
 */
BOOL _inventory_is_full(Inventory *inv);


Inventory *inventory_create()
{
    Inventory *inv = NULL;

    inv = (Inventory *)malloc(sizeof(Inventory));
    if (inv == NULL)
        return NULL;

    inv->objs = set_create();
    if (inv->objs == NULL)
    {
        free(inv);
        return NULL;
    }

    inv->max_objs = MAX_OBJS_INIT;

    return inv;
}

void inventory_destroy(Inventory *inv)
{
    set_destroy(inv->objs);
    free(inv);
}

BOOL inventory_is_empty(Inventory *inv)
{
    if (inv == NULL)
        return TRUE;

    return set_is_empty(inv->objs);
}

BOOL _inventory_is_full(Inventory *inv)
{
    if (inv == NULL)
        return TRUE;

    if (set_get_number_ids(inv->objs) == inv->max_objs)
        return TRUE;

    return FALSE;
}

STATUS inventory_add_id(Inventory *inv, Id id)
{
    if (inv == NULL || id == NO_ID)
        return ERROR;

    if (_inventory_is_full(inv) == TRUE)
        return ERROR;
    
    return set_add_id(inv->objs, id);
}

STATUS inventory_delete_id(Inventory *inv, Id id)
{
    if (inv == NULL || id == NO_ID)
        return ERROR;

    return set_delete_id(inv->objs, id);
}

int inventory_get_number_ids(Inventory *inv)
{
    if (inv == NULL)
        return -1;

    return set_get_number_ids(inv->objs);
}

BOOL inventory_contains_id(Inventory *inv, Id id)
{
    if (inv == NULL)
        return FALSE;

    return set_contains_id(inv->objs, id);
}

Id *inventory_get_all_ids(Inventory *inv, int *num)
{
    if (inv == NULL)
        return NULL;

    return set_get_all_ids(inv->objs, num);
}


int inventory_get_max_objs(Inventory *inv)
{
    if (!inv)
    {
        return -1;
    }

    return inv->max_objs;
}

STATUS inventory_set_max_objs(Inventory *inv, int newMaxObjs)
{
    if (inv == NULL)
    {
        return ERROR;
    }
    if (inventory_get_number_ids(inv) > newMaxObjs)
    {
        return ERROR;
    }

    inv->max_objs = newMaxObjs;

    return OK;
}


STATUS inventory_print(Inventory *inv, FILE *f)
{
    if (inv == NULL || f == NULL)
        return ERROR;

    fprintf(f, "\tInventory's maximum number of objects: %d\n", inv->max_objs);

    return set_print(inv->objs, f);
}