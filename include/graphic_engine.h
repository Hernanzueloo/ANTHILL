/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author David Brenchley
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "types.h"
#include "command.h"
#include "space.h"
#include "game.h"

#include "libscreen.h"

/**
 * @brief Graphic_engine struct
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Creates the graphic engine
 * @author David Brenchley
 * @return Pointer to the graphic engine or NULL if an error occurs
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Destroys the graphic engine adn frees it`s resources
 * @author David Brenchley
 * @param ge Pointer to the grahics engine
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief  Paints the game to the screen
 * @author David Brenchley
 * @param ge Pointer to the grahics engine
 * @param game Pointer to the game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
 * @brief  Paints the beggining of the game to the screen
 * @author Alejandro García
 * @param ge Pointer to the grahics engine
 * @param game Pointer to the game
 */
void graphic_engine_paint_init(Graphic_engine *ge, Game *game);


/**
 * @brief  Paints the game to the screen
 * @author David Brenchley
 * @param ge Pointer to the grahics engine
 * @param game Pointer to the game
 */
void graphic_engine_paint_win(Graphic_engine *ge, Game *game);

/**
 * @brief  Paints the game to the screen
 * @author David Brenchley
 * @param ge Pointer to the grahics engine
 * @param game Pointer to the game
 */
void graphic_engine_paint_lose(Graphic_engine *ge, Game *game);


#endif
