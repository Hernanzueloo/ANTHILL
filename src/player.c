/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Javier San Andrés
 * @version 3.0
 * @date 1/04/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

/**
 * @brief Player
 *
 * This struct stores all the information of a player.
 */
struct _Player
{
    Id id;                    /*!< Id number of the player, it must be unique */
    char name[WORD_SIZE + 1]; /*!< Name of the player */
    Id location;              /*!< Id of the player's location */
    Inventory *inv;           /*!< Id to the player's inventory*/
    int health;               /*!< Number of life points of a player*/
    T_PlayerType type;         /*!< The type of player*/
};

Player *player_create(Id id)
{
    Player *player;

    if (id == NO_ID)
        return NULL;

    if ((player = (Player *)malloc(sizeof(Player))) == NULL)
        return NULL;

    /* Initialization of an empty player*/
    if ((player->inv = inventory_create()) == NULL)
    {
        free(player);
        return NULL;
    }

    player->id = id;
    player->name[0] = '\0';
    player->location = NO_ID;
    player->health = INITIAL_LP;
    player->type = NO_TYPE;

    return player;
}

void player_destroy(Player *player)
{
    if (!player)
        return;
    inventory_destroy(player->inv);
    free(player);
}

Id player_get_id(Player *player)
{
    if (player == NULL)
        return NO_ID;

    return player->id;
}

STATUS player_set_name(Player *player, char *name)
{
    if (player == NULL || name == NULL)
        return ERROR;

    if (strcpy(player->name, name) == 0)
        return ERROR;

    return OK;
}

const char *player_get_name(Player *player)
{
    if (player == NULL)
        return NULL;

    return player->name;
}

Id player_get_location(Player *player)
{
    if (player == NULL)
        return NO_ID;

    return player->location;
}

STATUS player_set_location(Player *player, Id id)
{
    if (player == NULL || id == NO_ID)
        return ERROR;

    player->location = id;

    return OK;
}
/*ADD TEST*/
BOOL player_has_object(Player *player, Id obj)
{
    if (!player)
        return FALSE;
    if (obj == NO_ID)
        return TRUE;

    return inventory_contains_id(player->inv, obj);
}

Id *player_get_objects(Player *player, int *num)
{
    if (player == NULL)
        return NULL;

    return inventory_get_all_ids(player->inv, num);
}

STATUS player_add_object(Player *player, Id id)
{
    if (player == NULL)
        return ERROR;

    return inventory_add_id(player->inv, id);
}

STATUS player_remove_object(Player *player, Id id)
{
    if (player == NULL)
        return ERROR;

    return inventory_delete_id(player->inv, id);
}

int player_get_max_objects(Player *player)
{
    if (player == NULL)
        return -1;

    return inventory_get_max_objs(player->inv);
}

STATUS player_set_max_objects(Player *player, int maxObjs)
{
    if (player == NULL || maxObjs < 1)
        return ERROR;

    return inventory_set_max_objs(player->inv, maxObjs);
}

int player_get_num_objects(Player *player)
{
    if (player == NULL)
        return -1;

    return inventory_get_number_ids(player->inv);
}

int player_get_health(Player *player)
{

    if (player == NULL)
        return -1;

    return player->health;
}

STATUS player_set_health(Player *player, int health)
{
    if (player == NULL || health < 0)
        return ERROR;

    player->health = health;

    return OK;
}

int player_get_type(Player *player)
{
    if (player == NULL)
        return UNDEFPLY;

    return player->type;
}

STATUS player_set_type(Player *player, T_PlayerType type)
{
    if (player == NULL || type < 0 || type > TYPEPLAYERS)
        return ERROR;

    player->type = type;

    return OK;
}

STATUS player_print(Player *player, FILE *file)
{

    if (player == NULL || file == NULL)
        return ERROR;

    /* 1. Print the id, the name, location, objects and health of the player*/

    fprintf(file, "--> Player (Id: %ld; Name: %s; Location: %ld; Health: %d)\n", player->id, player->name, player->location, player->health);

    return inventory_print(player->inv, file);
}
