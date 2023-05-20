/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Javier San Andres
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space
{
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Set *objects;             /*!< Set of objects the space contains*/
  char *tdescr;             /*!< Pointer that will hold the main textual description*/
  char *idescr;             /*!< Pointer that will hold the detailed textual description*/
  char **gdesc;             /*!< Pointer of the array that will store the graphical descriptor*/
  BOOL light;               /*!< Boolean that states if the space has its on light or not*/
  SSTATUS flooded;               /*!< SSTATUS that states if the space has its safe, flooded or sunk*/
};

/*PRIVATE FUNCTION*/

/**
 * @brief It gets the number of objects in a space
 * @author Diego Rodríguez Ortiz
 * @param space a pointer to the space
 * @return The number of elements of a space
 */
int _space_get_number_objects(Space *space);


Space *space_create(Id id)
{
  Space *newSpace = NULL;

  /* Error control */
  if (id == NO_ID)
    return NULL;

  newSpace = (Space *)malloc(sizeof(Space));
  
  if (newSpace == NULL)
  {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->tdescr = NULL;
  newSpace->gdesc = NULL;
  newSpace->idescr = NULL;
  newSpace->light = TRUE;

  if ((newSpace->objects = set_create()) == NULL)
  {
    free(newSpace);
    return NULL;
  }

  return newSpace;
}

void space_destroy(Space *space)
{
  int i;

  if (space != NULL)
  {
    set_destroy(space->objects);
    
    free(space->tdescr);
    free(space->idescr);

    if (space->gdesc != NULL)
    {
      for (i = 0; i < GRAPHIC_ROWS; i++)
        free(space->gdesc[i]);

      free(space->gdesc);
    }

    free(space);
  }
}

Id space_get_id(Space *space)
{
  if (space == NULL)
  {
    return NO_ID;
  }
  return space->id;
}

STATUS space_set_name(Space *space, char *name)
{
  if (space == NULL || name == NULL)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }
  return OK;
}

const char *space_get_name(Space *space)
{
  if (space == NULL)
  {
    return NULL;
  }
  return space->name;
}

STATUS space_set_light(Space *space, BOOL light)
{
  if (space == NULL)
  {
    return ERROR;
  }

  space->light=light;
  return OK;
}

BOOL space_get_light(Space *space)
{
  if (space == NULL)
  {
    return FALSE;
  }
  return space->light;
}

STATUS space_set_flooded(Space *space, SSTATUS flooded)
{
  if (space == NULL)
  {
    return ERROR;
  }
  
  space->flooded=flooded;
  return OK;
}

SSTATUS space_get_flooded(Space *space)
{
  if (space == NULL)
  {
    return SUNK;
  }
  return space->flooded;
}

STATUS space_add_object(Space *space, Id id)
{
  if (space == NULL || id == NO_ID)
  {
    return ERROR;
  }

  return set_add_id(space->objects, id);
}

STATUS space_remove_object(Space *space, Id id)
{
  if (space == NULL || id == NO_ID)
  {
    return ERROR;
  }

  return set_delete_id(space->objects, id);
}

BOOL space_contains_object(Space *space, Id id)
{
  if (space == NULL || id == NO_ID)
    return FALSE;

  return set_contains_id(space->objects, id);
}

Id *space_get_objects(Space *space, int *num)
{
  if (space == NULL)
  {
    return NULL;
  }

  return set_get_all_ids(space->objects, num);
}

int _space_get_number_objects(Space *space)
{
  if (space == NULL)
  {
    return -1;
  }

  return set_get_number_ids(space->objects);
}

char *space_get_tdesc(Space *space)
{
  if (space == NULL)
    return NULL;

  return space->tdescr;
}

STATUS space_set_tdesc(Space *space, char *tdescr)
{
  int len;

  if (space == NULL || tdescr == NULL)
    return ERROR;

  len = strlen(tdescr);

  if ((space->tdescr = (char *)malloc((len + 1) * sizeof(char))) == NULL)
    return ERROR;

  strcpy(space->tdescr, tdescr);

  return OK;
}

char *space_get_idesc(Space *space)
{
  if (space == NULL)
    return NULL;

  return space->idescr;
}

STATUS space_set_idesc(Space *space, char *idescr)
{
  int len;

  if (space == NULL || idescr == NULL)
    return ERROR;

  len = strlen(idescr);

  if ((space->idescr = (char *)malloc((len + 1) * sizeof(char))) == NULL)
    return ERROR;

  strcpy(space->idescr, idescr);

  return OK;
}

char **space_get_gdesc(Space *space)
{
  if (space == NULL)
    return NULL;

  return space->gdesc;
}

STATUS space_set_gdesc(Space *space, char **gdesc)
{
  int i, j;

  if (space == NULL || gdesc == NULL)
    return ERROR;
  

  if (space->gdesc != NULL)
  {
    for (i = 0; i < GRAPHIC_ROWS; i++){
      free(space->gdesc[i]);
    }
  }
  else
  {
    if ((space->gdesc = (char **)calloc(GRAPHIC_ROWS, sizeof(char *))) == NULL)
    {
      return ERROR;
    }
  }
  
  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if ((space->gdesc[i] = (char *)calloc(GRAPHIC_COLS + 1, sizeof(char))) == NULL)
    {
      for (j = i - 1; j >= 0; j--)
      {
        free(space->gdesc[j]);
      }
      free(space->gdesc);
      return ERROR;
    }
  }

  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if (gdesc[i] == NULL)
      return ERROR;

    if (strncpy(space->gdesc[i], gdesc[i], GRAPHIC_COLS) != space->gdesc[i])
      return ERROR;
  }

  return OK;
}

STATUS space_print(Space *space, FILE *file)
{
  int i;

  /* Error Control */
  if (space == NULL || file == NULL)
  {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(file, "Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. Print if there is an object in the space or not */
  fprintf(file, "--->");
  set_print(space->objects, file);

  /* 3. Prints the graphic descriptor of the space */
  if (space_get_gdesc(space) != NULL)
  {
    for (i = 0; i < GRAPHIC_ROWS; i++)
      fprintf(file, "%s\n", space->gdesc[i]);
  }
  else
  {
    fprintf(file, "---> There's no graphical descriptor\n\n");
  }

  if (space_get_tdesc(space) != NULL)
  {
    fprintf(file, "---> %s\n", space->tdescr);
  }
  else
  {
    fprintf(file, "---> There's no textual descriptor\n\n");
  }

  return OK;
}
