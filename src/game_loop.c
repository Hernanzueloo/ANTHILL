/**
 * @brief It defines the module where the game runs, assigning resources, executing and freeing them.
 *
 * @file game_loop.c
 * @author David Brenchley
 * @version 3.0
 * @date 27/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "command.h"
#include "game.h"
#include "graphic_engine.h"
#include "game_management.h"

/*EXECUTION FUNCTIONS*/
/**
 * @brief Initializes the game and the graphic engine
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param gengine Pointer to the graphical engines pointer
 * @param file_name File that contains the game
 * @return 1 if not all the arguments have been added or 0 otherwise
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Executes the game
 * @author David Brenchley
 * @param game Pointer to the game that will be used
 * @param gengine Pointer to the graphical engine
 * @param file_log File whre the command results are dumped
 */
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *file_log);

/**
 * @brief Frees up the game and the graphic engine's resources
 * @author David Brenchley
 * @param game Pointer to the game that has been use
 * @param gengine Pointer to the graphical engine
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
 * @brief Main function
 * @author David Brenchley y Javier San Andrés
 * @param argc Number of parameters
 * @param argv Array of parameters
 */
int main(int argc, char *argv[])
{
  Game *game;
  Graphic_engine *gengine;
  FILE *file_log;

  if (argc == 2)
    file_log = NULL;
  else if (argc == 4)
  {
    if (strcmp("-l", argv[2]) != 0)
    {
      fprintf(stderr, "Use: %s <game_data_file> (-l <game_command_log>)\n", argv[0]);
      return 1;
    }

    if ((file_log = fopen(argv[3], "w")) == NULL)
      return 1;
  }
  else
  {
    fprintf(stderr, "Use: %s <game_data_file> (-l <game_command_log>)\n", argv[0]);
    return 1;
  }

  if (!game_loop_init(&game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine, file_log);
    game_loop_cleanup(game, gengine);
  }

  if (file_log != NULL)
    fclose(file_log);

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
  if (game == NULL || gengine == NULL || file_name == NULL)
    return 1;

  if (((*game) = game_create_from_file(file_name)) == NULL)
  {
    fprintf(stderr, "Error while initializing game\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine\n");
    game_destroy(*game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *file_log)
{
  T_Command command = NO_CMD;
  char *format_cmd;
  STATUS st;
  int playerType = -1;
  char op[3], garbage;

  srand((unsigned)time(NULL));

  if (game == NULL || gengine == NULL)
    return;

  if (player_get_type(game_get_player(game)) == UNDEFPLY)
  {
    do
    {
      graphic_engine_paint_init(gengine, game);

      fgets(op, 3, stdin);

      if (strlen(op) > 1 && op[1] != '\n')
        while ((garbage = (char)getchar()) != '\n' && (int)garbage != EOF)
          ;

    } while ((op[0] != 'e' || op[1] != '\n') && (op[1] != '\n' || (atoi(op) < UNDEFPLY + 1 || atoi(op) > TYPEPLAYERS - 1)));

    if (op[0] != 'e')
    {
      playerType = atoi(op);

      if (player_set_type(game_get_player(game), (T_PlayerType)playerType) == ERROR)
        return;
    }
    else
    {
      command = EXIT;
    }
  }

  switch (player_get_type(game_get_player(game)))
  {
  case SNAIL:
    player_set_max_objects(game_get_player(game), player_get_max_objects(game_get_player(game)) + EXTRASNAIL);
    break;
  case ANT:
    game_rule_spawn_ground(game, EXTRASANT);
    break;
  default:
    break;
  }

  while ((command != EXIT))
  {
    if (game_is_over(game) == TRUE)
    {
    
      if(game_get_num_executed_commands(game)==VICTORY)
        graphic_engine_paint_win(gengine, game);
      else
        graphic_engine_paint_lose(gengine, game);

      break;
    }
    else
    {

      graphic_engine_paint_game(gengine, game);

      command = commands_get_user_input(game_get_last_command(game), stdin);
      game_update(game);

      if (file_log != NULL)
      {
        format_cmd = commands_get_formatted_cmd(game_get_last_command(game));
        st = commands_get_status(game_get_last_command(game));
        
        if (st == OK)
          strcat(format_cmd, ": OK");
        else
          strcat(format_cmd, ": ERROR");

        fprintf(file_log, "%s\n", format_cmd);
        free(format_cmd);
      }
    }
  }

  return;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);

  return;
}