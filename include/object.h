/**
 * @brief It defines the object interface
 *
 * @file object.h
 * @author David Brenchley Uriol
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/**
 * @brief Object structure
 *
 */
typedef struct _Object Object;

#define N_OBJ_TYPES 8 /*!< Number of object types*/

/**
 * @brief Object types
 */
typedef enum enum_ObjectType
{
    NO_OTYPE=-1,
    STICK,          /*!<Stick type */
    LEAF,          /*!<Leaf type */
    WALNUT,        /*!<Walnut type */
    KEY,            /*!<Key type */
    GOLDKEY,        /*!<Goldkey type */
    LANTERN,        /*!<Lantern type */
    GROUND,          /*!<Ground type */
    SPECIAL         /*!<Special type */
} T_ObjectType;

/**
 * @brief It creates a new object, allocating memory and initializing its members
 * @author David Brenchley Uriol
 * @param id The identification number for the new object
 * @return Pointer to the new object or NULL if error
 */
Object *object_create(Id id);

/**
 * @brief It destroys an object, freeing the allocated memory
 * @author David Brenchley Uriol
 * @param obj A pointer to the object that must be destroyed
 */
void object_destroy(Object *obj);


/**
 * @brief It gets the id of an object
 * @author David Brenchley Uriol
 * @param obj A pointer to the object
 * @return The id of the object or NO_ID if error
 */
Id object_get_id(Object *obj);


/**
 * @brief It sets the name of an object
 * @author David Brenchley Uriol
 * @param obj A pointer to the object
 * @param name A string with the name to be store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_name(Object *obj, char *name);


/**
 * @brief It gets the name of an object
 * @author David Brenchley Uriol
 * @param obj A pointer to the object
 * @return A string with the name of the object or NULL if error
 */
char *object_get_name(Object *obj);


/**
 * @brief It gets the location of an object
 * @author David Brenchley Uriol
 * @param obj A pointer to the object
 * @return Id of the space where the object is located or NO_ID if error
 */
Id object_get_location(Object *obj);

/**
 * @brief It sets the location of an object
 * @author David Brenchley Uriol
 * @param obj A pointer to the object
 * @param id  The id of the space where the object will be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_location(Object *obj, Id id);

/**
 * @brief It sets if an object is hidden or not
 * @author Alejandro García
 * @param obj A pointer to the object
 * @param hidden The value to be given to hidden
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_hidden(Object *obj, BOOL hidden);

/**
 * @brief  It gets if an object is hidden or not
 * @author Alejandro García
 * @param obj A pointer to the object
 * @return TRUE if the object is hidden, FALSE in other cases
 */
BOOL object_get_hidden(Object *obj);

/**
 * @brief It sets if an object is movable or not
 * @author Alejandro García
 * @param obj A pointer to the object
 * @param movable The value to be given to movable
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_movable(Object *obj, BOOL movable);

/**
 * @brief  It gets if an object is movable or not
 * @author Alejandro García
 * @param obj A pointer to the object
 * @return TRUE if the object is movable, FALSE in other cases
 */
BOOL object_get_movable(Object *obj);

/**
 * @brief It sets the dependency on an object
 * @author Alejandro García
 * @param obj A pointer to the object
 * @param dependency The ID of the objects it depends on
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_dependency(Object *obj, Id dependency);

/**
 * @brief  It gets the dependency on an object
 * @author Alejandro García
 * @param obj A pointer to the object
 * @return The ID on the object it depends on, NO_ID in other cases
 */
Id object_get_dependency(Object *obj);

/**
 * @brief It sets the link it can open
 * @author Alejandro García
 * @param obj A pointer to the object
 * @param open The ID of the space it opens
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_open(Object *obj, Id open);

/**
 * @brief  It gets the link it can open
 * @author Alejandro García
 * @param obj A pointer to the object
 * @return The ID of the link it opens, NO_ID in case of error
 */
Id object_get_open(Object *obj);

/**
 * @brief  It dets the type of the object
 * @author Alejandro García
 * @param object A pointer to the object
 * @param type A object type
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_type(Object *object, T_ObjectType type);

/**
 * @brief  It gets the type of the object
 * @author Alejandro García
 * @param object A pointer to the object
 * @return The object type
 */
T_ObjectType object_get_type(Object *object);

/**
 * @brief It sets if the object can illuminate
 * @author Alejandro García
 * @param obj A pointer to the object
 * @param illuminate If it opens or not
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_illuminate(Object *obj, BOOL illuminate);

/**
 * @brief It gets if the object can illuminate
 * @author Alejandro García
 * @param obj A pointer to the object
 * @return TRUE if it illuminates, FALSE in other cases
 */
BOOL object_get_illuminate(Object *obj);

/**
 * @brief It sets if the object is turned on
 * @author Alejandro García
 * @param obj A pointer to the object
 * @param turnedon If it is turned on or not
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_turnedon(Object *obj, BOOL turnedon);

/**
 * @brief It gets if the object can illuminate
 * @author Alejandro García
 * @param obj A pointer to the object
 * @return TRUE if it is turned on, FALSE in other cases
 */
BOOL object_get_turnedon(Object *obj);

/**
 * @brief It gets the description of an object
 * @author David Brenchley Uriol
 * @param obj A pointer to the object
 * @return Pointer to the description;
 */
char *object_get_tdesc(Object *obj);

/**
 * @brief It sets the description of an object
 * @author David Brenchley Uriol
 * @param obj A pointer to the object
 * @param tdescr Pointer to the description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_set_tdesc(Object *obj, char * tdescr);

/**
 * @brief It prints the object's information
 * @author David Brenchley Uriol
 * This function shows the id, name and the objects location.
 * @param obj A pointer to the object
 * @param file Output file where it will be printed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS object_print(Object *obj, FILE *file);

/**
 * @brief It translates the object type
 * @author Diego Rodriguez
 * @param obj object type
 * @return a string with the object name
 */
char* object_translate_object_type_to_string(T_ObjectType obj);

/**
 * @brief It yranslates a sting into a object type
 * @author Diego Rodríguez
 * @param object_name a string to the object type name
 * @return The object type
 */
T_ObjectType object_translate_object_type(char *object_name);
#endif
