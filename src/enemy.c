/**
 * @brief It implements the enemy module
 *
 * @file enemy.c
 * @author Alejandro García Hernando
 * @version 3.0
 * @date  23/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"


/**
 * @brief Enemy
 *
 * This struct stores all the information of an enemy.
 */
struct _Enemy
{
  Id id;                    /*!< Id number of the enemy, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the enemy */
  Id location;              /*!< Id of the space the enemy is at */
  int health;               /*!< Health points the enemy has currently*/
  char *edesc;              /*!< Graphical descriptor for the enemy */
};

Enemy *enemy_create(Id id)
{
  Enemy *new_enemy = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  new_enemy = (Enemy *)malloc(sizeof(Enemy));
  if (new_enemy == NULL)
    return NULL;

  /* Initialization of an empty enemy*/
  new_enemy->id = id;
  new_enemy->name[0] = '\0';
  new_enemy->location = NO_ID;
  new_enemy->health = INITIAL_LP;

  new_enemy->edesc = NULL;

  return new_enemy;
}


STATUS enemy_destroy(Enemy *enemy)
{
  if (!enemy)
  {
    return ERROR;
  }
  free(enemy->edesc);
  free(enemy);
  enemy = NULL;
  return OK;
}

Id enemy_get_id(Enemy *enemy)
{
  if (!enemy)
  {
    return NO_ID;
  }

  return enemy->id;
}


STATUS enemy_set_name(Enemy *enemy, char *name)
{
  if (!enemy || !name)
  {
    return ERROR;
  }
  
  if (strcpy(enemy->name, name) != enemy->name)
  {
    return ERROR;
  }

  return OK;
}


const char *enemy_get_name(Enemy *enemy)
{
  if (!enemy)
  {
    return NULL;
  }

  return enemy->name;
}


STATUS enemy_set_location(Enemy *enemy, Id location)
{
  if (!enemy || location == NO_ID)
  {
    return ERROR;
  }
  enemy->location = location;

  return OK;
}


Id enemy_get_location(Enemy *enemy)
{
  if (!enemy)
  {
    return NO_ID;
  }
  return enemy->location;
}

STATUS enemy_set_health(Enemy *enemy, int health)
{
  if (!enemy)
  {
    return ERROR;
  }
  enemy->health = health;

  return OK;
}

int enemy_get_health(Enemy *enemy)
{
  if (!enemy)
  {
    return -1;
  }
  return enemy->health;
}

STATUS enemy_set_edesc(Enemy *enemy, char *aspect)
{
  int len;
  if (!enemy || !aspect)
  {
    return ERROR;
  }
  
  len=strlen(aspect);
  if((enemy->edesc = (char *)malloc((len + 1)*sizeof(char)))==NULL)
    return ERROR;

  strcpy(enemy->edesc, aspect);

  if(enemy->edesc[len-1]=='\n')
    enemy->edesc[len-1]='\0';
  
  return OK;
}

char *enemy_get_edesc(Enemy *enemy)
{
  if (!enemy)
  {
    return NULL;
  }
  return enemy->edesc;
}

STATUS enemy_print(Enemy *enemy, FILE *file)
{
  if (!enemy || !file)
    return FALSE;

  fprintf(file, "\n--> Enemy %s: (Id=%ld, location=%ld, health=%d)\n%s\n", enemy->name, enemy->id, enemy->location, enemy->health, enemy->edesc);

  return OK;
}
