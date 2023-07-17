/**
 * @brief It defines the textual graphic engine's module
 *
 * @file graphic_engine.c
 * @author David Brenchley
 * @version 3.0
 * @date 05/04/2023
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include "graphic_engine.h"

/*To change the map's sizes you only need to modify COLUMNS, ROWS,  BOX_COLS, BOX_ROWS, MAP_WIDTH,MAP_HEIGHT and MINIMAP_WIDTH accordingly and in unison*/

#define COLUMNS 172 /*!< Number of screen colums for the game*/
#define ROWS 51     /*!< Number of screen rows for the game*/

#define BOX_COLS 23 /*!< Number of columns for each representation of a space*/
#define BOX_ROWS 12 /*!< Number of rows for each representation of a space*/

#define GAP_BETWEEN_WALL_EMY 5 /*!< Gap in between left wall and the enemy*/
#define ANTSIZE TAMPLAYER      /*!< Size of the ant*/

#define DARK_CHAR '?'  /*!< Character of the dark spaces*/
#define FLOOD_CHAR '~' /*!< Character of the flooded spaces*/

/*AREA */

#define AREA_WALL_H 1 /*!<Width of the horizontal gap between areas*/
#define AREA_WALL_V 1 /*!<Width of the vertical gap between areas*/

#define MAP_X AREA_WALL_V /*!<x coordinates of the upper left part of the map area*/
#define MAP_Y AREA_WALL_H /*!<y coordinates of the upper left part of the map area*/
#define MAP_WIDTH 76      /*!<Width of the map area*/
#define MAP_HEIGHT 40     /*!<Hight of the map area*/

#define DESCRIPT_X (MAP_X + MAP_WIDTH + 2 * AREA_WALL_V)                       /*!<x coordinates of the upper left part of the descript area*/
#define DESCRIPT_Y (MAP_Y)                                                     /*!<y coordinates of the upper left part of the descript area*/
#define DESCRIPT_WIDTH (COLUMNS - MINIMAP_WIDTH - MAP_WIDTH - 6 * AREA_WALL_V) /*!<Width of the descript area*/
#define DESCRIPT_HEIGHT (MAP_HEIGHT)                                           /*!<Hight of the descript area*/

#define BANNER_X (MAP_WIDTH + DESCRIPT_WIDTH) / 2 - (BANNER_WIDTH / 2) /*!<x coordinates of the upper left part of the banner area*/
#define BANNER_Y (MAP_Y + MAP_HEIGHT + AREA_WALL_H)                    /*!<y coordinates of the upper left part of the banner area*/
#define BANNER_WIDTH (COLUMNS - MINIMAP_WIDTH - 2 * AREA_WALL_V) / 4   /*!<Width of the banner area*/
#define BANNER_HEIGHT 1                                                /*!<Hight of the banner area*/

#define HELP_X MAP_X                                           /*!<x coordinates of the upper left part of the help area*/
#define HELP_Y (BANNER_Y + BANNER_HEIGHT)                      /*!<y coordinates of the upper left part of the help area*/
#define HELP_WIDTH (COLUMNS - MINIMAP_WIDTH - 4 * AREA_WALL_V) /*!<Width of the help area*/
#define HELP_HEIGHT 3                                          /*!<Hight of the help area*/

#define FEEDBACK_X MAP_X                                                                    /*!<x coordinates of the upper left part of the feedback area*/
#define FEEDBACK_Y (HELP_Y + HELP_HEIGHT + AREA_WALL_H)                                     /*!<y coordinates of the upper left part of the feedback area*/
#define FEEDBACK_WIDTH (HELP_WIDTH)                                                         /*!<Width of the feedback area*/
#define FEEDBACK_HEIGHT (ROWS - MAP_HEIGHT - BANNER_HEIGHT - HELP_HEIGHT - 4 * AREA_WALL_H) /*!<Hight of the feedback area*/

#define MINIMAP_X DESCRIPT_X + DESCRIPT_WIDTH + 2 * AREA_WALL_V                                          /*!<x coordinates of the upper left part of the minimap area*/
#define MINIMAP_Y DESCRIPT_Y                                                                             /*!<y coordinates of the upper left part of the minimap area*/
#define MINIMAP_WIDTH 32                                                                                 /*!<Width of the minimap area*/
#define MINIMAP_HEIGHT DESCRIPT_HEIGHT + BANNER_HEIGHT + HELP_HEIGHT + FEEDBACK_HEIGHT + 2 * AREA_WALL_H /*!<Hight of the minimap area*/

/* NEW LIBSCREEN MACROS */
#define MULTIBYTE 16
#define SPACES_TO_PRINT 20
#define TAMENEMY 6
#define TAMCOLOR 22

#define LINK_WIDTH 2    /*!< Width (in characters) of a link frame */
#define LINK_HEIGHT 1   /*!< Height (in characters) of a link frame */
#define VLINK_WIDTH 5   /*!< Width (in characters) of a vertical (north and south) link */
#define H_LINK_HEIGHT 4 /*!< Width (in characters) of a horizontal (east and west) link */

/* Characters */

#define BLANK "                                                                                                    "  /*!< Blank character */
#define H_LINE "────────────────────────────────────────────────────────────────────────────────────────────────────" /*!< Horizontal line character */
#define Q_MARK "????????????????????????????????????????????????????????????????????????????????????????????????????" /*!< Question mark line character */
#define WAVE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣"   /*!< Wave line character */
#define TOP_WAVE "▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆"

#define V_LINE "│"      /*!< Vertical line character */
#define UP_R_CORNER "┌" /*!< Upper-right corner character */
#define UP_L_CORNER "┐" /*!< Upper-left corner character */
#define DW_R_CORNER "└" /*!< Down-right corner character */
#define DW_L_CORNER "┘" /*!< Down-left corner character */
#define UP_ARROW "^"    /*!< Up arrow character */
#define DW_ARROW "v"    /*!< Down arrow character */
#define CROSS "X"       /*!< Cross character */
#define UP_T "┴"        /*!< Up-pointing T character */
#define DW_T "┬"        /*!< Down-pointing T character */
#define LF_T "┤"        /*!< Left-pointing T character */
#define RG_T "├"        /*!< Right-pointing T character */
#define ONE_H_LINE "─"  /*!< Single horizontal line character */
#define ONE_BLANK " "   /*!< Silgle blank character */

/* COLORS */
/*Black*/
#define B_BLACK BACKGROUND(0, 0, 0) /*!< Black background color */
#define F_BLACK FOREGROUND(0, 0, 0) /*!< Black foreground color */
/*Grey*/
#define B_GREY BACKGROUND(90, 90, 90)         /*!< Grey background color */
#define F_GREY FOREGROUND(90, 90, 90)         /*!< Black foreground color */
#define B_LIGHTGREY BACKGROUND(140, 140, 140) /*!< Grey background color */
#define F_LIGHTGREY FOREGROUND(140, 140, 140) /*!< Black foreground color */
/*White*/
#define B_WHITE BACKGROUND(253, 253, 252) /*!< White background color */
#define F_WHITE FOREGROUND(253, 253, 252) /*!< White foreground color */
/*Blues*/
#define B_DARKBLUE BACKGROUND(0, 0, 200)
#define F_DARKBLUE FOREGROUND(0, 0, 200)
#define B_BLUE BACKGROUND(0, 150, 255)
#define F_BLUE FOREGROUND(0, 150, 255)
#define B_LIGHTBLUE BACKGROUND(110, 231, 255)
#define F_LIGHTBLUE FOREGROUND(110, 231, 255)
/*Greens*/
#define B_GREEN BACKGROUND(0, 150, 0)
#define F_GREEN FOREGROUND(0, 150, 0)
#define B_LIGHTGREEN BACKGROUND(50, 255, 50)
#define F_LIGHTGREEN FOREGROUND(50, 255, 50)
/*Browns*/
#define B_BROWN BACKGROUND(79, 36, 2)
#define F_BROWN FOREGROUND(79, 36, 2)
#define B_LIGHTBROWN BACKGROUND(195, 113, 47)
#define F_LIGHTBROWN FOREGROUND(195, 113, 47)
/*Purple*/
#define B_PURPLE BACKGROUND(74, 0, 55)
#define F_PURPLE FOREGROUND(74, 0, 55)
#define B_LIGHTPURPLE BACKGROUND(203, 86, 246)
#define F_LIGHTPURPLE FOREGROUND(203, 86, 246)
/*Reds*/
#define B_RED BACKGROUND(180, 0, 0)
#define F_RED FOREGROUND(180, 0, 0)
#define B_LIGHTRED BACKGROUND(255, 124, 124)
#define F_LIGHTRED FOREGROUND(255, 124, 124)
/*ORANGES*/
#define B_ORANGE BACKGROUND(200, 71, 12)
#define F_ORANGE FOREGROUND(200, 71, 12)
#define B_LIGHTORANGE BACKGROUND(255, 126, 67)
#define F_LIGHTORANGE FOREGROUND(255, 126, 67)

/*MINIMAP*/
#define B_MINIMAP BACKGROUND(62, 95, 138)
/*DESCRIPTION*/
#define B_DESCRIPT BACKGROUND(209, 177, 183)
/*MAP*/
#define B_MAP BACKGROUND(245, 175, 114)

static char pSkins[TYPEPLAYERS][TAMPLAYER + 1] = {{"    "}, {"Coo:"}, {"@_ll"}, {"cBo^"}, {"mmo^"}, {"}H{ "}};

/*Private functions*/
/**
 * @brief Paints the map
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_map(Graphic_engine *ge, Game *game);

/**
 * @brief Paints the initial, loose and win map
 * @author Alejandro García
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_map_frame(Graphic_engine *ge, Game *game, int type);

/**
 * @brief Paints the initial description
 * @author Alejandro García
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_description_init(Graphic_engine *ge, Game *game);

/**
 * @brief Paints the final exiting description
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_description_end(Graphic_engine *ge, Game *game);

/**
 * @brief Paints a single space to the north or too the south
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 * @param id_centre Id of the centre space
 * @param spc_dir_id Id of the space in the required direction (North space or South space)
 * @param cut_top Indicates if you want to print the top of a box (1) or not (0)
 * @param cut_bot Indicates if you want to print the bottom of a box (1) or not (0)
 */
void _paint_single_space(Graphic_engine *ge, Game *game, Id id_centre, Id spc_dir_id, int cut_top, int cut_bot);
/**
 * @brief Paints the player's description
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_player_description(Graphic_engine *ge, Game *game);
/**
 * @brief Paints the enemy's description
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_enemy_description(Graphic_engine *ge, Game *game);
/**
 * @brief Paints the objects' description
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_objects_description(Graphic_engine *ge, Game *game);
/**
 * @brief Paints the objects' description
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_links_description(Graphic_engine *ge, Game *game);
/**
 * @brief Paints the description of the space
 * @author Alejandro García
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_space_description(Graphic_engine *ge, Game *game);
/**
 * @brief Paints the inspections
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_inspection_description(Graphic_engine *ge, Game *game);

/**
 * @brief Paints the inspections
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_minimap(Graphic_engine *ge, Game *game);

/**
 * @brief Paints the dialogues
 * @author David Brenchley
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_feedback_dialogue(Graphic_engine *ge, Game *game);

/**
 * @brief Paints the inventory
 * @author Diego Rodriguez
 * @param ge Pointer to graphical descriptor
 * @param game Pointer to game
 */
void _paint_inventory(Graphic_engine *ge, Game *game);

/**
 * @brief Sets n enters
 * @author Alejandro García Hernando
 * @param ge Pointer to graphical descriptor
 * @param n number of enters
 * @param color background color
 */
void paint_n_enters(Area *area, int n, char *color);

void graphic_engine_sprint_objects(Game *game, Space *space, char *str);

void graphic_engine_sprint_enemy(Game *game, Id space_loc, char *str);

void graphic_engine_sprint_space_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west);

void graphic_engine_sprint_space_not_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west);

void graphic_engine_sprint_space_flooded(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west);

void graphic_engine_sprint_link(DIRECTION dir, LSTATUS status, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int x, int y, Space *space, Game *game);

void graphic_engine_space_frame_put(Area *area, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int height);

void graphic_engine_sprint_empty(char (*str_array)[MAP_WIDTH * MULTIBYTE + 1], int height, int width);

void _paint_map_new(Graphic_engine *ge, Game *game);

/**
 * @brief Graphic_engine
 *
 * This struct stores all the information of the graphics engine.
 */
struct _Graphic_engine
{
  Area *map,     /*!<Pointer to the grapical map*/
      *descript, /*!<Pointer to the graphical descript*/
      *banner,   /*!<Pointer to the screen banner*/
      *help,     /*!<Help pointer*/
      *feedback, /*!<Feedback pointer*/
      *minimap;  /*!< Minimap pointer*/
};

int num_commands_ex;

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  Color area_background = {255, 255, 255};
  Color area_foreground = {0, 0, 0};
  Color screen_foreground = {104, 104, 104};

  screen_init(ROWS, COLUMNS, area_foreground, area_background, screen_foreground);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
    return NULL;

  ge->map = screen_area_init(MAP_X, MAP_Y, MAP_WIDTH, MAP_HEIGHT);
  ge->descript = screen_area_init(DESCRIPT_X, DESCRIPT_Y, DESCRIPT_WIDTH, DESCRIPT_HEIGHT);
  ge->banner = screen_area_init(BANNER_X, BANNER_Y, BANNER_WIDTH, BANNER_HEIGHT);
  ge->help = screen_area_init(HELP_X, HELP_Y, HELP_WIDTH, HELP_HEIGHT);
  ge->feedback = screen_area_init(FEEDBACK_X, FEEDBACK_Y, FEEDBACK_WIDTH, FEEDBACK_HEIGHT);
  ge->minimap = screen_area_init(MINIMAP_X, MINIMAP_Y, MINIMAP_WIDTH, MINIMAP_HEIGHT);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (ge == NULL)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  screen_area_destroy(ge->minimap);
  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  int i, bytes = 0, f = game_get_num_commands_till_flood(game), n = game_get_num_commands_per_flood(game);
  char aux[WORD_SIZE];
  char str[WORD_SIZE];

  if (ge == NULL || game == NULL)
    return;

  /* Paint in the map area */
  /*_paint_map(ge, game);*/
  _paint_map_new(ge, game);

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  screen_area_puts(ge->descript, B_DESCRIPT "                 DESCRIPTION  ");
  paint_n_enters(ge->descript, 1, B_DESCRIPT);
  if (game_get_num_commands_till_flood(game) != -1)
  {
    sprintf(aux, B_DESCRIPT " - Commands until next flood: %d/%d", game_get_num_commands_till_flood(game), game_get_num_commands_per_flood(game));
    screen_area_puts(ge->descript, aux);
  }

  f = DESCRIPT_WIDTH - f * DESCRIPT_WIDTH / n;
  bytes += sprintf(aux, B_DESCRIPT " " F_DARKBLUE B_LIGHTBLUE);
  for (i = 0; i < f; i++)
    bytes += sprintf(aux + bytes, "~");
  for (; i < DESCRIPT_WIDTH - 3; i++)
    bytes += sprintf(aux + bytes, B_DESCRIPT " ");
  bytes += sprintf(aux + bytes, B_DESCRIPT " ");
  screen_area_puts(ge->descript, aux);

  _paint_player_description(ge, game);
  _paint_enemy_description(ge, game);
  _paint_objects_description(ge, game);
  _paint_links_description(ge, game);
  _paint_space_description(ge, game);
  /*_paint_inspection_description(ge, game);*/
  paint_n_enters(ge->descript, 1, B_DESCRIPT);

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "        THE ANTHILL GAME ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " Attack or a, take or t, drop or d, move or m, inspect or i, turnon or to, turnoff or tf, op or open with, cl or close with, l or load,");
  screen_area_puts(ge->help, str);
  sprintf(str, " s or save, info or y, exit or e");
  screen_area_puts(ge->help, str);

  _paint_feedback_dialogue(ge, game);

  /*Paint in the minimap area*/
  _paint_minimap(ge, game);

  /* Dump to the terminal */
  screen_paint();
  num_commands_ex = game_get_num_executed_commands(game);
  printf(B_BLACK F_WHITE "Write a command:> ");
}

void graphic_engine_paint_init(Graphic_engine *ge, Game *game)
{
  char str[WORD_SIZE];

  if (ge == NULL || game == NULL)
    return;

  /* Paint in the map area */
  _paint_map_frame(ge, game, 0);

  /* Paint in the description area */
  _paint_description_init(ge, game);

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "        THE ANTHILL GAME ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " Choose your player:");
  screen_area_puts(ge->help, str);
  sprintf(str, " Introduce a number between 1 and %d to choose a player. Type exit or e to leave the game", TYPEPLAYERS - 1);
  screen_area_puts(ge->help, str);

  /*Paint in the minimap area*/
  _paint_minimap(ge, game);

  /* Dump to the terminal */
  screen_paint();

  printf("\033[0;37mIntroduce the number:> ");
}

void graphic_engine_paint_win(Graphic_engine *ge, Game *game)
{
  char str[WORD_SIZE];

  if (ge == NULL || game == NULL)
    return;

  /* Paint in the map area */
  _paint_map_frame(ge, game, 1);

  /* Paint in the description area */
  _paint_description_end(ge, game);

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "        THE ANTHILL GAME ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, "Congratulation: YOU WON!");
  screen_area_puts(ge->help, str);

  _paint_feedback_dialogue(ge, game);

  /*Paint in the minimap area*/
  _paint_minimap(ge, game);

  /* Dump to the terminal */
  screen_paint();
}

void graphic_engine_paint_lose(Graphic_engine *ge, Game *game)
{
  char str[WORD_SIZE];

  if (ge == NULL || game == NULL)
    return;

  /* Paint in the map area */
  _paint_map_frame(ge, game, -1);

  /* Paint in the description area */
  _paint_description_end(ge, game);

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "        THE ANTHILL GAME ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " YOU LOST! ");
  screen_area_puts(ge->help, str);

  if (player_get_health(game_get_player(game)) > 0)
  {
    screen_area_clear(ge->feedback);
        _paint_feedback_dialogue(ge, game);
  }
  else
    _paint_feedback_dialogue(ge, game);

  /*Paint in the minimap area*/
  _paint_minimap(ge, game);

  /* Dump to the terminal */
  screen_paint();
}

void _paint_objects_description(Graphic_engine *ge, Game *game)
{
  Id obj_loc = NO_ID;
  int i, j, n, first, bytes = 0;
  Object *object;
  char str[WORD_SIZE] = "\0", aux[WORD_SIZE] = "\0";

  paint_n_enters(ge->descript, 1, B_DESCRIPT);
  sprintf(aux, B_DESCRIPT "                        OBJECTS ");
  screen_area_puts(ge->descript, aux);
  screen_area_puts(ge->descript, B_DESCRIPT " - Objects location:");
  n = game_get_num_objects(game);
  for (i = NO_OTYPE; i < N_OBJ_TYPES; i++)
  {
    first = 0;
    for (j = 0; j < n; j++)
    {
      object = game_get_object(game, game_get_object_id_at(game, j));
      if (object_get_type(object) == i)
      {
        if (((obj_loc = object_get_location(object)) >= 0) && object_get_hidden(object) == FALSE && object_get_movable(object) == TRUE && space_get_light(game_get_space(game, object_get_location(object))) == TRUE)
        {
          if (enemy_get_health(game_get_enemy_in_space(game, obj_loc)) < 1)
          {
            if (!first)
            {
              first = 1;
              bytes = sprintf(str, B_DESCRIPT " -%s: %ld", object_get_name(object), obj_loc);
            }
            else
            {
              sprintf(aux, B_DESCRIPT ", %ld", obj_loc);
              if ((screen_multibyte_strlen(str) + screen_multibyte_strlen(aux) + 2) > DESCRIPT_WIDTH)
              {
                if ((screen_multibyte_strlen(str) + 2) <= DESCRIPT_WIDTH)
                {
                  bytes += sprintf(str + bytes, B_DESCRIPT ",");
                  sprintf(aux, B_DESCRIPT "  %ld", obj_loc);
                }
                screen_area_puts(ge->descript, str);
                memcpy(str, aux, WORD_SIZE);
              }
              else
                bytes += sprintf(str + bytes, "%s", aux);
            }
          }
        }
      }
    }
    if (first)
      screen_area_puts(ge->descript, str);

    strcpy(str, "\0");
  }
  for (j = 0; j < n; j++)
  {
    object = game_get_object(game, game_get_object_id_at(game, j));
    if (object_get_type(object) == SPECIAL)
    {
      if (((obj_loc = object_get_location(object)) >= 0) && object_get_hidden(object) == FALSE && object_get_movable(object) == TRUE && space_get_light(game_get_space(game, object_get_location(object))) == TRUE)
      {
        if (enemy_get_health(game_get_enemy_in_space(game, obj_loc)) < 1)
        {
          first = 1;
          sprintf(aux, B_DESCRIPT " -%s: %ld", object_get_name(object), obj_loc);
          if ((strlen(str) + strlen(aux) + 2) > DESCRIPT_WIDTH)
          {
            screen_area_puts(ge->descript, str);
            strcpy(str, aux);
          }
          else
            strcat(str, aux);
        }
      }
      screen_area_puts(ge->descript, str);
    }
  }
}

void _paint_links_description(Graphic_engine *ge, Game *game)
{
  Id id_centre = NO_ID, link_id = NO_ID;
  int i;
  char str[WORD_SIZE];

  char *dir_to_str[N_DIR] = {"north", "south", "east", "west", "up", "down"};

  paint_n_enters(ge->descript, 1, B_DESCRIPT);
  sprintf(str, B_DESCRIPT "                         LINKS ");
  screen_area_puts(ge->descript, str);
  sprintf(str, B_DESCRIPT " - Links:");
  screen_area_puts(ge->descript, str);

  strcpy(str, "\0");
  if ((id_centre = player_get_location(game_get_player(game))) != NO_ID)
  {
    for (i = NO_DIR + 1; i < NO_DIR + N_DIR + 1; i++)
    {
      link_id = game_get_link_id(game, id_centre, i);

      if (link_id != NO_ID)
      {
        if (link_get_status(game_get_link(game, link_id)) == OPEN)
          sprintf(str, B_DESCRIPT "  Link %s (%s)= OPEN", dir_to_str[i], link_get_name(game_get_link(game, link_id)));
        else
          sprintf(str, B_DESCRIPT "  Link %s (%s)= CLOSED", dir_to_str[i], link_get_name(game_get_link(game, link_id)));

        screen_area_puts(ge->descript, str);
      }
    }
  }
}

void _paint_player_description(Graphic_engine *ge, Game *game)
{
  Id ply_loc = NO_ID;
  char str[WORD_SIZE], aux[WORD_SIZE];

  sprintf(aux, B_DESCRIPT " ");
  screen_area_puts(ge->descript, aux);
  sprintf(aux, B_DESCRIPT "                        PLAYER ");
  screen_area_puts(ge->descript, aux);

  if ((ply_loc = player_get_location(game_get_player(game))) != NO_ID)
  {
    sprintf(str, B_DESCRIPT "    Location        Type        Health        Actions");
    screen_area_puts(ge->descript, str);

    sprintf(str, B_DESCRIPT "      %.3ld             %d", ply_loc, player_get_type(game_get_player(game)));

    if (player_get_health(game_get_player(game)) == 0)
      strcat(str, B_DESCRIPT "         DEAD");
    else
    {
      sprintf(aux, B_DESCRIPT "           %.2d", player_get_health(game_get_player(game)));
      strcat(str, aux);
    }
    sprintf(aux, B_DESCRIPT "           %.4d", game_get_num_executed_commands(game));
    strcat(str, aux);
    screen_area_puts(ge->descript, str);
    _paint_inventory(ge, game);
  }
}

void _paint_enemy_description(Graphic_engine *ge, Game *game)
{
  Id enmy_loc = NO_ID;
  int i;
  char str[WORD_SIZE], aux[WORD_SIZE];
  Enemy *enemy;

  paint_n_enters(ge->descript, 1, B_DESCRIPT);
  sprintf(aux, B_DESCRIPT "                        ENEMIES ");
  screen_area_puts(ge->descript, aux);

  for (i = 0; i < MAX_ENEMIES; i++)
  {
    if ((enmy_loc = enemy_get_location(enemy = game_get_enemy(game, game_get_enemy_id_at(game, i)))) != NO_ID)
    {
      if (space_get_flooded(game_get_space(game, enmy_loc)) != SUNK)
      {
        sprintf(str, B_DESCRIPT " - %s: location: %ld", enemy_get_name(enemy), enmy_loc);

        if (enemy_get_health(enemy) == 0)
          sprintf(aux, B_DESCRIPT ", health: DEAD");
        else
          sprintf(aux, B_DESCRIPT ",  health: %d", enemy_get_health(enemy));

        strcat(str, aux);
        screen_area_puts(ge->descript, str);
      }
    }
  }
}

void _paint_space_description(Graphic_engine *ge, Game *game)
{
  char *tdesc = NULL;
  char str[WORD_SIZE];

  tdesc = game_get_last_tdesc(game);

  paint_n_enters(ge->descript, 1, B_DESCRIPT);

  sprintf(str, B_DESCRIPT " - Description: ");
  screen_area_puts(ge->descript, str);

  if (tdesc != NULL)
    sprintf(str, B_DESCRIPT "  %s", tdesc);
  else
    sprintf(str, B_DESCRIPT "  No description");

  screen_area_puts(ge->descript, str);
}

void _paint_inspection_description(Graphic_engine *ge, Game *game)
{
  char *idesc = NULL;
  char str[WORD_SIZE];

  paint_n_enters(ge->descript, 1, B_DESCRIPT);

  sprintf(str, B_DESCRIPT " - Inspection: ");
  screen_area_puts(ge->descript, str);

  if ((idesc = game_get_last_idesc(game)) != NULL)
    sprintf(str, B_DESCRIPT "  %s", idesc);
  else
    sprintf(str, B_DESCRIPT "  No description");

  screen_area_puts(ge->descript, str);
}

void _paint_description_init(Graphic_engine *ge, Game *game)
{
  int i;
  char buffer[WORD_SIZE];
  char ascii_art[12][30] = {
      "       /\\   /\\",
      "         \\_/",
      "    __   / \\   __",
      "  -'  `. \\_/ .'  `-",
      "        \\/ \\/",
      "   _.---(   )---._",
      "_.'   _.-\\_/-._   `._",
      "     /   /_\\   \\",
      "    /   /___\\   \\",
      "   /   |_____|   \\",
      "_.'    | ___ |    `._",
      "        \\___/"};

  screen_area_clear(ge->descript);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "                        Pick a player");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "     -Scorpion (1): %s", pSkins[SCORPION]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "The Scorpion is a venomous animal therefore it deals %d", EXTRASCORP);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " more damage");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "    -Snail (2): %s", pSkins[SNAIL]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "The snail can hold %d more objects due to its big shell.", EXTRASNAIL);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "    -Firefly (3): %s", pSkins[FIREFLY]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "The Firefly iluminates a room without the need of a torch");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "    -Ant (4): %s", pSkins[ANT]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "The ant creates %d ground at the beggining of the game", EXTRASANT);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "    -Butterfly (5): %s", pSkins[BUTTERFLY]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "The butterfly flies vertically thanks to its light and");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "powerful wings.");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, B_DESCRIPT "- Exit (e)");
  screen_area_puts(ge->descript, buffer);

  sprintf(buffer, B_DESCRIPT " ");
  screen_area_puts(ge->descript, buffer);
  for (i = 0; i < 12; i++)
  {
    sprintf(buffer, B_DESCRIPT "                %s", ascii_art[i]);
    screen_area_puts(ge->descript, buffer);
  }
  for (i = 0; i < 5; i++)
  {
    sprintf(buffer, B_DESCRIPT "              ");
    screen_area_puts(ge->descript, buffer);
  }
}

void _paint_description_end(Graphic_engine *ge, Game *game)
{
  int i, cont;
  Id space, enemy;
  char buffer[WORD_SIZE], ascii_art[12][30] = {
                              "       /\\   /\\",
                              "         \\_/",
                              "    __   / \\   __",
                              "  -'  `. \\_/ .'  `-",
                              "        \\/ \\/",
                              "   _.---(   )---._",
                              "_.'   _.-\\_/-._   `._",
                              "     /   /_\\   \\",
                              "    /   /___\\   \\",
                              "   /   |_____|   \\",
                              "_.'    | ___ |    `._",
                              "        \\___/"};

  screen_area_clear(ge->descript);
  paint_n_enters(ge->descript, 4, B_DESCRIPT);
  screen_area_puts(ge->descript, B_DESCRIPT "                     GAME HAS ENDED");
  paint_n_enters(ge->descript, 3, B_DESCRIPT);
  screen_area_puts(ge->descript, B_DESCRIPT "               Hope you enjoyed the game ");
  paint_n_enters(ge->descript, 3, B_DESCRIPT);

  sprintf(buffer, B_DESCRIPT "         Character you chose: %s (%d)", pSkins[player_get_type(game_get_player(game))], player_get_type(game_get_player(game)));
  screen_area_puts(ge->descript, buffer);
  paint_n_enters(ge->descript, 1, B_DESCRIPT);
  sprintf(buffer, B_DESCRIPT "         Number of commands executed: %.4d", num_commands_ex);
  screen_area_puts(ge->descript, buffer);
  paint_n_enters(ge->descript, 1, B_DESCRIPT);
  sprintf(buffer, B_DESCRIPT "         Player health: %d", player_get_health(game_get_player(game)));
  screen_area_puts(ge->descript, buffer);
  paint_n_enters(ge->descript, 1, B_DESCRIPT);

  for (i = 0; (i < MAX_SPACES) && ((space = game_get_space_id_at(game, i)) != NO_ID); i++);
  sprintf(buffer, B_DESCRIPT "         Spaces left: %d", i);
  screen_area_puts(ge->descript, buffer);
  paint_n_enters(ge->descript, 1, B_DESCRIPT);

  for (i = 0, cont = 0; (i < MAX_ENEMIES) && ((enemy = game_get_enemy_id_at(game, i)) != NO_ID); i++)
    if (enemy_get_health(game_get_enemy(game, enemy)))
      cont++;
  sprintf(buffer, B_DESCRIPT "         Enemies killed: %d / %d", i - cont, i);
  screen_area_puts(ge->descript, buffer);

  paint_n_enters(ge->descript, 3, B_DESCRIPT);
  for (i = 0; i < 12; i++)
  {
    sprintf(buffer, B_DESCRIPT "                %s", ascii_art[i]);
    screen_area_puts(ge->descript, buffer);
  }

  paint_n_enters(ge->descript, 4, B_DESCRIPT);
}

void _paint_feedback_dialogue(Graphic_engine *ge, Game *game)
{
  T_Command last_cmd = NO_CMD;
  int i = 0, num_executed = 0, num_dialogues = 0;
  char *dialogue_rule = NULL, **game_rules_dialogues;

  /* Paint in the feedback area */
  last_cmd = game_get_last_command_cmd(game);
  dialogue_rule = game_get_dialogue_of_defeat(game);
  if (dialogue_rule != NULL)
  {
    screen_area_puts(ge->feedback, dialogue_rule);
    free(dialogue_rule);
    return;
  }
  if (game_get_last_command_status(game) == ERROR)
  {
    if ((num_executed = game_get_dialogue_executed(game, last_cmd)) > 0)
    {
      game_increase_dialogue_executed(game, last_cmd);
      dialogue_rule = game_get_printed_repeated_error_rule(game, num_executed);
    }
    else
    {
      for (i = 0; i < MAX_DIALOGUES; i++)
        while (game_get_dialogue_executed(game, i) > 0)
          game_decrease_dialogue_executed(game, i);

      game_increase_dialogue_executed(game, last_cmd);

      switch (last_cmd)
      {
      case UNKNOWN:
        dialogue_rule = game_get_printed_dialogue_rule(game, rand() % 2, NULL, UNKNOWN, ERROR);
        break;

      case EXIT:
        dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, EXIT, ERROR);
        break;

      case MOVE:
        dialogue_rule = game_get_move_dialogue_rule(game, FAILURE);
        break;

      case ATTACK:
        dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, ATTACK, ERROR);
        break;

      case TAKE:
        dialogue_rule = game_get_take_dialogue_rule(game, FAILURE);
        break;

      case DROP:
        dialogue_rule = game_get_drop_dialogue_rule(game, FAILURE);
        break;

      case INSPECT:
        dialogue_rule = game_get_inspect_dialogue_rule(game, FAILURE);
        break;

      case TURNON:
        dialogue_rule = game_get_turn_on_off_dialogue_rule(game, TURNON, FAILURE);
        break;

      case TURNOFF:
        dialogue_rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, FAILURE);
        break;

      case OPENLINK:
        dialogue_rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
        break;

      case CLOSELINK:
        dialogue_rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
        break;

      case LOAD:
        if (commands_get_num_args(game_get_last_command(game)) == 0)
          dialogue_rule = game_get_printed_dialogue_rule(game, 1, NULL, LOAD, ERROR);
        else
          dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, LOAD, ERROR);
        break;

      case SAVE:
        if (commands_get_num_args(game_get_last_command(game)) == 0)
          dialogue_rule = game_get_printed_dialogue_rule(game, 1, NULL, SAVE, ERROR);
        else
          dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, SAVE, ERROR);
        break;

      case INFO:
        dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, INFO, ERROR);
        break;

      default:
        break;
      }
    }
  }
  else
  {
    for (i = 0; i < MAX_DIALOGUES; i++)
      while (game_get_dialogue_executed(game, i) > 0)
        game_decrease_dialogue_executed(game, i);

    switch (last_cmd)
    {
    case NO_CMD:
      break;

    case UNKNOWN:
      dialogue_rule = game_get_printed_dialogue_rule(game, rand() % 2, NULL, UNKNOWN, ERROR);
      break;

    case EXIT:
      dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, EXIT, OK);
      break;

    case MOVE:
      dialogue_rule = game_get_move_dialogue_rule(game, SUCCESS);
      break;

    case ATTACK:
      dialogue_rule = game_get_attack_dialogue_rule(game);
      break;

    case TAKE:
      dialogue_rule = game_get_take_dialogue_rule(game, SUCCESS);
      break;

    case DROP:
      dialogue_rule = game_get_drop_dialogue_rule(game, SUCCESS);
      break;

    case INSPECT:
      dialogue_rule = game_get_inspect_dialogue_rule(game, SUCCESS);
      break;

    case TURNON:
      dialogue_rule = game_get_turn_on_off_dialogue_rule(game, TURNON, SUCCESS);
      break;

    case TURNOFF:
      dialogue_rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, SUCCESS);
      break;

    case OPENLINK:
      dialogue_rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, SUCCESS);
      break;

    case CLOSELINK:
      dialogue_rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, SUCCESS);
      break;

    case LOAD:
      if (commands_get_num_args(game_get_last_command(game)) == 0)
        dialogue_rule = game_get_printed_dialogue_rule(game, 1, NULL, LOAD, OK);
      else
        dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, LOAD, OK);
      break;

    case SAVE:
      dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, SAVE, OK);
      break;

    case INFO:
      dialogue_rule = game_get_printed_dialogue_rule(game, 0, NULL, INFO, OK);
      break;

    default:
      break;
    }
  }

  screen_area_clear(ge->feedback);

  if (dialogue_rule != NULL)
  {
    screen_area_puts(ge->feedback, dialogue_rule);
      free(dialogue_rule);

  }
  
  if ((game_rules_dialogues = game_get_dialogue_of_game_rule(game, &num_dialogues)) != NULL)
  {
    for (i = 0; i < num_dialogues; i++)
    {
      screen_area_puts(ge->feedback, game_rules_dialogues[i]);
      free(game_rules_dialogues[i]);
    }

    free(game_rules_dialogues);
  }
}

void _paint_map_frame(Graphic_engine *ge, Game *game, int type)
{
  int i;

  char ascii_map[MAP_HEIGHT][MAP_WIDTH * MULTIBYTE + 1] = {
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      /* TITLE */
      B_LIGHTBLUE F_BLUE "             ▗█▖     ▐█▙   █▌ ▀▀▀█▛▀▀▘ █▌   ▐█ ▝▀█▛▀ ▐█     ▐█",
      B_LIGHTBLUE F_BLUE "            ▗█▀█▖    ▐█▜▙  █▌    █▌    █▌   ▐█   █▌  ▐█     ▐█",
      B_LIGHTBLUE F_BLUE "           ▗█▙▄▟█▖   ▐█ ▜▙ █▌    █▌    █▛▀▀▀▜█   █▌  ▐█     ▐█",
      B_LIGHTBLUE F_BLUE "          ▗█▘   ▝█▖  ▐█  ▜▙█▌    █▌    █▌   ▐█   █▌  ▐█     ▐█",
      B_LIGHTBLUE F_BLUE "         ▗█▘     ▝█▖ ▐█   ▜█▌    █▌    █▌   ▐█ ▗▄█▙▄ ▐█▄▄▄▄ ▐█▄▄▄▄",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE F_WHITE "                                                 ▁▃▅▆▆▅▃▁",
      B_LIGHTBLUE F_WHITE "                                          ▃▅▆▇▆▄▆████████▆▄▆▇▆▅▃",
      B_LIGHTBLUE F_WHITE "                                         ▐██████████████████████▌",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE F_BROWN "                   ▐" F_RED "▶",
      B_LIGHTBLUE F_WHITE "                  ▟" B_WHITE F_BROWN "▐" B_LIGHTBLUE F_WHITE "▙",
      B_LIGHTBLUE F_WHITE "                 ▟" B_WHITE F_BROWN " ▐ " B_LIGHTBLUE F_WHITE "▙",
      B_LIGHTBLUE F_WHITE "                ▟" B_WHITE F_BROWN "  ▐  " B_LIGHTBLUE F_WHITE "▙",
      B_LIGHTBLUE F_WHITE "               ▟" B_WHITE F_BROWN "   ▐   " B_LIGHTBLUE F_WHITE "▙",
      B_LIGHTBLUE F_WHITE "              ▟" B_WHITE F_BROWN "    ▐    " B_LIGHTBLUE F_WHITE "▙  " F_BLACK "mmo^",
      B_LIGHTBLUE F_BLUE "▂▃▄▅▆▆▅▄" B_BLUE F_RED "▜" B_RED F_WHITE "  ●   ●   ●   ●   ●  " B_BLUE F_RED "▛" B_LIGHTBLUE F_BLUE "▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆",
      B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢" F_RED "▜" B_RED F_WHITE "   ●   ●   ●   ●   " B_BLUE F_RED "▛" F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
      B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
      B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
      B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
  };

  char ascii_map_loose[7][MAP_WIDTH * MULTIBYTE + 1] = {
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE F_BLUE "        ▜▙  ▗█▘▟▛▀▀▀▜▙ █▌   ▐█    ▐█     ▟▛▀▀▀▜▙ ▟▛▀▀▀▜▙ ▀▀▀█▛▀▀▘",
      B_LIGHTBLUE F_BLUE "         ▜▙▗█▘ █▌   ▐█ █▌   ▐█    ▐█     █▌   ▐█ ▜▙▖        █▌",
      B_LIGHTBLUE F_BLUE "          ▜█▘  █▌   ▐█ █▌   ▐█    ▐█     █▌   ▐█  ▝▀█▄▖     █▌",
      B_LIGHTBLUE F_BLUE "          ▐█   █▌   ▐█ █▌   ▐█    ▐█     █▌   ▐█     ▝▜▙    █▌",
      B_LIGHTBLUE F_BLUE "          ▐█   ▜▙▄▄▄▟▛ ▜▙▄▄▄▟▛    ▐█▄▄▄▄ ▜▙▄▄▄▟▛ ▜▙▄▄▄▟▛    █▌"};
  char ascii_map_win[7][MAP_WIDTH * MULTIBYTE + 1] = {
      B_LIGHTBLUE " ",
      B_LIGHTBLUE " ",
      B_LIGHTBLUE F_BLUE "        ▜▙  ▗█▘▟▛▀▀▀▜▙ █▌   ▐█    ▐█   ██   █▌ ▟▛▀▀▀▜▙ ▐█▙   █▌",
      B_LIGHTBLUE F_BLUE "         ▜▙▗█▘ █▌   ▐█ █▌   ▐█     █▌ ▐██▌ ▐█  █▌   ▐█ ▐█▜▙  █▌ ",
      B_LIGHTBLUE F_BLUE "          ▜█▘  █▌   ▐█ █▌   ▐█     ▐█ █▌▐█ █▌  █▌   ▐█ ▐█ ▜▙ █▌",
      B_LIGHTBLUE F_BLUE "          ▐█   █▌   ▐█ █▌   ▐█      ███  ███   █▌   ▐█ ▐█  ▜▙█▌",
      B_LIGHTBLUE F_BLUE "          ▐█   ▜▙▄▄▄▟▛ ▜▙▄▄▄▟▛      ▐█▌  ▐█▌   ▜▙▄▄▄▟▛ ▐█   ▜█▌"

  };

  screen_area_clear(ge->map);

  if (type == -1)
  {
    sprintf(ascii_map[MAP_HEIGHT - 6], B_LIGHTBLUE F_WHITE "              ▟" B_WHITE F_BROWN "    ▐    " B_LIGHTBLUE F_WHITE "▙  " F_BLACK "%.4s", pSkins[player_get_type(game_get_player(game))]);
    for (i = 0; i < 7; i++)
      screen_area_puts(ge->map, ascii_map_loose[i]);
  }
  else if (type == 1)
  {
    sprintf(ascii_map[MAP_HEIGHT - 6], B_LIGHTBLUE F_WHITE "              ▟" B_WHITE F_BROWN "    ▐    " B_LIGHTBLUE F_WHITE "▙  " F_BLACK "%.4s", pSkins[player_get_type(game_get_player(game))]);
    for (i = 0; i < 7; i++)
      screen_area_puts(ge->map, ascii_map_win[i]);
  }
  else
    for (i = 0; i < 7; i++)
      screen_area_puts(ge->map, ascii_map[i]);

  for (; i < MAP_HEIGHT; i++)
    screen_area_puts(ge->map, ascii_map[i]);
}

void _paint_inventory(Graphic_engine *ge, Game *game)
{
  int i, n, count[N_OBJ_TYPES];
  char aux[WORD_SIZE] = "";
  Id *objs;
  Object *obj;

  if (!ge || !game)
    return;

  objs = game_get_player_objects(game, &n);
  sprintf(aux, B_DESCRIPT "  ");
  screen_area_puts(ge->descript, aux);

  sprintf(aux, B_DESCRIPT " - Inventory (%d/%d):", n, player_get_max_objects(game_get_player(game)));

  if (n < 1)
  {
    free(objs);
    strcat(aux, B_DESCRIPT " NONE");
    screen_area_puts(ge->descript, aux);
    return;
  }
  screen_area_puts(ge->descript, aux);

  for (i = 0; i < N_OBJ_TYPES; i++)
    count[i] = 0;
  for (i = 0; i < n; i++)
  {
    obj = game_get_object(game, objs[i]);

    if (object_get_type(obj) == SPECIAL || object_get_type(obj) == NO_OTYPE)
    {
      sprintf(aux, B_DESCRIPT "    -%s ", object_get_name(obj));
      screen_area_puts(ge->descript, aux);
    }
    else
      count[object_get_type(obj)]++;
  }

  for (i = 0; i < N_OBJ_TYPES; i++)
    if (count[i] != 0)
    {
      sprintf(aux, B_DESCRIPT "    -%s: %d ", object_translate_object_type_to_string(i), count[i]);
      screen_area_puts(ge->descript, aux);
    }

  free(objs);
}

void graphic_engine_sprint_objects(Game *game, Space *space, char *str)
{
  int j_c_len, c_len, i_objects, n_objects, bytes;
  Id *object_ids;
  Object *object;

  /* Error control */
  if (game == NULL || space == NULL || str == NULL)
    return;

  /* Gets the objects from the space*/
  object_ids = space_get_objects(space, &n_objects);

  if ((n_objects < 1) || (enemy_get_health(game_get_enemy_in_space(game, space_get_id(space))) > 0)) /* No object or enemy in space case*/
  {
    sprintf(str, "%.*s", BOX_COLS - 2, BLANK);
    free(object_ids);
    return;
  }

  /* if there are objects, it prints them in the string*/
  for (i_objects = 0, bytes = 0, j_c_len = 0; i_objects < n_objects; i_objects++)
  {
    /* Gets the object */
    if ((object = game_get_object(game, object_ids[i_objects])) == NULL)
    {
      free(object_ids);
      return;
    }

    /* Checks that is not hidden */
    if (object_get_hidden(object) == TRUE)
      continue;

    c_len = screen_multibyte_strlen(object_get_name(object));
    if (j_c_len + c_len + 1 <= BOX_COLS - 2)
    {
      bytes += sprintf(str + bytes, " %s", object_get_name(object));
      j_c_len += c_len + 1;
    }
    else
      break;
  }
  /* Fills the remaining space */
  free(object_ids);
  sprintf(str + bytes, "%.*s", BOX_COLS - 2 - j_c_len, BLANK);
}

void graphic_engine_sprint_enemy(Game *game, Id space_loc, char *str)
{
  Enemy *enemy;

  /* Error control */
  if (game == NULL || str == NULL || space_loc == NO_ID)
    return;

  /* Gets enemy */
  enemy = game_get_enemy_in_space(game, space_loc);
  if (enemy_get_health(enemy) > 0) /* Prints enemy */
    sprintf(str, B_LIGHTBROWN F_RED "%s" F_BROWN, enemy_get_edesc(enemy));
  else /* prints blank */
    sprintf(str, B_LIGHTBROWN F_BROWN "%.*s", TAMENEMY, BLANK);
}

void graphic_engine_sprint_space_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west)
{
  Space *space;
  int i, east_link_picker = 0, west_link_picker = 0;
  char **space_gdesc;
  char str_enemy[TAMENEMY * MULTIBYTE + 1];
  char str_objects[BOX_COLS * MULTIBYTE + 1];
  char west_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_L_CORNER, ONE_BLANK, ONE_BLANK, UP_L_CORNER};
  char east_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_R_CORNER, ONE_BLANK, ONE_BLANK, UP_R_CORNER};

  /* Error control */
  if (game == NULL || space_id == NO_ID || space_frame == NULL || offset < 0)
    return;

  /* Gets space*/
  if ((space = game_get_space(game, space_id)) == NULL)
    return;

  /* Gets space graphic description */
  if ((space_gdesc = space_get_gdesc(game_get_space(game, space_id))) == NULL)
    return;

  /* Gets enemy gdesc */
  graphic_engine_sprint_enemy(game, space_id, str_enemy);

  /* Get object names */
  graphic_engine_sprint_objects(game, space, str_objects);

  /* Top border */
  if (north)
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), B_LIGHTBROWN F_BROWN UP_R_CORNER "%.*s" DW_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK DW_R_CORNER "%.*s" UP_L_CORNER B_MAP F_BLACK, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE);
  else
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), B_LIGHTBROWN F_BROWN UP_R_CORNER "%.*s" UP_L_CORNER B_MAP F_BLACK, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  /* Player, enemy and id line */
  if (player_get_location(game_get_player(game)) == space_id)
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), B_LIGHTBROWN F_BROWN V_LINE "%s%.*s%s%.*s%.3ld" V_LINE B_MAP F_BLACK, pSkins[(int)player_get_type(game_get_player(game))], (BOX_COLS - 2 - TAMENEMY - TAMPLAYER - 3) / 2, BLANK, str_enemy, (BOX_COLS - 2 - TAMENEMY - TAMPLAYER - 3) / 2 + (BOX_COLS - 2 - TAMENEMY - TAMPLAYER - 3) % 2, BLANK, space_id);
  else
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), B_LIGHTBROWN F_BROWN V_LINE "%.*s%s%.*s%.3ld" V_LINE B_MAP F_BLACK, TAMPLAYER + (BOX_COLS - 2 - TAMENEMY - TAMPLAYER - 3) / 2, BLANK, str_enemy, (BOX_COLS - 2 - TAMENEMY - TAMPLAYER - 3) / 2 + (BOX_COLS - 2 - TAMENEMY - TAMPLAYER - 3) % 2, BLANK, space_id);

  /* Blank line */
  sprintf(space_frame[2] + screen_multibyte_move(space_frame[2], offset), B_LIGHTBROWN F_BROWN V_LINE "%.*s" V_LINE B_MAP F_BLACK, BOX_COLS - 2, BLANK);

  /* Space Gdesc lines */
  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if (west && i >= 1 && i <= 4)
      west_link_picker++;
    else
      west_link_picker = 0;
    if (east && i >= 1 && i <= 4)
      east_link_picker++;
    else
      east_link_picker = 0;
    sprintf(space_frame[3 + i] + screen_multibyte_move(space_frame[3 + i], offset), B_LIGHTBROWN F_BROWN "%s%s%.*s%s" B_MAP F_BLACK, west_link[west_link_picker], space_gdesc[i], BOX_COLS - GRAPHIC_COLS - 2, BLANK, east_link[east_link_picker]);
  }

  /* Blank line */
  sprintf(space_frame[2 + GRAPHIC_ROWS + 1] + screen_multibyte_move(space_frame[2 + GRAPHIC_ROWS + 1], offset), B_LIGHTBROWN F_BROWN V_LINE "%.*s" V_LINE B_MAP F_BLACK, BOX_COLS - 2, BLANK);

  /* Objects line */
  sprintf(space_frame[3 + GRAPHIC_ROWS + 1] + screen_multibyte_move(space_frame[3 + GRAPHIC_ROWS + 1], offset), B_LIGHTBROWN F_BROWN V_LINE "%s" V_LINE B_MAP F_BLACK, str_objects);

  /* Bottom border */
  if (south)
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), B_LIGHTBROWN F_BROWN DW_R_CORNER "%.*s" UP_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK UP_R_CORNER "%.*s" DW_L_CORNER B_MAP F_BLACK, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE);
  else
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), B_LIGHTBROWN F_BROWN DW_R_CORNER "%.*s" DW_L_CORNER B_MAP F_BLACK, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  for (i = 0; i < BOX_ROWS; i++)
    space_frame[i][strlen(space_frame[i])] = ' ';
}

void graphic_engine_sprint_space_not_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west)
{
  int i, east_link_picker = 0, west_link_picker = 0;
  char west_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_L_CORNER, ONE_BLANK, ONE_BLANK, UP_L_CORNER};
  char east_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_R_CORNER, ONE_BLANK, ONE_BLANK, UP_R_CORNER};

  /* Error control */
  if (game == NULL || space_id == NO_ID || space_frame == NULL || offset < 0)
    return;

  /* Top border */
  if (north)
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), B_BLACK F_WHITE UP_R_CORNER "%.*s" DW_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK DW_R_CORNER "%.*s" UP_L_CORNER F_BLACK B_MAP, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE);
  else
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), B_BLACK F_WHITE UP_R_CORNER "%.*s" UP_L_CORNER F_BLACK B_MAP, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  /* Player and id line */
  if (player_get_location(game_get_player(game)) == space_id)
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), B_BLACK F_WHITE V_LINE "%s %.*s %.3ld" V_LINE F_BLACK B_MAP, pSkins[(int)player_get_type(game_get_player(game))], BOX_COLS - 2 - TAMPLAYER - 3 - 2, Q_MARK, space_id);
  else
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), B_BLACK F_WHITE V_LINE "%.*s %.3ld" V_LINE F_BLACK B_MAP, BOX_COLS - 6, Q_MARK, space_id);

  /* In Between lines */
  for (i = 0; i < BOX_ROWS - 3; i++)
  {
    if (west && i >= 2 && i <= 5)
      west_link_picker++;
    else
      west_link_picker = 0;
    if (east && i >= 2 && i <= 5)
      east_link_picker++;
    else
      east_link_picker = 0;
    sprintf(space_frame[2 + i] + screen_multibyte_move(space_frame[2 + i], offset), B_BLACK F_WHITE "%s%.*s%s" F_BLACK B_MAP, west_link[west_link_picker], BOX_COLS - 2, Q_MARK, east_link[east_link_picker]);
  }

  /* Bottom border */
  if (south)
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), B_BLACK F_WHITE DW_R_CORNER "%.*s" UP_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK UP_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_MAP, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE);
  else
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), B_BLACK F_WHITE DW_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_MAP, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  for (i = 0; i < BOX_ROWS; i++)
    space_frame[i][strlen(space_frame[i])] = ' ';
}

void graphic_engine_sprint_space_flooded(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west)
{
  int i, east_link_picker = 0, west_link_picker = 0;
  char west_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_L_CORNER, ONE_BLANK, ONE_BLANK, UP_L_CORNER};
  char east_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_R_CORNER, ONE_BLANK, ONE_BLANK, UP_R_CORNER};

  /* Error control */
  if (game == NULL || space_id == NO_ID || space_frame == NULL || offset < 0)
    return;

  /* Top border */
  if (north)
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), UP_R_CORNER "%.*s" DW_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK DW_R_CORNER "%.*s" UP_L_CORNER, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE);
  else
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), UP_R_CORNER "%.*s" UP_L_CORNER, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  /* Player and id line */
  if (player_get_location(game_get_player(game)) == space_id)
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), V_LINE "%s %.*s %.3ld" V_LINE, pSkins[(int)player_get_type(game_get_player(game))], BOX_COLS - 2 - TAMPLAYER - 3 - 2, BLANK, space_id);
  else
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), V_LINE "%.*s %.3ld" V_LINE, BOX_COLS - 6, BLANK, space_id);

  /* Top wave line*/
  sprintf(space_frame[2] + screen_multibyte_move(space_frame[2], offset), F_BLACK B_MAP V_LINE F_BLUE "%.*s" F_BLACK V_LINE, screen_multibyte_move(TOP_WAVE, BOX_COLS - 2), TOP_WAVE);
  /* In Between lines */

  for (i = 0; i < BOX_ROWS - 4; i++)
  {
    if (west && i >= 1 && i <= 4)
      west_link_picker++;
    else
      west_link_picker = 0;
    if (east && i >= 1 && i <= 4)
      east_link_picker++;
    else
      east_link_picker = 0;
    sprintf(space_frame[3 + i] + screen_multibyte_move(space_frame[3 + i], offset), F_BLACK B_BLUE "%s" F_LIGHTBLUE "%.*s" F_BLACK "%s" F_BLACK B_MAP, west_link[west_link_picker], 3 * (BOX_COLS - 2), WAVE, east_link[east_link_picker]);
  }

  /* Bottom border */
  if (south)
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), F_BLACK B_BLUE DW_R_CORNER "%.*s" UP_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK UP_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_MAP, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH) / 2), H_LINE);
  else
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), F_BLACK B_BLUE DW_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_MAP, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  for (i = 0; i < BOX_ROWS; i++)
    space_frame[i][strlen(space_frame[i])] = ' ';
}

void graphic_engine_sprint_link(DIRECTION dir, LSTATUS status, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int x, int y, Space *space, Game *game)
{
  char str_color_beggining[2 * TAMCOLOR], str_color_end[2 * TAMCOLOR];

  /* Error control */
  if (dir == NO_DIR || space_frame == NULL || x < 0 || y < 0)
    return;

  /* Chooses color of link */
  if (space_get_flooded(space) == FLOODED && dir != NORTH)
  { /* Flooded */
    sprintf(str_color_beggining, B_BLUE);
    sprintf(str_color_end, B_WHITE);
  }
  else if (space_get_light(space) || game_player_has_light(game))
  { /* Illuminated */
    sprintf(str_color_beggining, B_LIGHTBROWN);
    sprintf(str_color_end, B_MAP);
  }
  else
  { /* Not illuminated */
    sprintf(str_color_beggining, B_BLACK F_WHITE);
    sprintf(str_color_end, B_BLACK F_BLACK);
  }

  if (dir == NORTH || dir == SOUTH)
  {
    if (status == OPEN)
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x), B_BROWN "%s" V_LINE ONE_BLANK ONE_BLANK ONE_BLANK V_LINE "%s", str_color_beggining, str_color_end);
    else
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x), B_BROWN "%s" RG_T ONE_H_LINE ONE_H_LINE ONE_H_LINE LF_T "%s" B_MAP, str_color_beggining, str_color_end);
  }
  else
  {
    if (status == OPEN)
    {
      sprintf(space_frame[y - 1] + screen_multibyte_move(space_frame[y - 1], x), B_BROWN "%s" ONE_H_LINE ONE_H_LINE "%s" B_MAP, str_color_beggining, str_color_end);
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x), B_BROWN "%s" ONE_BLANK ONE_BLANK "%s" B_MAP, str_color_beggining, str_color_end);
      sprintf(space_frame[y + 1] + screen_multibyte_move(space_frame[y + 1], x), B_BROWN "%s" ONE_BLANK ONE_BLANK "%s" B_MAP, str_color_beggining, str_color_end);
      sprintf(space_frame[y + 2] + screen_multibyte_move(space_frame[y + 2], x), B_BROWN "%s" ONE_H_LINE ONE_H_LINE "%s" B_MAP, str_color_beggining, str_color_end);
    }
    else
    {
      sprintf(space_frame[y - 1] + screen_multibyte_move(space_frame[y - 1], x), B_BROWN "%s" DW_T DW_T "%s" B_MAP, str_color_beggining, str_color_end);
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x), B_BROWN "%s" V_LINE V_LINE "%s" B_MAP, str_color_beggining, str_color_end);
      sprintf(space_frame[y + 1] + screen_multibyte_move(space_frame[y + 1], x), B_BROWN "%s" V_LINE V_LINE "%s" B_MAP, str_color_beggining, str_color_end);
      sprintf(space_frame[y + 2] + screen_multibyte_move(space_frame[y + 2], x), B_BROWN "%s" UP_T UP_T "%s" B_MAP, str_color_beggining, str_color_end);
    }
  }
}

void graphic_engine_space_frame_put(Area *area, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int height)
{
  int i;

  /* Error control */
  if (space_frame == NULL || area == NULL || height <= 0)
    return;

  /* Displays the space frame */
  for (i = 0; i < height; i++)
  {
    space_frame[i][screen_multibyte_move(space_frame[i], MAP_WIDTH)] = '\0';
    screen_area_puts(area, space_frame[i]);
  }
}

void graphic_engine_sprint_empty(char (*str_array)[MAP_WIDTH * MULTIBYTE + 1], int height, int width)
{
  int i;
  /* Error control */
  if (str_array == NULL || width <= 0 || height <= 0)
    return;

  /* Sprints spaces into an string array */
  for (i = 0; i < height; i++)
    snprintf(str_array[i], width - 1, B_MAP "%*c", width - 1, ' ');
}

void _paint_map_new(Graphic_engine *ge, Game *game)
{
  int i;
  char space_frame[BOX_ROWS][MAP_WIDTH * MULTIBYTE + 1];
  Id id_centre = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID;
  Space *space, *space_centre;

  /* Error control */
  if (ge == NULL || game == NULL)
    return;

  /* Clears the screen */
  screen_area_clear(ge->map);

  /* Print spaces */
  for (i = 0; i < SPACES_TO_PRINT; i++)
    fprintf(stdout, "\n");

  /* Gets the space id where the player is */
  if ((id_centre = player_get_location(game_get_player(game))) == NO_ID)
    return;

  /* Gets the space where the player is */
  if ((space_centre = game_get_space(game, id_centre)) == NULL)
    return;

  /* Gets the adjacent spaces */
  id_north = game_get_connection(game, id_centre, NORTH);
  id_south = game_get_connection(game, id_centre, SOUTH);
  id_east = game_get_connection(game, id_centre, EAST);
  id_west = game_get_connection(game, id_centre, WEST);

  /* Empties the strings*/
  graphic_engine_sprint_empty(space_frame, BOX_ROWS, MAP_WIDTH * MULTIBYTE + 1);

  /* Puts the first line blank */
  graphic_engine_space_frame_put(ge->map, space_frame, 1);

  /* Gets north space */
  space = game_get_space(game, id_north);
  if (id_north != NO_ID && space_get_flooded(space) != SUNK)
  {
    /* Prints north space */
    if (space_get_flooded(space) == FLOODED)
      graphic_engine_sprint_space_flooded(game, id_north, space_frame, 1 + BOX_COLS + LINK_WIDTH, FALSE, TRUE, FALSE, FALSE);
    else if (space_get_light(space))
      graphic_engine_sprint_space_illuminated(game, id_north, space_frame, 1 + BOX_COLS + LINK_WIDTH, FALSE, TRUE, FALSE, FALSE);
    else
      graphic_engine_sprint_space_not_illuminated(game, id_north, space_frame, 1 + BOX_COLS + LINK_WIDTH, FALSE, TRUE, FALSE, FALSE);

    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);

    /* Prints north link */
    graphic_engine_sprint_empty(space_frame, LINK_HEIGHT, MAP_WIDTH * MULTIBYTE + 1);
    graphic_engine_sprint_link(NORTH, game_get_connection_status(game, id_centre, NORTH), space_frame, BOX_COLS + 1 + LINK_WIDTH + (BOX_COLS - VLINK_WIDTH) / 2, 0, space_centre, game);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT);
  }
  else /* Print blank space */
  {
    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT);
  }

  /* Empties the strings*/
  graphic_engine_sprint_empty(space_frame, BOX_ROWS, MAP_WIDTH * MULTIBYTE + 1);

  /* Prints west space */
  space = game_get_space(game, id_west);
  if (id_west != NO_ID && space_get_flooded(space) != SUNK)
  {
    if (space_get_flooded(space) == FLOODED)
      graphic_engine_sprint_space_flooded(game, id_west, space_frame, 1, FALSE, FALSE, TRUE, FALSE);
    else if (space_get_light(space))
      graphic_engine_sprint_space_illuminated(game, id_west, space_frame, 1, FALSE, FALSE, TRUE, FALSE);
    else
      graphic_engine_sprint_space_not_illuminated(game, id_west, space_frame, 1, FALSE, FALSE, TRUE, FALSE);

    /* Prints west link */
    graphic_engine_sprint_link(WEST, game_get_connection_status(game, id_centre, WEST), space_frame, 1 + BOX_COLS, (BOX_ROWS - H_LINK_HEIGHT) / 2 + 1, space_centre, game);
  }

  /* Prints central space */
  if (space_get_flooded(space_centre) == FLOODED)
    graphic_engine_sprint_space_flooded(game, id_centre, space_frame, 1 + BOX_COLS + LINK_WIDTH, id_north != NO_ID, id_south != NO_ID, id_east != NO_ID, id_west != NO_ID);
  else if (space_get_light(space_centre) || game_player_has_light(game))
    graphic_engine_sprint_space_illuminated(game, id_centre, space_frame, 1 + BOX_COLS + LINK_WIDTH, id_north != NO_ID, id_south != NO_ID, id_east != NO_ID, id_west != NO_ID);
  else
    graphic_engine_sprint_space_not_illuminated(game, id_centre, space_frame, 1 + BOX_COLS + LINK_WIDTH, id_north != NO_ID, id_south != NO_ID, id_east != NO_ID, id_west != NO_ID);

  /* Gets east space */
  space = game_get_space(game, id_east);
  if (id_east != NO_ID && space_get_flooded(space) != SUNK)
  {
    /* Prints east link */
    graphic_engine_sprint_link(EAST, game_get_connection_status(game, id_centre, EAST), space_frame, 1 + 2 * BOX_COLS + LINK_WIDTH, (BOX_ROWS - H_LINK_HEIGHT) / 2 + 1, space_centre, game);

    /* Prints east space */
    if (space_get_flooded(space) == FLOODED)
      graphic_engine_sprint_space_flooded(game, id_east, space_frame, 1 + 2 * BOX_COLS + 2 * LINK_WIDTH, FALSE, FALSE, FALSE, TRUE);
    else if (space_get_light(space))
      graphic_engine_sprint_space_illuminated(game, id_east, space_frame, 1 + 2 * BOX_COLS + 2 * LINK_WIDTH, FALSE, FALSE, FALSE, TRUE);
    else
      graphic_engine_sprint_space_not_illuminated(game, id_east, space_frame, 1 + 2 * BOX_COLS + 2 * LINK_WIDTH, FALSE, FALSE, FALSE, TRUE);
  }

  /* Puts central frame */
  graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);

  /* Empties the strings*/
  graphic_engine_sprint_empty(space_frame, BOX_ROWS, MAP_WIDTH * MULTIBYTE + 1);

  /* Gets south space */
  space = game_get_space(game, id_south);
  if (id_south != NO_ID && space_get_flooded(space) != SUNK) /* Prints south link */
  {
    graphic_engine_sprint_link(SOUTH, game_get_connection_status(game, id_centre, SOUTH), space_frame, BOX_COLS + 1 + LINK_WIDTH + (BOX_COLS - VLINK_WIDTH) / 2, 0, space_centre, game);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT);
    graphic_engine_sprint_empty(space_frame, LINK_HEIGHT, MAP_WIDTH * MULTIBYTE + 1);

    /* Prints south space */
    if (space_get_flooded(space) == FLOODED)
      graphic_engine_sprint_space_flooded(game, id_south, space_frame, 1 + BOX_COLS + LINK_WIDTH, TRUE, FALSE, FALSE, FALSE);
    else if (space_get_light(space))
      graphic_engine_sprint_space_illuminated(game, id_south, space_frame, 1 + BOX_COLS + LINK_WIDTH, TRUE, FALSE, FALSE, FALSE);
    else
      graphic_engine_sprint_space_not_illuminated(game, id_south, space_frame, 1 + BOX_COLS + LINK_WIDTH, TRUE, FALSE, FALSE, FALSE);

    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);
  }
  else /* Print blank space */
  {
    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT);
  }
  screen_area_puts(ge->map, B_MAP " ");
}

void _paint_minimap(Graphic_engine *ge, Game *game)
{
  int i, j, k, bytes = 0;
  char buffer[2 * WORD_SIZE], aux[WORD_SIZE];
  Id Loc;
  Space *space;

  if (ge == NULL || game == NULL)
    return;

  screen_area_clear(ge->minimap);
  paint_n_enters(ge->minimap, 1, B_MINIMAP);
  sprintf(buffer, B_MINIMAP "            MINIMAP  ");
  screen_area_puts(ge->minimap, buffer);

  Loc = player_get_location(game_get_player(game));

  for (i = 2; i >= 0; i--)
  {
    paint_n_enters(ge->minimap, 2, B_MINIMAP);
    sprintf(buffer, B_MINIMAP "           Floor %d", i);
    screen_area_puts(ge->minimap, buffer);
    paint_n_enters(ge->minimap, 2, B_MINIMAP);
    screen_area_puts(ge->minimap, B_MINIMAP "    +----------------------+");
    for (j = 1; j < 9; j++)
    {
      bytes += sprintf(buffer, B_MINIMAP "    | ");
      for (k = 1; k < 8; k++)
      {
        if ((space = game_get_space(game, (Id)(i * 100 + k * 10 + j))) != NULL)
        {
          if (space_get_flooded(space) == SUNK)
            sprintf(aux, B_MINIMAP "   ");
          else if (Loc == (Id)(i * 100 + k * 10 + j))
            sprintf(aux, F_LIGHTGREEN B_GREEN " O ");
          else if (space_get_flooded(space) == FLOODED)
            sprintf(aux, F_LIGHTBLUE B_BLUE " ~ ");
          else if (space_get_light(space) == FALSE)
            sprintf(aux, F_PURPLE B_GREY "|?|");
          else if (enemy_get_health(game_get_enemy_in_space(game, (Id)(i * 100 + k * 10 + j))) > 0)
            sprintf(aux, F_LIGHTRED B_RED "|X|");
          else if (!strcmp(HARBOUR, space_get_name(space)))
            sprintf(aux, F_BROWN B_LIGHTBLUE "|H|");
          else if (!strcmp(WORKSHOP, space_get_name(space)))
            sprintf(aux, F_BROWN B_LIGHTORANGE "|W|");
          else /*Objects*/
          {
            if (game_space_has_object(game, space_get_id(space), STICK) + game_space_has_object(game, space_get_id(space), LEAF) + game_space_has_object(game, space_get_id(space), WALNUT) + game_space_has_object(game, space_get_id(space), GROUND) + game_space_has_object(game, space_get_id(space), LANTERN) + game_space_has_object(game, space_get_id(space), KEY) + game_space_has_object(game, space_get_id(space), LANTERN) + game_space_has_object(game, space_get_id(space), GOLDKEY) > 1)
              sprintf(aux, F_BROWN B_LIGHTBROWN "|*|");
            else if (game_space_has_object(game, space_get_id(space), STICK))
              sprintf(aux, F_BROWN B_LIGHTBROWN "|ᛅ|");
            else if (game_space_has_object(game, space_get_id(space), LEAF))
              sprintf(aux, F_BROWN B_LIGHTBROWN "|♠|");
            else if (game_space_has_object(game, space_get_id(space), WALNUT))
              sprintf(aux, F_BROWN B_LIGHTBROWN "|U|");
            else if (game_space_has_object(game, space_get_id(space), GROUND))
              sprintf(aux, F_BROWN B_LIGHTBROWN "|G|");
            else if (game_space_has_object(game, space_get_id(space), LANTERN))
              sprintf(aux, F_BROWN B_LIGHTBROWN "|L|");
            else if (game_space_has_object(game, space_get_id(space), KEY) || game_space_has_object(game, space_get_id(space), GOLDKEY))
              sprintf(aux, F_BROWN B_LIGHTBROWN "|¬|");
            else
              sprintf(aux, F_BROWN B_LIGHTBROWN "| |");
          }
          bytes += sprintf(buffer + bytes, "%s", aux);
        }
        else
          bytes += sprintf(buffer + bytes, F_BLACK B_MINIMAP "   ");
      }
      bytes += sprintf(buffer + bytes, F_BLACK B_MINIMAP "|");
      screen_area_puts(ge->minimap, buffer);
      bytes = 0;
    }
    sprintf(buffer, F_BLACK B_MINIMAP "    +----------------------+");
    screen_area_puts(ge->minimap, buffer);
  }
  paint_n_enters(ge->minimap, 2, B_MINIMAP);
}

void paint_n_enters(Area *area, int n, char *c)
{
  int i;
  char str[WORD_SIZE];
  if (area == NULL || n < 1)
    return;

  for (i = 0; i < n; i++)
  {
    sprintf(str, "%s"
                 " ",
            c);
    screen_area_puts(area, str);
  }
}