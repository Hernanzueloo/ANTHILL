/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author David Brenchley - Diego Rodríguez - Javier San Andrés
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */


#ifndef GAME_H
#define GAME_H

#include "types.h"
#include "command.h"
#include "set.h"
#include "space.h"
#include "object.h"
#include "player.h"
#include "link.h"
#include "enemy.h"
#include "rule.h"
#include "dialogue.h"

/**
 * @brief Game struct 
 */
typedef struct _Game Game;


/**
 * @brief Creates a game
 * @author David Brenchley
 * @return Pointer to the game or NULL if an error ocurred
 */
Game *game_create();

/**
 * @brief creates a game based on a given file
 * @author David Brenchley
 * @param filename pointer to the file where the info is
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Game *game_create_from_file( char *filename);


/**
 * @brief Frees the game's resources and frees the game structure
 * @author David Brenchley
 * @param game Pointer to the game
 */
void game_destroy(Game *game);


/**
 * @brief Creates a duplicate game structure, to destroy use either game_destroy or game_destroy_dup
 * @author David Brenchley
 * @param game Pointer to the game that will be duplicated
 * @return Pointer to new game structure
 */
Game *game_create_dup(Game *game);

/**
 * @brief Frees a duplicate game struture. Note that if all game structure were freed as duplicates, 
 *        the actual game data would be lost, therfore one must be freed with game_destroy
 * @author David Brenchley
 * @param dupgame Pointer to the duplicate game structure
 */
void game_destroy_dup(Game * dupgame);


/**
 * @brief Updates the game according to the last command
 * @author David Brenchley
 * @param game Pointer to the game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_update(Game *game);

/**
 * @brief Checks if the game is over
 * @author Javier San Andres
 * @param game Pointer to the game
 * @return TRUE if game is over or FALSE otherwise
 */
BOOL game_is_over(Game *game);


/**
 * @brief Prints game's information
 * @author Javier San Andres
 * @param game Pointer to the game
 * @param file Output file where it will be printed
 */
STATUS game_print_data(Game *game, FILE *file);



/*GAME PLAYER FUNCTIONS*/

/**
 * @brief It gets the game's player
 * @author Javier San Andres
 * @param game Pointer to the game
 * @return Pointer to the game's player or NULL in case of error
 */
Player* game_get_player(Game *game);

/**
 * @brief It sets the game's player
 * @author Javier San Andres
 * @param game Pointer to the game
 * @param ply Pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_player(Game *game, Player *ply);

/**
 * @brief It gets an array of objects on the player
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @param num Variable where number of objects will be stored
 * @return Array of Id of the objects held by the player or NULL if error
 */
Id *game_get_player_objects(Game *game, int *num);

/**
 * @brief Function to know if the player has an object that lights up the space
 * @author Alejandro García
 * @param game Pointer to the game
 * @return TRUE it it has an object that lights up the space or the player has that ability, FALSE in other cases
 */
BOOL game_player_has_light(Game *game);


/*GAME ENEMY FUNCTIONS*/

/**
 * @brief It gets a game's enemy
 * @author Alejandro García
 * @param game Pointer to the game
 * @param id The Id of the enemy
 * @return Pointer to the game's enemy or NULL if error
 */
Enemy *game_get_enemy(Game *game, Id id);

/**
 * @brief It sets the game's enemy
 * @author Alejandro García
 * @param game Pointer to the game
 * @param enemy Pointer to the enemy
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_enemy(Game *game, Enemy *enemy);

/**
 * @brief deletes an enemy from the game
 * @author David Brenchley
 * @param game Pointer to the game
 * @param enmyid id of the enemy
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_delete_enemy(Game *game, Id enmyid);

/**
 * @brief It gets the postition enemy's id
 * @author Alejandro García
 * @param game Pointer to the game
 * @param position position of the enemy
 * @return The id of the enemy in that position or NO_ID if error
 */
Id game_get_enemy_id_at(Game *game, int position);

/**
 * @brief Gets the enemy ID in a space
 * @author Alejandro García Hernando
 * @param game Pointer to the game
 * @param space ID of the space
 * @return the enemy in the space
 */
Enemy *game_get_enemy_in_space(Game *game, Id space);

/**
 * @brief It gets the number of enemies the game has
 * @author Alejandro García
 * @return The number of enemies the game has, -1 in case of ERROR
 */
int game_get_num_enemies(Game *game);



/*GAME OBJECT FUNCTIONS*/

/**
 * @brief It gets an object of the game
 * @author Javier San Andres
 * @param game Pointer to the game
 * @param id The object's Id
 * @return The Id of the object or NULL in case of error
 */
Object* game_get_object(Game *game, Id id);

/**
 * @brief It adds an object to the game
 * @author Javier San Andres
 * @param game Pointer to the game
 * @param obj Pointer to the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_object(Game *game, Object *obj);

/**
 * @brief deletes an object from the game
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @param objid id of the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_delete_object(Game *game, Id objid);

/**
 * @brief It gets the object's id that is in that position in the object array
 * @author David Brenchley
 * @param game Pointer to the game
 * @param position Number of the object in the object array
 * @return The object's Id or NO_ID in case of error
 */
Id game_get_object_id_at(Game *game, int position);

/**
 * @brief It gets the object's in a space
 * @author Alejandro García Hernando
 * @param game Pointer to the game
 * @param space ID of the space
 * @param n number of the objects in the space
 * @return The object's or NULL in case of error
 */
Object **game_get_objects_in_space(Game *game, Id space, int *n);

/**
 * @brief It gets the number of objects in the game
 * @author David Brenchley
 * @param game Pointer to the game
 * @return Number of objects int the game or -1 in case of error
 */
int game_get_num_objects(Game *game);

/**
 * @brief It gets the object's name
 * @author David Brenchley
 * @param game Pointer to the game
 * @param id Id of the object of which location we want to know
 * @return The name of the objector NULL in case of error
 */
char* game_get_object_name(Game *game, Id id);

/**
 * @brief It sets the object's location
 * @author David Brenchley
 * @param game Pointer to the game
 * @param object_id The id of the object of which location is to be set
 * @param location_id The id of the space where the object will be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_object_location(Game *game, Id object_id, Id location_id);


/*GAME SPACE FUNCTIONS*/

/**
 * @brief It gets a space of the game
 * @author Javier San Andres
 * @param game Pointer to the game
 * @param id The space's Id
 * @return Pointer to the space with such Id or NULL if error */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Adds a space to the game
 * @author Javier San Andres
 * @param game Pointer to the game
 * @param space Pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_space(Game *game, Space *space);


/**
 * @brief deletes a space from the game, the object inside the space and the links associated to it
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @param id id of the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_delete_space(Game *game, Id id);


/**
 * @brief It gets a space's Id
 * @author David Brenchley
 * @param game Pointer to the game
 * @param position Number of the space in the spaces' array
 * @return The space's Id or NO_ID if error
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief It gets the number of spaces the game has
 * @author Alejandro García
 * @param game Pointer to the game
 * @return The number of spaces the game has or -1 if error
 */
int game_get_num_of_spaces(Game *game);

/**
 * @brief It evaluates if a space has a given type of object in it  
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @param id Id of the sapce looking into
 * @param type of the object looking for
 * @return TRUE it the space has an object of that type, FALSE in other cases
 */
BOOL game_space_has_object(Game *game, Id id,T_ObjectType type);


/*GAME LINK FUNCTIONS*/

/**
 * @brief It sets a link
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @param link pointer to the link to be setted
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_link(Game * game, Link * link);

/**
 * @brief deletes a link from the game
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @param link id of the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_delete_link(Game *game, Id link);

/**
 * @brief It gets a link
 * @author Diego  Rodríguez Ortiz
 * @param game Pointer to the game
 * @param id Id of the link  we want to get
 * @return Pointer to the link we want to get
 */
Link *game_get_link(Game * game, Id id);

/**
 * @brief It gets a links id
 * @author Javier San Andrés
 * @param game Pointer to the game
 * @param origin Id of the origin space
 * @param dir Direction of the link
 * @return Link id
 */
Id game_get_link_id(Game *game, Id origin, DIRECTION dir);

/**
 * @brief It gets the link's id that is in that position in the object array
 * @author Alejandro García
 * @param game Pointer to the game
 * @param position Number of the link in the object array
 * @return The link's Id or NO_ID in case of error
 */
Id game_get_link_id_at(Game *game, int position);


/**
 * @brief It sets the link's origin for a link in the game
 * @author Javier San Andrés
 * @param game Pointer to the game
 * @param link_id Id of the link whose origin is to be set
 * @param origin_id Id of the space of the link's origin
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_link_origin(Game *game, Id link_id, Id origin_id);

/**
 * @brief It sets the link's destination for a link in the game
 * @author Javier San Andrés
 * @param game Pointer to the game
 * @param link_id Id of the link whose destination is to be set
 * @param destination_id Id of the space of the link's destination
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_link_destination(Game *game, Id link_id, Id destination_id);

/**
 * @brief It gets the status of the link between two points
 * @author Diego  Rodríguez Ortiz
 * @param game pointer to the game where the link is going to be search
 * @param origin Id of the origin of the link
 * @param dir Direction of the link
 * @return the status of the link if it exists, CLOSE if it doesn't
 */
LSTATUS game_get_connection_status(Game *game, Id origin, DIRECTION dir);

/**
 * @brief It gets the id of a link's destination
 * @author Diego  Rodríguez Ortiz
 * @param game pointer to the game where the link is going to be search
 * @param origin Id of the origin of the link
 * @param dir Direction of the link
 * @return Id of the link's destination (NO_ID if the link doesn't exist)
 */
Id game_get_connection(Game * game, Id origin, DIRECTION dir);

/**
 * @brief It gets the id of space situated at the direction given if it the link is open
 * @author Javier San Andres 
 * @param game Pointer to the game
 * @param origin Id of the space origin
 * @param dir DIRECTION of the link we are looking for
 * @return The Id of the space situated at that direction if the link is open, NO_ID otherwise.
 */
Id game_get_open_link(Game *game, Id origin, DIRECTION dir); 

/**
 * @brief It gets the number of links of a game
 * @author Alejandro García
 * @param game Pointer to the game
 * @return The number of links the game has, or -1 if something goes wrong
 */
int game_get_num_links(Game *game);


/*DIALOGUE FUNCTIONS*/

/**
 * @brief It returns all the dialogues stored in a game
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param num_dialogues pointer to the number of dialogues stored
 * @return pointer to the array of dialogues in the game
 */
Dialogue **game_get_all_dialogues(Game *game, int *num_dialogues);

/**
 * @brief It tells whether a dialogue_id is already registered in the game
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param id id of the dialog
 * @return TRUE, if it does and FALSE in any other case
 */
BOOL game_existing_dialogue_id(Game *game, Id id);

/**
 * @brief It adds a dialogue to the game
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param dialogue pointer to the dialogue to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_dialogue(Game *game, Dialogue *dialogue);

/**
 * @brief It adds a rule to an exiting dialogue in the game
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param id id of the dialog
 * @param rule string with the rule to be added to the dialog
 * @param type type of the dialogue rule to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_dialogue_rule(Game *game, Id id, char *rule, DTYPE type);

/**
 * @brief It gets the number of consecutive error executions of a dialogue rule
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param id id of the dialog
 * @return the number of executions or -1 in case of error
 */
int game_get_dialogue_executed(Game *game, Id id);

/**
 * @brief It increases the number of consecutive error executions of a dialogue
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param id id of the dialog
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_increase_dialogue_executed(Game *game, Id id);

/**
 * @brief It decreases the number of consecutive error executions of a dialogue
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param id id of the dialog
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_decrease_dialogue_executed(Game *game, Id id);

/**
 * @brief It gives one of the dialogue rules associated to a command
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param position index in the array of the rule to be printed
 * @param args arguments of the command executed and for which the dialog response is
 * @param command type of command associated to the dialogue
 * @param command_status Status of the command
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_printed_dialogue_rule(Game *game, int position, char *args, T_Command command, STATUS command_status);


/**
 * @brief It gives one of the dialogue rules associated to the repeated error commands
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param num_times number of times it has been consecutively executed without success
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_printed_repeated_error_rule(Game *game, int num_times);

/**
 * @brief It gives the rule associated to the command move depending on the case
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param type type of the rule to be given (SUCCESS or FAILURE)
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_move_dialogue_rule(Game *game, DTYPE type);

/**
 * @brief It gives the rule associated to the command attack depending on the case
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_attack_dialogue_rule(Game *game);

/**
 * @brief It gives the rule associated to the command take depending on the case
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param type type of the rule to be given (SUCCESS or FAILURE)
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_take_dialogue_rule(Game *game, DTYPE type);

/**
 * @brief It gives the rule associated to the command drop depending on the case
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param type type of the rule to be given (SUCCESS or FAILURE)
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_drop_dialogue_rule(Game *game, DTYPE type);

/**
 * @brief It gives the rule associated to the command inspect depending on the case
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param type type of the rule to be given (SUCCESS or FAILURE)
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_inspect_dialogue_rule(Game *game, DTYPE type);

/**
 * @brief It gives the rule associated to the command turnon/turnoff depending on the case
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param command which of those two is executed
 * @param type type of the rule to be given (SUCCESS or FAILURE)
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_turn_on_off_dialogue_rule(Game *game, T_Command command, DTYPE type);

/**
 * @brief It gives the rule associated to the commands openlink or closelink depending on the case
 * @author Javier San Andrés de Pedro
 * @param game Pointer to the game
 * @param command which of those two is executed
 * @param type type of the rule to be given (SUCCESS or FAILURE)
 * @return the string with dialogue rule or NULL in case of error
 */
char *game_get_open_close_link_dialogue_rule(Game *game, T_Command command, DTYPE type);

/**
 * @brief It gets all the dialogues of the rules just executed
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @param num_dialogues The number of dialogues to be retorned
 * @return An array of strings with the diferent dialogues rules or NULL in case of error
 */
char **game_get_dialogue_of_game_rule(Game *game, int *num_dialogues);

/*GAME COMMAND FUNCTIONS*/

/**
 * @brief It get's the last command that was executed
 * @author David Brenchley
 * @param game Pointer to the game
 * @return Pointer to the last command structure or NULL if error
 */
Commands *game_get_last_command(Game *game);

/**
 * @brief It get's the last command type that was executed
 * @author David Brenchley Uriol
 * @param game Pointer to the game
 * @return Last command type or NO_CMD if error
 */
T_Command game_get_last_command_cmd(Game *game);

/**
 * @brief It get's the last command that was executed (only the type of command)
 * @author David Brenchley Uriol
 * @param game Pointer to the game
 * @return The last command type or NO_CMD if error
 */
STATUS game_get_last_command_status(Game *game);

/**
 * @brief It gets the number of executed commands
 * @author David Brenchley Uriol
 * @param game Pointer to the game
 * @return Number of executed commands or -1 if error
 */
int game_get_num_executed_commands(Game *game);

/**
 * @brief It sets the number of executed commands
 * @author David Brenchley Uriol
 * @param game Pointer to the game
 * @param num Number to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_num_executed_commands(Game *game, int num);

/**
 * @brief It gets the number of  commands per flood if there is a rule with such action
 * @author Alejandro García
 * @param game Pointer to the game
 * @return Number of number of commands per flood commands or -1 if error
 */
int game_get_num_commands_per_flood(Game *game);

/**
 * @brief It gets the number of  commands until the next flood if there is a rule with such action
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game
 * @return Number of number of commands until the next flood commands or -1 if error
 */
int game_get_num_commands_till_flood(Game *game);

/**
 * @brief It gets the a number of random Id spaces
 * @author David Brenchley Uriol
 * @param game Pointer to the game that will be used
 * @param nids the number of spaces to get
 * @return The ids of the choosen space
 */
Id *game_get_rand_space_id(Game *game, int nids);

/*TDESC FUNCTIONS*/

/**
 * @brief It get's the main description of the space
 * @author David Brenchley
 * @param game Pointer to the game
 * @return Pointer to the description or NULL if error
 */
char *game_get_last_tdesc(Game *game);

/**
 * @brief It set's the tdesc pointer
 * @author David Brenchley
 * @param game Pointer to the game
 * @param tdesc Pointer to the textual description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_last_tdesc(Game *game, char *tdesc);

/**
 * @brief It get's the description of the last inspection that was executed
 * @author Alejandro García
 * @param game Pointer to the game
 * @return Pointer to the description or NULL if error
 */
char *game_get_last_idesc(Game *game);

/**
 * @brief It set's the idesc pointer
 * @author Alejandro García
 * @param game Pointer to the game
 * @param idesc Pointer to the textual description
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_set_last_idesc(Game *game, char *idesc);


/*GAME RULE FUNCTIONS*/

/**
 * @brief It gets a game rule
 * @author David Brenchley
 * @param game Pointer to the game
 * @param id Rule id
 * @return Pointer to the rule or NULL in case of error
 */
Rule* game_get_rule(Game *game, Id id);

/**
 * @brief It gets the postition rule's id
 * @author Alejandro García
 * @param game Pointer to the game
 * @param position position of the rule
 * @return The id of the rule in that position or NO_ID if error
 */
Id game_get_rule_id_at(Game *game, int position);

/**
 * @brief It gets the number of rules the game has
 * @author Alejandro García
 * @return The number of rules the game has, -1 in case of ERROR
 */
int game_get_num_rules(Game *game);

/**
 * @brief It sets a game rule
 * @author David Brenchley
 * @param game Pointer to the game
 * @param rule Pointer to the rule
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_add_rule(Game *game, Rule *rule);

/**
 * @brief It gets the a unique Id for a new object
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game that will be used
 * @return The id generated
 */
Id game_get_unique_object_id(Game *game);

/**
 * @brief It spawns random grounds
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game that will be used
 * @param argint the number of ground that will spawn
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_rule_spawn_ground(Game * game, int argint);


/*DIEGO: ESTO VA AL GAME.C HAY UN HUECO PARA ELLO BUSCA DIEGO: */

/**
 * @brief  It evaluates if there is a path between 2 spaces
 * @author Diego Rodríguez Ortiz
 * @param game  Pointer to a game
 * @param orig id of origin space
 * @param dest id of the destination
 * @return True if there is a path and False otherwise
 */
BOOL game_get_path(Game *game, Id orig, Id dest);


#endif
