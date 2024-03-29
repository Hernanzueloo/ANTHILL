/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author David Brenchley - Javier San Andrés
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H


#define WORD_SIZE 1000  /*!< Maximum word size for strings */ 

#define NO_ID -1        /*!< NO_ID values */ 

#define NO_TYPE -1      /*!< value for no_type player */

#define ON_PLAYER -2    /*!< ID for when an object is on a player */ 

#define NO_HEALTH -1   /*!< NO_HEALTH value */

#define INITIAL_LP 2    /*!< Initial number of Life Points of any player and enemy*/

#define MAX_OBJECTS 100   /*!< Maximum number of objects that a can be in a game*/

#define MAX_LINKS 100     /*!<Maximum number of links in a game*/

#define MAX_SPACES 100      /*!< Maximum number of game spaces */

#define MAX_ENEMIES 20      /*!< Maximum number of game enemies */

#define MAX_RULES 600      /*!< Maximum number of game rules */

#define MAX_DIALOGUES 50    /*!< Maximum number of game dialogues */

#define GRAPHIC_ROWS 6      /*!< Number of rows of the space's graphical descriptor */

#define GRAPHIC_COLS 14     /*!< Number of columns of the space's graphical descriptor */

#define REPEATED_ERROR_ID 14  /*!< Id for the dialogue with the rules in case of repeated errors */

#define GROUND_NAME "Ground"  /*!< Name of the objects that represent gorund*/

#define GROUND_DESCRIPTION "It allows you to secure a flooded space"  /*!< Textual description of the objects that represent ground*/

#define N_UPGRADES 2 /*!< Number of upgrades a object can have*/

#define NOT_UPGRADED 0 /*!< Number that indicates that an object has not been upgraded*/

#define UPGRADED 1  /*!< Number that indicates that an object has been upgraded*/
 
#define WORKSHOP "The Workshop"  /*!<Name of the workshop*/

#define BOAT "ANTBOAT"  /*!<Name of the boat*/

#define HARBOUR "Harbour"    /*!<Name of the harbour*/

#define PROB_VICT_ATACK 6 /*!<Probability of attacking an enemy succesfully (1 to 10)*/

#define MAX_GROUND 70  /*!<Maximum number of grounds to be spawned*/

#define NUM_FINISHES 8   /*Number of diferent finishes for the game*/

#define RANDLOC -3 /*!<The object will be assigned a random location*/

#define SUSPICIOUS "Suspicious" /*!<The initial letters that a space with hidden objects must have in its description*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Id data type 
 */
typedef long Id;

/**
 * @brief Bool data type False-True
 */
typedef enum
{
  FALSE,  /*!< False value */
  TRUE    /*!< True value*/
} BOOL;

/**
 * @brief Status data type Error-OK
 */
typedef enum
{
  ERROR,    /*!< Error value */
  OK        /*!< OK value*/
} STATUS;

/**
 * @brief State data type Error-OK
 */

typedef enum
{
  SAFE,    /*!< Space is safe */
  FLOODED,  /*!< Space is flooded*/
  SUNK        /*!< Space is sunk*/
} SSTATUS;

/**
 * @brief Status data type OPEN-CLOSE
 */
typedef enum
{
  CLOSE,      /*!< Value for a close link */
  OPEN        /*!< Value for an open link */
} LSTATUS;

/**
 * @brief Status data type SUCCESS-FAILURE
 */
typedef enum
{
  FAILURE,       /*!< Value for an error dialogue rule*/
  SUCCESS        /*!< Value for a success dialogue rule */

} DTYPE;

/**
 * @brief Status data type SUCCESS-FAILURE
 */
typedef enum
{
  VICTORY = -200,       /*!< Value for a Victory finish*/
  DEATH,                /*!< Value for a DEATH finish*/
  STICK_NO_ACC,         /*!< Value for a STICKS NO ACCESIBLE therefore defeat*/
  LEAF_NO_ACC,          /*!< Value for a LEAFS NO ACCESIBLE therefore defeat*/
  WALNUT_NO_ACC,        /*!< Value for a WALNUTS NO ACCESIBLE therefore defeat*/
  BOAT_NO_ACC,          /*!< Value for a BOAT_PARTS NO ACCESIBLE therefore defeat*/
  HARBOUR_NO_ACC,        /*!< Value for a HARBOUR NO ACCESIBLE therefore defeat*/
  WORKSHOP_NO_ACC,       /*!< Value for a WHORKSHOP NO ACCESIBLE and Boat not build therefore defeat*/

} END_TYPE;

/**
 * @brief Cardinality directions N,S,E,W,U,D
 */
typedef enum
{
  NO_DIR = -1,
  NORTH,    /*!< North value*/
  SOUTH,    /*!< South value*/
  EAST,     /*!< East value*/
  WEST,     /*!< West value*/
  UP,       /*!< Up value*/
  DOWN      /*!< Down value*/
} DIRECTION;

#endif
