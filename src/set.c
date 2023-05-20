/**
 * @brief It implements the set's module
 *
 * @file set.c
 * @author David Brenchley
 * @version 3.0
 * @date 19/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

#define TAM 5        /*!<Initial size for the set*/
#define MULT 2       /*!<Size multiplier for each resizing*/

/**
 * @brief Set
 *
 * This struct stores all the information of a set.
 */
struct _Set
{
    Id *IDs;        /*!<Pointer to the array of ids in the set*/
    int nId;        /*!<Number of ids in the set*/
    int size;       /*!<Current maximum size of the set*/
};


/**
 * @brief Tells if the set is full
 * @author David Brenchley
 * @param s Pointer to the set
 * @return True if the set is full or NULL, False if the set is not full
 */
BOOL _set_is_full(Set *s);


Set *set_create()
{
    Set *s = NULL;
    int i = 0;

    if ((s = (Set *)malloc(sizeof(Set))) == NULL)
        return NULL;

    if ((s->IDs = (Id *)malloc(TAM * sizeof(Id))) == NULL)
    {
        free(s);
        return NULL;
    }

    for (i = 0; i < TAM; i++)
    {
        s->IDs[i] = NO_ID;
    }

    s->nId = 0;
    s->size = TAM;

    return s;
}

void set_destroy(Set *s)
{
    if(!s)
        return;
    free(s->IDs);
    free(s);
}

BOOL set_is_empty(Set *s)
{
    if (s == NULL)
        return TRUE;

    if (s->nId == 0)
        return TRUE;

    return FALSE;
}

BOOL _set_is_full(Set *s)
{
    if (s == NULL)
        return TRUE;

    if (s->nId == s->size)
        return TRUE;

    return FALSE;
}

STATUS set_add_id(Set *s, Id id)
{
    Id *temp;
    int i;

    if (s == NULL || id == NO_ID)
        return ERROR;

    if (set_contains_id(s, id) == TRUE)
        return OK;

    if (_set_is_full(s) == FALSE)
    {
        s->IDs[s->nId] = id;
        s->nId++;
    }
    else
    {
        if ((temp = (Id *)realloc(s->IDs, MULT * s->size * sizeof(Id))) == NULL)
            return ERROR;
        
        s->IDs = temp;

        for (i = s->size; i < s->size * MULT; i++)
            s->IDs[i] = NO_ID;

        s->size = s->size * MULT;

        s->IDs[s->nId] = id;
        s->nId++;

        return OK;
    }

    return OK;
}

STATUS set_massive_add(Set *s, Id *ids, int num_ids)
{
    int i = 0;
    STATUS st = OK;
    if (s == NULL || ids == NULL || num_ids <= 0)
        return ERROR;

    for (i = 0; i < num_ids && st == OK; i++)
    {
        st = set_add_id(s, ids[i]);
    }

    return st;
}

STATUS set_delete_id(Set *s, Id id)
{
    int i = 0;

    if (s == NULL || id == NO_ID)
        return ERROR;

    if (set_is_empty(s) == TRUE)
        return OK;

    for (i = 0; i < s->nId; i++)
    {
        if (s->IDs[i] == id)
        {
            s->IDs[i] = s->IDs[s->nId - 1];
            s->IDs[s->nId - 1] = NO_ID;
            s->nId--;

            return OK;
        }
    }

    return OK;
}

int set_get_number_ids(Set *s)
{
    if (s == NULL)
        return -1;

    return s->nId;
}

BOOL set_contains_id(Set *s, Id id)
{
    int i;
    if (s == NULL || id == NO_ID)
    {
        return FALSE;
    }

    for (i = 0; i < s->nId; i++)
    {
        if (s->IDs[i] == id)
            return TRUE;
    }

    return FALSE;
}

Id *set_get_all_ids(Set *s, int *num)
{
    int i;
    Id *arr;

    if (s == NULL || num == NULL)
    {
        return NULL;
    }

    if (set_is_empty(s))
    {
        *num = 0;
        return NULL;
    }

    *num = s->nId;
    if ((arr = (Id *)malloc((long) s->nId * sizeof(Id))) == NULL)
    {
        *num = -1;
        return NULL;
    }

    for (i = 0; i < s->nId; i++)
    {
        arr[i] = s->IDs[i];
    }

    return arr;
}

STATUS set_print(Set *s, FILE *f)
{
    int i;

    if (s == NULL || f == NULL)
    {
        return ERROR;
    }

    fprintf(f, "\tSet's size: %d, Set's number of current Ids: %d",  s->size, s->nId);

    for (i = 0; i < s->nId; i++)
    {   
        if(i==0)
            fprintf(f,", Ids:");
        fprintf(f, " %ld", s->IDs[i]);
    }
    fprintf(f,"\n");

    return OK;
}