/**
 * @brief It defines the game management interface
 *
 * @file game_management.c
 * @author Javier San Andrés - Alejandro García Hernando
 * @version 3.0
 * @date 29/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_management.h"
#include "game.h"

#define MAXLINE 10000   /*!<MAX number of lines needed to  load and save a game*/
#define BUFFERSIZE 1000 /*!<The size of the buffer*/

/*Declaration of private functions*/
/**
 * @brief given a file and a pointer to the game it loads the data from the file onto the game
 * @author Alejandro García Hernando
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_game_data(Game *game, char *filename);

/**
 * @brief given a file and a pointer to the game it loads the space from the file onto the game
 * @author Javier San Andrés de Pedro
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_spaces(Game *game, char *filename);

/**
 * @brief given a file and a pointer to the game it sets the darks spaces in the given proportion
 * @author Alejandro García Hernando
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_set_dark_spaces(Game *game, char *filename);

/**
 * @brief given a file and a pointer to the game it loads the enemy from the file onto the game
 * @author Javier San Andrés de Pedro
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_enemy(Game *game, char *filename);

/**
 * @brief given a file and a pointer to the game it sets a random location to the enemies
 * @author Alejandro García Hernando
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_set_random_enemies(Game *game);

/**
 * @brief given a file and a pointer to the game it loads the objects from the file onto the game
 * @author Alejandro García Hernando
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_objects(Game *game, char *filename);

/**
 * @brief given a file and a pointer to the game it loads the links from the file onto the game
 * @author Alejandro García Hernando
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_link(Game *game, char *filename);

/**
 * @brief given a file and a pointer to the game it loads the player from the file onto the game
 * @author Diego Rodríguez Ortiz
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_player(Game *game, char *filename);

/**
 * @brief Given a game it saves the data into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file  pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_game_data(Game *game, FILE *file);

/**
 * @brief Given a game it saves the spaces into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_spaces(Game *game, FILE *file);

/**
 * @brief Given a game it saves the player into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_player(Game *game, FILE *file);

/**
 * @brief Given a game it saves the enemies into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file  pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_enemies(Game *game, FILE *file);

/**
 * @brief Given a game it saves the objects into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file  pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_objects(Game *game, FILE *file);

/**
 * @brief Given a game it saves the links into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file  pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_links(Game *game, FILE *file);

/**
 * @brief Given a game it saves the links into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file  pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_dialogues(Game *game, FILE *file);

/**
 * @brief given a file and a pointer to the game it loads the game rules from the file onto the game
 * @author Diego Rodríguez Ortiz
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_rules(Game *game, char *filename);

/**
 * @brief given a file and a pointer to the game it loads the game dialogues from the file onto the game
 * @author Javier San Andrés
 * @param game pointer to the game
 * @param filename name to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_load_dialogues(Game *game, char *filename);

/**
 * @brief Given a game it saves the rules into a file
 * @author Alejandro García
 * @param game pointer to the game
 * @param file pointer to the file
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS game_management_save_game_rules(Game *game, FILE *file);

/**
 * Loads all the game on the file onto the game
 */
STATUS game_management_load(Game *game, char *filename)
{
  srand(time(NULL));
  if (game == NULL || filename == NULL)
    return ERROR;

  /*Loads the the game data onto the game*/
  if (game_management_load_game_data(game, filename) == ERROR)
    return ERROR;

  /*Loads the the spaces onto the game*/
  if (game_management_load_spaces(game, filename) == ERROR)
    return ERROR;

  /*Loads the the player onto the game*/
  if (game_management_load_player(game, filename) == ERROR)
    return ERROR;

  if (game_management_load_objects(game, filename) == ERROR)
    return ERROR;

  if (game_management_load_enemy(game, filename) == ERROR)
    return ERROR;

  if (game_management_load_link(game, filename) == ERROR)
    return ERROR;

  if (game_management_load_rules(game, filename) == ERROR)
    return ERROR;

  if (game_management_load_dialogues(game, filename) == ERROR)
    return ERROR;

  return OK;
}

/**
 * Loads the game data on the file onto the game
 */
STATUS game_management_load_game_data(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  int n_commands = 0;

  if (game == NULL || filename == NULL)
  {
    return ERROR;
  }

  file = fopen(filename, "r"); /*Open file + error control*/
  if (file == NULL)
  {
    return ERROR;
  }

  /*Loop that reads all the lines*/
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#G:", line, 3) == 0)
    {
      /*Number of commands introduced*/
      toks = strtok(line + 3, "|");
      n_commands = atoi(toks);
    }
  }

  game_set_num_executed_commands(game, n_commands);

  fclose(file);

  return OK;
}

/**
 * Loads the spaces on the file onto the game
 */
STATUS game_management_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  int i, flag = 0;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char tdesc[WORD_SIZE] = "";
  char idesc[WORD_SIZE] = "";
  char *toks = NULL, **gdesc;
  Id id = NO_ID;
  Space *space = NULL;
  BOOL light;
  SSTATUS flooded;

  if (game == NULL || filename == NULL)
  {
    return ERROR;
  }

  file = fopen(filename, "r"); /*Open file + error control*/
  if (file == NULL)
  {
    return ERROR;
  }

  if ((gdesc = (char **)calloc(GRAPHIC_ROWS, sizeof(char *))) == NULL)
  {
    fclose(file);
    return ERROR;
  }

  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if ((gdesc[i] = (char *)calloc(GRAPHIC_COLS + 1, sizeof(char))) == NULL)
    {
      for (; i >= 0; i--)
      {
        free(gdesc[i]);
      }
      free(gdesc);

      fclose(file);
      return ERROR;
    }
  }

  /*Loop that reads all the lines*/
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      /*ID*/
      toks = strtok(line + 3, "|");
      id = atol(toks);
      /*NAME*/
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      /*LIGHT*/
      toks = strtok(NULL, "|");
      if (atoi(toks) == 0)
        light = FALSE;
      else
        light = TRUE;
      /*FLOODED*/
      toks = strtok(NULL, "|");
      if ((i = atoi(toks)) == 0)
        flooded = SAFE;
      else if (i == 1)
        flooded = FLOODED;
      else
        flooded = SUNK;
      /*GDESC*/

      toks = strtok(NULL, "|\r\n");
      if (toks != NULL) /*That means a graphical descriptor is specified*/
      {
        strncpy(gdesc[0], toks, GRAPHIC_COLS);

        for (i = 1; i < GRAPHIC_ROWS; i++)
        {
          toks = strtok(NULL, "|");
          strncpy(gdesc[i], toks, GRAPHIC_COLS);
        }

        flag = 1;
      }
      else
        for (i = 0; i < GRAPHIC_ROWS; i++)
          strcpy(gdesc[i], "\0");

      toks = strtok(NULL, "|\r\n");
      if (toks != NULL) /*That means a main textual description is specified*/
        strcpy(tdesc, toks);
      else
        strcpy(tdesc, "\0");

      toks = strtok(NULL, "|\r\n");
      if (toks != NULL) /*That means a detailed textual description is specified*/
        strcpy(idesc, toks);
      else
        strcpy(idesc, "\0");

#ifdef DEBUG /*Prints all the information read if the game is being executed in debug mode*/
      printf("Leido: %ld|%s|", id, name);
      if (light == TRUE)
        printf("light|");
      else
        printf("NO light|");

      if (flag == 1)
      {
        for (i = 0; i < GRAPHIC_ROWS; i++)
          printf("%s", gdesc[i]);
      }
      if (toks != NULL)
        printf("   %s\n\n", tdesc);
#endif

      space = space_create(id);
      if (space != NULL)
      {                                    /*Uploads the readen information in the game structure*/
        (void)space_set_name(space, name); /* They could fail but we do not consider that as a global error that should finish execution*/
        (void)space_set_light(space, light);
        (void)space_set_flooded(space, flooded);

        if (flag == 1)
          space_set_gdesc(space, gdesc); /*It could fail but we do not consider that as a global error that should finish execution*/

        space_set_tdesc(space, tdesc); /* They could fail but we do not consider that as a global error that should finish execution*/
        space_set_idesc(space, idesc);

        if (game_add_space(game, space) == ERROR)
        {
          space_destroy(space);

          for (i = 0; i < GRAPHIC_ROWS; i++)
            free(gdesc[i]);
          free(gdesc);

          fclose(file);
          return ERROR;
        }
      }
      else
      {
        for (i = 0; i < GRAPHIC_ROWS; i++)
          free(gdesc[i]);
        free(gdesc);
        fclose(file);
        return ERROR;
      }
    }
  }

  for (i = 0; i < GRAPHIC_ROWS; i++)
    free(gdesc[i]);
  free(gdesc);

  fclose(file);

  return game_management_set_dark_spaces(game, filename);
}

/**
 * Sets the dark spaces in the given proportion
 */
STATUS game_management_set_dark_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  int nSpaces, i;
  float propSpaces;
  Id *spacesIds;

  if (game == NULL || filename == NULL)
  {
    return ERROR;
  }

  file = fopen(filename, "r"); /*Open file + error control*/
  if (file == NULL)
  {
    return ERROR;
  }

  /*Loop that reads all the lines*/
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#G:", line, 3) == 0)
    {
      /*Proportion of dark spaces*/
      toks = strtok(line + 3, "|");
      if (!(toks = strtok(NULL, "|")))
        return OK;
      break;
    }
  }

  propSpaces = atof(toks);

  for (i = 0; game_get_space_id_at(game, i) != NO_ID; i++)
    ;
  nSpaces = i * propSpaces;

  spacesIds = game_get_rand_space_id(game, nSpaces);
  for (i = 0; i < nSpaces; i++)
    (void)space_set_light(game_get_space(game, spacesIds[i]), FALSE);

  free(spacesIds);
  fclose(file);

  return OK;
}

/**
 * Loads the enemy on the file onto the game
 */
STATUS game_management_load_enemy(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL, edesc[WORD_SIZE];
  Id id = NO_ID, location = NO_ID, health = NO_ID;
  Enemy *enemy = NULL;

  if (game == NULL || filename == NULL)
  { /*Error control*/
    return ERROR;
  }

  file = fopen(filename, "r"); /*Open file + error control*/
  if (file == NULL)
  {
    return ERROR;
  }

  /*Loop that reads all the lines*/
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#e:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(edesc, toks);

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
      fprintf(stderr, "Leido e: %ld|%s|%ld|%ld|\n", id, name, location, health);
#endif

      enemy = enemy_create(id);
      if (enemy != NULL)
      { /*Uploads the readen information in the game structure*/
        enemy_set_name(enemy, name);

        if (enemy_set_location(enemy, location) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        if (enemy_set_health(enemy, health) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        if (enemy_set_edesc(enemy, edesc) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        game_add_enemy(game, enemy);
      }
      else
      {
        fclose(file);
        return ERROR;
      }
    }
  }

  fclose(file);

  if (game_management_set_random_enemies(game) == ERROR)
    return ERROR;

  return OK;
}

/**
 * Sets the dark spaces in the given proportion
 */
STATUS game_management_set_random_enemies(Game *game)
{
  int i, nEn;
  Id *spacesIds;
  Object *obj;
  char name[WORD_SIZE];

  if (game == NULL)
    return ERROR;

  for (nEn = 0; game_get_enemy_id_at(game, nEn) != NO_ID; nEn++)
    ;

  spacesIds = game_get_rand_space_id(game, nEn);

  for (i = 0; i < nEn; i++)
  {
    if (enemy_get_location(game_get_enemy(game, game_get_enemy_id_at(game, i))) == RANDLOC)
      (void)enemy_set_location(game_get_enemy(game, game_get_enemy_id_at(game, i)), spacesIds[i]);

    obj = object_create(game_get_unique_object_id(game));

    if (game_add_object(game, obj) == ERROR)
    {
      object_destroy(obj);
      free(spacesIds);
      return ERROR;
    }
    
    sprintf(name, "%s", enemy_get_name(game_get_enemy(game, game_get_enemy_id_at(game, i))));
    if(strstr(name, "walnut") != NULL)
      strcpy(name, "Walnut");
    if(strstr(name, "leaf") != NULL)
      strcpy(name, "Leaf");
    if(strstr(name, "stick") != NULL)
      strcpy(name, "Stick");
    if(strstr(name, "lantern") != NULL)
      strcpy(name, "Lantern");
    
    (void)object_set_name(obj, name);
    
    object_set_location(obj, spacesIds[i]);
    object_set_hidden(obj, FALSE);
    object_set_movable(obj, TRUE);
    object_set_dependency(obj, NO_ID);
    object_set_open(obj, NO_ID);
    if(strcmp(name, "LanternE")==0)
      object_set_illuminate(obj, TRUE);
    else
      object_set_illuminate(obj, FALSE);
    object_set_turnedon(obj, FALSE);

    if (space_add_object(game_get_space(game, spacesIds[i]), object_get_id(obj)) == ERROR)
    {
      object_destroy(obj);
      free(spacesIds);
      return ERROR;
    }
  }

  free(spacesIds);

  return OK;
}

/**
 * Loads the objects on the file onto the game
 */
STATUS game_management_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char tdesc[WORD_SIZE] = "";
  char *toks = NULL;
  Object *object = NULL;
  Id object_id = NO_ID, location_id = NO_ID, dependency, open, *aux;
  STATUS status = OK;
  BOOL hidden, movable, illuminate, turnedon;

  if (game == NULL || filename == NULL)
    return ERROR;

  file = fopen(filename, "r");
  if (file == NULL)
    return ERROR;

  /* Reads the information from each object and adds it to the map */
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      /*ID*/
      toks = strtok(line + 3, "|");
      object_id = atol(toks);
      /*NAME*/
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      /*LOCATION*/
      toks = strtok(NULL, "|");
      location_id = atol(toks);
      if (location_id == RANDLOC)
      {
        aux = game_get_rand_space_id(game, 1);
        location_id = *aux;
        free(aux);
      }

      /*DESCRIPTION*/
      toks = strtok(NULL, "|\r\n");
      if (toks != NULL) /*That means a textual description is specified*/
        strcpy(tdesc, toks);
      else
        strcpy(tdesc, " \0");
      /*HIDDEN*/
      toks = strtok(NULL, "|\n\r");
      if (!toks)
        hidden = TRUE;
      else
      {
        if (atoi(toks) == 0)
          hidden = FALSE;
        else
          hidden = TRUE;
      }
      /*MOVABLE*/
      toks = strtok(NULL, "|\n\r");
      if (!toks)
        movable = FALSE;
      else
      {
        if (atoi(toks) == 0)
          movable = FALSE;
        else
          movable = TRUE;
      }
      /*DEPENDENCY*/
      toks = strtok(NULL, "|\n\r");
      if (!toks)
        dependency = NO_ID;
      else
      {
        if (atoi(toks) == -1)
          dependency = NO_ID;
        else
          dependency = atol(toks);
      }
      /*OPEN*/
      toks = strtok(NULL, "|\n\r");
      if (!toks)
        open = NO_ID;
      else
      {
        if (atoi(toks) == -1)
          open = NO_ID;
        else
          open = atol(toks);
      }
      /*ILLUMINATE*/
      toks = strtok(NULL, "|\n\r");
      if (!toks)
        illuminate = FALSE;
      else
      {
        if (atoi(toks) == 0)
          illuminate = FALSE;
        else
          illuminate = TRUE;
      }
      /*TURNEDON*/
      toks = strtok(NULL, "|\n\r");
      if (!toks)
        turnedon = FALSE;
      else
      {
        if (atoi(toks) == 0)
          turnedon = FALSE;
        else
          turnedon = TRUE;
      }

      if (location_id >= 0)
        if (!strncmp(space_get_tdesc(game_get_space(game, location_id)), SUSPICIOUS, strlen(SUSPICIOUS) - 1))
          hidden = TRUE;

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
      if (toks != NULL)
        fprintf(stderr, "Leido o: %ld|%s|%ld\n", object_id, name, location_id);
      else
        fprintf(stderr, "Leido o: %ld|%s|%ld|%s\n", object_id, name, location_id, tdesc);
#endif

      object = object_create(object_id);
      if (object != NULL)
      {
        if (game_add_object(game, object) == ERROR)
        {
          object_destroy(object);
          fclose(file);
          return ERROR;
        }

        (void)object_set_name(object, name);
        if (location_id == ON_PLAYER)
        {
          (void)player_add_object(game_get_player(game), object_id);
          (void)object_set_location(object, ON_PLAYER);
        }
        else
          (void)game_set_object_location(game, object_id, location_id); /*They could fail but we do not consider that as a global error that should finish execution*/

        (void)object_set_tdesc(object, tdesc); /*It could fail but we do not consider that as a global error that should finish execution*/
        (void)object_set_hidden(object, hidden);
        (void)object_set_movable(object, movable);
        (void)object_set_dependency(object, dependency);
        (void)object_set_open(object, open);
        (void)object_set_illuminate(object, illuminate);
        (void)object_set_turnedon(object, turnedon);
      }
      else
      {
        fclose(file);
        return ERROR;
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * Loads the links on the file onto the game
 */
STATUS game_management_load_link(Game *game, char *filename)
{

  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, origin = NO_ID, dest = NO_ID;
  Link *link = NULL;
  DIRECTION dir;
  LSTATUS Lst;
  STATUS status = OK;

  if (game == NULL || filename == NULL)
  { /*Error control*/
    return ERROR;
  }

  file = fopen(filename, "r"); /*Open file + error control*/
  if (file == NULL)
  {
    return ERROR;
  }
  /*Loop that reads all the lines*/
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      origin = atol(toks);
      toks = strtok(NULL, "|");
      dest = atol(toks);
      toks = strtok(NULL, "|");
      dir = atoi(toks);
      toks = strtok(NULL, "|");
      Lst = atoi(toks);

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
      printf("Leido l: %ld|%s|%ld|%ld|%d|\n", id, name, origin, dest, Lst);
#endif
      link = link_create(id);
      if (link != NULL)
      { /*Uploads the readen information in the game structure*/
        if (game_add_link(game, link) == ERROR)
        {
          link_destroy(link);
          fclose(file);
          return ERROR;
        }

        link_set_name(link, name);
        if (game_set_link_origin(game, id, origin) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        if (game_set_link_destination(game, id, dest) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        if (link_set_direction(link, dir) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        link_set_status(link, Lst);
      }
      else
      {
        fclose(file);
        return ERROR;
      }
    }
  }
  /*Error control*/
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

/**
 * Loads the player on the file onto the game
 */
STATUS game_management_load_player(Game *game, char *filename)
{

  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Player *player = NULL;
  STATUS status = OK;
  int health, maxObjs, typePlayer;

  if (game == NULL || filename == NULL)
  { /*Error control*/
    return ERROR;
  }

  file = fopen(filename, "r"); /*Open file + error control*/
  if (file == NULL)
  {
    return ERROR;
  }
  /*Loop that reads all the lines*/
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      maxObjs = atoi(toks);
      toks = strtok(NULL, "|");
      typePlayer = atoi(toks);

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
      fprintf(stderr, "Leido p: %ld|%s|%ld|%d|%d|\n", id, name, location, health, maxObjs);
#endif

      player = player_create(id);

      if (player != NULL)
      { /*Uploads the readen information in the game structure*/
        game_set_player(game, player);
        player_set_name(player, name);

        if (game_set_player_location(game, location) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        if (game_set_player_health(game, health) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        if (player_set_max_objects(player, maxObjs) == ERROR)
        {
          fclose(file);
          return ERROR;
        }

        if (player_set_type(player, (T_PlayerType)typePlayer) == ERROR)
        {
          fclose(file);
          return ERROR;
        }
      }
      else
      {
        fclose(file);
        return ERROR;
      }
    }
  }
  /*Error control*/
  if (ferror(file))
  {
    status = ERROR;
  }

  game_set_last_tdesc(game, space_get_tdesc(game_get_space(game, game_get_player_location(game)))); /*Sets the description of the player intitial position*/
  fclose(file);

  return status;
}

/*
 * Loads the rules of the game
 */

STATUS game_management_load_rules(Game *game, char *filename)
{
  FILE *f;
  char line[WORD_SIZE], *toks = NULL;
  char name[WORD_SIZE];
  int argint, n_ids, n, i, j;
  Id ids[MAX_ARGS], id;
  T_ACTION Tact;
  T_CONDITION Tcond;
  Rule *rule = NULL;

  if (!game || !filename)
  {
    return ERROR;
  }

  f = fopen(filename, "r");
  if (!f)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, f) != NULL)
  {

    if (strncmp("#r:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = (Id)atol(toks);
      if ((rule = rule_create(id)) == NULL)
      {
        fclose(f);
        return ERROR;
      }
      toks = strtok(NULL, "|");
      n = atol(toks);

      for (i = 0; i < n; i++)
      {
        toks = strtok(NULL, "|");
        Tact = rule_translate_action(toks);
        toks = strtok(NULL, "|");
        n_ids = atoi(toks);

        for (j = 0; j < n_ids; j++)
        {
          toks = strtok(NULL, "|");
          ids[j] = (Id)atol(toks);
        }
        toks = strtok(NULL, "|");
        argint = atoi(toks);
        toks = strtok(NULL, "|");
        strcpy(name, toks);
      }

      if (rule_add_action(rule, Tact, ids, n_ids, argint, name) == ERROR)
      {
        rule_destroy(rule);
        fclose(f);
        return ERROR;
      }
      toks = strtok(NULL, "|");
      n = atol(toks);

      for (i = 0; i < n; i++)
      {
        toks = strtok(NULL, "|");
        Tcond = rule_translate_condition(toks);
        toks = strtok(NULL, "|");
        n_ids = atoi(toks);
        for (j = 0; j < n_ids; j++)
        {
          toks = strtok(NULL, "|");
          ids[j] = (Id)atol(toks);
        }
        toks = strtok(NULL, "|");
        argint = atoi(toks);
        toks = strtok(NULL, "|");
        strcpy(name, toks);

        if (rule_add_condition(rule, Tcond, ids, n_ids, argint, name) == ERROR)
        {
          rule_destroy(rule);
          fclose(f);
          return ERROR;
        }
      }
      if (game_add_rule(game, rule) == ERROR)
      {
        rule_destroy(rule);
        fclose(f);
        return ERROR;
      }
    }
  }
  fclose(f);
  return OK;
}

STATUS game_management_load_dialogues(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char rule[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID;
  Dialogue *dialogue = NULL;
  DTYPE type;
  STATUS status = OK;

  if (game == NULL || filename == NULL)
  { /*Error control*/
    return ERROR;
  }

  file = fopen(filename, "r"); /*Open file + error control*/
  if (file == NULL)
  {
    return ERROR;
  }
  /*Loop that reads all the lines*/
  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#d:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      type = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(rule, toks);

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
      fprintf(stderr, "Leido d: %ld|%d|%s|\n", id, type, rule);
#endif

      if (game_existing_dialogue_id(game, id) == FALSE)
      {
        dialogue = dialogue_create(id);

        if (dialogue != NULL)
        { /*Uploads the readen information in the game structure*/

          if (dialogue_set_rule(dialogue, rule, type) == ERROR)
          {
            dialogue_destroy(dialogue);
            fclose(file);
            return ERROR;
          }

          if (game_add_dialogue(game, dialogue) == ERROR)
          {
            dialogue_destroy(dialogue);
            fclose(file);
            return ERROR;
          }
        }
        else
        {
          fclose(file);
          return ERROR;
        }
      }
      else
      {
        if (game_add_dialogue_rule(game, id, rule, type) == ERROR)
        {
          fclose(file);
          return ERROR;
        }
      }
    }
  }
  /*Error control*/
  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}

STATUS game_management_save(Game *game, char *filename)
{
  FILE *file;
  file = fopen(filename, "w"); /*Empty file + error control*/
  if (file == NULL)
    return ERROR;

  fprintf(file, "                GAMEDATA\n");
  if (game_management_save_game_data(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fprintf(file, "\n                PLAYER\n");
  if (game_management_save_player(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fprintf(file, "\n                SPACES\n");
  if (game_management_save_spaces(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fprintf(file, "\n                ENEMIES\n");
  if (game_management_save_enemies(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fprintf(file, "\n                LINKS\n");
  if (game_management_save_links(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fprintf(file, "\n                OBJECTS\n");
  if (game_management_save_objects(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fprintf(file, "\n                RULES\n");
  if (game_management_save_game_rules(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fprintf(file, "\n                DIALOGUE\n");
  if (game_management_save_dialogues(game, file) == ERROR)
  {
    fclose(file);
    return ERROR;
  }

  fclose(file);
  return OK;
}

STATUS game_management_save_game_data(Game *game, FILE *file)
{
  int n_commands;

  if (game == NULL || file == NULL)
    return ERROR;

  n_commands = game_get_num_executed_commands(game);

  fprintf(file, "#G:%d|\n", n_commands);

  return OK;
}

STATUS game_management_save_spaces(Game *game, FILE *file)
{
  int i, j, nspaces;
  char str[MAXLINE], buffer[BUFFERSIZE];
  Space *space;
  char **gdesc;

  if (game == NULL || file == NULL)
    return ERROR;

  /*Gets the number of spaces the game has*/
  if ((nspaces = game_get_num_of_spaces(game)) == -1)
    return ERROR;

  /*Gets and prints all the information of the spaces*/
  for (i = 0; i < nspaces; i++)
  {
    if ((space = game_get_space(game, game_get_space_id_at(game, i))) == ERROR)
      return ERROR;
    if ((gdesc = space_get_gdesc(space)) == ERROR)
      return ERROR;

    sprintf(str, "#s:%ld|%s|%d|%d|", space_get_id(space), space_get_name(space), space_get_light(space), space_get_flooded(space));

    for (j = 0; j < GRAPHIC_ROWS; j++)
    {
      sprintf(buffer, "%s", gdesc[j]);
      strcat(str, buffer);
      strcat(str, "|");
    }
    sprintf(buffer, "%s|%s|", space_get_tdesc(space), space_get_idesc(space));
    strcat(str, buffer);

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
    printf("Guardado espacio(%d): %s\n", i + 1, str);
#endif
    fprintf(file, "%s\n", str);
  }

  return OK;
}

STATUS game_management_save_player(Game *game, FILE *file)
{
  char str[MAXLINE];
  Player *player;

  if (game == NULL || file == NULL)
    return ERROR;

  if ((player = game_get_player(game)) == NULL)
    return OK;

  sprintf(str, "#p:%ld|%s|%ld|%d|%d|%d|", player_get_id(player), player_get_name(player), player_get_location(player), player_get_health(player), player_get_max_objects(player), player_get_type(player));

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
  printf("Guardado jugador: %s\n", str);
#endif
  fprintf(file, "%s\n", str);

  return OK;
}

STATUS game_management_save_enemies(Game *game, FILE *file)
{
  char str[MAXLINE];
  Enemy *enemy;
  int i;
  Id id;

  if (game == NULL || file == NULL)
    return ERROR;

  for (i = 0; i < MAX_ENEMIES; i++)
  {
    if ((id = game_get_enemy_id_at(game, i)) == NO_ID)
      break;
    if ((enemy = game_get_enemy(game, id)) == NULL)
      return ERROR;

    sprintf(str, "#e:%ld|%s|%ld|%d|%s|", enemy_get_id(enemy), enemy_get_name(enemy), enemy_get_location(enemy), enemy_get_health(enemy), enemy_get_edesc(enemy));

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
    printf("Guardado jugador: %s\n", str);
#endif
    fprintf(file, "%s\n", str);
  }

  return OK;
}

STATUS game_management_save_objects(Game *game, FILE *file)
{
  int i, nobjects;
  char str[MAXLINE], buffer[BUFFERSIZE];
  Object *object;

  if (game == NULL || file == NULL)
    return ERROR;

  /*Save objects situation*/
  if ((nobjects = game_get_num_objects(game)) == -1)
    return ERROR;

  for (i = 0; i < nobjects; i++)
  {
    if ((object = game_get_object(game, game_get_object_id_at(game, i))) == ERROR)
      return ERROR;

    sprintf(str, "#o:%ld|%s|%ld|", object_get_id(object), object_get_name(object), object_get_location(object));
    sprintf(buffer, "%s|", object_get_tdesc(object));
    strcat(str, buffer);
    sprintf(buffer, "%d|%d|%ld|%d|%d|%d|", (int)object_get_hidden(object), (int)object_get_movable(object), object_get_dependency(object), (int)object_get_open(object), (int)object_get_illuminate(object), (int)object_get_turnedon(object));
    strcat(str, buffer);

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
    printf("Guardado objeto(%d): %s\n", i + 1, str);
#endif
    fprintf(file, "%s\n", str);
  }

  return OK;
}

STATUS game_management_save_links(Game *game, FILE *file)
{
  int i, nlinks;
  char str[MAXLINE];
  Link *link;

  if (game == NULL || file == NULL)
    return ERROR;

  /*Save links situation*/
  if ((nlinks = game_get_num_links(game)) == -1)
    return ERROR;

  for (i = 0; i < nlinks; i++)
  {
    if ((link = game_get_link(game, game_get_link_id_at(game, i))) == ERROR)
      return ERROR;

    sprintf(str, "#l:%ld|%s|%ld|%ld|%d|", link_get_id(link), link_get_name(link), link_get_origin(link), link_get_destination(link), link_get_direction(link));

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
    printf("Guardado link(%d): %s\n", i + 1, str);
#endif
    if (link_get_status(link) == CLOSE)
      fprintf(file, "%s0|\n", str);
    else
      fprintf(file, "%s1|\n", str);
  }

  return OK;
}

STATUS game_management_save_dialogues(Game *game, FILE *file)
{
  int i, j, num_dialogues = 0;
  char str[MAXLINE];
  Dialogue **dialogues = NULL;

  if (game == NULL || file == NULL)
    return ERROR;

  if ((dialogues = game_get_all_dialogues(game, &num_dialogues)) == NULL)
    return ERROR;

  for (i = 0; i < num_dialogues; i++)
  {
    for (j = 0; j <= dialogue_get_last_rule_position(dialogues[i]); j++)
    {
      sprintf(str, "#d:%ld|1|%s|", dialogue_get_id(dialogues[i]), dialogue_get_rule(dialogues[i], j));

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
      fprintf(stderr, "Guardando dialogue: %s\n", str);
#endif

      fprintf(file, "%s\n", str);
    }

    for (j = 0; j <= dialogue_get_last_error_rule_position(dialogues[i]); j++)
    {
      sprintf(str, "#d:%ld|0|%s|", dialogue_get_id(dialogues[i]), dialogue_get_error_rule(dialogues[i], j));

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
      printf("Guardando dialogue: %s\n", str);
#endif

      fprintf(file, "%s\n", str);
    }
  }

  return OK;
}

STATUS game_management_save_game_rules(Game *game, FILE *f)
{
  char str[WORD_SIZE], *rule_name, rule_text[WORD_SIZE];
  int n_rules, n_ids, n_act, i, j, k, argint;
  Id *ids, id;
  Rule *rule = NULL;
  Action *act;
  Condition *cond;

  if (!game || !f)
  {
    return ERROR;
  }

  n_rules = game_get_num_rules(game);

  for (i = 0; i < n_rules; i++)
  {
    sprintf(rule_text, "#r:");
    id = game_get_rule_id_at(game, i);

    sprintf(str, "%ld|", id);
    strcat(rule_text, str);
    rule = game_get_rule(game, id);

    n_act = rule_get_num_actions(rule);
    sprintf(str, "%d|", n_act);
    strcat(rule_text, str);

    for (j = 0; j < n_act; j++)
    {
      act = rule_get_action(rule, j);
      rule_name = rule_translate_Taction(rule_action_get_type(act));
      sprintf(str, "%s|", rule_name);
      strcat(rule_text, str);

      n_ids = rule_action_get_numId(act);
      sprintf(str, "%d|", n_ids);
      strcat(rule_text, str);

      ids = rule_action_get_argsId(act);
      for (k = 0; k < n_ids; k++)
      {
        sprintf(str, "%ld|", ids[k]);
        strcat(rule_text, str);
      }
      argint = rule_action_get_argint(act);
      sprintf(str, "%d|", argint);
      strcat(rule_text, str);

      rule_name = rule_action_get_argname(act);
      sprintf(str, "%s|", rule_name);
      strcat(rule_text, str);
    }

    n_act = rule_get_num_conditions(rule);
    sprintf(str, "%d|", n_act);
    strcat(rule_text, str);

    for (j = 0; j < n_act; j++)
    {
      cond = rule_get_condition(rule, j);
      rule_name = rule_translate_Tcondition(rule_condition_get_type(cond));
      sprintf(str, "%s|", rule_name);
      strcat(rule_text, str);

      n_ids = rule_condition_get_numId(cond);
      sprintf(str, "%d|", n_ids);
      strcat(rule_text, str);

      ids = rule_condition_get_argsId(cond);
      for (k = 0; k < n_ids; k++)
      {
        sprintf(str, "%ld|", ids[k]);
        strcat(rule_text, str);
      }
      argint = rule_condition_get_argint(cond);
      sprintf(str, "%d|", argint);
      strcat(rule_text, str);

      rule_name = rule_condition_get_argname(cond);
      sprintf(str, "%s|", rule_name);
      strcat(rule_text, str);
    }

#ifdef DEBUG /*Prints all the information readen if the game is being executed in debug mode*/
    fprintf(stderr, "Guardando rule: %s\n", rule_text);
#endif
    fprintf(f, "%s\n", rule_text);
  }
  return OK;
}
