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

#define LINK_WIDTH                2     /*!< Width (in characters) of a link frame */
#define LINK_HEIGHT               1     /*!< Height (in characters) of a link frame */
#define VLINK_WIDTH               5     /*!< Width (in characters) of a vertical (north and south) link */
#define H_LINK_HEIGHT             3     /*!< Width (in characters) of a horizontal (east and west) link */

/* Characters */

#define BLANK           "                                                                                                    "         /*!< Blank character */
#define H_LINE          "────────────────────────────────────────────────────────────────────────────────────────────────────"         /*!< Horizontal line character */
#define Q_MARK          "????????????????????????????????????????????????????????????????????????????????????????????????????"         /*!< Question mark line character */
#define WAVE            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"         /*!< Wave line character */

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
#define B_LIGHTBROWN BACKGROUND(157, 83, 23)
#define F_LIGHTBROWN FOREGROUND(157, 83, 23)
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

static char **black;
static char **flooded;
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
 */
void paint_n_enters(Area *area, int n);

/**
 * @brief Gets the enemy ID in a space
 * @author Alejandro García Hernando
 * @param game Pointer to the game
 * @param space ID of the space
 */
Id get_enemy_id_in_space(Game *game, Id space);

void graphic_engine_sprint_objects(Game * game, Space *space, char *str);

void graphic_engine_sprint_enemy(Game *game, Id space_loc, char *str);

void graphic_engine_sprint_space_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west);

void graphic_engine_sprint_space_not_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west);

void graphic_engine_sprint_space_flooded(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west);

void graphic_engine_sprint_link(DIRECTION dir, LSTATUS status, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int x, int y, Space *space);

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

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;
  int i, j;

  if ((black = (char **)calloc(GRAPHIC_ROWS, sizeof(char *))) == NULL)
    return NULL;

  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if ((black[i] = (char *)calloc(GRAPHIC_COLS + 1, sizeof(char))) == NULL)
    {
      for (j = 0; j < i; j++)
        free(black[j]);

      return NULL;
    }

    for (j = 0; j < GRAPHIC_COLS; j++)
      black[i][j] = DARK_CHAR;

    black[i][GRAPHIC_COLS] = '\0';
  }

  if ((flooded = (char **)calloc(GRAPHIC_ROWS, sizeof(char *))) == NULL)
    return NULL;

  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if ((flooded[i] = (char *)calloc(GRAPHIC_COLS + 1, sizeof(char))) == NULL)
    {
      for (j = 0; j < i; j++)
        free(flooded[j]);

      return NULL;
    }
    for (j = 0; j < GRAPHIC_COLS; j++)
      flooded[i][j] = FLOOD_CHAR;
    flooded[i][GRAPHIC_COLS] = '\0';
  }

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
  int i;
  if (ge == NULL)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);
  screen_area_destroy(ge->minimap);
  for (i = 0; i < GRAPHIC_ROWS; i++)
    free(black[i]);
  free(black);
  for (i = 0; i < GRAPHIC_ROWS; i++)
    free(flooded[i]);
  free(flooded);
  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  int i, f = game_get_num_commands_till_flood(game), n = game_get_num_commands_per_flood(game);
  char aux[WORD_SIZE];
  char str[WORD_SIZE];

  if (ge == NULL || game == NULL)
    return;

  /* Paint in the map area */
  /*_paint_map(ge, game);*/
  _paint_map_new(ge, game);

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  sprintf(str, "                 DESCRIPTION  ");
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, " ");
  if (game_get_num_commands_till_flood(game) != -1)
  {
    sprintf(aux, " - Commands until next flood: %d", game_get_num_commands_till_flood(game));
    screen_area_puts(ge->descript, aux);
  }

  f = DESCRIPT_WIDTH - f * DESCRIPT_WIDTH / n;
  sprintf(aux, " ");
  for (i = 0; i < f; i++)
  {
    strcat(aux, "~");
  }
  for (; i < n; i++)
  {
    strcat(aux, " ");
  }
  screen_area_puts(ge->descript, aux);

  _paint_player_description(ge, game);
  _paint_enemy_description(ge, game);
  _paint_objects_description(ge, game);
  _paint_links_description(ge, game);
  _paint_space_description(ge, game);
  _paint_inspection_description(ge, game);
  screen_area_puts(ge->descript, " ");

  /* Paint in the banner area */
  screen_area_puts(ge->banner, "        THE ANTHILL GAME ");

  /* Paint in the help area */
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " attack or a, take or t, drop or d, move or m, inspect or i, turnon or to, turnoff or tf, op or open with, cl or close with, l or load, s or save, info or y, exit or e");
  screen_area_puts(ge->help, str);

  _paint_feedback_dialogue(ge, game);

  /*Paint in the minimap area*/
  _paint_minimap(ge, game);

  /* Dump to the terminal */
  screen_paint();
  printf("\033[0;37mWrite a command:> ");
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

  if (game_get_player_health(game) != 0)
  {
    screen_area_clear(ge->feedback);
    sprintf(str, "The Harbour has sunk, you cannot escape that's a game over");
    screen_area_puts(ge->feedback, str);
  }
  else
  {
    _paint_feedback_dialogue(ge, game);
  }

  /*Paint in the minimap area*/
  _paint_minimap(ge, game);

  /* Dump to the terminal */
  screen_paint();
}

void _paint_objects_description(Graphic_engine *ge, Game *game)
{
  Id obj_id = NO_ID, obj_loc = NO_ID, enmy_id = NO_ID;
  int i, j;
  char *obj_name;
  char str[WORD_SIZE], aux[WORD_SIZE];

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, " - Objects location:");
  screen_area_puts(ge->descript, str);

  strcpy(str, "\0");
  if (game_get_num_objects(game) > 0)
  {
    for (i = 0; i < game_get_num_objects(game); i++)
    {
      obj_id = game_get_object_id_at(game, i);

      if (((obj_loc = game_get_object_location(game, obj_id)) > 0) && object_get_hidden(game_get_object(game, obj_id)) == FALSE && object_get_movable(game_get_object(game, obj_id)) == TRUE && space_get_light(game_get_space(game, object_get_location(game_get_object(game, obj_id)))) == TRUE)
      {

        if ((enmy_id = get_enemy_id_in_space(game, obj_loc)) != NO_ID)
        {
          if (enemy_get_health(game_get_enemy(game, enmy_id)) < 1)
            enmy_id = NO_ID;
        }

        if (enmy_id == NO_ID || j == MAX_ENEMIES)
        {
          obj_name = game_get_object_name(game, obj_id);
          sprintf(aux, "  %s:%ld", obj_name, obj_loc);
          if ((strlen(str) + strlen(aux) + 2) > DESCRIPT_WIDTH)
          {
            screen_area_puts(ge->descript, str);
            strcpy(str, aux);
          }
          else
            strcat(str, aux);
        }
      }
    }
    screen_area_puts(ge->descript, str);
  }
}

void _paint_links_description(Graphic_engine *ge, Game *game)
{
  Id id_centre = NO_ID, link_id = NO_ID;
  int i;
  char str[WORD_SIZE];

  char *dir_to_str[N_DIR] = {"north", "south", "east", "west", "up", "down"};

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, " - Links:");
  screen_area_puts(ge->descript, str);

  strcpy(str, "\0");
  if ((id_centre = game_get_player_location(game)) != NO_ID)
  {

    for (i = NO_DIR + 1; i < NO_DIR + N_DIR + 1; i++)
    {
      link_id = game_get_link_id(game, id_centre, i);

      if (link_id != NO_ID)
      {
        if (link_get_status(game_get_link(game, link_id)) == OPEN)
          sprintf(str, "  Link %s (%s)= OPEN", dir_to_str[i], game_get_link_name(game, link_id));
        else
          sprintf(str, "  Link %s (%s)= CLOSED", dir_to_str[i], game_get_link_name(game, link_id));

        screen_area_puts(ge->descript, str);
      }
    }
  }
}

void _paint_player_description(Graphic_engine *ge, Game *game)
{
  Id ply_loc = NO_ID;
  char str[WORD_SIZE], aux[WORD_SIZE];

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  if ((ply_loc = game_get_player_location(game)) != NO_ID)
  {
    sprintf(str, " - Player location: %ld", ply_loc);

    sprintf(aux, ", Type: %d", player_get_type(game_get_player(game)));
    strcat(str, aux);

    if (game_get_player_health(game) == 0)
      strcat(str, ", Health: DEAD");
    else
    {
      sprintf(aux, ", Health: %d", game_get_player_health(game));
      strcat(str, aux);
    }

    sprintf(aux, ", Max_objects: %d", player_get_max_objects(game_get_player(game)));
    strcat(str, aux);

    screen_area_puts(ge->descript, str);

    sprintf(str, " - Player objects:");
    screen_area_puts(ge->descript, str);
    _paint_inventory(ge, game);

    /*
    if ((objs_ids = game_get_player_objects(game, &num_objs)) != NULL)
    {

      for (i = 0; i < num_objs; i++)
      {
        obj_id = objs_ids[i];
        if ((obj_loc = game_get_object_location(game, obj_id)) == ON_PLAYER)
        {
          obj_name = game_get_object_name(game, obj_id);
          sprintf(aux, " %s", obj_name);
          if ((strlen(str) + strlen(aux) + 2) > DESCRIPT_WIDTH)
          {
            screen_area_puts(ge->descript, str);
            strcpy(str, aux);
          }
          else
            strcat(str, aux);
        }
      }
      free(objs_ids);
    }
    else
    {
      sprintf(aux, " NONE");
      strcat(str, aux);
    }
    screen_area_puts(ge->descript, str);*/
  }

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
}

void _paint_enemy_description(Graphic_engine *ge, Game *game)
{
  Id enmy_loc = NO_ID;
  int i;
  char str[WORD_SIZE], aux[WORD_SIZE];
  Enemy *enemy;

  screen_area_puts(ge->descript, " ");

  for (i = 0; i < MAX_ENEMIES; i++)
  {
    if ((enemy = game_get_enemy(game, game_get_enemy_id_at(game, i))) != NULL)
    {
      if ((enmy_loc = enemy_get_location(enemy)) != NO_ID)
      {
        sprintf(str, " - %s: location: %ld", enemy_get_name(enemy), enmy_loc);

        if (enemy_get_health(enemy) == 0)
          sprintf(aux, ", health: DEAD");
        else
          sprintf(aux, ",  health: %d", enemy_get_health(enemy));

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

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, " - Description: ");
  screen_area_puts(ge->descript, str);

  if (tdesc != NULL)
  {
    sprintf(str, "  %s", tdesc);
    screen_area_puts(ge->descript, str);
  }
  else
  {
    sprintf(str, "  No description");
    screen_area_puts(ge->descript, str);
  }
}

void _paint_inspection_description(Graphic_engine *ge, Game *game)
{
  char *idesc = NULL;
  char str[WORD_SIZE];

  idesc = game_get_last_idesc(game);

  sprintf(str, " ");
  screen_area_puts(ge->descript, str);

  sprintf(str, " - Inspection: ");
  screen_area_puts(ge->descript, str);

  if (idesc != NULL)
  {
    sprintf(str, "  %s", idesc);
    screen_area_puts(ge->descript, str);
  }
  else
  {
    sprintf(str, "  No description");
    screen_area_puts(ge->descript, str);
  }
}

void _paint_description_init(Graphic_engine *ge, Game *game)
{
  char buffer[WORD_SIZE];

  screen_area_clear(ge->descript);
  paint_n_enters(ge->descript, 1);
  sprintf(buffer, "                        Pick a player");
  screen_area_puts(ge->descript, buffer);
  paint_n_enters(ge->descript, 2);
  sprintf(buffer, "     -Scorpion (1): %s", pSkins[SCORPION]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "The Scorpion is a venomous animal therefore it deals %d more damage", EXTRASCORP);
  paint_n_enters(ge->descript, 1);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "     -Snail (2): %s", pSkins[SNAIL]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "The snail can hold %d more objects due to its big shell.", EXTRASNAIL);
  paint_n_enters(ge->descript, 1);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "     -Firefly (3): %s", pSkins[FIREFLY]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "The Firefly iluminates a room without the need of a torch");
  paint_n_enters(ge->descript, 1);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "     -Ant (4): %s", pSkins[ANT]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "The ant creates %d ground at the beggining of the game", EXTRASANT);
  paint_n_enters(ge->descript, 1);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "     -Butterfly (5): %s", pSkins[BUTTERFLY]);
  screen_area_puts(ge->descript, buffer);
  sprintf(buffer, "The butterfly flies vertically thanks to its light and powerful wings.");
  paint_n_enters(ge->descript, 1);
  screen_area_puts(ge->descript, buffer);
  paint_n_enters(ge->descript, 1);
  sprintf(buffer, " - Exit (e)");
  screen_area_puts(ge->descript, buffer);
}

void _paint_description_end(Graphic_engine *ge, Game *game)
{
  char buffer[WORD_SIZE];

  screen_area_clear(ge->descript);
  paint_n_enters(ge->descript, 2);
  sprintf(buffer, "                        Game has ended");
  screen_area_puts(ge->descript, buffer);
  paint_n_enters(ge->descript, 2);
  sprintf(buffer, "       Hope you enjoyed the game ");
  screen_area_puts(ge->descript, buffer);
}

void _paint_feedback_dialogue(Graphic_engine *ge, Game *game)
{
  T_Command last_cmd = NO_CMD;
  int i = 0, num_executed = 0, num_dialogues = 0;
  char *dialogue_rule = NULL, **game_rules_dialogues;
  STATUS st = OK;

  char str[WORD_SIZE];
  /* Paint in the feedback area */
  last_cmd = game_get_last_command_cmd(game);
  st = game_get_last_command_status(game);

  if (st == ERROR)
  {
    num_executed = game_get_dialogue_executed(game, last_cmd);

    if (num_executed > 0)
    {
      game_increase_dialogue_executed(game, last_cmd);
      dialogue_rule = game_get_printed_repeated_error_rule(game, num_executed);
    }
    else
    {
      for (i = 0; i < MAX_DIALOGUES; i++)
      {
        while (game_get_dialogue_executed(game, i) > 0)
        {
          game_decrease_dialogue_executed(game, i);
        }
      }

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
    {
      while (game_get_dialogue_executed(game, i) > 0)
      {
        game_decrease_dialogue_executed(game, i);
      }
    }

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
    sprintf(str, "%s", dialogue_rule);

    free(dialogue_rule);

    screen_area_puts(ge->feedback, str);
  }

  game_rules_dialogues = game_get_dialogue_of_game_rule(game, &num_dialogues);

  if (game_rules_dialogues != NULL)
  {
    for (i = 0; i < num_dialogues; i++)
    {
      sprintf(str, "%s", game_rules_dialogues[i]);

      free(game_rules_dialogues[i]);
      screen_area_puts(ge->feedback, str);
    }

    free(game_rules_dialogues);
  }
}

void _paint_map_frame(Graphic_engine *ge, Game *game, int type)
{
  int i;

  char new_ascii_map[MAP_HEIGHT][MAP_WIDTH * MULTIBYTE + 1] = {
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
    B_LIGHTBLUE " ",
    B_LIGHTBLUE " ",
    B_LIGHTBLUE " ",
    B_LIGHTBLUE F_BROWN "                   ▐" F_RED "▶",
    B_LIGHTBLUE F_WHITE "                  ▟" B_WHITE F_BROWN "▐" B_LIGHTBLUE F_WHITE "▙",
    B_LIGHTBLUE F_WHITE "                 ▟" B_WHITE F_BROWN " ▐ " B_LIGHTBLUE F_WHITE "▙",
    B_LIGHTBLUE F_WHITE "                ▟" B_WHITE F_BROWN "  ▐  " B_LIGHTBLUE F_WHITE "▙",
    B_LIGHTBLUE F_WHITE "               ▟" B_WHITE F_BROWN "   ▐   " B_LIGHTBLUE F_WHITE "▙",
    B_LIGHTBLUE F_WHITE "              ▟" B_WHITE F_BROWN "    ▐    " B_LIGHTBLUE F_WHITE "▙  " F_BLACK "mmo^",
    B_LIGHTBLUE F_BLUE "▂▃▄▅▆▆▅▄" B_BLUE F_RED "▜" B_RED F_WHITE "  ●   ●   ●   ●   ●  " B_BLUE F_RED "▛" B_LIGHTBLUE F_BLUE"▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆▆▅▄▃▂▂▃▄▅▆",
    B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢" F_RED "▜" B_RED F_WHITE "   ●   ●   ●   ●   " B_BLUE F_RED "▛" F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
    B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
    B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
    B_BLUE F_LIGHTBLUE "⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣⌢⌣",
  };

  char ascii_map[MAP_HEIGHT][(MAP_WIDTH)*3 + 1] = {
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "                         _______              ______  ",
      B_LIGHTBLUE "       //\\\\   ||\\\\  ||     ||      ||    ||     ||    ||      ||",
      B_LIGHTBLUE "      //__\\\\  || \\\\ ||     ||      ||____||     ||    ||      ||",
      B_LIGHTBLUE "     //    \\\\ ||  \\\\||     ||      ||    ||   __||__  ||____  ||___",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "     ",
      B_LIGHTBLUE "                   |>              ",
      B_LIGHTBLUE "                   |               ",
      B_LIGHTBLUE "                  " B_WHITE "/|\\" B_LIGHTBLUE "              ",
      B_LIGHTBLUE "                 " B_WHITE "/.| \\" B_LIGHTBLUE "             ",
      B_LIGHTBLUE "                " B_WHITE "/^^|^^\\" B_LIGHTBLUE "            ",
      B_LIGHTBLUE "        _______" B_WHITE "/___|___\\" B_LIGHTBLUE "_mmo^__    ",
      F_DARKBLUE BACKGROUND(0, 150, 255) "⌢⌣⌢⌣⌢⌣⌢⌣" FOREGROUND(0, 0, 0) BACKGROUND(200, 0, 0) "\\...................../" F_DARKBLUE BACKGROUND(0, 150, 255) "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
      F_DARKBLUE BACKGROUND(0, 150, 255) "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
      F_DARKBLUE BACKGROUND(0, 150, 255) "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
      F_DARKBLUE BACKGROUND(0, 150, 255) "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"};

  char ascii_map_loose[7][MAP_WIDTH + 1] = {
      "     ",
      "           ",
      "       \\   /  ____               |       ____      _____   _____    ||",
      "        \\ / //    \\\\  ||   ||    |     //    \\\\   /          |      ||",
      "         |  ||    ||  ||   ||    |     ||    ||   \\_____     |      ||",
      "         |  ||    ||  ||   ||    |     ||    ||        \\\\    |        ",
      "         |  \\\\____//  \\\\___//    |____ \\\\____//   _____//    |      []",
  };
  char ascii_map_win[7][MAP_WIDTH + 1] = {
      "     ",
      "           ",
      "    \\\\   //  _____                                ____             ||",
      "     \\\\ // //    \\\\  ||   ||   \\              / //    \\\\  ||\\   || ||",
      "       |   ||    ||  ||   ||    \\     /\\     /  ||    ||  || \\  || ||",
      "       |   ||    ||  ||   ||     \\   /  \\   /   ||    ||  ||  \\ ||   ",
      "       |   \\\\____//  \\\\___//      \\ /    \\ /    \\\\____//  ||   \\|| []",
  };

  screen_area_clear(ge->map);

  if (type == -1)
  {
    sprintf(ascii_map_loose[MAP_HEIGHT - 5], "        _______/___|___\\_%.4s__    ", pSkins[player_get_type(game_get_player(game))]);
    for (i = 0; i < 7; i++)
      screen_area_puts(ge->map, ascii_map_loose[i]);
  }
  else if (type == 1)
  {
    sprintf(ascii_map[MAP_HEIGHT - 5], "        _______/___|___\\_%.4s__    ", pSkins[player_get_type(game_get_player(game))]);
    for (i = 0; i < 7; i++)
      screen_area_puts(ge->map, ascii_map_win[i]);
  }
  else
  {
    for (i = 0; i < 7; i++)
      screen_area_puts(ge->map, new_ascii_map[i]);
  }
  for (; i < MAP_HEIGHT; i++)
    screen_area_puts(ge->map, new_ascii_map[i]);
}

void _paint_inventory(Graphic_engine *ge, Game *game)
{
  int i, f = 0, n, count[N_OBJ_TYPES];
  char aux[WORD_SIZE] = "";
  Id *objs;
  Object *obj;

  if (!ge || !game)
  {
    return;
  }
  objs = game_get_player_objects(game, &n);
  for (i = 0; i < N_OBJ_TYPES; i++)
    count[i] = 0;
  for (i = 0; i < n; i++)
  {
    obj = game_get_object(game, objs[i]);

    if (object_get_type(obj) == SPECIAL || object_get_type(obj) == NO_OTYPE)
    {
      f = 1;
      fprintf(stderr, "%d %s\n", object_get_type(obj), object_get_name(obj));

      sprintf(aux, "-%s ", object_get_name(obj));
      screen_area_puts(ge->descript, aux);
    }
    else
    {
      count[object_get_type(obj)]++;
    }
  }

  for (i = 0; i < N_OBJ_TYPES; i++)
  {
    if (count[i] != 0)
    {
      f = 1;
      fprintf(stderr, "%d %s\n", i, object_translate_object_type_to_string(i));
      sprintf(aux, "-%s: %d ", object_translate_object_type_to_string(i), count[i]);
      screen_area_puts(ge->descript, aux);
    }
  }
  if (f == 0)
  {
    sprintf(aux, " NONE");
    screen_area_puts(ge->descript, aux);
  }
  free(objs);
}

void graphic_engine_sprint_objects(Game * game, Space *space, char *str) {
  int j_c_len, c_len, i_objects, n_objects, bytes;
  Id *object_ids;
  Object *object;

  /* Error control */
  if (game == NULL || space == NULL || str == NULL) {
    return;
  }

  /* Gets the objects from the space*/
  object_ids = space_get_objects(space, &n_objects);

  /* if there are objects, it prints them in the string*/
  if (n_objects > 0) {

    for (bytes = 0, j_c_len = 0; i_objects < n_objects; i_objects++) {

      /* Gets the object */
      object = game_get_object(game, object_ids[i_objects]);
      if (object == NULL) {
        #ifdef DEBUG
          fprintf(stderr, "Error graphic engine sprint objects: error while getting the object n: %d\n",i_objects);
        #endif
        return;
      }

      /* Checks that is not hidden */
      if (object_get_hidden(object) == TRUE) {
        continue;
      }

      c_len = screen_multibyte_strlen(object_get_name(object));
      if (j_c_len + c_len + 1 <= BOX_COLS - 2) {
        bytes += sprintf(str + bytes, " %s", object_get_name(object));
        j_c_len +=  c_len + 1;
      } else {
        break;
      }
    }
    /* Fills the remaining space */
    sprintf(str + bytes, "%.*s", BOX_COLS - 2 - j_c_len, BLANK);
  } else {
    /* No object case */
    sprintf(str, "%.*s", BOX_COLS - 2, BLANK);
    
  }  
}

void graphic_engine_sprint_enemy(Game *game, Id space_loc, char *str) {
  Enemy *enemy;
  int i;

  /* Error control */
  if (game == NULL || str == NULL || space_loc == NO_ID) {
    #ifdef DEBUG
      fprintf(stderr, "Error graphic engine sprint enemy: invalid parameters\n");
    #endif
    return;
  }

  /* Gets enemy (SUSUSUSUSUS) */
  for (i = 0; i < MAX_ENEMIES; i++) {
    enemy = game_get_enemy(game, game_get_enemy_id_at(game, i));
    if (enemy == NULL || enemy_get_location(enemy) == space_loc){
      break;
    }
  }

  if (enemy != NULL && enemy_get_health(enemy) > 0){
    /* Prints enemy */
    sprintf(str, "%s", enemy_get_edesc(enemy));
  } else {
    /* prints blank */
    sprintf(str, "%.*s", TAMENEMY, BLANK);
  }  
}

void graphic_engine_sprint_space_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west) {
  Space *space;
  int i, east_link_picker = 0, west_link_picker = 0;
  char **space_gdesc;
  char str_enemy[TAMENEMY * MULTIBYTE + 1];
  char str_objects[BOX_COLS * MULTIBYTE + 1];
  char west_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_L_CORNER, ONE_BLANK, UP_L_CORNER};
  char east_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_R_CORNER, ONE_BLANK, UP_R_CORNER};

  /* Error control */
  if ( game == NULL || space_id == NO_ID || space_frame == NULL || offset < 0) {
    #ifdef DEBUG
      fprintf(stderr, "Error graphic engine sprint space illuminated: invalid parameters\n");
    #endif
    return;
  }

  /* Gets space*/
  space = game_get_space(game, space_id);
  if (space == NULL) {
    #ifdef DEBUG
      fprintf(stderr, "Error graphic engine sprint space illuminated: could not get space\n");
    #endif
    return;
  }

  /* Gets space graphic description */
  space_gdesc = space_get_gdesc(space);
  if (space_gdesc == NULL) {
    #ifdef DEBUG
      fprintf(stderr, "Error graphic engine sprint space illuminated: could not get space graphic description\n");
    #endif
    return;
  }

  /* Gets enemy gdesc */
  graphic_engine_sprint_enemy(game, space_id, str_enemy);

  /* Get object names */
  graphic_engine_sprint_objects(game, space, str_objects);

  /* Top border */
  if (north)
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), UP_R_CORNER "%.*s" DW_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK DW_R_CORNER "%.*s" UP_L_CORNER, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE);
  else
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), UP_R_CORNER "%.*s" UP_L_CORNER, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  /* Player, enemy and id line */
  if (game_get_player_location(game) == space_id){
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), V_LINE "%s %s%.*s%.3ld" V_LINE, pSkins[(int)player_get_type(game_get_player(game))], str_enemy, BOX_COLS - 3 - TAMENEMY - TAMPLAYER - 3, BLANK, space_id);
  } else {
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), V_LINE "%.*s %s%.*s%.3ld" V_LINE, TAMPLAYER, BLANK, str_enemy, BOX_COLS - 3 - TAMENEMY - TAMPLAYER - 3, BLANK, space_id);
  }

  /* Blank line */
  sprintf(space_frame[2] + screen_multibyte_move(space_frame[2], offset), V_LINE "%.*s" V_LINE, BOX_COLS - 2, BLANK);
  
  /* Space Gdesc lines */
  for (i = 0; i < GRAPHIC_ROWS; i++){
    if (west && i >= 1 && i <= 3)
      west_link_picker++;
    else 
      west_link_picker = 0;
    if (east && i >= 1 && i <= 3)
      east_link_picker++;
    else 
      east_link_picker = 0;  
    sprintf(space_frame[3 + i] + screen_multibyte_move(space_frame[3 + i], offset), "%s%s%.*s%s", west_link[west_link_picker], space_gdesc[i], BOX_COLS - GRAPHIC_COLS - 2, BLANK, east_link[east_link_picker]);
  }

  /* Blank line */
  sprintf(space_frame[2 + GRAPHIC_ROWS + 1] + screen_multibyte_move(space_frame[2 + GRAPHIC_ROWS + 1], offset), V_LINE "%.*s" V_LINE, BOX_COLS - 2, BLANK);

  /* Objects line */
  sprintf(space_frame[3 + GRAPHIC_ROWS + 1] + screen_multibyte_move(space_frame[2 + GRAPHIC_ROWS + 1], offset), V_LINE "%s" V_LINE, str_objects);

  /* Bottom border */
  if (south)
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), DW_R_CORNER "%.*s" UP_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK UP_R_CORNER "%.*s" DW_L_CORNER, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE);
  else
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), DW_R_CORNER "%.*s" DW_L_CORNER, screen_multibyte_move(H_LINE, BOX_COLS - 2) , H_LINE);

  for (i = 0; i < BOX_ROWS; i++) {
    space_frame[i][strlen(space_frame[i])] = ' ';
  }
}

void graphic_engine_sprint_space_not_illuminated(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west) {
  int i, east_link_picker = 0, west_link_picker = 0;
  char west_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_L_CORNER, ONE_BLANK, UP_L_CORNER};
  char east_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_R_CORNER, ONE_BLANK, UP_R_CORNER};

  /* Error control */
  if ( game == NULL || space_id == NO_ID || space_frame == NULL || offset < 0) {
    #ifdef DEBUG
      fprintf(stderr, "Error graphic engine sprint space illuminated: invalid parameters\n");
    #endif
    return;
  }

  /* Top border */
  if (north)
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), B_BLACK F_WHITE UP_R_CORNER "%.*s" DW_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK DW_R_CORNER "%.*s" UP_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE);
  else
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), B_BLACK F_WHITE UP_R_CORNER "%.*s" UP_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  /* Player and id line */
  if (game_get_player_location(game) == space_id){
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), B_BLACK F_WHITE V_LINE "%s %.*s %.3ld" V_LINE F_BLACK B_WHITE, pSkins[(int)player_get_type(game_get_player(game))], BOX_COLS - 2 - TAMPLAYER - 3 - 2, Q_MARK, space_id);
  } else {
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), B_BLACK F_WHITE V_LINE "%.*s %.3ld" V_LINE F_BLACK B_WHITE, BOX_COLS - 6, Q_MARK, space_id);
  }

  /* In Between lines */
  for (i = 0; i < BOX_ROWS - 3; i++){
    if (west && i >= 2 && i <= 4)
      west_link_picker++;
    else 
      west_link_picker = 0;
    if (east && i >= 2 && i <= 4)
      east_link_picker++;
    else 
      east_link_picker = 0;  
    sprintf(space_frame[2 + i] + screen_multibyte_move(space_frame[2 + i], offset), B_BLACK F_WHITE "%s%.*s%s" F_BLACK B_WHITE, west_link[west_link_picker], BOX_COLS - 2, Q_MARK, east_link[east_link_picker]);
  }

  /* Bottom border */
  if (south)
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), B_BLACK F_WHITE DW_R_CORNER "%.*s" UP_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK UP_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE);
  else
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset), B_BLACK F_WHITE DW_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, BOX_COLS - 2) , H_LINE);

  for (i = 0; i < BOX_ROWS; i++) {
    space_frame[i][strlen(space_frame[i])] = ' ';
  }
}

void graphic_engine_sprint_space_flooded(Game *game, Id space_id, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int offset, BOOL north, BOOL south, BOOL east, BOOL west) {
  int i, east_link_picker = 0, west_link_picker = 0;
  char west_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_L_CORNER, ONE_BLANK, UP_L_CORNER};
  char east_link[H_LINK_HEIGHT + 1][MULTIBYTE + 1] = {V_LINE, DW_R_CORNER, ONE_BLANK, UP_R_CORNER};

  /* Error control */
  if ( game == NULL || space_id == NO_ID || space_frame == NULL || offset < 0) {
    #ifdef DEBUG
      fprintf(stderr, "Error graphic engine sprint space illuminated: invalid parameters\n");
    #endif
    return;
  }

  /* Top border */
  if (north)
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), F_BLACK B_BLUE UP_R_CORNER "%.*s" DW_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK DW_R_CORNER "%.*s" UP_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE);
  else
    sprintf(space_frame[0] + screen_multibyte_move(space_frame[0], offset), F_BLACK B_BLUE UP_R_CORNER "%.*s" UP_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, BOX_COLS - 2), H_LINE);

  /* Player and id line */
  if (game_get_player_location(game) == space_id){
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), F_BLACK B_BLUE V_LINE "%s " F_LIGHTBLUE "%.*s" F_BLACK " %.3ld" V_LINE F_BLACK B_WHITE, pSkins[(int)player_get_type(game_get_player(game))], BOX_COLS - 2 - TAMPLAYER - 3 - 2, WAVE, space_id);
  } else {
    sprintf(space_frame[1] + screen_multibyte_move(space_frame[1], offset), F_BLACK B_BLUE V_LINE F_LIGHTBLUE "%.*s" F_BLACK " %.3ld" V_LINE F_BLACK B_WHITE,BOX_COLS - 6, WAVE, space_id);
  }

  /* In Between lines */
  for (i = 0; i < BOX_ROWS - 3; i++){
    if (west && i >= 2 && i <= 4)
      west_link_picker++;
    else 
      west_link_picker = 0;
    if (east && i >= 2 && i <= 4)
      east_link_picker++;
    else 
      east_link_picker = 0;  
    sprintf(space_frame[2 + i] + screen_multibyte_move(space_frame[2 + i], offset),F_BLACK B_BLUE "%s" F_LIGHTBLUE "%.*s" F_BLACK "%s" F_BLACK B_WHITE, west_link[west_link_picker], BOX_COLS - 2, WAVE, east_link[east_link_picker]);
  }

  /* Bottom border */
  if (south)
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset),F_BLACK B_BLUE DW_R_CORNER "%.*s" UP_L_CORNER ONE_BLANK ONE_BLANK ONE_BLANK UP_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE, screen_multibyte_move(H_LINE, (BOX_COLS - 2 - VLINK_WIDTH)/2), H_LINE);
  else
    sprintf(space_frame[BOX_ROWS - 1] + screen_multibyte_move(space_frame[BOX_ROWS - 1], offset),F_BLACK B_BLUE DW_R_CORNER "%.*s" DW_L_CORNER F_BLACK B_WHITE, screen_multibyte_move(H_LINE, BOX_COLS - 2) , H_LINE);

  for (i = 0; i < BOX_ROWS; i++) {
    space_frame[i][strlen(space_frame[i])] = ' ';
  }
}

void graphic_engine_sprint_link(DIRECTION dir, LSTATUS status, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int x, int y, Space *space) {
  char str_color_beggining[2 * TAMCOLOR], str_color_end[2 * TAMCOLOR];

  /* Error control */
  if (dir == NO_DIR || space_frame == NULL ||x < 0 ||y < 0) {
    #ifdef DEBUG
      fprintf(stderr, "Error in graphic engine space frame put: invalid parameters\n");
    #endif
    return;
  }

  /* Chooses color of link */
  if (space_get_flooded(space) == FLOODED){ /* Flooded */
      sprintf(str_color_beggining, B_BLUE);
      sprintf(str_color_end, B_WHITE);
    } else {
      if (space_get_light(space)){ /* Illuminated */
        sprintf(str_color_beggining, B_WHITE);
        sprintf(str_color_end, B_WHITE);
      } else {  /* Not illuminated */
        sprintf(str_color_beggining, B_BLACK F_WHITE);
        sprintf(str_color_end, B_WHITE F_BLACK);
      }
    }

  if (dir == NORTH || dir == SOUTH) {
    if (status == OPEN) {
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x), "%s" V_LINE ONE_BLANK ONE_BLANK ONE_BLANK V_LINE "%s", str_color_beggining, str_color_end);
    } else {
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x),"%s" RG_T ONE_H_LINE ONE_H_LINE ONE_H_LINE LF_T "%s", str_color_beggining, str_color_end);
    }
    
  } else {
    if (status == OPEN) {
      sprintf(space_frame[y - 1] + screen_multibyte_move(space_frame[y - 1], x),"%s" ONE_H_LINE ONE_H_LINE "%s", str_color_beggining, str_color_end);
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x),"%s" ONE_BLANK ONE_BLANK "%s", str_color_beggining, str_color_end);
      sprintf(space_frame[y + 1] + screen_multibyte_move(space_frame[y + 1], x),"%s" ONE_H_LINE ONE_H_LINE "%s", str_color_beggining, str_color_end);
    } else {
      sprintf(space_frame[y - 1] + screen_multibyte_move(space_frame[y - 1], x),"%s" DW_T DW_T "%s", str_color_beggining, str_color_end);
      sprintf(space_frame[y] + screen_multibyte_move(space_frame[y], x),"%s" V_LINE V_LINE "%s", str_color_beggining, str_color_end);
      sprintf(space_frame[y + 1] + screen_multibyte_move(space_frame[y + 1], x),"%s" UP_T UP_T "%s", str_color_beggining, str_color_end);
    }
  }

}

void graphic_engine_space_frame_put(Area *area, char (*space_frame)[MAP_WIDTH * MULTIBYTE + 1], int height) {
  int i;
  
  /* Error control */
  if (space_frame == NULL || area == NULL || height <= 0) {
    #ifdef DEBUG
      fprintf(stderr, "Error in graphic engine space frame put: invalid parameters\n");
    #endif
    return;
  }

  /* Displays the space frame */
  for (i = 0; i < height; i++) {
    space_frame[i][screen_multibyte_move(space_frame[i], MAP_WIDTH)] = '\0';
    screen_area_puts(area, space_frame[i]);
  }
}

void graphic_engine_sprint_empty(char (*str_array)[MAP_WIDTH * MULTIBYTE + 1], int height, int width) {
  int i, j;
  /* Error control */
  if (str_array == NULL || width <= 0 || height <= 0) {
    #ifdef DEBUG
      fprintf(stderr, "Error in graphic engine sprint empty: invalid parameters\n");
    #endif
    return;
  }

  /* Sprints spaces into an string array */
  for (i = 0; i < height; i++) {
    for (j = 0; j < width - 1; j++) {
      str_array[i][j] = ' ';
      
    }
    str_array[i][j] = '\0';
  }
}

void _paint_map_new(Graphic_engine *ge, Game *game){
  int i;
  char space_frame[BOX_ROWS][MAP_WIDTH * MULTIBYTE + 1];
  Id id_centre = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID;
  Space *space, *space_centre;

  /* Error control */
  if (ge == NULL || game == NULL) {
    return;
  }

  /* Clears the screen */
  screen_area_clear(ge->map);

  /* Print spaces */
  for (i = 0; i < SPACES_TO_PRINT; i++){
    fprintf(stdout, "\n");
  }

  /* Gets the space id where the player is */
  if ((id_centre = game_get_player_location(game)) == NO_ID) {
    return;
  }

  /* Gets the space where the player is */
  if ((space_centre = game_get_space(game, id_centre)) == NULL) {
    return;
  }

  /* Gets the adjacent spaces */
  id_north = game_get_connection(game, id_centre, NORTH);
  id_south = game_get_connection(game, id_centre, SOUTH);
  id_east = game_get_connection(game, id_centre, EAST);
  id_west = game_get_connection(game, id_centre, WEST);

  /* Empties the strings*/
  graphic_engine_sprint_empty(space_frame, BOX_ROWS, MAP_WIDTH * MULTIBYTE + 1);

  /* Puts the first line blank */
  graphic_engine_space_frame_put(ge->map, space_frame, 1);

  if (id_north != NO_ID) {
    /* Prints north space */

    /* Gets north space */
    space = game_get_space(game, id_north);
    if (space_get_flooded(space) == FLOODED){
      graphic_engine_sprint_space_flooded(game, id_north, space_frame, 1 + BOX_COLS + LINK_WIDTH, FALSE, TRUE, FALSE, FALSE);
    } else {
      if (space_get_light(space)){
        graphic_engine_sprint_space_illuminated(game, id_north, space_frame, 1 + BOX_COLS + LINK_WIDTH, FALSE, TRUE, FALSE, FALSE);
      } else {
        graphic_engine_sprint_space_not_illuminated(game, id_north, space_frame, 1 + BOX_COLS + LINK_WIDTH, FALSE, TRUE, FALSE, FALSE);
      }
    }
    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);

    /* Prints north link */
    graphic_engine_sprint_empty( space_frame, LINK_HEIGHT, MAP_WIDTH * MULTIBYTE + 1);
    graphic_engine_sprint_link(NORTH, game_get_connection_status(game, id_centre, NORTH), space_frame, BOX_COLS + 1 + LINK_WIDTH + (BOX_COLS - VLINK_WIDTH) / 2, 0, space_centre);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT); 

  } else {
    /* Print blank space */
    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT);
  }

  /* Empties the strings*/
  graphic_engine_sprint_empty(space_frame, BOX_ROWS, MAP_WIDTH * MULTIBYTE + 1);

  if (id_west != NO_ID) {
    /* Prints west space */
    fprintf(stderr, "%ld\n", id_west);
    /* Gets west space */
    space = game_get_space(game, id_west);
    if (space_get_flooded(space) == FLOODED){
      graphic_engine_sprint_space_flooded(game, id_west, space_frame, 1, FALSE, FALSE, TRUE, FALSE);
    } else {
      if (space_get_light(space)){
        graphic_engine_sprint_space_illuminated(game, id_west, space_frame, 1, FALSE, FALSE, TRUE, FALSE);
      } else {
        graphic_engine_sprint_space_not_illuminated(game, id_west, space_frame, 1, FALSE, FALSE, TRUE, FALSE);
      }
    }

    /* Prints west link */
    graphic_engine_sprint_link(WEST, game_get_connection_status(game, id_centre, WEST), space_frame, 1 + BOX_COLS, (BOX_ROWS - H_LINK_HEIGHT)/2 + 1, space_centre);
  }

  /* Prints central space */
  if (space_get_flooded(space_centre) == FLOODED){
    graphic_engine_sprint_space_flooded(game, id_centre, space_frame, 1 + BOX_COLS + LINK_WIDTH, id_north != NO_ID, id_south != NO_ID, id_east != NO_ID, id_west != NO_ID);
  } else {
    if (space_get_light(space_centre)){
      graphic_engine_sprint_space_illuminated(game, id_centre, space_frame, 1 + BOX_COLS + LINK_WIDTH, id_north != NO_ID, id_south != NO_ID, id_east != NO_ID, id_west != NO_ID);
    } else {
      graphic_engine_sprint_space_not_illuminated(game, id_centre, space_frame, 1 + BOX_COLS + LINK_WIDTH, id_north != NO_ID, id_south != NO_ID, id_east != NO_ID, id_west != NO_ID);
    }
  }

  if (id_east != NO_ID) {
    /* Prints east link */
    graphic_engine_sprint_link(EAST, game_get_connection_status(game, id_centre, EAST), space_frame, 1 + 2 * BOX_COLS + LINK_WIDTH, (BOX_ROWS - H_LINK_HEIGHT)/2 + 1, space_centre);

    /* Prints east space */

    /* Gets east space */
    space = game_get_space(game, id_east);
    if (space_get_flooded(space) == FLOODED){
      graphic_engine_sprint_space_flooded(game, id_east, space_frame, 1 + 2 * BOX_COLS + 2 * LINK_WIDTH, FALSE, FALSE, FALSE, TRUE);
    } else {
      if (space_get_light(space)){
        graphic_engine_sprint_space_illuminated(game, id_east, space_frame, 1 + 2 * BOX_COLS + 2 * LINK_WIDTH, FALSE, FALSE, FALSE, TRUE);
      } else {
        graphic_engine_sprint_space_not_illuminated(game, id_east, space_frame, 1 + 2 * BOX_COLS + 2 * LINK_WIDTH, FALSE, FALSE, FALSE, TRUE);
      }
    }
  }

  /* Puts central frame */
  graphic_engine_space_frame_put(ge->map,  space_frame, BOX_ROWS);

  /* Empties the strings*/
  graphic_engine_sprint_empty(space_frame, BOX_ROWS, MAP_WIDTH * MULTIBYTE + 1);

  if (id_south != NO_ID) {

    /* Prints south link */
    graphic_engine_sprint_link(SOUTH, game_get_connection_status(game, id_centre, SOUTH), space_frame, BOX_COLS + 1 + LINK_WIDTH + (BOX_COLS - VLINK_WIDTH) / 2, 0, space_centre);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT); 
    graphic_engine_sprint_empty(space_frame, LINK_HEIGHT, MAP_WIDTH * MULTIBYTE + 1);

    /* Prints south space */

    /* Gets north space */
    space = game_get_space(game, id_south);
    if (space_get_flooded(space) == FLOODED){
      graphic_engine_sprint_space_flooded(game, id_south, space_frame, 1 + BOX_COLS + LINK_WIDTH, TRUE, FALSE, FALSE, FALSE);
    } else {
      if (space_get_light(space) || game_player_has_light(game)){
        graphic_engine_sprint_space_illuminated(game, id_south, space_frame, 1 + BOX_COLS + LINK_WIDTH, TRUE, FALSE, FALSE, FALSE);
      } else {
        graphic_engine_sprint_space_not_illuminated(game, id_south, space_frame, 1 + BOX_COLS + LINK_WIDTH, TRUE, FALSE, FALSE, FALSE);
      }
    }
    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);

    

  } else {
    /* Print blank space */
    graphic_engine_space_frame_put(ge->map, space_frame, BOX_ROWS);
    graphic_engine_space_frame_put(ge->map, space_frame, LINK_HEIGHT);
  }
}

void _paint_map(Graphic_engine *ge, Game *game)
{
  Id id_centre = NO_ID, id_north = NO_ID, id_south = NO_ID, id_east = NO_ID, id_west = NO_ID, enmy_id = NO_ID;
  Id *objs_ids = NULL, *wobjs_ids = NULL, *eobjs_ids = NULL;
  Space *space_centre = NULL, *space_west = NULL, *space_east = NULL;
  Enemy *enemy;

  int i, j, num_objs = 0, wnum_objs = 0, enum_objs = 0, slen, total_len;
  char **gdesc = NULL, **wgdesc = NULL, **egdesc = NULL, *obj_name = NULL, *edesc = NULL;

  char str[WORD_SIZE], aux[WORD_SIZE];

  screen_area_clear(ge->map);
  if ((id_centre = game_get_player_location(game)) != NO_ID)
  {
    id_north = game_get_connection(game, id_centre, NORTH);
    id_south = game_get_connection(game, id_centre, SOUTH);
    id_east = game_get_connection(game, id_centre, EAST);
    id_west = game_get_connection(game, id_centre, WEST);

    space_centre = game_get_space(game, id_centre);
    objs_ids = space_get_objects(space_centre, &num_objs);
    if (space_get_light(space_centre) || game_player_has_light(game))
    {
      if (space_get_flooded(space_centre) == FLOODED)
        gdesc = flooded;
      else
        gdesc = space_get_gdesc(space_centre);
    }
    else
    {
      gdesc = black;
    }
    if (id_west != NO_ID)
    {
      space_west = game_get_space(game, id_west);
      if (space_get_light(space_west))
      {
        wgdesc = space_get_gdesc(space_west);
        if (space_get_flooded(space_west) == FLOODED)
          wgdesc = flooded;
      }
      else
        wgdesc = black;
      wobjs_ids = space_get_objects(space_west, &wnum_objs);
    }
    if (id_east != NO_ID)
    {
      space_east = game_get_space(game, id_east);
      if (space_get_light(space_east))
      {
        egdesc = space_get_gdesc(space_east);
        if (space_get_flooded(space_east) == FLOODED)
          egdesc = flooded;
      }
      else
        egdesc = black;
      eobjs_ids = space_get_objects(space_east, &enum_objs);
    }

    /*NORTH*/
    _paint_single_space(ge, game, id_centre, id_north, 1, 0);

    if (game_get_connection_status(game, id_centre, NORTH) == OPEN)
      sprintf(str, "%*c  %*c^", BOX_COLS, ' ', BOX_COLS / 2, ' ');
    else
      sprintf(str, " ");
    screen_area_puts(ge->map, str);

    /*CENTRE_EAST_WEST*/
    if (id_centre != NO_ID)
    {
      /*Ceiling*/
      strcpy(str, "\0");
      if (id_west != NO_ID)
      {
        strcat(str, "+");
        for (i = 0; i < BOX_COLS - 2; i++)
          strcat(str, "-");
        strcat(str, "+");
      }
      else
      {
        sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);
      }

      strcat(str, "  +");
      for (i = 0; i < BOX_COLS - 2; i++)
        strcat(str, "-");
      strcat(str, "+  ");

      if (id_east != NO_ID)
      {
        strcat(str, "+");
        for (i = 0; i < BOX_COLS - 2; i++)
          strcat(str, "-");
        strcat(str, "+");
      }
      else
      {
        sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);
      }

      screen_area_puts(ge->map, str);

      /*Ant, enemy and space_id*/
      strcpy(str, "\0");
      if (id_west != NO_ID)
      {
        /*Looks for an enemy in the west space*/
        enemy = game_get_enemy(game, get_enemy_id_in_space(game, id_west));

        if (enemy != NULL && enemy_get_health(enemy) > 0)
        {
          edesc = enemy_get_edesc(enemy);
          slen = strlen(edesc);
          sprintf(aux, "|%*c%s%*d|", GAP_BETWEEN_WALL_EMY, ' ', edesc, BOX_COLS - GAP_BETWEEN_WALL_EMY - slen - 2, (int)id_west);
          enemy = NULL;
        }
        else
          sprintf(aux, "|%*d|", BOX_COLS - 2, (int)id_west);
      }
      else
        sprintf(aux, "%*c", BOX_COLS, ' ');
      strcat(str, aux);

      /*Looks for an enemy in the centre space*/
      enemy = game_get_enemy(game, get_enemy_id_in_space(game, id_centre));
      if (enemy != NULL && enemy_get_health(enemy) > 0)
      {
        edesc = enemy_get_edesc(enemy);
        slen = strlen(edesc);
        sprintf(aux, "  |%s%*c%s%*d|  ", pSkins[(int)player_get_type(game_get_player(game))], (GAP_BETWEEN_WALL_EMY - ANTSIZE), ' ', edesc, BOX_COLS - GAP_BETWEEN_WALL_EMY - slen - 2, (int)id_centre);
        enemy = NULL;
      }
      else
        sprintf(aux, "  |%s%*d|  ", pSkins[(int)player_get_type(game_get_player(game))], BOX_COLS - ANTSIZE - 2, (int)id_centre);
      strcat(str, aux);

      if (id_east != NO_ID)
      {
        /*Looks for an enemy in the east space*/
        for (i = 0; i < MAX_ENEMIES; i++)
        {
          enemy = game_get_enemy(game, game_get_enemy_id_at(game, i));
          if (enemy == NULL || enemy_get_location(enemy) == id_east)
            break;
        }
        if (enemy != NULL && enemy_get_health(enemy) > 0)
        {
          edesc = enemy_get_edesc(enemy);
          slen = strlen(edesc);
          sprintf(aux, "|%*c%s%*d|", GAP_BETWEEN_WALL_EMY, ' ', edesc, BOX_COLS - GAP_BETWEEN_WALL_EMY - slen - 2, (int)id_east);
          enemy = NULL;
        }
        else
          sprintf(aux, "|%*d|", BOX_COLS - 2, (int)id_east);
      }
      else
        sprintf(aux, "%*c", BOX_COLS, ' ');
      strcat(str, aux);

      screen_area_puts(ge->map, str);

      /*Fill upper half blanks before gdesc*/
      for (j = 0; j < (((BOX_ROWS - GRAPHIC_ROWS - 4) + 1) / 2); j++) /*+1 In case of having odd number of blanks*/
      {
        strcpy(str, "\0");

        if (id_west != NO_ID)
        {
          sprintf(aux, "|%*c|", BOX_COLS - 2, ' ');
        }
        else
          sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);

        sprintf(aux, "  |%*c|  ", BOX_COLS - 2, ' ');
        strcat(str, aux);

        if (id_east != NO_ID)
        {
          sprintf(aux, "|%*c|", BOX_COLS - 2, ' ');
        }
        else
          sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);

        screen_area_puts(ge->map, str);
      }

      /*Graphical descriptors*/
      for (i = 0; i < GRAPHIC_ROWS; i++)
      {
        strcpy(str, "\0");

        if (id_west != NO_ID)
        {
          /*if (space_get_flooded(space_west) == FLOODED)
            sprintf(aux, "|" F_DARKBLUE BACKGROUND(0, 150, 255) "%s" FOREGROUND(0, 0, 0) BACKGROUND(253, 253, 252)"%*c|", flooded[i], BOX_COLS - GRAPHIC_COLS - 2, ' ');
          else*/
          if (wgdesc != NULL)
            sprintf(aux, "|%s%*c|", wgdesc[i], BOX_COLS - GRAPHIC_COLS - 2, ' ');
          else
            sprintf(aux, "|%*c|", BOX_COLS - 2, ' ');
        }
        else
          sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);

        if (gdesc != NULL)
          sprintf(aux, "  |%s%*c|  ", gdesc[i], BOX_COLS - GRAPHIC_COLS - 2, ' ');
        else
          sprintf(aux, "  |%*c|  ", BOX_COLS - 2, ' ');
        strcat(str, aux);

        if (id_east != NO_ID)
        {
          if (egdesc != NULL)
            sprintf(aux, "|%s%*c|", egdesc[i], BOX_COLS - GRAPHIC_COLS - 2, ' ');
          else
            sprintf(aux, "|%*c|", BOX_COLS - 2, ' ');
        }
        else
          sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);

        screen_area_puts(ge->map, str);
      }

      /*Fill lower blanks after gdesc*/
      for (j = 0; j < (((BOX_ROWS - GRAPHIC_ROWS - 4)) / 2); j++)
      {
        strcpy(str, "\0");

        if (id_west != NO_ID)
          sprintf(aux, "|%*c|", BOX_COLS - 2, ' ');
        else
          sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);

        sprintf(aux, "  |%*c|  ", BOX_COLS - 2, ' ');
        strcat(str, aux);

        if (id_east != NO_ID)
        {
          sprintf(aux, "|%*c|", BOX_COLS - 2, ' ');
        }
        else
          sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);

        screen_area_puts(ge->map, str);
      }

      /*Object names and arrows*/
      strcpy(str, "\0");

      if (id_west != NO_ID)
      {
        total_len = 0;
        strcat(str, "|");

        enmy_id = get_enemy_id_in_space(game, space_get_id(space_west));
        if (enmy_id != NO_ID)
        {
          if (enemy_get_health(game_get_enemy(game, enmy_id)) < 1)
            enmy_id = NO_ID;
        }

        if (enmy_id == NO_ID || i == MAX_ENEMIES)
        {
          for (i = 0; i < wnum_objs; i++)
          {
            if (space_get_light(space_west) && !object_get_hidden(game_get_object(game, wobjs_ids[i])))
            {
              obj_name = game_get_object_name(game, wobjs_ids[i]);
              slen = strlen(obj_name);
              if (total_len + slen <= BOX_COLS - 2)
              {
                sprintf(aux, "%s", obj_name);
                strcat(str, aux);
                total_len += slen;
              }

              if (total_len + 1 <= BOX_COLS - 2)
              {
                sprintf(aux, " ");
                strcat(str, aux);
                total_len += 1;
              }
            }
          }
        }
        sprintf(aux, "%*c", BOX_COLS - total_len - 1, '|');
        strcat(str, aux);
      }
      else
      {
        sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);
      }

      if (id_west != NO_ID)
      {
        if (game_get_connection_status(game, id_centre, WEST) == OPEN)
          strcat(str, "<<");
        else
          strcat(str, "  ");
      }
      else
        strcat(str, "  ");

      total_len = 0;
      strcat(str, "|");

      enmy_id = get_enemy_id_in_space(game, space_get_id(space_centre));
      if (enmy_id != NO_ID)
      {
        if (enemy_get_health(game_get_enemy(game, enmy_id)) < 1)
          enmy_id = NO_ID;
      }

      if (enmy_id == NO_ID || j == MAX_ENEMIES)
      {
        for (i = 0; i < num_objs; i++)
        {
          if ((space_get_light(space_centre) || game_player_has_light(game)) && !object_get_hidden(game_get_object(game, objs_ids[i])))
          {
            obj_name = game_get_object_name(game, objs_ids[i]);
            slen = strlen(obj_name);
            if (total_len + slen <= BOX_COLS - 2)
            {
              sprintf(aux, "%s", obj_name);
              strcat(str, aux);
              total_len += slen;
            }

            if (total_len + 1 <= BOX_COLS - 2)
            {
              sprintf(aux, " ");
              strcat(str, aux);
              total_len += 1;
            }
          }
        }
      }

      sprintf(aux, "%*c", BOX_COLS - total_len - 1, '|');
      strcat(str, aux);

      if (id_east != NO_ID)
      {
        if (game_get_connection_status(game, id_centre, EAST) == OPEN)
          strcat(str, ">>");
        else
          strcat(str, "  ");
      }

      if (id_east != NO_ID)
      {
        total_len = 0;
        strcat(str, "|");

        enmy_id = get_enemy_id_in_space(game, space_get_id(space_east));
        if (enmy_id != NO_ID)
        {
          if (enemy_get_health(game_get_enemy(game, enmy_id)) < 1)
            enmy_id = NO_ID;
        }

        if (enmy_id == NO_ID || i == MAX_ENEMIES)
        {
          for (i = 0; i < enum_objs; i++)
          {
            if (space_get_light(space_east) && !object_get_hidden(game_get_object(game, eobjs_ids[i])))
            {
              obj_name = game_get_object_name(game, eobjs_ids[i]);
              slen = strlen(obj_name);
              if (total_len + slen <= BOX_COLS - 2)
              {
                sprintf(aux, "%s", obj_name);
                strcat(str, aux);
                total_len += slen;
              }

              if (total_len + 1 <= BOX_COLS - 2)
              {
                sprintf(aux, " ");
                strcat(str, aux);
                total_len += 1;
              }
            }
          }
        }
        sprintf(aux, "%*c", BOX_COLS - total_len - 1, '|');
        strcat(str, aux);
      }
      else
      {
        sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);
      }

      screen_area_puts(ge->map, str);

      /*Floor*/
      strcpy(str, "\0");
      if (id_west != NO_ID)
      {
        strcat(str, "+");
        for (i = 0; i < BOX_COLS - 2; i++)
          strcat(str, "-");
        strcat(str, "+");
      }
      else
      {
        sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);
      }

      strcat(str, "  +");
      for (i = 0; i < BOX_COLS - 2; i++)
        strcat(str, "-");
      strcat(str, "+  ");

      if (id_east != NO_ID)
      {
        strcat(str, "+");
        for (i = 0; i < BOX_COLS - 2; i++)
          strcat(str, "-");
        strcat(str, "+");
      }
      else
      {
        sprintf(aux, "%*c", BOX_COLS, ' ');
        strcat(str, aux);
      }
      screen_area_puts(ge->map, str);
    }

    /*SOUTH*/
    if (game_get_connection_status(game, id_centre, SOUTH) == OPEN)
      sprintf(str, "%*c  %*cv", BOX_COLS, ' ', BOX_COLS / 2, ' ');
    else
      sprintf(str, " ");

    screen_area_puts(ge->map, str);

    _paint_single_space(ge, game, id_centre, id_south, 0, 1);

    /*Free all 3 objs_ids*/
    free(objs_ids);
    free(wobjs_ids);
    free(eobjs_ids);
  }
}

void _paint_single_space(Graphic_engine *ge, Game *game, Id id_centre, Id spc_dir_id, int cut_top, int cut_bot)
{
  Id *objs_ids = NULL, enmy_id = NO_ID;
  Space *space_act = NULL;
  int i, j, num_objs, slen, total_len;
  char **gdesc, *obj_name, *edesc;
  Enemy *enemy;

  char str[WORD_SIZE], aux[WORD_SIZE];

  if (ge == NULL || game == NULL || id_centre == NO_ID)
    return;

  if (spc_dir_id != NO_ID)
  {
    space_act = game_get_space(game, spc_dir_id);
    objs_ids = space_get_objects(space_act, &num_objs);
    if (space_get_light(space_act))
    {
      gdesc = space_get_gdesc(space_act);
    }
    else
      gdesc = black;

    /*Ceiling*/
    if (cut_top == 0)
    {
      strcpy(str, "\0");
      sprintf(str, "%*c  +", BOX_COLS, ' ');

      strcat(str, "");
      for (i = 0; i < BOX_COLS - 2; i++)
        strcat(str, "-");
      strcat(str, "+  ");

      screen_area_puts(ge->map, str);
    }

    /*Enemy and space id*/

    enemy = game_get_enemy(game, get_enemy_id_in_space(game, spc_dir_id));
    if (enemy != NULL && enemy_get_health(enemy) > 0)
    {
      edesc = enemy_get_edesc(enemy);
      slen = strlen(edesc);
      sprintf(str, "%*c  |%*c%s%*d|", BOX_COLS, ' ', GAP_BETWEEN_WALL_EMY, ' ', edesc, BOX_COLS - slen - GAP_BETWEEN_WALL_EMY - 2, (int)spc_dir_id);
    }
    else
      sprintf(str, "%*c  |%*d|", BOX_COLS, ' ', BOX_COLS - 2, (int)spc_dir_id);
    screen_area_puts(ge->map, str);

    /*Fill upper half blanks before gdesc*/
    for (j = 0; j < ((BOX_ROWS - GRAPHIC_ROWS - 4) + 1) / 2; j++) /*+1 In case of having odd number of blanks*/
    {
      strcpy(str, "\0");
      sprintf(aux, "%*c  |%*c|", BOX_COLS, ' ', BOX_COLS - 2, ' ');
      strcat(str, aux);
      screen_area_puts(ge->map, str);
    }

    /*gdesc*/
    /*if (space_get_flooded(space_act) == FLOODED)
    {
      gdesc = flooded;
      for (i = 0; i < GRAPHIC_ROWS; i++)
      {
        sprintf(str, "%*c  |" F_DARKBLUE BACKGROUND(0, 150, 255) "%s" FOREGROUND(0, 0, 0) BACKGROUND(253, 253, 252) "%*c|", BOX_COLS, ' ', gdesc[i], BOX_COLS - GRAPHIC_COLS - 2, ' ');
        screen_area_puts(ge->map, str);
      }
    }
    else*/
    if (gdesc != NULL)
    {
      for (i = 0; i < GRAPHIC_ROWS; i++)
      {
        sprintf(str, "%*c  |%s%*c|", BOX_COLS, ' ', gdesc[i], BOX_COLS - GRAPHIC_COLS - 2, ' ');
        screen_area_puts(ge->map, str);
      }
    }
    else
    {
      for (i = 0; i < GRAPHIC_ROWS; i++)
      {
        sprintf(str, "%*c  |%*c|", BOX_COLS, ' ', BOX_COLS - 2, ' ');
        screen_area_puts(ge->map, str);
      }
    }

    /*Fill lower half blanks after gdesc*/
    for (j = 0; j < (BOX_ROWS - GRAPHIC_ROWS - 4) / 2; j++)
    {
      strcpy(str, "\0");
      sprintf(aux, "%*c  |%*c|", BOX_COLS, ' ', BOX_COLS - 2, ' ');
      strcat(str, aux);
      screen_area_puts(ge->map, str);
    }

    /*Objects*/
    total_len = 0;
    sprintf(str, "%*c  |", BOX_COLS, ' ');

    enmy_id = get_enemy_id_in_space(game, space_act);
    if (enmy_id != NO_ID)
    {
      if (enemy_get_health(game_get_enemy(game, enmy_id)) < 1)
        enmy_id = NO_ID;
    }

    if (enmy_id == NO_ID || i == MAX_ENEMIES)
    {
      for (i = 0; i < num_objs; i++)
      {
        if (space_get_light(space_act) && object_get_hidden(game_get_object(game, objs_ids[i])) == FALSE)
        {
          obj_name = game_get_object_name(game, objs_ids[i]);
          slen = strlen(obj_name);
          if (total_len + slen <= BOX_COLS - 2)
          {
            sprintf(aux, "%s", obj_name);
            strcat(str, aux);
            total_len += slen;
          }

          if (total_len + 1 <= BOX_COLS - 2)
          {
            sprintf(aux, " ");
            strcat(str, aux);
            total_len += 1;
          }
        }
      }
    }

    sprintf(aux, "%*c", BOX_COLS - total_len - 1, '|');
    strcat(str, aux);

    screen_area_puts(ge->map, str);

    /*Floor*/
    if (cut_bot == 0)
    {
      strcpy(str, "\0");
      sprintf(str, "%*c", BOX_COLS, ' ');

      strcat(str, "  +");
      for (i = 0; i < BOX_COLS - 2; i++)
        strcat(str, "-");
      strcat(str, "+  ");

      screen_area_puts(ge->map, str);
    }

    free(objs_ids);
  }
  else
  {
    for (i = 0; i < BOX_ROWS; i++)
    {
      strcpy(str, " ");
      screen_area_puts(ge->map, str);
    }
  }
}

void _paint_minimap(Graphic_engine *ge, Game *game)
{
  int i, j, k, m;
  char buffer[2 * WORD_SIZE], aux[WORD_SIZE], aux2[2 * WORD_SIZE];
  Id Loc;
  Space *space;

  if (ge == NULL || game == NULL)
    return;

  Loc = player_get_location(game_get_player(game));
  screen_area_clear(ge->minimap);

  sprintf(buffer, "            MINIMAP  ");
  screen_area_puts(ge->minimap, buffer);

  for (i = 2; i >= 0; i--)
  {
    paint_n_enters(ge->minimap, 2);
    sprintf(buffer, "           Floor %d", i);
    screen_area_puts(ge->minimap, buffer);
    paint_n_enters(ge->minimap, 2);
    sprintf(buffer, "    +----------------------+");
    screen_area_puts(ge->minimap, buffer);
    for (j = 1; j < 8; j++)
    {
      sprintf(buffer, "    | ");
      for (k = 1; k < 8; k++)
      {
        for (m = 0; m < game_get_num_enemies(game); m++)
          if ((enemy_get_location(game_get_enemy(game, game_get_enemy_id_at(game, m))) == (Id)i * 100 + k * 10 + j) && enemy_get_health(game_get_enemy(game, game_get_enemy_id_at(game, m))) > 0)
            break;

        if ((space = game_get_space(game, (Id)i * 100 + k * 10 + j)) != NULL)
        {
          if (Loc == i * 100 + k * 10 + j)
            sprintf(aux, F_LIGHTGREEN B_GREEN " O ");
          else if (space_get_flooded(space) == SUNK)
            sprintf(aux, "  ");
          else if (space_get_light(space) == FALSE)
            sprintf(aux, F_PURPLE B_GREY "|?|");
          else if (space_get_flooded(space) == FLOODED)
            sprintf(aux, F_LIGHTBLUE B_BLUE " ~ ");
          else if (m != game_get_num_enemies(game))
            sprintf(aux, F_LIGHTRED B_RED "|X|");
          else if (!strcmp(HARBOUR, space_get_name(space)))
            sprintf(aux, F_BROWN B_LIGHTBLUE "|H|");
          else if (!strcmp(WORKSHOP, space_get_name(space)))
            sprintf(aux, F_BROWN B_LIGHTORANGE "|W|");
          else if (game_space_has_object(game, space_get_id(space), STICK) || game_space_has_object(game, space_get_id(space), LEAF) || game_space_has_object(game, space_get_id(space), WALNUT))
            sprintf(aux, F_BROWN B_LIGHTBROWN "|!|");
          else if (game_space_has_object(game, space_get_id(space), GROUND))
            sprintf(aux, F_BROWN B_LIGHTBROWN "|.|");
          else if (game_space_has_object(game, space_get_id(space), LANTERN))
            sprintf(aux, F_BROWN B_LIGHTBROWN "|*|");
          else if (game_space_has_object(game, space_get_id(space), KEY) || game_space_has_object(game, space_get_id(space), GOLDKEY))
            sprintf(aux, F_BROWN B_LIGHTBROWN "|¬|");
          else
            sprintf(aux, F_BROWN B_LIGHTBROWN "| |");

          sprintf(aux2, "%s", buffer);
          snprintf(buffer, 2 * WORD_SIZE, "%s%s", aux2, aux);
        }
        else
        {
          sprintf(aux2, "%s", buffer);
          snprintf(buffer, 2 * WORD_SIZE, "%s" F_BLACK B_WHITE "   ", aux2);
        }
      }
      sprintf(aux2, "%s", buffer);
      snprintf(buffer, 2 * WORD_SIZE, "%s" F_BLACK B_WHITE "|", aux2);
      screen_area_puts(ge->minimap, buffer);
    }
    sprintf(buffer, F_BLACK B_WHITE "    +----------------------+");
    screen_area_puts(ge->minimap, buffer);
  }
}

void paint_n_enters(Area *area, int n)
{
  int i;
  if (area == NULL || n < 1)
    return;

  for (i = 0; i < n; i++)
    screen_area_puts(area, " ");
}

Id get_enemy_id_in_space(Game *game, Id space)
{
  int i;
  Id enemy_id = NO_ID + 1;
  Enemy *enemy;

  if (game == NULL || space == NO_ID)
    return NO_ID;

  for (i = 0; i < MAX_ENEMIES && enemy_id != NO_ID; i++)
  {
    enemy_id = game_get_enemy_id_at(game, i);
    enemy = game_get_enemy(game, enemy_id);
    if (enemy_get_location(enemy) == space)
      return enemy_id;
  }

  return NO_ID;
}