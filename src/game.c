/**
 * @brief It implements the  games's module
 *
 * @file game.c
 * @author David Brenchley - Diego Rodríguez - Javier San Andrés
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <sys/time.h>
#include "game.h"
#include "game_management.h"

/**
 * @brief Game
 *
 * This struct stores all the information of a game.
 */
struct _Game
{
  Player *player;                     /*!< Pointer to the player structure */
  Enemy *enemies[MAX_ENEMIES];        /*!< Array of pointers to the enemy structure*/
  Commands *last_cmd;                 /*!< Pointer to last command structure*/
  Object *objects[MAX_OBJECTS];       /*!< Array of pointers to object structures */
  Space *spaces[MAX_SPACES];          /*!< Arrau of pointers to space structures */
  Link *links[MAX_LINKS];             /*!< Array of pointers to link structures*/
  Rule *rules[MAX_RULES];             /*!< Array of pointer to rule structures*/
  Dialogue *dialogues[MAX_DIALOGUES]; /*!< Array of pointer to dialogues structures*/
  char *last_tdesc;                   /*!< Pointer to main description of the space*/
  char *last_idesc;                   /*!< Pointer to latest inspected description*/
  int num_executed_commands;          /*!< Number of executed commands*/
};

/*PRIVATE COMMAND FUNCTIONS*/
/**
 * @brief Executes the unknown command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_unknown(Game *game);
/**
 * @brief Executes the exit command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_exit(Game *game);

/**
 * @brief Executes the move command to the direction given
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game that will be used
 * @param direction Direction in which to move
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_move(Game *game, DIRECTION direction);

/**
 * @brief Executes the command to attack an enemy
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_attack(Game *game);

/**
 * @brief Executes the take command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param cmds Pointer to an structure Command
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_take(Game *game, Commands *cmds);

/**
 * @brief Executes the drop command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param cmds Pointer to an structure Command
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_drop(Game *game, Commands *cmds);

/**
 * @brief Executes the inspect command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param cmds Pointer to an structure Command
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_inspect(Game *game, Commands *cmds);

/**
 * @brief Executes the turn on or of command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param on_off True to turn on or False to turn off
 * @param cmds Pointer to an structure Command
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_turn_on_off(Game *game, Commands *cmds, BOOL on_off);

/**
 * @brief Executes the open link command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param cmds Pointer to an structure Command
 * @param opn_cls The LSTATUS of the action being executed
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_open_close(Game *game, Commands *cmds, LSTATUS opn_cls);

/**
 * @brief Executes the load command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param cmds Pointer to an structure Command
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_load(Game *game, Commands *cmds);
/**
 * @brief Executes the save command
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param cmds Pointer to an structure Command
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_save(Game *game, Commands *cmds);

/**
 * @brief Executes the info command(Shows the info of the game)
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @return OK, if everything goes well or ERROR if command not possible or if there was a mistake
 */
STATUS game_command_info(Game *game);

/*PRIVATE RULE FUNCTIONS*/

/**
 * @brief It evaluates and executes all game rules
 * @author David Brenchley
 * @param game Pointer to the game
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_rule_evaluate_execute_all(Game *game);

/**
 * @brief It executes a game rule
 * @author David Brenchley
 * @param game Pointer to the game
 * @param rule Pointer to the rule
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_rule_execute(Game *game, Rule *rule);

/**
 * @brief It executes a game rule's action
 * @author David Brenchley
 * @param game Pointer to the game
 * @param action Pointer to the rule's action
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_rule_execute_action(Game *game, Action *action);

/**
 * @brief It evaluates a game rule
 * @author David Brenchley
 * @param game Pointer to the game
 * @param rule Pointer to the rule
 * @return TRUE if evaluation was correct or False if not or in case of error
 */
BOOL game_rule_evaluate(Game *game, Rule *rule);

/**
 * @brief It evaluates a game rule's condition
 * @author David Brenchley
 * @param game Pointer to the game
 * @param condition Pointer to the rule's condition
 * @return TRUE if evaluation was correct or False if not or in case of error
 */
BOOL game_rule_evaluate_condition(Game *game, Condition *condition);

/*PRIVATE GAME STRUCTURE HANDLING FUNCTIONS*/

/**
 * @brief Initializes all the values of an existing game, making it ready for loading a game into it.
 *        In case of an old game,resources are not freed, so a duplicate must be created beforehand.
 * @author David Brenchley
 * @param game Pointer to the game that will be initialized
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_init(Game *game);

/**
 * @brief Copies the values of one game stucture into another, but doesn´t create a copy of the actual game
 * @author David Brenchley
 * @param dest_game Pointer to the destination game structure
 * @param org_game Pointer to the original game structure
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_copy(Game *dest_game, Game *org_game);

/*PRIVATE AUXILIARY FUNCTIONS*/

/**
 * @brief It gets the Id of a link if exist from the space in a given direction
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game that will be used
 * @param orig Space id of the origin of the link
 * @param dir The direction of the link
 * @return The id of the link if exist NO_ID otherwise
 */
Id game_get_link_from_space(Game *game, Id orig, DIRECTION dir);

/**
 * @brief It gets the Id of a link if exist to a space in a given direction
 * @author Diego Rodríguez Ortiz
 * @param game Pointer to the game that will be used
 * @param dest Space id of the destination of the link
 * @param dir The direction of the link
 * @return The id of the link if exist NO_ID otherwise
 */
Id game_get_link_to_space(Game *game, Id dest, DIRECTION dir);

/**
 * @brief It gets the nmae of the upgraded object
 * @author Diego Rodríguez Ortiz
 * @param name the name of the object
 * @return The name of the upgraded object
 */
char *game_get_upgraded_name(char *name);

/**
 * @brief Recursive drop function for dependant objects
 * @author David Brenchley
 * @param game Pointer to game
 * @param objs_id Pointer to array of objs_id
 * @param nobj number of ids in array
 * @param space Pointer to current space
 * @param space_id Current space's id
 * @param obj_name name of the object to be dropped
 * @param count pointer to a counter of objects that have been dropped
 * @return The name of the upgraded object
 */
STATUS _drop_rec(Game *game, Id *objs_id, int nobj, Space *space, Id space_id, char *obj_name, int *count);

/**
 * @brief  It evaluates if the harbour has sunk
 * @author Diego Rodríguez Ortiz
 * @param game  Pointer to a game
 * @return True if the harbour has sunk and False otherwise
 */
BOOL game_check_harbour_sunk(Game *game);
/**
 * @brief  It evaluates if there is a path between 2 spaces
 * @author Diego Rodríguez Ortiz
 * @param game  Pointer to a game
 * @param orig id of origin space
 * @param dest id of the destination
 * @param array a boolean array to check if visited
 * @return True if there is a path and False otherwise
 */                                                               
BOOL game_get_path_rec(Game *game, Id orig, Id dest, BOOL *array);

/**
 * @brief  It evaluates if there is a path between 2 spaces
 * @author Diego Rodríguez Ortiz
 * @param game  Pointer to a game
 * @param orig id of origin space
 * @param dest id of the destination
 * @return True if there is a path and False otherwise
 */
BOOL game_get_path(Game *game, Id orig, Id dest);
/**
 * @brief  It evaluates if there is a number of accesible object of a given type
 * @author Diego Rodríguez Ortiz
 * @param game  Pointer to a game
 * @param orig id of origin space
 * @param type type of the object to evaluate
 * @param num the number of objects accesibles
 * @return True if there is a path and False otherwise
 */
BOOL game_rule_get_path_to_type_of_object(Game *game, Id orig, T_ObjectType type, int num);


/**
 * @brief  It evaluates if there is a path to the space with a given name
 * @author Diego Rodríguez Ortiz
 * @param game  Pointer to a game
 * @param orig id of origin space
 * @param space_name the name of the space to evaluate
 * @return True if there is a path and False otherwise
 */
BOOL game_rule_get_path_to_space_by_name(Game *game, Id orig, char *space_name);
/**
 * @brief Value with the effect of an attacked command
 */
DTYPE command_attack_effect = SUCCESS;

/**
 * @brief The number of grounds that has spawn
 */
int number_of_grounds = 0;

/**
 * @brief Array of the different objects and the result of their upgrade
 */
char *upgrades_object[N_OBJ_TYPES][N_UPGRADES] ={{"Stick", "Boat_Mast"},
                                                 {"Leaf", "Boat_Sail"},
                                                 {"Walnut", "Boat_Hull"},
                                                 {"Key",""},
                                                 {"Goldkey", "Magicalkey"},
                                                 {"Lantern",""},
                                                 {"Ground",""},
                                                 {"Boat", "ANTBOAT"},
                                                };
/**
 * @brief Array of ids of spaces that hast just recently been flooded
 *
 */
Id JustFlooded[MAX_SPACES] = {0};

/**
 * @brief Array of the names of the spaces just flooded
 */
char JustFloodedName[MAX_SPACES][WORD_SIZE];

/**
 * @brief Array of objects that have just been dropped
 */
Id DroppedObjects[MAX_OBJECTS] = {0};

/**
 * @brief Value with the effect of the drop ground command
 */
DTYPE drop_ground = SUCCESS;

/**
   Game interface implementation
*/
Game *game_create()
{
  Game *game;

  if ((game = (Game *)calloc(1, sizeof(Game))) == NULL)
    return NULL;

  if ((game->last_cmd = commands_create()) == NULL)
  {
    free(game);
    return ERROR;
  }

  game_init(game);

  return game;
}

Game *game_create_from_file(char *filename)
{
  Game *game = NULL;

  if (!filename)
    return NULL;

  if ((game = game_create(game)) == NULL)
    return NULL;

  if (game_management_load(game, filename) == ERROR)
  {
    game_destroy(game);
    return NULL;
  }

  return game;
}

STATUS game_init(Game *game)
{
  int i = 0;

  if (game == NULL)
    return ERROR;

  commands_set_cmd(game->last_cmd, LOAD);
  commands_set_status(game->last_cmd, OK);

  for (i = 0; i < MAX_ENEMIES; i++)
    game->enemies[i] = NULL;

  for (i = 0; i < MAX_OBJECTS; i++)
    game->objects[i] = NULL;

  for (i = 0; i < MAX_SPACES; i++)
    game->spaces[i] = NULL;

  for (i = 0; i < MAX_LINKS; i++)
    game->links[i] = NULL;

  for (i = 0; i < MAX_RULES; i++)
    game->rules[i] = NULL;

  for (i = 0; i < MAX_DIALOGUES; i++)
    game->dialogues[i] = NULL;

  game->player = NULL;

  game->last_tdesc = NULL;
  game->last_idesc = NULL;
  game->num_executed_commands = 0;

  return OK;
}

STATUS game_copy(Game *dest_game, Game *org_game)
{
  int i;

  if (dest_game == NULL || org_game == NULL)
    return ERROR;

  commands_set_cmd(dest_game->last_cmd, commands_get_cmd(org_game->last_cmd));
  commands_set_status(dest_game->last_cmd, commands_get_status(org_game->last_cmd));

  for (i = 0; i < MAX_SPACES; i++)
    dest_game->spaces[i] = org_game->spaces[i];

  for (i = 0; i < MAX_OBJECTS; i++)
    dest_game->objects[i] = org_game->objects[i];

  for (i = 0; i < MAX_LINKS; i++)
    dest_game->links[i] = org_game->links[i];

  for (i = 0; i < MAX_ENEMIES; i++)
    dest_game->enemies[i] = org_game->enemies[i];

  for (i = 0; i < MAX_RULES; i++)
    dest_game->rules[i] = org_game->rules[i];

  for (i = 0; i < MAX_DIALOGUES; i++)
    dest_game->dialogues[i] = org_game->dialogues[i];

  dest_game->player = org_game->player;

  dest_game->last_tdesc = org_game->last_tdesc;
  dest_game->last_idesc = org_game->last_idesc;
  dest_game->num_executed_commands = org_game->num_executed_commands;
  return OK;
}

void game_destroy(Game *game)
{
  int i = 0;

  if (game == NULL)
    return;

  if (game->last_cmd)
    commands_destroy(game->last_cmd);

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    space_destroy(game->spaces[i]);

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    object_destroy(game->objects[i]);

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    link_destroy(game->links[i]);

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
    enemy_destroy(game->enemies[i]);

  for (i = 0; i < MAX_RULES && game->rules[i] != NULL; i++)
    rule_destroy(game->rules[i]);

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
    dialogue_destroy(game->dialogues[i]);

  if (game->player)
    player_destroy(game->player);

  free(game);
}

Game *game_create_dup(Game *game)
{
  Game *dupgame;

  if (game == NULL)
    return NULL;

  if ((dupgame = (Game *)malloc(sizeof(Game))) == NULL)
    return NULL;

  if ((dupgame->last_cmd = commands_create()) == NULL)
  {
    free(dupgame);
    return ERROR;
  }
  game_init(dupgame);

  game_copy(dupgame, game);

  return dupgame;
}

void game_destroy_dup(Game *dupgame)
{
  commands_destroy(dupgame->last_cmd);
  free(dupgame);
}

STATUS game_update(Game *game)
{
  T_Command cmd;
  STATUS sts;
  int i;

  if (game == NULL)
    return ERROR;

  if (game->last_cmd == NULL)
    return ERROR;

  cmd = commands_get_cmd(game->last_cmd);

  switch (cmd)
  {
  case UNKNOWN:
    sts = game_command_unknown(game);
    break;

  case EXIT:
    sts = game_command_exit(game);
    break;

  case MOVE:
    sts = game_command_move(game, commands_get_direction(game->last_cmd));
    break;

  case ATTACK:
    sts = game_command_attack(game);
    break;

  case TAKE:
    sts = game_command_take(game, game->last_cmd);
    break;

  case DROP:
    sts = game_command_drop(game, game->last_cmd);
    break;

  case INSPECT:
    sts = game_command_inspect(game, game->last_cmd);
    game->last_tdesc = space_get_tdesc(game_get_space(game, player_get_location(game_get_player(game))));
    break;

  case TURNON:
    sts = game_command_turn_on_off(game, game->last_cmd, TRUE);
    break;

  case TURNOFF:
    sts = game_command_turn_on_off(game, game->last_cmd, FALSE);
    break;

  case OPENLINK:
    sts = game_command_open_close(game, game->last_cmd, OPEN);
    break;

  case CLOSELINK:
    sts = game_command_open_close(game, game->last_cmd, CLOSE);
    break;

  case LOAD:
    sts = game_command_load(game, game->last_cmd);
    break;

  case SAVE:
    sts = game_command_save(game, game->last_cmd);
    break;

  case INFO:
    sts = game_command_info(game);
    break;

  default:
    break;
  }
  commands_set_status(game->last_cmd, sts);

  for (i = 0; i < MAX_RULES && game->rules[i] != NULL; i++)
    rule_set_executed(game->rules[i], FALSE);

  if (sts == OK && cmd != UNKNOWN && cmd != SAVE && cmd != LOAD)
  {
    if (commands_get_cmd(game->last_cmd) != INSPECT)
    {
      game->last_idesc = NULL;
      game->num_executed_commands++;
    }
    game_rule_evaluate_execute_all(game);
  }

  return OK;
}

BOOL game_is_over(Game *game)
{
  if (!game)
    return TRUE;

  if (game->num_executed_commands == VICTORY || (game->num_executed_commands > VICTORY && game->num_executed_commands < 0) || player_get_health(game_get_player(game)) <= 0)
    return TRUE;

  return FALSE;
}

STATUS game_print_data(Game *game, FILE *file)
{
  int i = 0;

  if (game == NULL || file == NULL)
    return ERROR;

  fprintf(file, "\n\n-------------\n\n");

  fprintf(file, "\n=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    space_print(game->spaces[i], file);

  fprintf(file, "\n=> Objects: \n");
  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    object_print(game->objects[i], file);

  fprintf(file, "\n=> Links: \n");
  for (i = 0; i < MAX_LINKS; i++)
  {
    if (game->links[i])
      link_print(game->links[i], file);
  }

  fprintf(file, "\n=> Dialogues: \n");
  for (i = 0; i < MAX_DIALOGUES; i++)
  {
    if (game->dialogues[i])
      dialogue_print(game->dialogues[i], file);
  }

  fprintf(file, "\n");
  player_print(game->player, file);

  for (i = 0; i < MAX_ENEMIES; i++)
  {
    if (game->enemies[i])
      enemy_print(game->enemies[i], file);
  }
 for (i = 0; i < MAX_RULES; i++)
  {
    if (game->rules[i])
      rule_print(game->rules[i], file);
  }

  fprintf(file, "\n");

  return OK;
}

/* Player's functions */
Player *game_get_player(Game *game)
{
  if (game == NULL)
    return NULL;

  return game->player;
}

STATUS game_set_player(Game *game, Player *ply)
{
  if (game == NULL || ply == NULL)
    return ERROR;

  game->player = ply;
  return OK;
}

Id *game_get_player_objects(Game *game, int *num)
{
  if (game == NULL)
    return NULL;

  return player_get_objects(game->player, num);
}

BOOL game_player_has_light(Game *game)
{
  Id *objs = NULL;
  int num, i;

  if (!game)
    return FALSE;

  if (player_get_type(game_get_player(game)) == FIREFLY)
    return TRUE;

  objs = player_get_objects(game_get_player(game), &num);
  for (i = 0; i < num; i++)
    if (object_get_illuminate(game_get_object(game, objs[i])) && object_get_turnedon(game_get_object(game, objs[i])))
    {
      free(objs);
      return TRUE;
    }

  free(objs);
  return FALSE;
}

/* Enemy's functions */

Enemy *game_get_enemy(Game *game, Id id)
{
  int i = 0;

  if (game == NULL || id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
    if (id == enemy_get_id(game->enemies[i]))
      return game->enemies[i];

  return NULL;
}

Enemy *game_get_enemy_in_space(Game *game, Id space)
{
  int i;
  Id enemy_id = NO_ID + 1;
  Enemy *enemy;

  if (game == NULL || space == NO_ID)
    return NULL;

  for (i = 0; i < MAX_ENEMIES && enemy_id != NO_ID; i++)
  {
    enemy_id = game_get_enemy_id_at(game, i);
    enemy = game_get_enemy(game, enemy_id);
    if (enemy_get_location(enemy) == space)
      return enemy;
  }

  return NULL;
}

STATUS game_add_enemy(Game *game, Enemy *enemy)
{
  int i;

  if (game == NULL || enemy == NULL)
    return ERROR;

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
    ;

  if (i == MAX_ENEMIES)
    return ERROR;

  game->enemies[i] = enemy;

  return OK;
}

STATUS game_delete_enemy(Game *game, Id enmyid)
{
  int i;
  int index = -1;
  if (!game || enmyid == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
    if (enemy_get_id(game->enemies[i]) == enmyid)
    {
      index = i;
      enemy_destroy(game->enemies[i]);
    }

  if (index != -1)
  {
    game->enemies[index] = game->enemies[i - 1];
    game->enemies[i - 1] = NULL;
    return OK;
  }
  else
    return ERROR;
}

Id game_get_enemy_id_at(Game *game, int position)
{
  if (game == NULL || position < 0 || position >= game_get_num_enemies(game))
    return NO_ID;

  return enemy_get_id(game->enemies[position]);
}

int game_get_num_enemies(Game *game)
{
  int i;

  if (game == NULL)
    return -1;

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
    ;

  return i;
}

/* Object's functions */

STATUS game_delete_object(Game *game, Id objid)
{
  int i;
  int index = -1;

  if (!game || objid == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    if (object_get_id(game->objects[i]) == objid)
    {
      index = i;
      object_destroy(game->objects[i]);
    }

  if (index != -1)
  {
    game->objects[index] = game->objects[i - 1];
    game->objects[i - 1] = NULL;
    return OK;
  }

  return ERROR;
}

Object *game_get_object(Game *game, Id id)
{
  int i = 0;

  if (game == NULL || id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    if (id == object_get_id(game->objects[i]))
      return game->objects[i];

  return NULL;
}

STATUS game_add_object(Game *game, Object *obj)
{
  int i;

  if (game == NULL || obj == NULL)
    return ERROR;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    ;

  if (i == MAX_OBJECTS)
    return ERROR;
  game->objects[i] = obj;

  return OK;
}

Id game_get_object_id_at(Game *game, int position)
{
  if (game == NULL || position < 0 || position >= game_get_num_objects(game))
    return NO_ID;

  return object_get_id(game->objects[position]);
}

Object **game_get_objects_in_space(Game *game, Id space, int *n)
{
  int i, j = 0;
  Object **objects, *obj;

  if (game == NULL || space == NO_ID)
    return NULL;

  if ((objects = (Object **)malloc(MAX_OBJECTS * sizeof(Object *))) == NULL)
    return NULL;

  for (i = 0; i < MAX_OBJECTS && obj != NULL; i++)
  {
    obj = game_get_object(game, game_get_object_id_at(game, i));
    if (object_get_location(obj) == space)
    {
      objects[j] = obj;
      j++;
    }
  }

  *n = j;
  return objects;
}

int game_get_num_objects(Game *game)
{
  int i;

  if (game == NULL)
    return -1;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    ;

  return i;
}

char *game_get_object_name(Game *game, Id id)
{
  int i;

  if (game == NULL || id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
  {
    if (id == object_get_id(game->objects[i]))
      return object_get_name(game->objects[i]);
  }

  return NULL;
}

STATUS game_set_object_location(Game *game, Id object_id, Id location_id)
{
  int i = 0;

  if (game == NULL || object_id == NO_ID || location_id == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    if (object_id == object_get_id(game->objects[i]))
    {
      object_set_location(game->objects[i], location_id);
      return space_add_object(game_get_space(game, location_id), object_id);
    }

  return ERROR;
}

/* Space's functions */

STATUS game_delete_space(Game *game, Id spaceid)
{
  int i, j, n;
  int index = -1;
  Id *objs;

  if (!game || spaceid == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    if (space_get_id(game->spaces[i]) == spaceid)
    {
      for (j = 0; j < N_DIR; j++)
      {
        game_delete_link(game, game_get_link_from_space(game, spaceid, (DIRECTION)j));
        game_delete_link(game, game_get_link_to_space(game, spaceid, (DIRECTION)j));
      }

      objs = space_get_objects(game->spaces[i], &n);

      for (j = 0; j < n; j++)
        game_delete_object(game, objs[j]);

      free(objs);

      for (j = 0; j < MAX_ENEMIES && game->enemies[j] != NULL; j++)
        if (enemy_get_location(game->enemies[i]) == spaceid)
          game_delete_enemy(game, enemy_get_id(game->enemies[i]));

      index = i;
      space_destroy(game->spaces[index]);
    }

  if (index != -1)
  {
    game->spaces[index] = game->spaces[i - 1];
    game->spaces[i - 1] = NULL;
    return OK;
  }
  else
    return ERROR;
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (game == NULL || id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
      return game->spaces[i];
  }

  return NULL;
}

STATUS game_add_space(Game *game, Space *space)
{
  int i;

  if (game == NULL || space == NULL)
    return ERROR;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    ;

  if (i == MAX_SPACES)
    return ERROR;

  game->spaces[i] = space;

  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
  if (game == NULL || position < 0 || position >= MAX_SPACES)
    return NO_ID;

  return space_get_id(game->spaces[position]);
}

int game_get_num_of_spaces(Game *game)
{
  int i;

  if (game == NULL)
    return -1;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    ;

  return i;
}

Id game_get_unique_object_id(Game *game)
{
  int i;

  for (i = 1; i <= MAX_OBJECTS && game_get_object(game, (Id)i) != NULL; i++)
    ;
  if (i != MAX_OBJECTS)
    return (Id)i;

  return NO_ID;
}

Id *game_get_rand_space_id(Game *game, int nids)
{
  int i = 0, j = 0, r, numallids;
  Id *randids, allids[MAX_SPACES];
  struct timeval currentTime;

  gettimeofday(&currentTime, NULL);
  srand((unsigned)currentTime.tv_usec);

  if (game == NULL || nids < 1)
    return NULL;

  if ((randids = (Id *)malloc(nids * sizeof(Id))) == NULL)
    return NULL;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    allids[i] = space_get_id(game->spaces[i]);

  numallids = i;

  if (numallids <= nids)
  {
    for (i = 0; i < numallids; i++)
      randids[i] = space_get_id(game->spaces[i]);
    for (j = i; j < nids; j++)
      randids[i] = NO_ID;
  }
  else
  {
    for (i = 0; i < nids; i++)
    {
      r = rand() % numallids;
      randids[i] = allids[r];
      allids[r] = allids[numallids - 1];
      allids[numallids - 1] = NO_ID;
      numallids--;
    }
  }
  return randids;
}

BOOL game_space_has_object(Game *game, Id id, T_ObjectType type)
{
  int i, n;
  Id *ido;
  Space *space;

  if (!game || id == NO_ID || type == NO_OTYPE)
    return FALSE;

  space = game_get_space(game, id);
  ido = space_get_objects(space, &n);
  for (i = 0; i < n; i++)
  {
    if (object_get_type(game_get_object(game, ido[i])) == type)
    {
      free(ido);
      return TRUE;
    }
  }
  free(ido);

  return FALSE;
}
/* Link functions */

STATUS game_delete_link(Game *game, Id linkid)
{
  int i = 0, index = -1;

  if (!game || linkid == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_id(game->links[i]) == linkid)
    {
      index = i;
      link_destroy(game->links[i]);
    }
  }

  if (index != -1)
  {
    game->links[index] = game->links[i - 1];
    game->links[i - 1] = NULL;
    return OK;
  }

  return ERROR;
}

STATUS game_add_link(Game *game, Link *link)
{
  int i;

  if (!link || !game)
    return ERROR;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    ;

  if (i == MAX_LINKS)
    return ERROR;

  game->links[i] = link;

  return OK;
}

Id game_get_link_id(Game *game, Id origin, DIRECTION dir)
{
  int i;

  if (game == NULL || origin == NO_ID || dir == NO_DIR)
    return NO_ID;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    if (link_get_origin(game->links[i]) == origin && link_get_direction(game->links[i]) == dir)
      return link_get_id(game->links[i]);

  return NO_ID;
}

Link *game_get_link(Game *game, Id id)
{
  int i;

  if (!game)
    return NULL;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_id(game->links[i]) == id)
      return game->links[i];
  }

  return NULL;
}

STATUS game_set_link_origin(Game *game, Id link_id, Id origin_id)
{
  int i;

  if (game == NULL || link_id == NO_ID || origin_id == NO_ID)
    return ERROR;

  if (game_get_space(game, origin_id) == NULL)
    return ERROR;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_id(game->links[i]) == link_id)
      return link_set_origin(game->links[i], origin_id);
  }

  return ERROR;
}

STATUS game_set_link_destination(Game *game, Id link_id, Id destination_id)
{
  int i;

  if (game == NULL || link_id == NO_ID || destination_id == NO_ID)
    return ERROR;

  if (game_get_space(game, destination_id) == NULL)
    return ERROR;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    if (link_get_id(game->links[i]) == link_id)
      return link_set_destination(game->links[i], destination_id);

  return ERROR;
}

LSTATUS game_get_connection_status(Game *game, Id origin, DIRECTION dir)
{
  int i;

  if (game == NULL || origin == NO_ID || dir == NO_DIR)
    return CLOSE;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_origin(game->links[i]) == origin && link_get_direction(game->links[i]) == dir)
      return link_get_status(game->links[i]);
  }

  return CLOSE;
}

Id game_get_connection(Game *game, Id origin, DIRECTION dir)
{
  int i;

  if (game == NULL || origin == NO_ID || dir == NO_DIR)
    return NO_ID;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_origin(game->links[i]) == origin && link_get_direction(game->links[i]) == dir)
      return link_get_destination(game->links[i]);
  }

  return NO_ID;
}

Id game_get_link_from_space(Game *game, Id orig, DIRECTION dir)
{
  int i;

  if (game == NULL || orig == NO_ID || dir == NO_DIR)
    return NO_ID;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_origin(game->links[i]) == orig && link_get_direction(game->links[i]) == dir)
      return link_get_id(game->links[i]);
  }

  return NO_ID;
}

Id game_get_link_to_space(Game *game, Id dest, DIRECTION dir)
{
  int i;

  if (game == NULL || dest == NO_ID || dir == NO_DIR)
    return NO_ID;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_get_destination(game->links[i]) == dest && link_get_direction(game->links[i]) == dir)
      return link_get_id(game->links[i]);
  }

  return NO_ID;
}

Id game_get_open_link(Game *game, Id origin, DIRECTION dir)
{
  if (game == NULL || origin == NO_ID || dir == NO_DIR)
    return NO_ID;

  if (game_get_connection_status(game, origin, dir) != CLOSE)
    return game_get_connection(game, origin, dir);

  return NO_ID;
}

int game_get_num_links(Game *game)
{
  int i;

  if (game == NULL)
    return -1;

  for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    ;

  return i;
}

Id game_get_link_id_at(Game *game, int position)
{
  if (game == NULL || position < 0 || position >= game_get_num_links(game))
    return NO_ID;

  return link_get_id(game->links[position]);
}

/* Dialogue functions */

Dialogue **game_get_all_dialogues(Game *game, int *num_dialogues)
{
  if (game == NULL || num_dialogues == NULL)
    return NULL;

  (*num_dialogues) = 0;
  while (game->dialogues[*num_dialogues] != NULL)
    (*num_dialogues)++;

  return game->dialogues;
}

BOOL game_existing_dialogue_id(Game *game, Id id)
{
  int i;

  if (game == NULL || id == NO_ID)
    return FALSE;

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
  {
    if (dialogue_get_id(game->dialogues[i]) == id)
      return TRUE;
  }

  return FALSE;
}

STATUS game_add_dialogue(Game *game, Dialogue *dialogue)
{
  int i;

  if (game == NULL || dialogue == NULL || game_existing_dialogue_id(game, dialogue_get_id(dialogue)) == TRUE)
    return ERROR;

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
    ;

  if (i == MAX_DIALOGUES)
    return ERROR;

  game->dialogues[i] = dialogue;

  return OK;
}

STATUS game_add_dialogue_rule(Game *game, Id id, char *rule, DTYPE type)
{
  int i;

  if (game == NULL || id == NO_ID || rule == NULL)
    return ERROR;

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
  {
    if (dialogue_get_id(game->dialogues[i]) == id)
      return dialogue_set_rule(game->dialogues[i], rule, type);
  }

  return ERROR;
}

int game_get_dialogue_executed(Game *game, Id id)
{
  int i;

  if (game == NULL || id == NO_ID)
    return -1;

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
  {
    if (dialogue_get_id(game->dialogues[i]) == id)
      return dialogue_get_executed(game->dialogues[i]);
  }

  return -1;
}

STATUS game_increase_dialogue_executed(Game *game, Id id)
{
  int i;

  if (game == NULL || id == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
  {
    if (dialogue_get_id(game->dialogues[i]) == id)
      return dialogue_increase_executed(game->dialogues[i]);
  }

  return ERROR;
}

STATUS game_decrease_dialogue_executed(Game *game, Id id)
{
  int i;

  if (game == NULL || id == NO_ID)
    return ERROR;

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
  {
    if (dialogue_get_id(game->dialogues[i]) == id)
      return dialogue_decrease_executed(game->dialogues[i]);
  }

  return ERROR;
}

char *game_get_printed_dialogue_rule(Game *game, int position, char *args, T_Command command, STATUS command_status)
{
  int i;

  if (game == NULL || command == NO_CMD)
    return ERROR;

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
  {
    if (dialogue_get_id(game->dialogues[i]) == command)
      return dialogue_get_printed_rule(game->dialogues[i], position, args, command_status);
  }

  return NULL;
}

char *game_get_printed_repeated_error_rule(Game *game, int num_times)
{
  char arg[WORD_SIZE] = "";
  int i;

  if (game == NULL || num_times <= 0)
    return ERROR;

  sprintf(arg, "%d", num_times);

  for (i = 0; i < MAX_DIALOGUES && game->dialogues[i] != NULL; i++)
  {
    if (dialogue_get_id(game->dialogues[i]) == REPEATED_ERROR_ID)
      break;
  }

  if (i == MAX_DIALOGUES)
    return NULL;

  if (num_times == 1)
    return dialogue_get_printed_rule(game->dialogues[i], 0, NULL, ERROR);
  else if (num_times == 2)
    return dialogue_get_printed_rule(game->dialogues[i], 1, NULL, ERROR);
  else
    return dialogue_get_printed_rule(game->dialogues[i], 2, arg, ERROR);
}

char *game_get_move_dialogue_rule(Game *game, DTYPE type)
{
  int i = 0;
  Commands *cmds;
  Space *space = NULL;
  Enemy *enemy = NULL;
  char args[WORD_SIZE] = "";
  char *dir;

  if (game == NULL || game_get_last_command_cmd(game) != MOVE)
    return NULL;

  cmds = game_get_last_command(game);
  dir = commands_get_formatted_direction(cmds);

  if (type == FAILURE)
  {
    if (commands_get_num_args(cmds) == 0)
      return game_get_printed_dialogue_rule(game, 2, NULL, MOVE, ERROR);

    if (dir == NULL)
      return game_get_printed_dialogue_rule(game, 3, NULL, MOVE, ERROR);

    for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    {
      if (link_get_origin(game->links[i]) == player_get_location(game_get_player(game)) && link_get_direction(game->links[i]) == commands_get_direction(cmds))
        return game_get_printed_dialogue_rule(game, 1, NULL, MOVE, ERROR);
    }

    return game_get_printed_dialogue_rule(game, 0, dir, MOVE, ERROR);
  }
  else
  {
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      if (space_get_id(game->spaces[i]) == player_get_location(game_get_player(game)))
      {
        space = game->spaces[i];
        break;
      }
    }

    if (space == NULL)
      return NULL;

    for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
    {
      if (enemy_get_location(game->enemies[i]) == space_get_id(space))
      {
        enemy = game->enemies[i];
        break;
      }
    }

    if (space_get_light(space) == TRUE)
    {
      if (enemy != NULL)
      {
        strcat(args, dir);
        strcat(args, "|");
        strcat(args, space_get_name(space));
        strcat(args, "|");
        strcat(args, enemy_get_name(enemy));

        return game_get_printed_dialogue_rule(game, 1, args, MOVE, OK);
      }
      else
      {
        strcat(args, dir);
        strcat(args, "|");
        strcat(args, space_get_name(space));

        return game_get_printed_dialogue_rule(game, 0, args, MOVE, OK);
      }
    }
    else
    {
      if (enemy != NULL)
      {
        strcat(args, dir);
        strcat(args, "|");
        strcat(args, enemy_get_name(enemy));

        return game_get_printed_dialogue_rule(game, 3, args, MOVE, OK);
      }
      else
        return game_get_printed_dialogue_rule(game, 2, dir, MOVE, OK);
    }
  }
}

char *game_get_attack_dialogue_rule(Game *game)
{
  int player_health, enemy_health, i = 0;
  Enemy *enemy = NULL;

  if (game == NULL || game_get_last_command_cmd(game) != ATTACK)
    return NULL;

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
  {
    if (enemy_get_location(game->enemies[i]) == player_get_location(game_get_player(game)))
    {
      enemy = game->enemies[i];
      break;
    }
  }

  if (enemy == NULL)
    return NULL;

  player_health = player_get_health(game_get_player(game));
  enemy_health = enemy_get_health(enemy);

  if (enemy_health == 0)
    return game_get_printed_dialogue_rule(game, 2, (char *)enemy_get_name(enemy), ATTACK, OK);
  else if (player_health == 0)
    return game_get_printed_dialogue_rule(game, 3, (char *)enemy_get_name(enemy), ATTACK, OK);

  if (command_attack_effect == SUCCESS)
    return game_get_printed_dialogue_rule(game, 0, (char *)enemy_get_name(enemy), ATTACK, OK);
  else
    return game_get_printed_dialogue_rule(game, 1, (char *)enemy_get_name(enemy), ATTACK, OK);
}

char *game_get_take_dialogue_rule(Game *game, DTYPE type)
{
  Commands *cmds;
  char object_name[WORD_SIZE], args[WORD_SIZE] = "";
  Space *space = NULL;
  Object *object = NULL;
  int i;

  if (game == NULL || game_get_last_command_cmd(game) != TAKE)
    return NULL;

  cmds = game_get_last_command(game);

  if ((commands_get_args(cmds, 0)) == NULL)
    return game_get_printed_dialogue_rule(game, 7, NULL, TAKE, ERROR);

  strcpy(object_name, commands_get_args(cmds, 0));
  if (type == FAILURE)
  {
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      if (space_get_id(game->spaces[i]) == player_get_location(game_get_player(game)))
      {
        space = game->spaces[i];
        break;
      }
    }

    if (space == NULL)
      return NULL;

    if (space_get_light(space) == FALSE)
      return game_get_printed_dialogue_rule(game, 2, object_name, TAKE, ERROR);
    else if (player_get_max_objects(game_get_player(game)) == player_get_num_objects(game_get_player(game)))
      return game_get_printed_dialogue_rule(game, 1, object_name, TAKE, ERROR);
    else
    {
      for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
      {
        if (strcasecmp(object_get_name(game->objects[i]), object_name) == 0)
        {
          object = game->objects[i];
          break;
        }
      }

      if (object == NULL)
        return game_get_printed_dialogue_rule(game, 6, object_name, TAKE, ERROR);

      strcpy(object_name, object_get_name(object));

      if (player_has_object(game_get_player(game), object_get_id(object)) == TRUE)
        return game_get_printed_dialogue_rule(game, 5, object_name, TAKE, ERROR);
      else if (object_get_location(object) != space_get_id(space))
        return game_get_printed_dialogue_rule(game, 0, object_name, TAKE, ERROR);
      else if (object_get_movable(object) == FALSE)
        return game_get_printed_dialogue_rule(game, 3, object_name, TAKE, ERROR);
      else if (player_has_object(game_get_player(game), object_get_dependency(object)) == FALSE)
      {
        strcat(args, object_name);
        strcat(args, "|");

        for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
        {
          if (object_get_id(game->objects[i]) == object_get_dependency(object))
          {
            object = game->objects[i];
            break;
          }
        }

        strcat(args, object_get_name(object));

        return game_get_printed_dialogue_rule(game, 4, args, TAKE, ERROR);
      }
      else
        return game_get_printed_dialogue_rule(game, 0, object_name, TAKE, ERROR);
    }
  }
  else
  {
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), object_name) == 0)
      {
        object = game->objects[i];
        break;
      }
    }
    if (game->objects[i] == NULL)
      return game_get_printed_dialogue_rule(game, 0, object_name, TAKE, OK);

    return game_get_printed_dialogue_rule(game, 0, object_get_name(object), TAKE, OK);
  }
}

char *game_get_drop_dialogue_rule(Game *game, DTYPE type)
{
  Commands *cmds;
  char object_name[WORD_SIZE], args[WORD_SIZE] = "";
  Object *object = NULL;
  int i, cont = 0;
  Id *ids;

  if (game == NULL || game_get_last_command_cmd(game) != DROP)
    return NULL;

  cmds = game_get_last_command(game);

  if ((commands_get_args(cmds, 0)) == NULL)
    return game_get_printed_dialogue_rule(game, 3, NULL, DROP, ERROR);

  strcpy(object_name, commands_get_args(cmds, 0));

  if (type == FAILURE)
  {
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), object_name) == 0)
      {
        object = game->objects[i];
        break;
      }
    }

    if (object == NULL)
      return game_get_printed_dialogue_rule(game, 2, object_name, DROP, ERROR);

    ids = game_get_player_objects(game, &cont);
    free(ids);

    strcpy(object_name, object_get_name(object));

    if (cont == 0)
      return game_get_printed_dialogue_rule(game, 0, object_name, DROP, ERROR);

    strcat(args, object_name);
    strcat(args, "|");
    strcat(args, object_name);

    return game_get_printed_dialogue_rule(game, 1, args, DROP, ERROR);
  }
  else
  {
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), object_name) == 0)
      {
        object = game->objects[i];
        strcpy(object_name, object_get_name(game->objects[i]));
        break;
      }
    }

    if (strncasecmp(commands_get_args(game_get_last_command(game), 0), GROUND_NAME, strlen(GROUND_NAME)) == 0)
    {
      if (drop_ground == SUCCESS)
        return game_get_printed_dialogue_rule(game, 3, (char *)space_get_name(game_get_space(game, player_get_location(game_get_player(game)))), DROP, SUCCESS);
      else
        return game_get_printed_dialogue_rule(game, 4, NULL, DROP, SUCCESS);
    }

    if (object == NULL)
      return game_get_printed_dialogue_rule(game, 2, object_name, DROP, ERROR);

    strcat(args, object_get_name(object));
    strcat(args, "|");

    for (i = 0; i < MAX_OBJECTS && DroppedObjects[i] != 0; i++)
    {
      if (DroppedObjects[i] != object_get_id(object))
      {
        if (cont > 0)
          strcat(args, ", ");

        strcat(args, object_get_name(game_get_object(game, DroppedObjects[i])));
        cont++;
      }
    }

    if (cont == 1)
      return game_get_printed_dialogue_rule(game, 1, args, DROP, OK);
    else if (cont > 1)
      return game_get_printed_dialogue_rule(game, 2, args, DROP, OK);

    strcat(args, space_get_name(game_get_space(game, player_get_location(game_get_player(game)))));

    return game_get_printed_dialogue_rule(game, 0, args, DROP, OK);
  }
}

char *game_get_inspect_dialogue_rule(Game *game, DTYPE type)
{
  Commands *cmds;
  char *inspect_name;
  Space *space;
  int i, flag = 0;

  if (game == NULL || game_get_last_command_cmd(game) != INSPECT)
    return NULL;

  cmds = game_get_last_command(game);

  if ((inspect_name = commands_get_args(cmds, 0)) == NULL)
    return game_get_printed_dialogue_rule(game, 1, NULL, INSPECT, ERROR);

  if (strcasecmp(inspect_name, "space") == 0 || strcasecmp(inspect_name, "s") == 0)
  {
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      if (space_get_id(game->spaces[i]) == player_get_location(game_get_player(game)))
      {
        space = game->spaces[i];
        break;
      }
    }

    if (space == NULL)
      return NULL;

    inspect_name = (char *)space_get_name(space);
    flag = 1;
  }

  if (type == FAILURE)
    return game_get_printed_dialogue_rule(game, 0, inspect_name, INSPECT, ERROR);
  else
  {
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), inspect_name) == 0)
      {
        strcpy(inspect_name, object_get_name(game->objects[i]));
        break;
      }
    }

    if (flag == 1)
      return game_get_printed_dialogue_rule(game, 1, inspect_name, INSPECT, OK);
    else
      return game_get_printed_dialogue_rule(game, 0, inspect_name, INSPECT, OK);
  }
}

char *game_get_turn_on_off_dialogue_rule(Game *game, T_Command command, DTYPE type)
{
  Commands *cmds;
  char object_name[WORD_SIZE];
  int i;
  Object *object = NULL;

  if (game == NULL || (command != TURNON && command != TURNOFF))
    return NULL;

  cmds = game_get_last_command(game);

  if ((commands_get_args(cmds, 0)) == NULL)
    return game_get_printed_dialogue_rule(game, 4, NULL, command, ERROR);

  strcpy(object_name, commands_get_args(cmds, 0));

  if (type == FAILURE)
  {
    if (commands_get_num_args(cmds) == 0)
      return game_get_printed_dialogue_rule(game, 4, NULL, command, ERROR);

    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
      if (strcasecmp(object_get_name(game->objects[i]), object_name) == 0)
      {
        object = game->objects[i];
        break;
      }

    if (object == NULL)
      return game_get_printed_dialogue_rule(game, 2, NULL, command, ERROR);

    strcpy(object_name, object_get_name(object));

    if (player_has_object(game_get_player(game), object_get_id(object)) == FALSE && object_get_location(object) != player_get_location(game_get_player(game)))
      return game_get_printed_dialogue_rule(game, 3, object_name, command, ERROR);

    if (space_get_light(game_get_space(game, player_get_location(game_get_player(game)))) == FALSE && game_player_has_light(game) == FALSE)
      return game_get_printed_dialogue_rule(game, 1, object_name, command, ERROR);

    return game_get_printed_dialogue_rule(game, 0, object_name, command, ERROR);
  }
  else
  {
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), object_name) == 0)
      {
        strcpy(object_name, object_get_name(game->objects[i]));
        break;
      }
    }

    return game_get_printed_dialogue_rule(game, 0, object_name, command, OK);
  }
}

char *game_get_open_close_link_dialogue_rule(Game *game, T_Command command, DTYPE type)
{
  Commands *cmds;
  char args[WORD_SIZE] = "";
  int i;
  Space *space1 = NULL, *space2 = NULL;
  Link *link = NULL;
  Object *object = NULL;

  if (game == NULL || (command != CLOSELINK && command != OPENLINK))
    return NULL;

  cmds = game_get_last_command(game);

  if (type == FAILURE)
  {
    if (commands_get_num_args(cmds) < 3)
    {
      if (commands_get_num_args(cmds) == 0)
        return game_get_printed_dialogue_rule(game, 8, NULL, command, ERROR);
      else if (commands_get_num_args(cmds) == 1)
        return game_get_printed_dialogue_rule(game, 8, NULL, command, ERROR);
      else if (strcasecmp(commands_get_args(cmds, 0), "with") == 0)
        return game_get_printed_dialogue_rule(game, 7, NULL, command, ERROR);
      else if (strcasecmp(commands_get_args(cmds, 1), "with") == 0)
        return game_get_printed_dialogue_rule(game, 6, NULL, command, ERROR);
      else
        return game_get_printed_dialogue_rule(game, 5, NULL, command, ERROR);
    }

    if (strcasecmp(commands_get_args(cmds, 1), "with") != 0)
      return game_get_printed_dialogue_rule(game, 5, NULL, command, ERROR);

    for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    {
      if (strcasecmp(link_get_name(game->links[i]), commands_get_args(cmds, 0)) == 0)
      {
        link = game->links[i];
        break;
      }
    }

    if (commands_get_direction(cmds) == NO_DIR && link == NULL)
      return game_get_printed_dialogue_rule(game, 3, NULL, command, ERROR);

    if (commands_get_direction(cmds) != NO_DIR)
    {
      if ((link = game_get_link(game, game_get_link_id(game, player_get_location(game_get_player(game)), commands_get_direction(cmds)))) == NULL)
        return game_get_printed_dialogue_rule(game, 9, NULL, command, ERROR);
    }
    else
    {
      for (i = 0, link = NULL; i < MAX_LINKS && game->links[i] != NULL; i++)
      {
        if (strcasecmp(link_get_name(game->links[i]), commands_get_args(cmds, 0)) == 0)
        {
          if (link_get_origin(game->links[i]) == player_get_location(game_get_player(game)))
          {
            link = game->links[i];
            break;
          }
        }
      }

      if (link == NULL)
        return game_get_printed_dialogue_rule(game, 1, NULL, command, ERROR);
    }

    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), commands_get_args(cmds, 2)) == 0)
      {
        object = game->objects[i];
        break;
      }
    }

    if (object == NULL)
      return game_get_printed_dialogue_rule(game, 2, NULL, command, ERROR);

    if (player_has_object(game_get_player(game), object_get_id(object)) == FALSE)
    {
      if (object_get_location(object) != player_get_location(game_get_player(game)))
        return game_get_printed_dialogue_rule(game, 4, object_get_name(object), command, ERROR);
    }

    strcat(args, commands_get_args(cmds, 0));
    strcat(args, "|");
    strcat(args, object_get_name(object));

    return game_get_printed_dialogue_rule(game, 0, args, command, ERROR);
  }
  else
  {
    for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
    {
      if ((strcasecmp(link_get_name(game->links[i]), commands_get_args(cmds, 0)) == 0) || (link_get_direction(game->links[i]) == commands_get_direction(cmds) && link_get_origin(game->links[i]) == player_get_location(game_get_player(game))))
      {
        link = game->links[i];
        break;
      }
    }

    if (link == NULL)
      return NULL;

    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), commands_get_args(cmds, 2)) == 0)
      {
        object = game->objects[i];
        break;
      }
    }

    strcat(args, link_get_name(link));
    strcat(args, "|");
    strcat(args, object_get_name(object));
    strcat(args, "|");

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      if (space_get_id(game->spaces[i]) == link_get_origin(link))
        space1 = game->spaces[i];

      if (space_get_id(game->spaces[i]) == link_get_destination(link))
        space2 = game->spaces[i];
    }

    if (space1 == NULL || space2 == NULL)
      return NULL;

    strcat(args, space_get_name(space1));
    strcat(args, "|");
    strcat(args, space_get_name(space2));

    return game_get_printed_dialogue_rule(game, 0, args, command, OK);
  }
}

char *game_get_dialogue_of_defeat(Game *game){
  char args[100], *dialogue= NULL;
  if(!game)
    return NULL;
  
  switch (game->num_executed_commands)
  {
  case VICTORY:
    return NULL;
  case DEATH:
      return NULL;
  case STICK_NO_ACC:

    strncpy(args,"Sticks", 7);
    dialogue=game_get_printed_dialogue_rule(game, 0, args, REPEATED_ERROR_ID+3, OK);
    break;

  case LEAF_NO_ACC:
    strncpy(args,"Leafs",6);
    dialogue=game_get_printed_dialogue_rule(game, 0, args, REPEATED_ERROR_ID+3, OK);
    break;
  case WALNUT_NO_ACC:
    strncpy(args,"Walnuts",8);
    dialogue=game_get_printed_dialogue_rule(game, 0, args, REPEATED_ERROR_ID+3, OK);
    break;
  case BOAT_NO_ACC:
    dialogue=game_get_printed_dialogue_rule(game, 1, args, REPEATED_ERROR_ID+3, OK);
    break;
  case HARBOUR_NO_ACC:
    dialogue=game_get_printed_dialogue_rule(game, 2, args,REPEATED_ERROR_ID+3, OK);
    break;
  case WORKSHOP_NO_ACC:
    dialogue=game_get_printed_dialogue_rule(game, 3, args, REPEATED_ERROR_ID+3, OK);
    break;
  default:
  break;
  }
  return dialogue;

}

char **game_get_dialogue_of_game_rule(Game *game, int *num_dialogues)
{
  int i, j, count1 = 0, count2 = 0, n_act, indexrule, indexact, n_flooded, indexcombine[MAX_RULES], indexesact[MAX_RULES], n_indexes = 0, argint;
  BOOL inundation = FALSE, combine = FALSE;
  char *dialogues[MAX_RULES], *aux = NULL, args[WORD_SIZE] = "", *argname, **retorno, cadena[WORD_SIZE] = "";

  if (!game || !num_dialogues)
    return NULL;
  *num_dialogues = 0;

  for (i = 0; i < MAX_RULES && game->rules[i] != NULL; i++)
  {
    n_act = rule_get_num_actions(game->rules[i]);
    if (rule_get_executed(game->rules[i]) == TRUE)
    {
      for (j = 0; j < n_act; j++)
      {
        if (rule_action_get_type(rule_get_action(game->rules[i], j)) == INUNDATION)
        {
          inundation = TRUE;
          indexrule = i;
          indexact = j;
        }
        if (rule_action_get_type(rule_get_action(game->rules[i], j)) == COMBINE)
        {
          combine = TRUE;
          indexcombine[n_indexes] = i;
          indexesact[n_indexes] = j;
          n_indexes++;
        }
      }
    }
  }

  if (inundation)
  {
    if (player_get_health(game_get_player(game)) == 0 /*&& game_check_harbour_sunk(game)==TRUE*/){
      sprintf(cadena,"%ld",player_get_location(game_get_player(game)));
      aux = game_get_printed_dialogue_rule(game, 5,cadena, REPEATED_ERROR_ID + 1, OK);
    }
    else
    {
      n_flooded = rule_action_get_argint(rule_get_action(game->rules[indexrule], indexact));

      for (j = 0, count1 = 0; j < n_flooded; j++)
      {
        if (JustFlooded[j] != NO_ID)
        {
          if (game_get_space(game, JustFlooded[j]) != NULL)
          {
            if (count1 == 0)
            {
              strcat(args, JustFloodedName[j]);
              strcat(args, "(");
              sprintf(cadena, "Id:%ld", JustFlooded[j]);
              strcat(args, cadena);
              strcat(args, ")");
            }
            else
            {
              strcat(args, ", ");
              strcat(args, JustFloodedName[j]);
              strcat(args, "(");
              sprintf(cadena, "Id:%ld", JustFlooded[j]);
              strcat(args, cadena);
              strcat(args, ")");
            }
            count1++;
          }
        }
      }

      for (j = 0, count2 = 0; j < n_flooded; j++)
      {
        if (JustFlooded[j] != NO_ID)
        {
          if (game_get_space(game, JustFlooded[j]) == NULL)
          {
            if (count2 == 0)
            {
              if (count1 > 0)
                strcat(args, "|");
              strcat(args, JustFloodedName[j]);
              strcat(args, "(");
              sprintf(cadena, "Id:%ld", JustFlooded[j]);
              strcat(args, cadena);
              strcat(args, ")");
            }
            else
            {
              strcat(args, ", ");
              strcat(args, JustFloodedName[j]);
              strcat(args, "(");
              sprintf(cadena, "Id:%ld", JustFlooded[j]);
              strcat(args, cadena);
              strcat(args, ")");
            }
            count2++;
          }
        }
      }

      if (count1 == 0)
        aux = game_get_printed_dialogue_rule(game, 4, args, REPEATED_ERROR_ID + 1, OK);
      else if (count2 == 0)
        aux = game_get_printed_dialogue_rule(game, 0, args, REPEATED_ERROR_ID + 1, OK);
      else if (count1 == 1)
        aux = game_get_printed_dialogue_rule(game, 2, args, REPEATED_ERROR_ID + 1, OK);
      else if (count2 == 1)
        aux = game_get_printed_dialogue_rule(game, 3, args, REPEATED_ERROR_ID + 1, OK);
      else
        aux = game_get_printed_dialogue_rule(game, 1, args, REPEATED_ERROR_ID + 1, OK);
    }

    dialogues[*num_dialogues] = aux;
    (*num_dialogues)++;
  }

  if (combine)
  {
    for (i = 0; i < n_indexes; i++)
    {
      args[0] = 0;
      argint = rule_action_get_argint(rule_get_action(game->rules[indexcombine[i]], indexesact[i]));

      argname = rule_action_get_argname(rule_get_action(game->rules[indexcombine[i]], indexesact[i]));
      if (strcmp(argname, "Boat") == 0)
      {
        sprintf(cadena, " ");
        strcat(args, cadena);
        strcat(args, "|");
        strcat(args, "a Sail, a Mast and a Hull");
      }
      else
      {
        sprintf(cadena, "%d", argint);
        strcat(args, cadena);
        strcat(args, "|");
        strcat(args, argname);
      }

      strcat(args, "|");
      strcat(args, game_get_upgraded_name(argname));
      aux = game_get_printed_dialogue_rule(game, 0, args, REPEATED_ERROR_ID + 2, OK);

      dialogues[*num_dialogues] = aux;
      (*num_dialogues)++;
    }
  }

  if ((*num_dialogues) == 0)
    return NULL;

  if ((retorno = (char **)calloc((*num_dialogues), sizeof(char *))) == NULL)
  {
    for (i = 0; i < *num_dialogues; i++)
      free(dialogues[i]);
    return NULL;
  }

  for (i = 0; i < *num_dialogues; i++)
    retorno[i] = dialogues[i];

  return retorno;
}

char *game_get_upgraded_name(char *name)
{
  int i;

  if (!name)
    return NULL;

  for (i = 0; i < N_OBJ_TYPES; i++)
  {
    if (strcasecmp(upgrades_object[i][NOT_UPGRADED], name) == 0)
      return upgrades_object[i][UPGRADED];
  }

  return NULL;
}

/*************************************************************** Command functions******************************************************************* */

Commands *game_get_last_command(Game *game)
{
  if (game == NULL)
    return NULL;

  return game->last_cmd;
}

T_Command game_get_last_command_cmd(Game *game)
{
  if (game == NULL)
    return NO_CMD;

  return commands_get_cmd(game->last_cmd);
}

STATUS game_get_last_command_status(Game *game)
{
  if (game == NULL)
    return NO_CMD;

  return commands_get_status(game->last_cmd);
}

int game_get_num_executed_commands(Game *game)
{
  if (game == NULL)
    return -1;

  return game->num_executed_commands;
}

STATUS game_set_num_executed_commands(Game *game, int num)
{
  if (game == NULL || num < 0)
    return ERROR;

  game->num_executed_commands = num;

  return OK;
}

int game_get_num_commands_per_flood(Game *game)
{
  int i, j, k, n_cond, n_act;
  if (!game)
    return -1;

  for (i = 0; i < MAX_RULES && game->rules[i] != NULL; i++)
  {
    n_act = rule_get_num_actions(game->rules[i]);
    for (j = 0; j < n_act; j++)
    {
      if (rule_action_get_type(rule_get_action(game->rules[i], j)) == INUNDATION)
      {
        n_cond = rule_get_num_conditions(game->rules[i]);
        for (k = 0; k < n_cond; k++)
        {
          if (rule_condition_get_type(rule_get_condition(game->rules[i], k)) == N_COMANDS)
            return rule_condition_get_argint(rule_get_condition(game->rules[i], k));
        }
      }
    }
  }
  return -1;
}

int game_get_num_commands_till_flood(Game *game)
{
  int n;

  if ((n = game_get_num_commands_per_flood(game)) == -1)
    return -1;

  return n - game_get_num_executed_commands(game) % n;
}
/*tdesc functions*/

char *game_get_last_tdesc(Game *game)
{
  if (game == NULL)
    return NULL;

  return game->last_tdesc;
}

STATUS game_set_last_tdesc(Game *game, char *tdesc)
{
  if (game == NULL)
    return ERROR;

  game->last_tdesc = tdesc;
  return OK;
}

/*idesc functions*/

char *game_get_last_idesc(Game *game)
{
  if (game == NULL)
    return NULL;

  return game->last_idesc;
}

STATUS game_set_last_idesc(Game *game, char *idesc)
{
  if (game == NULL)
    return ERROR;

  game->last_idesc = idesc;
  return OK;
}



/***************************************************************rule functions*********************************************************************/



Rule *game_get_rule(Game *game, Id id)
{
  int i;

  if (game == NULL || id == NO_ID)
    return NULL;

  for (i = 0; i < MAX_RULES && game->rules[i] != NULL; i++)
  {
    if (rule_get_id(game->rules[i]) == id)
      return game->rules[i];
  }

  return NULL;
}

Id game_get_rule_id_at(Game *game, int position)
{
  if (game == NULL || position < 0 || position >= game_get_num_rules(game))
    return NO_ID;

  return rule_get_id(game->rules[position]);
}

int game_get_num_rules(Game *game)
{
  int i;

  if (game == NULL)
    return -1;

  for (i = 0; i < MAX_RULES && game->rules[i] != NULL; i++)
    ;

  return i;
}

STATUS game_add_rule(Game *game, Rule *rule)
{
  int i;

  if (game == NULL || rule == NULL)
    return ERROR;

  for (i = 0; i < MAX_RULES && game->rules[i] != NULL; i++)
    ;

  if (i == MAX_RULES)
    return ERROR;

  game->rules[i] = rule;

  return OK;
}

STATUS game_rule_evaluate_execute_all(Game *game)
{
  int i;
  STATUS st = OK;

  if (!game)
    return ERROR;

  for (i = 0; i < MAX_RULES && game->rules != NULL; i++)
    if (game_rule_evaluate(game, game->rules[i]) == TRUE)
    {
      st = game_rule_execute(game, game->rules[i]);
      rule_set_executed(game->rules[i], TRUE);
    }

  return st;
}

STATUS game_rule_execute(Game *game, Rule *rule)
{
  int i;
  STATUS st = OK;

  if (!game || !rule)
    return ERROR;

  for (i = 0; i < rule_get_num_actions(rule) && st == OK; i++)
    st = game_rule_execute_action(game, rule_get_action(rule, i));

  return st;
}

BOOL game_rule_evaluate(Game *game, Rule *rule)
{
  int i;
  BOOL eval = TRUE;
  if (!game || !rule)
    return FALSE;

  for (i = 0; i < rule_get_num_conditions(rule) && eval == TRUE; i++)
    eval = game_rule_evaluate_condition(game, rule_get_condition(rule, i));

  return eval;
}

BOOL game_check_harbour_sunk(Game *game)
{
  BOOL eval = TRUE;
  int i;
  if (!game)
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL && eval == TRUE; i++)
    {
      if (strcasecmp(space_get_name(game->spaces[i]), HARBOUR) == 0)
        eval = FALSE;
    }
  return eval;
}

BOOL game_rule_evaluate_condition(Game *game, Condition *condition)
{
  int i, numId, argint, n_objs = 0, len, count = 0;
  Id *argsId, *objs;
  char argname[WORD_SIZE];

  BOOL eval = FALSE;
  T_CONDITION tcond;

  if (!game || !condition)
    return FALSE;

  /*Get all arguments*/
  tcond = rule_condition_get_type(condition);
  numId = rule_condition_get_numId(condition);
  argsId = rule_condition_get_argsId(condition);
  argint = rule_condition_get_argint(condition);
  strcpy(argname, rule_condition_get_argname(condition));

  switch (tcond)
  {
  case IN_SPACE:
    if (player_get_location(game_get_player(game)) == argsId[0])
      eval = TRUE;
    if (strcasecmp(space_get_name(game_get_space(game, player_get_location(game_get_player(game)))), argname) == 0)
      eval = TRUE;
    break;

  case HAS_OBJECT:
    eval = TRUE;
    for (i = 0; i < numId && eval == TRUE; i++)
      eval = player_has_object(game_get_player(game), argsId[i]);
    break;

  case HEALTH_POINTS_P:
    if (player_get_health(game_get_player(game)) == argint)
      eval = TRUE;
    break;

  case HEALTH_POINTS_E:
    eval = FALSE;
    for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
    {
      if (enemy_get_location(game->enemies[i]) == player_get_location(game_get_player(game)))
      {
        eval = TRUE;
        if (enemy_get_health(game->enemies[i]) > argint)
          eval = FALSE;
      }
    }
    break;

  case N_COMANDS:
    eval = game_get_num_executed_commands(game) % argint == 0;
    break;

  case DROP_OBJ:

    if (commands_get_cmd(game_get_last_command(game)) == DROP && strcasecmp(commands_get_args(game_get_last_command(game), 0), BOAT) == 0)
      eval = TRUE;
    else if (commands_get_cmd(game_get_last_command(game)) == DROP && strncasecmp(commands_get_args(game_get_last_command(game), 0), GROUND_NAME, strlen(GROUND_NAME)) == 0 && space_get_flooded(game_get_space(game, player_get_location(game_get_player(game)))) == FLOODED)
    {
      eval = TRUE;
      objs = space_get_objects(game_get_space(game, player_get_location(game_get_player(game))), &n_objs);

      for (i = 0; i < n_objs; i++)
      {
        if (strcasecmp(object_get_name(game_get_object(game, objs[i])), commands_get_args(game_get_last_command(game), 0)) == 0)
        {
          space_remove_object(game_get_space(game, player_get_location(game_get_player(game))), objs[i]);
          game_delete_object(game, objs[i]);
          break;
        }
      }
      free(objs);
    }
    break;
  case SAME_OBJECT:
    if (space_get_name(game_get_space(game, player_get_location(game_get_player(game)))) != NULL)
    {
      if (strncasecmp(space_get_name(game_get_space(game, player_get_location(game_get_player(game)))), WORKSHOP, strlen(WORKSHOP)) == 0)
      {
        objs = player_get_objects(game_get_player(game), &n_objs);
        len = strlen(argname);
        if (objs)
        {
          for (i = 0, count = 0; i < n_objs && count < argint; i++)
          {
            if (strncasecmp(object_get_name(game_get_object(game, objs[i])), argname, len) == 0)
              count++;
          }
          if (count == argint)
            eval = TRUE;
          free(objs);
        }
      }
    }

    break;
  case PLAYER_TYPE:
    eval = player_get_type(game_get_player(game)) == (T_PlayerType)argint;
    break;
  case HAS_SUNK:
    for (i = 0, eval = TRUE; i < MAX_SPACES && game->spaces[i] != NULL && eval == TRUE; i++)
    {
      if (strcasecmp(space_get_name(game->spaces[i]), argname) == 0)
        eval = FALSE;
    }
    break;
  case NO_PATH_TO_N_OBJ:
     eval =  !game_rule_get_path_to_type_of_object(game,player_get_location(game_get_player(game)),object_translate_object_type(argname),argint);
    break;
  case NO_PATH_TO_NAME:
        eval = !game_rule_get_path_to_space_by_name(game,player_get_location(game_get_player(game)),argname);
  break;  
  case OBJECT_NOT_BUILT_OR_NOT_ACCESIBLE:
    eval = FALSE;
    for(i=0;i<MAX_OBJECTS && game->objects[i]!=NULL && eval == FALSE;i++){
      if(!strcasecmp(object_get_name( game->objects[i]),argname)){
        if(object_get_location(game->objects[i])==NO_ID ||!game_get_path(game,player_get_location(game_get_player(game)),object_get_location(game->objects[i])==NO_ID))
        eval = TRUE;
      }
    }
  break;
  default:
    break;
  }

  return eval;
}

STATUS game_rule_execute_action(Game *game, Action *action)
{
  int i, numId, argint, len, n_objs = 0, indexs[MAX_OBJECTS], count;
  Id *argsId, *objs;
  STATUS st = OK;
  char argname[WORD_SIZE];
  T_ACTION tact;
  Id *idsflood;

  if (!game || !action)
    return FALSE;

  /*Get all arguments*/
  tact = rule_action_get_type(action);
  numId = rule_action_get_numId(action);
  argsId = rule_action_get_argsId(action);
  argint = rule_action_get_argint(action);
  strcpy(argname, rule_action_get_argname(action));

  switch (tact)
  {
  case ATTACK_P:
    st = player_set_health(game_get_player(game), player_get_health(game_get_player(game)) - argint);
    break;

  case HEAL_P:
    st = player_set_health(game_get_player(game), player_get_health(game_get_player(game)) + argint);
    break;

  case ATTACK_E:
    for (i = 0; i < numId && st == OK; i++)
      st = enemy_set_health(game_get_enemy(game, argsId[i]), enemy_get_health(game_get_enemy(game, argsId[i])) - argint);
    break;

  case HEAL_E:
    for (i = 0; i < numId && st == OK; i++)
      st = enemy_set_health(game_get_enemy(game, argsId[i]), enemy_get_health(game_get_enemy(game, argsId[i])) + argint);
    break;

  case OPEN_LINK:
    for (i = 0; i < numId && st == OK; i++)
      st = link_set_status(game_get_link(game, argsId[i]), OPEN);
    break;

  case CLOSE_LINK:
    for (i = 0; i < numId && st == OK; i++)
      st = link_set_status(game_get_link(game, argsId[i]), CLOSE);
    break;

  case INUNDATION:

    if ((idsflood = game_get_rand_space_id(game, argint)) == NULL)
      return ERROR;

    for (i = 0; i < argint; i++)
    {
      if (idsflood[i] == NO_ID)
        break;

      JustFlooded[i] = idsflood[i];
      strcpy(JustFloodedName[i], space_get_name(game_get_space(game, idsflood[i])));

      st = space_set_flooded(game_get_space(game, idsflood[i]), (SSTATUS)(space_get_flooded(game_get_space(game, idsflood[i])) + 1));

      if (space_get_flooded(game_get_space(game, idsflood[i])) == SUNK)
      {
        if (player_get_location(game_get_player(game)) == idsflood[i])
          player_set_health(game_get_player(game), 0);

        game_delete_space(game, idsflood[i]);
      }
    }
    JustFlooded[i] = NO_ID;

    free(idsflood);
    break;
  case SAVE_SPACE:
    if (space_get_flooded(game_get_space(game, player_get_location(game_get_player(game)))) != SAFE)
    {
      drop_ground = SUCCESS;
      st = space_set_flooded(game_get_space(game, player_get_location(game_get_player(game))), (SSTATUS)(space_get_flooded(game_get_space(game, player_get_location(game_get_player(game)))) - 1));
    }
    else
      drop_ground = FAILURE;
    break;

  case SPAWN_GROUND:
    st = game_rule_spawn_ground(game, argint);
    break;

  case COMBINE:

    objs = player_get_objects(game_get_player(game), &n_objs);
    len = strlen(argname);

    for (i = 0, count = 0; i < n_objs && count < argint; i++)
    {
      if (strncasecmp(object_get_name(game_get_object(game, objs[i])), argname, len) == 0)
      {
        indexs[count] = i;
        count++;
      }
    }

    for (i = 0; i < argint; i++)
    {
      player_remove_object(game_get_player(game), objs[indexs[i]]);
      game_delete_object(game, objs[indexs[i]]);
    }

    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    {
      if (strcasecmp(object_get_name(game->objects[i]), game_get_upgraded_name(argname)) == 0)
      {
        (void)object_set_location(game->objects[i], ON_PLAYER);
        (void)player_add_object(game_get_player(game), object_get_id(game->objects[i]));

        break;
      }
    }
    free(objs);
    break;
  case SET_MOVABLE:
    objs = space_get_objects(game_get_space(game, player_get_location(game_get_player(game))), &n_objs);

    if (objs)
    {
      for (i = 0; i < n_objs; i++)
        object_set_movable(game_get_object(game, objs[i]), (BOOL)argint);
    }
    free(objs);
    break;

  case VICTORY_ACT:
    if (commands_get_cmd(game_get_last_command(game)) == DROP && strcasecmp(commands_get_args(game_get_last_command(game), 0), BOAT) == 0)
      game->num_executed_commands = VICTORY;
    break;
  case DEFEAT_ACT:
    game->num_executed_commands = VICTORY + argint; /*En el Argint esta codificado que fin de partida se da*/
    FILE *f;
    f = fopen("path.log", "a");
    fprintf(f,"NUM: %d %d",game->num_executed_commands, argint);
    fclose(f);
    break;
  default:
    st = ERROR;
    break;
  }
  return st;
}

BOOL game_rule_get_path_to_type_of_object(Game *game, Id orig, T_ObjectType type, int num)
{
  int i, count = 0;
  
  if (!game || orig == NO_ID || type == NO_OTYPE)
    return TRUE;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL && count < num; i++)
  {
    if (object_get_type(game->objects[i]) == type)
    {
      count += game_get_path(game, orig, object_get_location(game->objects[i]));
    }
  }
  return count >= num;
}

BOOL game_rule_get_path_to_space_by_name(Game *game, Id orig, char *space_name)
{

  int i;
  BOOL b = FALSE;
  if (!game || orig == NO_ID || !space_name)
    return TRUE;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL && b == FALSE; i++)
  {
    if (!strcasecmp(space_get_name(game->spaces[i]), space_name))
    {
      game_get_path(game, orig, space_get_id(game->spaces[i]));
      b = TRUE;
    }
  }
  return b;
}

BOOL game_get_path_rec(Game *game, Id orig, Id dest, BOOL *array)
{
  int i;
  Id id;
  BOOL b = FALSE;
  if (orig == dest)
    return TRUE;
  if(array[(int)orig] == TRUE){
    return FALSE; 
  } 

  array[(int)orig]=TRUE;
  for (i = 0; i < N_DIR && b == FALSE; i++)
  {

    id = game_get_connection(game, orig, i);

    if (id != NO_ID)
      b=game_get_path_rec(game, id, dest,array);
  }
  if(b == FALSE && orig>=100 && player_get_type(game_get_player(game))==BUTTERFLY)
      b=game_get_path_rec(game, orig-100, dest,array);
  if(b == FALSE && orig<200 && player_get_type(game_get_player(game))==BUTTERFLY)
      b=game_get_path_rec(game, orig+100, dest,array);
  return b;
}

BOOL game_get_path(Game *game, Id orig, Id dest)
{
  int i;
  BOOL *array;
  BOOL b;
  /*DIEGO:*/
  FILE *fpath;
  /*************/
  if (!game || orig == NO_ID)
    return FALSE;
  if(dest == NO_ID|| dest == ON_PLAYER)
    return TRUE;
  array =(BOOL*) calloc(1000,sizeof(BOOL));
  for(i= 0 ; i< 1000; i++){
    array[i] = FALSE;
  }
    if(!array)
     return TRUE;
  /*DIEGO PRUEBAS PATH*/
  fpath= fopen("path.log", "a");
      fprintf(fpath,"\nBUSCAMOS : %d->%d",orig,dest);

    /*DIEGO FIN PRUEBAS PATH*/

  b = game_get_path_rec(game, orig, dest,array);
    fprintf(fpath,"  BOOL : %d",b);

  free(array);
  /*DIEGO PRUEBAS PATH*/
  fclose(fpath);
    /*DIEGO FIN PRUEBAS PATH*/
  return b;
}

STATUS game_rule_spawn_ground(Game *game, int argint)
{
  int i, ant = 0;
  Id *idsspace;
  Object *obj;

  if (player_get_type(game_get_player(game)) == ANT)
    ant = 1;
  if (number_of_grounds + argint <= MAX_GROUND + ant * EXTRASANT)
  {
    if ((idsspace = game_get_rand_space_id(game, argint)) == NULL)
      return ERROR;

    for (i = 0; i < argint; i++)
    {
      obj = object_create(game_get_unique_object_id(game));
      number_of_grounds++;

      if (game_add_object(game, obj) == ERROR)
      {
        object_destroy(obj);
        free(idsspace);
        return ERROR;
      }

      if (object_set_name(obj, GROUND_NAME) == ERROR)
      {
        object_destroy(obj);
        free(idsspace);
        return ERROR;
      }

      object_set_location(obj, idsspace[i]);
      object_set_hidden(obj, FALSE);
      object_set_movable(obj, TRUE);
      object_set_dependency(obj, NO_ID);
      object_set_open(obj, NO_ID);
      object_set_illuminate(obj, FALSE);
      object_set_turnedon(obj, FALSE);
      object_set_tdesc(obj, GROUND_DESCRIPTION);

      if (space_add_object(game_get_space(game, idsspace[i]), object_get_id(obj)) == ERROR)
      {
        object_destroy(obj);
        free(idsspace);
        return ERROR;
      }
    }

    free(idsspace);
  }

  return OK;
}

/**
   Calls implementation for each action
*/
STATUS game_command_unknown(Game *game)
{
  if (game == NULL)
    return ERROR;

  return ERROR;
}

STATUS game_command_exit(Game *game)
{
  if (game == NULL)
    return ERROR;

  fprintf(stdout, "\nHAVE FUN & THANKS FOR PLAYING OUR GAME\n");
  return OK;
}

STATUS game_command_move(Game *game, DIRECTION direction)
{
  Id moveto_id = NO_ID;
  Id space_id = NO_ID;

  if (game == NULL)
    return ERROR;

  space_id = player_get_location(game_get_player(game));
  if (space_id == NO_ID)
    return ERROR;

  if (player_get_type(game_get_player(game)) == BUTTERFLY)
  {
    if ((direction == UP) && ((moveto_id = space_get_id(game_get_space(game, space_id + 100))) != NO_ID))
    {
      player_set_location(game_get_player(game), moveto_id);
      return OK;
    }

    if ((direction == DOWN) && ((moveto_id = space_get_id(game_get_space(game, space_id - 100))) != NO_ID))
    {
      player_set_location(game_get_player(game), moveto_id);
      return OK;
    }
  }

  moveto_id = game_get_open_link(game, space_id, direction);

  if (moveto_id != NO_ID)
  {
    player_set_location(game_get_player(game), moveto_id);
    return OK;
  }
  else
    return ERROR;
}

STATUS game_command_attack(Game *game)
{
  int aleat, i;
  Enemy *enemy;

  if (game == NULL)
    return ERROR;

  for (i = 0; i < MAX_ENEMIES && game_get_enemy_id_at(game, i); i++)
  {
    enemy = game_get_enemy(game, game_get_enemy_id_at(game, i));
    if (enemy_get_location(enemy) == player_get_location(game_get_player(game)))
      break;
  }

  if (enemy != NULL)
  {
    if (enemy_get_health(enemy) > 0)
    {
      aleat = rand() % 10;

      if (aleat < PROB_VICT_ATACK)
      {
        if (player_get_type(game_get_player(game)) == SCORPION)
        {
          enemy_set_health(enemy, enemy_get_health(enemy) - 1 - EXTRASCORP);

          if (enemy_get_health(enemy) < 0)
            enemy_set_health(enemy, 0);
        }
        else
          enemy_set_health(enemy, enemy_get_health(enemy) - 1);

        command_attack_effect = SUCCESS;
      }
      else
      {
        player_set_health(game->player, player_get_health(game->player) - 1);
        command_attack_effect = FAILURE;
      }

      return OK;
    }
    else
      return ERROR;
  }
  else
    return ERROR;
}

STATUS game_command_take(Game *game, Commands *cmds)
{
  int i, nobj;
  Id *objs_id;
  Id space_id = NO_ID;
  Object *obj;
  Space *space = NULL;
  char obj_name[WORD_SIZE + 1];

  if (game == NULL || cmds == NULL)
    return ERROR;

  if ((commands_get_num_args(cmds) == 0) || ((space_id = player_get_location(game_get_player(game))) == NO_ID))
    return ERROR;

  strcpy(obj_name, commands_get_args(cmds, 0));

  if (((space = game_get_space(game, space_id)) == NULL) || (player_get_num_objects(game->player) >= player_get_max_objects(game->player)))
    return ERROR;

  if ((objs_id = space_get_objects(space, &nobj)) == NULL)
    return ERROR;

  if ((space_get_light(space) == FALSE && game_player_has_light(game) == FALSE) || space_get_flooded(space) != SAFE) /*If the space is available*/
  {
    free(objs_id);
    return ERROR;
  }

  for (i = 0; i < nobj; i++)
  {
    if ((obj = game_get_object(game, objs_id[i])) == NULL)
    {
      free(objs_id);
      return ERROR;
    }

    if (strcasecmp(object_get_name(obj), obj_name) == 0)
    {
      if (object_get_movable(obj) &&
          player_has_object(game_get_player(game), object_get_dependency(obj)) &&
          object_get_hidden(obj) == FALSE)
      {
        space_remove_object(space, objs_id[i]);
        player_add_object(game->player, objs_id[i]);
        object_set_location(obj, ON_PLAYER);

        free(objs_id);
        return OK;
      }
      else
      {
        free(objs_id);
        return ERROR;
      }
    }
  }
  free(objs_id);

  return ERROR;
}

STATUS _drop_rec(Game *game, Id *objs_id, int nobj, Space *space, Id space_id, char *obj_name, int *count)
{
  int i;
  char *dependency;
  Object *obj;
  STATUS st = ERROR;
  BOOL is_first=TRUE;

  for (i = 0; i < nobj; i++)
  {
    if ((obj = game_get_object(game, objs_id[i])) == NULL)
      return ERROR;

    dependency = object_get_name(game_get_object(game, object_get_dependency(obj)));
    if (dependency == NULL)
      dependency = "";

    if ((strcasecmp(object_get_name(obj), obj_name) == 0) && is_first==TRUE)
    {
      space_add_object(space, objs_id[i]);
      player_remove_object(game->player, objs_id[i]);
      object_set_location(obj, space_id);

      DroppedObjects[(*count)] = object_get_id(obj);
      (*count)++;

      is_first=FALSE;
      st = OK;
    }
    else if (strcasecmp(dependency, obj_name) == 0)
    {
      if (_drop_rec(game, objs_id, nobj, space, space_id, object_get_name(obj), count) == ERROR)
        return ERROR;
    }
  }

  DroppedObjects[(*count)] = 0;

  return st;
}

STATUS game_command_drop(Game *game, Commands *cmds)
{
  int nobj, count = 0;
  Id *objs_id;
  Id space_id = NO_ID;
  Space *space = NULL;
  char obj_name[WORD_SIZE];
  STATUS st = ERROR;

  if (game == NULL || cmds == NULL)
    return ERROR;

  if ((commands_get_num_args(cmds) == 0) || ((space_id = player_get_location(game_get_player(game))) == NO_ID))
    return ERROR;

  strcpy(obj_name, commands_get_args(cmds, 0));

  if ((space = game_get_space(game, space_id)) == NULL)
    return ERROR;

  if ((objs_id = player_get_objects(game->player, &nobj)) == NULL)
    return ERROR;

  st = _drop_rec(game, objs_id, nobj, space, space_id, obj_name, &count);

  free(objs_id);
  return st;
}

STATUS game_command_inspect(Game *game, Commands *cmds)
{
  int i, spc_nobj, ply_nobj;
  Id *spc_objs_id, *ply_objs_id;
  Id space_id = NO_ID;
  Object *obj;
  Space *space = NULL;
  char insp_name[WORD_SIZE + 1];
  char *desc;

  if (game == NULL || cmds == NULL)
    return ERROR;

  if (commands_get_num_args(cmds) == 0)
    return ERROR;

  strcpy(insp_name, commands_get_args(cmds, 0));

  if ((space_id = player_get_location(game_get_player(game))) == NO_ID)
    return ERROR;

  if ((space = game_get_space(game, space_id)) == NULL)
    return ERROR;

  for (i = 0; i < MAX_ENEMIES && game->enemies[i] != NULL; i++)
  {
    if (enemy_get_location(game->enemies[i]) == space_id && enemy_get_health(game->enemies[i]) > 0)
    {
      desc = "The space has an enemy, kill it to investigate further";
      game_set_last_idesc(game, desc);
      return OK;
    }
  }

  if (space_get_light(space) == FALSE && game_player_has_light(game) == FALSE) /*If the space has no light*/
  {
    desc = "The space has no light, turn on a light to investigate further";
    game_set_last_idesc(game, desc);
    return OK;
  }

  spc_objs_id = space_get_objects(space, &spc_nobj);
  ply_objs_id = player_get_objects(game->player, &ply_nobj);

  if (strcasecmp(insp_name, "s") == 0 || strcasecmp(insp_name, "space") == 0)
  {
    desc = space_get_idesc(space);
    game_set_last_idesc(game, desc);

    for (i = 0; i < spc_nobj; i++) /*Making visible all the hidden objects*/
      (void)object_set_hidden(game_get_object(game, spc_objs_id[i]), FALSE);

    free(ply_objs_id);
    free(spc_objs_id);
    return OK;
  }
  else
  {
    if (spc_objs_id != NULL)
    {
      for (i = 0; i < spc_nobj; i++)
      {
        if ((obj = game_get_object(game, spc_objs_id[i])) == NULL)
        {
          free(spc_objs_id);
          free(ply_objs_id);
          return ERROR;
        }

        if (strcasecmp(object_get_name(obj), insp_name) == 0)
        {
          desc = object_get_tdesc(obj);
          game_set_last_idesc(game, desc);
          free(spc_objs_id);
          free(ply_objs_id);
          return OK;
        }
      }
    }

    if (ply_objs_id != NULL)
    {
      for (i = 0; i < ply_nobj; i++)
      {
        if ((obj = game_get_object(game, ply_objs_id[i])) == NULL)
        {
          free(spc_objs_id);
          free(ply_objs_id);
          return ERROR;
        }

        if (strcasecmp(object_get_name(obj), insp_name) == 0)
        {
          desc = object_get_tdesc(obj);
          game_set_last_idesc(game, desc);
          free(spc_objs_id);
          free(ply_objs_id);
          return OK;
        }
      }
    }

    free(spc_objs_id);
    free(ply_objs_id);
    return ERROR;
  }
}

STATUS game_command_turn_on_off(Game *game, Commands *cmds, BOOL on_off)
{
  int i, ply_nobj;
  Id *ply_objs_id;
  Object *obj;
  Space *space = NULL;
  char obj_name[WORD_SIZE + 1];

  if (game == NULL || cmds == NULL)
    return ERROR;

  if (commands_get_num_args(cmds) == 0)
    return ERROR;

  strcpy(obj_name, commands_get_args(cmds, 0));

  if ((space = game_get_space(game, player_get_location(game_get_player(game)))) == NULL)
    return ERROR;

  if ((ply_objs_id = player_get_objects(game->player, &ply_nobj)) != NULL)
  {
    for (i = 0; i < ply_nobj; i++)
    {
      if ((obj = game_get_object(game, ply_objs_id[i])) == NULL)
        break;

      if (strcasecmp(object_get_name(obj), obj_name) == 0)
      {
        if (object_get_illuminate(obj) == TRUE)
        {
          object_set_turnedon(obj, on_off);

          free(ply_objs_id);
          return OK;
        }
      }
    }
  }

  free(ply_objs_id);
  return ERROR;
}

STATUS game_command_open_close(Game *game, Commands *cmds, LSTATUS opn_cls)
{

  int i, spc_nobj, ply_nobj, numlinks;
  Id *spc_objs_id, *ply_objs_id;
  Id space_id = NO_ID;
  Object *obj;
  Space *space = NULL;
  Link *link = NULL;
  char lnk_name[WORD_SIZE + 1], obj_name[WORD_SIZE + 1];

  if (game == NULL || cmds == NULL)
    return ERROR;

  if (commands_get_num_args(cmds) < 3)
    return ERROR;

  strcpy(lnk_name, commands_get_args(cmds, 0));

  if (strcasecmp("with", commands_get_args(cmds, 1)) != 0)
    return ERROR;

  strcpy(obj_name, commands_get_args(cmds, 2));

  if ((space_id = player_get_location(game_get_player(game))) == NO_ID)
    return ERROR;

  if ((space = game_get_space(game, space_id)) == NULL)
    return ERROR;

  numlinks = game_get_num_links(game);
  for (i = 0; i < numlinks; i++)
  {
    if ((strcasecmp(lnk_name, link_get_name(game->links[i]))) == 0 && link_get_origin(game->links[i]) == space_id)
    {
      link = game->links[i];
      break;
    }
  }

  if (link == NULL)
  {
    for (i = 0; i < numlinks; i++)
    {
      if (link_get_direction(game->links[i]) == commands_get_direction(cmds) && link_get_origin(game->links[i]) == space_id)
      {
        link = game->links[i];
        break;
      }
    }
  }

  if (link == NULL)
    return ERROR;

  spc_objs_id = space_get_objects(space, &spc_nobj);
  ply_objs_id = player_get_objects(game->player, &ply_nobj);

  if (spc_objs_id != NULL)
  {
    for (i = 0; i < spc_nobj; i++)
    {
      if ((obj = game_get_object(game, spc_objs_id[i])) == NULL)
      {
        free(ply_objs_id);
        free(spc_objs_id);
        return ERROR;
      }

      if (strcasecmp(object_get_name(obj), obj_name) == 0)
      {
        if (object_get_open(obj) == link_get_id(link) &&
            object_get_hidden(obj) == FALSE)
        {
          link_set_status(link, opn_cls);
          free(ply_objs_id);
          free(spc_objs_id);
          return OK;
        }
      }
    }
  }

  if (ply_objs_id != NULL)
  {
    for (i = 0; i < ply_nobj; i++)
    {
      if ((obj = game_get_object(game, ply_objs_id[i])) == NULL)
      {
        free(ply_objs_id);
        free(spc_objs_id);
        return ERROR;
      }

      if (strcasecmp(object_get_name(obj), obj_name) == 0)
      {
        if (object_get_open(obj) == link_get_id(link) &&
            object_get_hidden(obj) == FALSE)
        {
          link_set_status(link, opn_cls);
          free(ply_objs_id);
          free(spc_objs_id);
          return OK;
        }
      }
    }
  }

  free(spc_objs_id);
  free(ply_objs_id);
  return ERROR;
}

STATUS game_command_load(Game *game, Commands *cmds)
{
  Game *dupgame;
  char load_file[WORD_SIZE + 1];
  char real_file[WORD_SIZE + 1];

  if (game == NULL || cmds == NULL)
    return ERROR;

  if (commands_get_num_args(cmds) == 0)
    return ERROR;

  strcpy(load_file, commands_get_args(cmds, 0));
  sprintf(real_file, "saved_games/");
  strcat(real_file, load_file);

  /*Check that loading will work*/
  if ((dupgame = game_create_dup(game)) == NULL)
    return ERROR;

  game_init(game);

  if (game_management_load(game, real_file) == ERROR)
  {
    game_copy(game, dupgame);
    game_destroy_dup(dupgame);
    return ERROR;
  }

  game_destroy(dupgame);
  return OK;
}

STATUS game_command_save(Game *game, Commands *cmds)
{
  char save_file[WORD_SIZE + 1];
  char real_file[WORD_SIZE + 1];

  if (game == NULL || cmds == NULL)
    return ERROR;

  if (commands_get_num_args(cmds) == 0)
    return ERROR;

  strcpy(save_file, commands_get_args(cmds, 0));

  sprintf(real_file, "saved_games/");
  strcat(real_file, save_file);

  return game_management_save(game, real_file);
}

STATUS game_command_info(Game *game)
{
  if (game == NULL)
    return ERROR;

  game_print_data(game, stdout);
  return OK;
}
