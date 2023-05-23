/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author David Brenchley
 * @version 2.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "object.h"

/**
 * @brief Object
 *
 * This struct stores all the information of an object.
 */
struct _Object
{
    Id id;                    /*!< Id number of the object, it must be unique */
    char name[WORD_SIZE + 1]; /*!< Name of the object */
    Id location;              /*!< Id of the object's location */
    BOOL hidden;              /*!< Boolean that states if the object is hidden or not*/
    BOOL movable;             /*!< Boolean that states if the object is movable or not*/
    Id dependency;            /*!< Id of the pointer it dependson*/
    Id open;                  /*!< Boolean that states if the object can open links or not*/
    T_ObjectType type;         /*!< Object type*/
    BOOL illuminate;          /*!< Boolean that states if the object can light up spaces or not*/
    BOOL turnedon;            /*!< Boolean that states if the object is turned on or not*/
    char *tdescr;             /*!< Pointer that will hold textual description*/
};


/**
 * @brief Array of possible object types
 */
char *object_type_to_str[N_OBJ_TYPES-NO_OTYPE] = {"no object type",
                                  "Stick",
                                  "Leaf",
                                  "Walnut",
                                  "Key",
                                  "Goldkey",
                                  "Lantern",
                                  "Ground",
                                  "Special"};

/**
 * @brief It yranslates a sting into a object type
 * @author Diego Rodríguez
 * @param object_name a string to the object type name
 * @return The object type
 */
T_ObjectType object_translate_object_type(char *object_name);

Object *object_create(Id id)
{
    Object *obj;

    if (id == NO_ID)
        return NULL;

    if ((obj = (Object *)malloc(sizeof(Object))) == NULL)
        return NULL;

    /* Initialization of an empty object*/
    obj->id = id;
    obj->name[0] = '\0';
    obj->tdescr = NULL; /*Initialized when setting descriptor*/
    obj->location = NO_ID;
    obj->hidden = FALSE;
    obj->movable = TRUE;
    obj->dependency = NO_ID;
    obj->open = NO_ID;
    obj->illuminate = FALSE;
    obj->turnedon = FALSE;


    return obj;
}

void object_destroy(Object *obj)
{
    if(!obj)
        return;
    free(obj->tdescr);
    free(obj);
}

Id object_get_id(Object *obj)
{
    if (obj == NULL)
        return NO_ID;

    return obj->id;
}

STATUS object_set_name(Object *obj, char *name)
{
    if (obj == NULL || name == NULL || strcasecmp(name, "s") == 0 || strcasecmp(name, "space") == 0)
        return ERROR;

    if (strcpy(obj->name, name) == 0)
        return ERROR;

    return object_set_type(obj,object_translate_object_type(name));
}

char *object_get_name(Object *obj)
{
    if (obj == NULL)
        return NULL;

    return obj->name;
}

Id object_get_location(Object *obj)
{
    if (obj == NULL)
        return NO_ID;

    return obj->location;
}

STATUS object_set_location(Object *obj, Id id)
{
    if (obj == NULL || id == NO_ID)
        return ERROR;

    obj->location = id;

    return OK;
}

STATUS object_set_hidden(Object *object, BOOL hidden)
{
    if (object == NULL)
        return ERROR;

    object->hidden = hidden;
    return OK;
}

BOOL object_get_hidden(Object *object)
{
    if (object == NULL)
        return FALSE;

    return object->hidden;
}

STATUS object_set_movable(Object *object, BOOL movable)
{
    if (object == NULL)
        return ERROR;

    object->movable = movable;
    return OK;
}

BOOL object_get_movable(Object *object)
{
    if (object == NULL)
        return FALSE;

    return object->movable;
}

STATUS object_set_dependency(Object *object, Id dependency)
{
    if (object == NULL)
        return ERROR;

    object->dependency = dependency;
    return OK;
}

Id object_get_dependency(Object *object)
{
    if (object == NULL)
        return NO_ID;

    return object->dependency;
}

STATUS object_set_open(Object *object, Id open)
{
    if (object == NULL)
        return ERROR;

    object->open = open;
    return OK;
}

Id object_get_open(Object *object)
{
    if (object == NULL)
        return NO_ID;

    return object->open;
}

STATUS object_set_type(Object *object, T_ObjectType type)
{
    if (object == NULL)
        return ERROR;

    object->type = type;

    return OK;
}

T_ObjectType object_get_type(Object *object)
{
    if (object == NULL)
        return NO_ID;

    return object->type;
}

STATUS object_set_illuminate(Object *object, BOOL illuminate)
{
    if (object == NULL)
        return ERROR;

    object->illuminate = illuminate;
    return OK;
}

BOOL object_get_illuminate(Object *object)
{
    if (object == NULL)
        return FALSE;

    return object->illuminate;
}

STATUS object_set_turnedon(Object *object, BOOL turnedon)
{
    if (object == NULL)
        return ERROR;

    object->turnedon = turnedon;
    return OK;
}

BOOL object_get_turnedon(Object *object)
{
    if (object == NULL)
        return FALSE;

    return object->turnedon;
}

char *object_get_tdesc(Object *obj)
{
    if (obj == NULL)
        return NULL;

    return obj->tdescr;
}

STATUS object_set_tdesc(Object *obj, char *tdescr)
{
    int len;

    if (obj == NULL || tdescr == NULL)
        return ERROR;

    len = strlen(tdescr);

    if ((obj->tdescr = (char *)malloc((len + 1) * sizeof(char))) == NULL)
        return ERROR;

    strcpy(obj->tdescr, tdescr);

    return OK;
}

STATUS object_print(Object *obj, FILE *file)
{

    if (obj == NULL || file == NULL)
        return ERROR;

    /* 1. Print the id, the name, and either the id of the space it's located or ON_PLAYER*/

    if (obj->location != ON_PLAYER)
        fprintf(file, "--> Object (Id: %ld; Name: %s; Location: %ld )", obj->id, obj->name, obj->location);
    else
        fprintf(file, "--> Object (Id: %ld; Name: %s; Location: ON_PLAYER(%d) )", obj->id, obj->name, ON_PLAYER);

    if (object_get_tdesc(obj) != NULL)
    {
        fprintf(file, "  %s\n", object_get_tdesc(obj));
    }
    else
    {
        fprintf(file, "  There's no textual descriptor\n");
    }

    return OK;
}

T_ObjectType object_translate_object_type(char *object_name)
{
    T_ObjectType otype = NO_OTYPE;
    int i = NO_OTYPE;
    if (!object_name)
        return otype;

    while (otype == NO_OTYPE && i < N_OBJ_TYPES+NO_OTYPE)
    {
        if (!strncasecmp(object_name, object_type_to_str[i-NO_OTYPE], strlen(object_name)))
            otype = i;
        i++;
    }

    if(!strncasecmp(BOAT, object_name,strlen(BOAT)) || !strncasecmp("Boat", object_name,4) ||!strcasecmp("Magicalkey", object_name)){
        otype = SPECIAL;
    }

    return otype;
}


char * object_translate_object_type_to_string(T_ObjectType obj){
    return object_type_to_str[obj-NO_OTYPE];
}
