/**
 * @brief It defines the game management interface
 *
 * @file game_management.h
 * @author Javier San Andrés - Alejandro García Hernando -Diego Rodriguez -David Brenchley
 * @version 3.0
 * @date 04-04-2023
 * @copyright GNU Public License
 */

#ifndef GAME_MANAGEMENT_H
#define GAME_MANAGEMENT_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "game.h"
#include "rule.h"
#include "enemy.h"
#include "dialogue.h"
#include <time.h>

/*LOADING FUNCTION*/

/**
 * @brief Given a game it loads the game from a file
 * @author David Brenchley Uriol
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
STATUS game_management_load(Game *game, char*filename);

/*SAVING FUNCTION*/

/**
 * @brief Given a game it saves the game into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param filename  name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
STATUS game_management_save(Game *game, char*filename);




#endif
