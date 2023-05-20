/**
 * @brief It implements the command interpreter module
 *
 * @file command.c
 * @author David Brenchley - Javier San Andrés - Diego Rodríguez
 * @version 3.0
 * @date 10/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "command.h"

/**
 * @brief Array of the posible options that the player has
 */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "no command"},
                                   {"", "unknown"},
                                   {"e", "exit"},
                                   {"m", "move"},
                                   {"a", "attack"},
                                   {"t", "take"},
                                   {"d", "drop"},
                                   {"i", "inspect"},
                                   {"to", "turnon"},
                                   {"tf", "turnoff"},
                                   {"op", "open"},
                                   {"cl", "close"},
                                   {"l", "load"},
                                   {"s","save"},
                                   {"Y", "info"}};


/**
 * @brief Array of the posible directions that the player can move in
 */
char *dir_to_str[N_DIR][N_DIRT] = {{"n", "north"},
                                   {"s", "south"},
                                   {"e", "east"},
                                   {"w", "west"},
                                   {"u", "up"},
                                   {"d", "down"}};


/**
 * @brief Commands
 *
 * This struct stores all the information of a command.
 */
struct _Commands
{
  T_Command cmd;                              /*!<Kind of command executed*/
  char cmd_args[CMD_NARGS][CMD_ARG_LEN];      /*!<Array of strings of the arguments of the command*/
  int n_args_read;                            /*!<Number of arguments of the command*/
  STATUS cmd_status;                          /*!<Status of the command*/
};

Commands *commands_create()
{
  Commands *cmds;
  if ((cmds = (Commands *)malloc(sizeof(Commands))) == NULL)
  {
    return NULL;
  }

  cmds->cmd = NO_CMD;
  cmds->n_args_read = 0;
  cmds->cmd_status = OK;

  return cmds;
}

void commands_destroy(Commands *cmds)
{
  free(cmds);
}

T_Command commands_get_cmd(Commands *cmds)
{
  if (cmds == NULL)
    return NO_CMD;

  return cmds->cmd;
}

STATUS commands_set_cmd(Commands *cmds, T_Command cmd)
{
  if (cmds == NULL)
    return ERROR;

  cmds->cmd=cmd;
  return OK;
}

char *commands_get_args(Commands *cmds, int num)
{
  if (cmds == NULL)
    return NULL;

  if (num >=0 && num < cmds->n_args_read )
    return cmds->cmd_args[num];
  else
    return NULL;
}

int commands_get_num_args(Commands *cmds)
{
  if (cmds == NULL)
    return -1;

  return cmds->n_args_read;
}

STATUS commands_get_status(Commands *cmds)
{
  if (cmds == NULL)
    return ERROR;

  return cmds->cmd_status;
}

STATUS commands_set_status(Commands *cmds, STATUS status)
{
  if (cmds == NULL)
    return ERROR;

  cmds->cmd_status = status;

  return OK;
}

T_Command commands_get_user_input(Commands *cmds, FILE *f)
{
  char input[CMD_LENGTH];
  char *main_cmd, *args;
  int j, i = UNKNOWN - NO_CMD + 1;

  if (cmds == NULL)
    return NO_CMD;

  cmds->cmd = UNKNOWN;
  cmds->n_args_read = 0;

  if (fgets(input, CMD_LENGTH, f) == input)
  {
    if ((main_cmd = strtok(input, DELIMITATORS)) != NULL)
    {
      for (j = 0; j < CMD_NARGS; j++)
      {
        if ((args = strtok(NULL, DELIMITATORS)) == NULL)
          break;

        strcpy(cmds->cmd_args[j], args);
        cmds->n_args_read++;
        
      }

      while (cmds->cmd == UNKNOWN && i < N_CMD)
      {
        if (!strcasecmp(main_cmd, cmd_to_str[i][CMDS]) || !strcasecmp(main_cmd, cmd_to_str[i][CMDL]))
          cmds->cmd = i + NO_CMD;
        else
          i++;
      }
    }
  }

  return cmds->cmd;
}

/*
 * It gets the direction of a command
 */
DIRECTION commands_get_direction(Commands *cmds)
{
  char *args;
  int i;

  if (!cmds)
    return NO_DIR;

  if (commands_get_cmd(cmds) != MOVE && commands_get_cmd(cmds) != OPENLINK && commands_get_cmd(cmds) != CLOSELINK)
    return NO_DIR;

  if ((args = commands_get_args(cmds, 0)) == NULL)
    return NO_DIR;

  for (i = 0; i < N_DIR; i++)
  {
    if (!strcasecmp(args, dir_to_str[i][CMDS]) || !strcasecmp(args, dir_to_str[i][CMDL]))
    {
      return i;
    }
  }
  return NO_DIR;
}

char *commands_get_formatted_cmd(Commands *cmds)
{
  char *cmd;
  int i;

  if (cmds == NULL)
    return NULL;

  if ((cmd = (char *)calloc(CMD_LENGTH + CMD_ARG_LEN * CMD_NARGS + 1, sizeof(char))) == NULL)
    return NULL;

  strcpy(cmd, cmd_to_str[cmds->cmd - NO_CMD][CMDL]);

  for (i = 0; i < cmds->n_args_read; i++)
  {
    strcat(cmd, " ");

    if (i == 0)
    {
      if (commands_get_direction(cmds) != NO_DIR)
        strcat(cmd, dir_to_str[commands_get_direction(cmds)][CMDL]);
      else
        strcat(cmd, cmds->cmd_args[0]);
    }
    else
      strcat(cmd, cmds->cmd_args[i]);
      
  }

  return cmd;
}

char *commands_get_formatted_direction(Commands *cmds)
{
  char *args;
  int i;

  if (!cmds)
    return NULL;

  if (commands_get_cmd(cmds) != MOVE)
    return NULL;

  if ((args = commands_get_args(cmds, 0)) == NULL)
    return NULL;

  for (i = 0; i < N_DIR; i++)
  {
    if (!strcasecmp(args, dir_to_str[i][CMDS]) || !strcasecmp(args, dir_to_str[i][CMDL]))
    {
      return dir_to_str[i][CMDL];
    }
  }
  return NULL;
}