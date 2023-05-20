/**
 * @brief It defines the enemy interface
 *
 * @file enemy.h
 * @author Alejandro García Hernando
 * @version 3.0
 * @date 23-03-2023
 * @copyright GNU Public License
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

/**
 * @brief Enemy struct 
 */
typedef struct _Enemy Enemy;

/**
 * @brief It creates a new Enemy, allocating memory and initializing its members
 * @author Alejandro García Hernando
 * @param id the identification number for the new Enemy
 * @return a new Enemy, initialized
 */
Enemy *enemy_create(Id id);

/**
 * @brief It destroys a Enemy, freeing the allocated memory
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_destroy(Enemy *enemy);

/**
 * @brief It gets the id of a Enemy
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @return the id of Enemy
 */
Id enemy_get_id(Enemy *enemy);

/**
 * @brief It sets the name of a Enemy
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_set_name(Enemy *enemy, char *name);

/**
 * @brief It gets the name of a Enemy
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @return  a string with the name of the Enemy
 */
const char *enemy_get_name(Enemy *enemy);

/**
 * @brief It sets the location of a Enemy
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @param location an Id with the location to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_set_location(Enemy *enemy, Id location);

/**
 * @brief It gets the location of a Enemy
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @return  an Id with the location of the Enemy
 */
Id enemy_get_location(Enemy *enemy);

/**
 * @brief It sets the health the enemy has
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @param health number of health points
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_set_health(Enemy *enemy, int health);

/**
 * @brief It gets the health the enemy has
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @return the health points, if everything goes well or -1 if there was some mistake
 */
int enemy_get_health(Enemy *enemy);

/**
 * @brief It gets the edesc the enemy has
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @return the pointer edesc, if everything goes well or NULL if there was some mistake
 */
char* enemy_get_edesc(Enemy *enemy);

/**
 * @brief It sets the edesc the enemy has
 * @author Alejandro García Hernando
 * @param enemy a pointer to the Enemy
 * @param desc a pointer to the edesc
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_set_edesc(Enemy *enemy,char *desc);


/**
 * @brief It prints the Enemy information
 * @author Alejandro García Hernando
 * This function shows the Enemy.
 * @param enemy a pointer to the Enemy
 * @param file a pointer to a file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS enemy_print(Enemy *enemy, FILE *file);

#endif