/**
 * @brief It defines the player interface
 *
 * @file player.h
 * @author Javier San Andrés
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#include "types.h"
#include "inventory.h"

#ifndef PLAYER_H
#define PLAYER_H

#define TYPEPLAYERS 6 /*!<Number of types of players*/
#define TAMPLAYER 4   /*!<Number of characters the player has */

#define EXTRASCORP 10  /*!<Number of extra damage the scorpion deals */
#define EXTRASNAIL 2  /*!<Number of extra spaces the snail has */
#define EXTRASANT 5   /*!<Number of extra grounds the ant has */

/**
 * @brief Player types
 */
typedef enum enum_playerType
{
    UNDEFPLY,
    SCORPION,       /*!<Deals more damage per attack */
    SNAIL,          /*!<Can hold more objects */
    FIREFLY,        /*!<Can see in the dark spaces without a torch */
    ANT,            /*!<Can repair the flodded space */
    BUTTERFLY            /*!<Can leave without taking the leave */
} T_PlayerType;

/**
 * @brief Player structure
 *
 */
typedef struct _Player Player;


/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Javier San Andres
 * @param id The identification number for the new player
 * @return A pointer to the player or NULL if error
 */
Player *player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Javier San Andres
 * @param player A pointer to the player that must be destroyed
 */
void player_destroy(Player *player);

/**
 * @brief It gets the id of a player
 * @author Javier San Andres
 * @param player A pointer to the player
 * @return The id of the player or NO_ID if error
 */
Id player_get_id(Player *player);

/**
 * @brief It sets the name of a player
 * @author Javier San Andres 
 * @param player A pointer to the player
 * @param name A string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_set_name(Player *player, char *name);

/**
 * @brief It gets the name of a player
 * @author Javier San Andres
 * @param player A pointer to the player
 * @return  A string with the name of the player or NULL if error
 */
const char *player_get_name(Player *player);

/**
 * @brief It gets the current location of the player
 ** @author Javier San Andres 
 * @param player A pointer to the player
 * @return The id of its current location or NO_ID if error
 */
Id player_get_location(Player *player);

/**
 * @brief It sets the location of a player
 * @author Javier San Andres
 * @param player A pointer to the player
 * @param id The id of the space where the player will be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_set_location(Player *player, Id id);

/**
 * @brief It gets the number of life points of the player
 * @author Javier San Andres 
 * @param player A pointer to the player
 * @return The player's life points or -1 if error
 */
int player_get_health(Player *player);

/**
 * @brief It associates a player to a certain number of life points
 * @author Javier San Andres 
 * @param player A pointer to the player
 * @param health Number of life points to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_set_health(Player *player, int health);

/**
 * @brief It gets whether the player has an object
 * @author Diego Rodríguez
 * @param player A pointer to the player
 * @param obj the id of the object you want to check
 * @return TRUE if the player has the object, FLASE otherwise 
 */
BOOL player_has_object(Player *player, Id obj);

/**
 * @brief It gets the pointer of the objects held by the player
 * @author Javier San Andres
 * @param player A pointer to the player
 * @param num A pointer to a variable to save the number of objects
 * @return The pointer of the array of the objects' Ids held by the player or NULL if error
 */
Id *player_get_objects(Player *player, int *num);

/**
 * @brief It adds an object to the player's inventory
 * @author Javier San Andres
 * @param player A pointer to the player
 * @param id Id of the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_add_object(Player *player, Id id);

/**
 * @brief It removes an object to the player's inventory
 * @author Javier San Andres
 * @param player A pointer to the player
 * @param id A pointer to the id of the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_remove_object(Player *player, Id id);

/**
 * @brief It sets the max number of object that the player can hold
 * @author Javier San Andres
 * @param player A pointer to the player
 * @param max Number of objects that the player can hold
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_set_max_objects(Player *player, int max);

/**
 * @brief It gets the max number of object that the player can hold
 * @author Javier San Andres
 * @param player A pointer to the player
 * @return It gets the max number of object that the player can hold
 */
int player_get_max_objects(Player *player);

/**
 * @brief It gets the  number of object that the player holds
 * @author Javier San Andres 
 * @param player A pointer to the player
 * @return It gets the max number of object that the player can hold
 */
int player_get_num_objects(Player *player);

/**
 * @brief It prints the information
 * @author Javier San Andres 
 * This function shows the player's id, name, location and the object he holds
 * @param player A pointer to the player
 * @param file Output file where it will be printed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_print(Player *player, FILE *file);

/**
 * @brief It gets the type of the player
 * @author Aljandro García
 * @param player A pointer to the player
 * @return The player's type or -1 if error
 */
int player_get_type(Player *player);

/**
 * @brief It gets the type of the player
 * @author Alejandro García
 * @param player A pointer to the player
 * @param type Number of life points to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS player_set_type(Player *player, T_PlayerType type);

#endif
