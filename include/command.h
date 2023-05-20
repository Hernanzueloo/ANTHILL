/**
 * @brief It implements the command interpreter interface
 *
 * @file command.h
 * @author David Brenchley - Javier San Andrés
 * @version 3.0
 * @date 10/03/2023
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2             /*!<Number of ways to reference a command*/
#define N_CMD 15             /*!<Number of commands */

#define N_DIRT 2              /*!<Number of ways to reference a direction*/
#define N_DIR 6              /*!<Number of directions */

#define CMD_LENGTH 300        /*!<Maximum length of the commands*/
#define CMD_NARGS 3           /*!<Maximum number of the arguments for each command*/
#define CMD_ARG_LEN 200       /*!<Maximum lenth of each argument for a command*/

#define DELIMITATORS " \n"   /*!<Command argument delimitators*/

/**
 * @brief Command struct 
 */
typedef struct _Commands Commands;

/**
 * @brief Command types 
 */
typedef enum enum_CmdType
{
  CMDS,       /*!<Command strings value*/
  CMDL        /*!<Command letters value*/
} T_CmdType;

/**
 * @brief Commands 
 */
typedef enum enum_Command
{
  NO_CMD = -1,      /*!<No command value*/              
  UNKNOWN,          /*!<Unkown command value*/      
  EXIT,             /*!<Exit command value*/  
  MOVE,             /*!<Move command value*/
  ATTACK,           /*!<Attack command value*/
  TAKE,             /*!<Take command value*/  
  DROP,             /*!<Drop command value*/ 
  INSPECT,          /*!<Inspect command value*/ 
  TURNON,           /*!<Turn on command value*/ 
  TURNOFF,          /*!<Turn off command value*/ 
  OPENLINK,         /*!<Open link command value*/
  CLOSELINK,        /*!<Open link command value*/
  LOAD,             /*!<Load command value*/
  SAVE,             /*!<Save link command value*/
  INFO              /*!<Info command value*/  
} T_Command;                

/**
 * @brief Creates a command structure 
 * @author David Brenchley
 * @return Pointer to a command structure
 */
Commands *commands_create();

/**
 * @brief Destroys a command structure
 * @author David Brenchley
 * @param cmds Pointer to command structure
 */
void commands_destroy(Commands *cmds);

/**
 * @brief Gets the commmand 
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @return Command or NO_CMD if error
 */
T_Command commands_get_cmd(Commands *cmds);

/**
 * @brief Sets the Type of commmand 
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @param cmd a Type of command to be set
 * @return OK or ERROR
 */
STATUS commands_set_cmd(Commands *cmds, T_Command cmd);

/**
 * @brief Gets an argument from a command structure
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @param num Number of the argument (first, second, ...)
 * @return Pointer to string with the command arguments
 */
char *commands_get_args(Commands *cmds, int num);

/**
 * @brief Gets the number of arguments from a command structure
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @return Number of arguments that such command structure holds or -1 if error
 */
int commands_get_num_args(Commands *cmds);

/**
 * @brief Gets the status of a command
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @return OK or ERROR
 */
STATUS commands_get_status(Commands *cmds);

/**
 * @brief Sets the status of a command
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @param status Status value 
 * @return OK or ERROR
 */
STATUS commands_set_status(Commands *cmds, STATUS status);

/**
 * @brief Gets the direction from the move command structure 
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @return The direction of the move command 
 */
DIRECTION commands_get_direction(Commands *cmds);

/**
 * @brief Gets a command and its arguments from a user and saves them in the commmand structure
 * @author David Brenchley
 * @param cmds Pointer to command structure
 * @param f Pointer to file with command
 * @return Command read or NO_CMD if error
 */
T_Command commands_get_user_input(Commands *cmds, FILE *f);

/**
 * @brief Gets the command in a formatted way (extended, not compact)
 * @author Javier San Andrés
 * @param cmds Pointer to command structure
 * @return String with the formatted command
 */
char *commands_get_formatted_cmd(Commands *cmds);

/**
 * @brief Gets the direction as a string from the move command structure 
 * @author Javier San Andrés
 * @param cmds Pointer to command structure
 * @return The string with the direction of the move command 
 */
char *commands_get_formatted_direction(Commands *cmds);

#endif
