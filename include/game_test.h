/**
 * @brief It declares the tests for the game module
 *
 * @file game_test.h
 * @author Alejandro García Hernando - Diego Rodríguez Ortiz - David Brenchley Uriol - Javier San Andrés
 * @version 3.0
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef GAME_TEST_H
#define GAME_TEST_H

/**
 * @test Test game creation
 * @pre id != NO_ID
 * @post Non NULL pointer to game
 */
void test1_game_create();

/**
 * @test Test game creation
 * @pre game ID
 * @post game_ID == Supplied game Id
 */
void test2_game_create();

/**
 * @test Test game duplicate creation
 * @pre id != NO_ID
 * @post Non NULL pointer to game
 */
void test1_game_create_dup();

/**
 * @test Test game duplicate creation
 * @pre game ID
 * @post game_ID == Supplied game Id
 */
void test2_game_create_dup();


/**
 * @test Test game creation from a file
 * @pre no name
 * @post game == NULL
 */
void test1_game_create_from_file();

/**
 * @test Test game creation from a file
 * @pre name of a real file
 * @post game != NULL
 */
void test2_game_create_from_file();

/**
 * @test Test function for updating the game
 * @pre game is NULL
 * @post update ERROR
 */
void test1_game_update();

/**
 * @test Test function for updating the game
 * @pre command take
 * @post update OK
 */
void test2_game_update();

/**
 * @test Test function for updating the game
 * @pre command take
 * @post update OK
 */
void test3_game_update();


/**
 * @test Test function for finishing the game
 * @pre game is NULL
 * @post game_is_over(game)==TRUE
 */
void test1_game_is_over();

/**
 * @test Test function for game_last_command getting
 * @pre game was just created from a file
 * @post game_is_over(game)==FALSE
 */
void test2_game_is_over();

/**
 * @test Test function for game data printing
 * @pre pointer to game NULL full of information, pointer to file NON NULL
 * @post Output == OK
 */
void test1_game_print_data();

/**
 * @test Test function for game data printing
 * @pre pointer to game NULL, pointer to file NULL
 * @post Output == ERROR
 */
void test2_game_print_data();

/**
 * @test Test function for game data printing
 * @pre pointer to game NULL, pointer to file NON NULL
 * @post Output == ERROR
 */
void test3_game_print_data();


/*GAME PLAYER TESTS*/

/**
 * @test Test function for getting the player of the game
 * @pre game player is NULL
 * @post game_get_player(game)==NULL
 */
void test1_game_get_player();

/**
 * @test Test function for getting the player of the game
 * @pre game is not null, player is not NULL
 * @post game_get_player(game) == ply
 */
void test2_game_get_player();

/**
 * @test Test function for setting the player of the game
 * @pre game is NULL
 * @post game_set_player(game,player) == ERROR
 */
void test1_game_set_player();

/**
 * @test Test function for setting the player of the game
 * @pre player is NULL
 * @post game_set_player(game,player) == ERROR
 */
void test2_game_set_player();

/**
 * @test Test function for setting the player of the game
 * @pre game and player exist
 * @post game_set_player_health(game, 1) == OK
 */
void test3_game_set_player();

/**
 * @test Test function for getting the objects of the game
 * @pre game is NULL
 * @post game_get_player_objects(game) == NULL
 */
void test1_game_get_player_objects();

/**
 * @test Test function for getting the objects of the game
 * @pre player has no objects
 * @post game_get_player_objects(game) == NULL
 */
void test2_game_get_player_objects();

/**
 * @test Test function for getting the objects of the game
 * @pre player has an object
 * @post ids[0]==ID_OBJECT
 */
void test3_game_get_player_objects();

/**
 * @test Test function for getting the player's location
 * @pre game is NULL
 * @post game_get_player_location(game) == NO_ID
 */
void test1_game_get_player_location();

/**
 * @test Test function for getting the player's location
 * @pre player doesn´t have a location
 * @post game_get_player_location(game) == NO_ID
 */
void test2_game_get_player_location();

/**
 * @test Test function for getting the player's location
 * @pre player location is defined
 * @post game_get_player_location(game) == ID_LOC
 */
void test3_game_get_player_location();

/**
 * @test Test function for setting the player's location
 * @pre player is NULL
 * @post player_set_location(player, ID_LOC) == ERROR
 */
void test1_game_set_player_location();

/**
 * @test Test function for setting the player's location
 * @pre player location is NO_ID
 * @post game_get_player_location(game) == NO_ID
 */
void test2_game_set_player_location();

/**
 * @test Test function for setting the player's location
 * @pre player location is ID_LOC
 * @post game_get_player_location(game) == ID_LOC
 */
void test3_game_set_player_location();

/**
 * @test Test function for getting the player's health
 * @pre game is NULL
 * @post game_get_player_health(game) == -1
 */
void test1_game_get_player_health();

/**
 * @test Test function for getting the player's health
 * @pre game is just created form file
 * @post game_get_player_health(game) == 3
 */
void test2_game_get_player_health();

/**
 * @test Test function for setting the player's health
 * @pre game is NULL
 * @post game_set_player_health(game, 3) == ERROR
 */
void test1_game_set_player_health();

/**
 * @test Test function for setting the player's health
 * @pre game is just created from file
 * @post game_set_player_health(game, -1) == ERROR
 */
void test2_game_set_player_health();

/**
 * @test Test function for setting the player's health
 * @pre player´s health is set to 1
 * @post game_set_player_health(game, 1) == OK
 */
void test3_game_set_player_health();

/**
 * @test Test function for checking whether the player can currently illuminate a space or not
 * @pre game==NULL
 * @post game_get_player_has_light(game) == FALSE
 */
void test1_game_player_has_light();

/**
 * @test Test function for checking whether the player can currently illuminate a space
 * @pre game not NULL, player is the FIREFLY
 * @post game_get_player_has_light(game) == TRUE
 */
void test2_game_player_has_light();

/**
 * @test Test function for checking whether the player can currently illuminate a space
 * @pre game not NULL, player is the SNAIL
 * @post game_get_player_has_light(game) == False
 */
void test3_game_player_has_light();

/**
 * @test Test function for checking whether the player can currently illuminate a space
 * @pre game not NULL, player is the snail, player has lamp
 * @post game_get_player_has_light(game) == TRUE
 */
void test4_game_player_has_light();


/*GAME ENEMY TESTS*/


/**
 * @test Test function for getting the enemy
 * @pre game is NULL
 * @post game_get_enemy(game) == NULL
 */
void test1_game_get_enemy();

/**
 * @test Test function for getting th enemy
 * @pre game is just created from file
 * @post game_get_enemy(game) != NULL
 */
void test2_game_get_enemy();

/**
 * @test Test function for setting the enemy
 * @pre game is  NULL
 * @post game_add_enemy(game, enemy) == ERROR
 */
void test1_game_add_enemy();

/**
 * @test Test function for setting the enemy
 * @pre enemy is NULL
 * @post game_add_enemy(game, enemy) == ERROR
 */
void test2_game_add_enemy();

/**
 * @test Test function for setting the enemy
 * @pre game is just created from file and enemy created
 * @post game_add_enemy(game, enemy) == OK
 */
void test3_game_add_enemy();

/**
 * @test Test function for setting the enemy
 * @pre game is just created from file and enemy created
 * @post enemy_get_id(enemy)==ID
 */
void test4_game_add_enemy();

/**
 * @test Test function for getting the enemy's location
 * @pre game is NULL
 * @post game_get_enemy_id_at(game) == NO_ID
 */
void test1_game_get_enemy_id_at();

/**
 * @test Test function for getting the enemy's id
 * @pre game not NULL, enemy not null
 * @post game_get_enemy_id_at(game) == ID
 */
void test2_game_get_enemy_id_at();


/**
 * @test Test function for getting the enemy's health
 * @pre game is NULL
 * @post game_get_num_enemies(game) == -1
 */
void test1_game_get_num_enemies();

/**
 * @test Test function for getting the enemy's health
 * @pre game is just created from file
 * @post game_get_num_enemies(game) == 3
 */
void test2_game_get_num_enemies();




/*GAME OBJECT TESTS*/


/**
 * @test Test function for getting the objects of the game
 * @pre game is  not NULL, 2 enemies in game
 * @post game_get_num_enemies(game) == 2
 */
void test1_game_get_object();

/**
 * @test Test function for getting the objects of the game
 * @pre game is just created from file
 * @post game_get_object(game, NO_ID) == NULL
 */
void test2_game_get_object();

/**
 * @test Test function for getting the objects of the game
 * @pre game is just created from file
 * @post game_get_object(game, ID_OBJECT) != NULL
 */
void test3_game_get_object();

/**
 * @test Test function for adding an object to the game
 * @pre game and object are NULL
 * @post game_add_object(game, obj) == ERROR
 */
void test1_game_add_object();

/**
 * @test Test function for adding an object to the game
 * @pre object is NULL
 * @post game_add_object(game, obj) == ERROR
 */
void test2_game_add_object();

/**
 * @test Test function for adding an object to the game
 * @pre game and object exist
 * @post game_add_object(game, obj) == OK
 */
void test3_game_add_object();

/**
 * @test Test function for deleting an object in the game
 * @pre game is NULL
 * @post game_delete_object(game, obj) == ERROR
 */
void test1_game_delete_object();

/**
 * @test Test function for deleting an object in the game
 * @pre game is not NULL, object is not NULL
 * @post game_delete_object(game, obj) == ERROR
 */
void test2_game_delete_object();

/**
 * @test Test function for deleting an object in the game
 * @pre game is not NULL, object NO_ID
 * @post game_delete_object(game, obj) == ERROR
 */
void test3_game_delete_object();


/**
 * @test Test function for getting an object's ID
 * @pre game is NULL
 * @post game_add_object(game, 0) == NO_ID
 */
void test1_game_get_object_id_at();

/**
 * @test Test function for getting an object's ID
 * @pre just one object is added to the game
 * @post game_add_object(game, 0) == ID_OBJECT
 */
void test2_game_get_object_id_at();

/**
 * @test Test function for getting the number if the objects in the game
 * @pre game is NULL
 * @post game_get_num_objects(game) == -1
 */
void test1_game_get_num_objects();

/**
 * @test Test function for getting the number if the objects in the game
 * @pre game is created with no objects
 * @post game_get_num_objects(game) == 0
 */
void test2_game_get_num_objects();

/**
 * @test Test function for getting the number if the objects in the game
 * @pre game is created with no objects and an object added to it
 * @post game_get_num_objects(game) == 1
 */
void test3_game_get_num_objects();

/**
 * @test Test function for getting the name of an object in the game
 * @pre pointer to game NON NULL, object with a name
 * @post Output != NULL
 */
void test1_game_get_object_name();

/**
 * @test Test function for getting the name of an object in the game
 * @pre pointer to game NON NULL, object with no name
 * @post Output == NO_NAME
 */
void test2_game_get_object_name();

/**
 * @test Test function for getting the name of an object in the game
 * @pre pointer to game NON NULL, pointer to object NULL
 * @post Output == NULL
 */
void test3_game_get_object_name();

/**
 * @test Test function for getting the name of an object in the game
 * @pre pointer to game NULL, pointer to object NON NULL
 * @post Output == NULL
 */
void test4_game_get_object_name();

/**
 * @test Test function for getting the location of an object in the game
 * @pre game is NULL
 * @post game_get_object_location(game, ID_OBJECT) == NO_ID
 */
void test1_game_get_object_location();

/**
 * @test Test function for getting the location of an object in the game
 * @pre object is not added to the space
 * @post game_get_object_location(game, ID_OBJECT) == NO_ID
 */
void test2_game_get_object_location();

/**
 * @test Test function for getting the location of an object in the game
 * @pre gets the location of NO_ID
 * @post game_get_object_location(game, NO_ID) == NO_ID
 */
void test3_game_get_object_location();

/**
 * @test Test function for getting the location of an object in the game
 * @pre gets the location of an added object
 * @post game_get_object_location(game, ID_OBJECT)==ID_LOC
 */
void test4_game_get_object_location();

/**
 * @test Test function for setting the location of an object in the game
 * @pre game is NULL
 * @post game_set_object_location(game, NO_ID, NO_ID)==ERROR
 */
void test1_game_set_object_location();

/**
 * @test Test function for setting the location of an object in the game
 * @pre the location of an object is set to ID_LOC
 * @post game_set_object_location(game, ID, ID_LOC)==ERROR
 */
void test2_game_set_object_location();

/**
 * @test Test function for setting the location of an object in the game
 * @pre the location of an object is set to ID_LOC
 * @post game_get_object_location(game, ID_OBJECT)==ID_LOC
 */
void test3_game_set_object_location();



/*GAME SPACE TESTS*/

/**
 * @test Test function for getting a space in the game
 * @pre game is NULL
 * @post game_get_space(game, ID_LOC)==NULL
 */
void test1_game_get_space();

/**
 * @test Test function for getting a space in the game
 * @pre gets the space of NO_ID
 * @post game_get_space(game, NO_ID)==NULL
 */
void test2_game_get_space();

/**
 * @test Test function for getting a space in the game
 * @pre gets the space of and existing space
 * @post game_get_space(game, ID_LOC)!=NULL
 */
void test3_game_get_space();

/**
 * @test Test function for adding a space to the game
 * @pre game and space are NULL
 * @post game_add_space(game, space)==ERROR
 */
void test1_game_add_space();

/**
 * @test Test function for adding a space to the game
 * @pre a space is added to the game
 * @post game_add_space(game, space)==OK
 */
void test2_game_add_space();

/**
 * @test Test function for adding a space to the game
 * @pre a space is added to the game
 * @post game_get_space_id_at(game, 0)==ID_LOC
 */
void test3_game_add_space();

/**
 * @test Test function for deleting a space in the game
 * @pre game is NULL
 * @post game_delete_space(game, ID_SPACE) == ERROR
 */
void test1_game_delete_space();

/**
 * @test Test function for deleting a space in the game
 * @pre game is not NULL
 * @post game_delete_space(game, ID_SPACE) == OK
 */
void test2_game_delete_space();

/**
 * @test Test function for deleting a space in the game
 * @pre game is not NULL, space NO_ID, object ID_OBJECT
 * @post game_delete_space(game, ID_SPACE) == OK && object == NULL
 */
void test3_game_delete_space();

/**
 * @test Test function for getting a space ID
 * @pre game and space are NULL
 * @post game_get_space_id_at(game, 0)==NO_ID
 */
void test1_game_get_space_id_at();

/**
 * @test Test function for getting a space ID
 * @pre space is NULL
 * @post game_get_space_id_at(game, 0)==NO_ID
 */
void test2_game_get_space_id_at();

/**
 * @test Test function for getting a space ID
 * @pre one space is added to the game
 * @post game_get_space_id_at(game, 0)==ID_LOC
 */
void test3_game_get_space_id_at();


/**
 * @test Test function for getting anumber of spaces
 * @pre game is NULL
 * @post game_get_num_of_spaces(game)==0
 */
void test1_game_get_num_of_spaces();

/**
 * @test Test function for getting anumber of spaces
 * @pre game is not NULL,
 * @post game_get_num_of_spaces(game)==0
 */
void test2_game_get_num_of_spaces();

/**
 * @test Test function for getting anumber of spaces
 * @pre game is not NULL, object added is not null
 * @post game_get_num_of_spaces(game)==0
 */
void test3_game_get_num_of_spaces();



/*GAME LINK TESTS*/

/**
 * @test Test function for adding a link
 * @pre link is NULL
 * @post game_add_link(game, link)==ERROR
 */
void test1_game_add_link();

/**
 * @test Test function for adding a link
 * @pre game is NULL
 * @post game_add_link(game, link)==ERROR
 */
void test2_game_add_link();

/**
 * @test Test function for adding a link
 * @pre a link is added to the game
 * @post game_add_link(game, link)==OK
 */
void test3_game_add_link();


/**
 * @test Test function for deleting a link in the game
 * @pre game is NULL
 * @post game_delete_link(game, ID_LINK) == ERROR
 */
void test1_game_delete_link();

/**
 * @test Test function for deleting a link in the game
 * @pre game is not NULL
 * @post game_delete_link(game, ID_LINK) == ERROR
 */
void test2_game_delete_link();


/**
 * @test Test function for deleting a link in the game
 * @pre game is not NULL, link not null
 * @post game_delete_link(game, ID_LINK) == ERROR
 */
void test3_game_delete_link();

/**
 * @test Test function for getting a link in the game
 * @pre pointer to game NON NULL, one link added
 * @post Output == Supplied_link_name
 */
void test1_game_get_link();

/**
 * @test Test function for getting a link in the game
 * @pre link is not added to the game
 * @post game_get_link(game, ID_LINK)==NULL
 */
void test2_game_get_link();

/**
 * @test Test function for getting a link in the game
 * @pre link is added to the game
 * @post game_get_link(game, ID_LINK)==link
 */
void test3_game_get_link();


/**
 * @test Test function for getting a link's id
 * @pre game is null
 * @post game_get_link_id(game, ID_LOC, NORTH) == NO_ID
 */
void test1_game_get_link_id();

/**
 * @test Test function for getting a link's id
 * @pre game is not null
 * @post game_get_link_id(game, ID_LOC, UP) == NO_ID
 */
void test2_game_get_link_id();

/**
 * @test Test function for getting a link's id
 * @pre game is null, link is not null
 * @post game_get_link_id(game, ID_LINK, NORTH) ==ID_LINK
 */
void test3_game_get_link_id();


/**
 * @test Test function for getting a link's id at a certain position in the array of links
 * @pre game is null
 * @post ggame_get_link_id_at(game, 0) == NO_ID
 */
void test1_game_get_link_id_at();

/**
 * @test Test function for getting a link's id at a certain position in the array of links
 * @pre game is not null
 * @post game_get_link_id_at(game, 0) == NO_ID
 */
void test2_game_get_link_id_at();

/**
 * @test Test function for getting a link's id at a certain position in the array of links
 * @pre game is null, link is not null
 * @post game_get_link_id_at(game, 0) == ID_LINK
 */
void test3_game_get_link_id_at();


/**
 * @test Test function for getting a link's name'
 * @pre pointer to game NON NULL, one link added
 * @post Output == Supplied_link_name
 */
void test1_game_get_link_name();

/**
 * @test Test function for getting a link's name'
 * @pre pointer to game NON NULL, one link added
 * @post Output == Default_link_name
 */
void test2_game_get_link_name();

/**
 * @test Test function for getting a link's name'
 * @pre pointer to game NON NULL, NO_ID link
 * @post Output == NULL
 */
void test3_game_get_link_name();


/**
 * @test Test function for getting a link's name'
 * @pre pointer to game is NULL
 * @post Output == NULL
 */
void test4_game_get_link_name();

/**
 * @test Test function for setting the link's origin in a space
 * @pre pointer to game NON NULL, id_link = game_existing_id, origin = game_existing_space_id
 * @post Output == OK
 */
void test1_game_set_link_origin();

/**
 * @test Test function for setting the link's origin in a space
 * @pre pointer to game NON NULL, id_link = game_existing_id, origin != game_existing_space_id
 * @post Output == ERROR
 */
void test2_game_set_link_origin();

/**
 * @test Test function for setting the link's origin in a space
 * @pre pointer to game NON NULL, id_link != game_existing_id, origin == game_existing_space_id
 * @post Output == ERROR
 */
void test3_game_set_link_origin();

/**
 * @test Test function for setting the link's origin in a space
 * @pre pointer to game NON NULL, id_link == game_existing_id, origin == NO_ID
 * @post Output == ERROR
 */
void test4_game_set_link_origin();

/**
 * @test Test function for setting the link's origin in a space
 * @pre pointer to game NON NULL, id_link == NO_ID, origin != NO_ID
 * @post Output == ERROR
 */
void test5_game_set_link_origin();

/**
 * @test Test function for setting the link's origin in a space
 * @pre pointer to game NULL, id_link != NO_ID, origin != NO_ID
 * @post Output == ERROR
 */
void test6_game_set_link_origin();

/**
 * @test Test function for setting the link's destination in a space
 * @pre pointer to game NON NULL, id_link = game_existing_id, destination = game_existing_space_id
 * @post Output == OK
 */
void test1_game_set_link_destination();

/**
 * @test Test function for setting the link's destination in a space
 * @pre pointer to game NON NULL, id_link = game_existing_id, destination != game_existing_space_id
 * @post Output == ERROR
 */
void test2_game_set_link_destination();

/**
 * @test Test function for setting the link's destination in a space
 * @pre pointer to game NON NULL, id_link != game_existing_id, destination == game_existing_space_id
 * @post Output == ERROR
 */
void test3_game_set_link_destination();

/**
 * @test Test function for setting the link's destination in a space
 * @pre pointer to game NON NULL, id_link == game_existing_id, destination == NO_ID
 * @post Output == ERROR
 */
void test4_game_set_link_destination();

/**
 * @test Test function for setting the link's destination in a space
 * @pre pointer to game NON NULL, id_link == NO_ID, destination != NO_ID
 * @post Output == ERROR
 */
void test5_game_set_link_destination();

/**
 * @test Test function for setting the link's destination in a space
 * @pre pointer to game NULL, id_link != NO_ID, destination != NO_ID
 * @post Output == ERROR
 */
void test6_game_set_link_destination();

/**
 * @test Test function for getting the status of a connection in the game
 * @pre game is NULL
 * @post game_get_connection_status(game, origin, destination)==ERROR
 */
void test1_game_get_connection_status();

/**
 * @test Test function for getting the status of a connection in the game
 * @pre connection is in the game
 * @post game_get_connection_status(game, origin, destination)==ERROR
 */
void test2_game_get_connection_status();

/**
 * @test Test function for getting the status of a connection in the game
 * @pre connection is in the game
 * @post game_get_connection_status(game, origin, destination)==OK
 */
void test3_game_get_connection_status();

/**
 * @test Test function for getting a connection in the game
 * @pre Pointe to game NON NULL, link = existing_game_link
 * @post Output == link_destination
 */
void test1_game_get_connection();

/**
 * @test Test function for getting a connection in the game
 * @pre Pointe to game NON NULL, connection != existing_game_link
 * @post Output == NO_ID
 */
void test2_game_get_connection();

/**
 * @test Test function for getting a connection in the game
 * @pre Pointe to game NULL
 * @post Output == NO_ID
 */
void test3_game_get_connection();

/**
 * @test Test function for getting the destination of an open link
 * @pre game is NULL
 * @post game_get_open_link(game, space, dir)==NO_ID
 */
void test1_game_get_open_link();

/**
 * @test Test function for getting the destination of an open link
 * @pre game has no open link
 * @post game_get_open_link(game, space, dir)==NO_ID
 */
void test2_game_get_open_link();

/**
 * @test Test function for getting the destination of an open link
 * @pre game is NULL
 * @post game_get_open_link(game, space, dir)==ID_LOC2
 */
void test3_game_get_open_link();

/**
 * @test Test function for getting the number of links
 * @pre pointer to game NULL
 * @post Output == -1
 */
void test1_game_get_num_links();

/**
 * @test Test function for getting the number of links
 * @pre pointer to game not NULL
 * @post Output == 0
 */
void test2_game_get_num_links();

/**
 * @test Test function for getting the number of links
 * @pre pointer to game not NULL, 1 link added
 * @post Output == 1
 */
void test3_game_get_num_links();


/**
 * @test Test function for game_last_command getting
 * @pre pointer to game NON NULL, command == exit e
 * @post game_last_command != NULL
 */
void test1_game_get_last_command();

/**
 * @test Test function for game_last_command getting
 * @pre pointer to game NULL, no_commands_executed
 * @post game_last_command == NULL
 */
void test2_game_get_last_command();

/**
 * @test Test function for game_last_command_cmd getting
 * @pre pointer to game NON NULL, command Exit e
 * @post command == EXIT
 */
void test1_game_get_last_command_cmd();

/**
 * @test Test function for game_last_command_cmd getting
 * @pre pointer to game NON NULL, command Move w
 * @post command == Move
 */
void test2_game_get_last_command_cmd();

/**
 * @test Test function for game_last_command getting
 * @pre pointer to game NON NULL, no_commands_executed but game created
 * @post command == LOAD
 */
void test3_game_get_last_command_cmd();

/**
 * @test Test function for game_last_command_status getting
 * @pre pointer to game NON NULL, command Move s
 * @post command_status == OK
 */
void test1_game_get_last_command_status();

/**
 * @test Test function for game_last_command_status getting
 * @pre pointer to game NON NULL with no spaces, command Move w
 * @post command_status == ERROR
 */
void test2_game_get_last_command_status();

/**
 * @test Test function for game_num_executed_commands getting
 * @pre pointer to game NULL
 * @post Output == -1
 */
void test1_game_get_num_executed_commands();

/**
 * @test Test function for game_num_executed_commands getting
 * @pre pointer to game non NULL, command Move s already executed
 * @post Output == 1
 */
void test2_game_get_num_executed_commands();

/**
 * @test Test function for game_num_executed_commands setting
 * @pre pointer to game NULL
 * @post Output == ERROR
 */
void test1_game_set_num_executed_commands();

/**
 * @test Test function for game_num_executed_commands setting
 * @pre pointer to game non NULL, num_executed == 3
 * @post Output == OK
 */
void test2_game_set_num_executed_commands();

/**
 * @test Test function to get last textual description
 * @pre pointer to game NULL
 * @post Output == NULL
 */
void test1_game_get_last_tdesc();

/**
 * @test Test function to get last textual description
 * @pre pointer to game non NULL, pointer to textual descriptor non NULL
 * @post Output == textual descriptor
 */
void test2_game_get_last_tdesc();

/**
 * @test Test function to set last textual description
 * @pre pointer to game NULL
 * @post Output == ERROR
 */
void test1_game_set_last_tdesc();

/**
 * @test Test function to set last textual description
 * @pre pointer to game non NULL, pointer to textual descriptor non NULL
 * @post Output == textual descriptor
 */
void test2_game_set_last_tdesc();

/**
 * @test Test function to get last inspection
 * @pre pointer to game NULL
 * @post Output == NULL
 */
void test1_game_get_last_idesc();

/**
 * @test Test function to get last inspection
 * @pre pointer to game non NULL, pointer to textual inspection non NULL
 * @post Output == textual descriptor
 */
void test2_game_get_last_idesc();

/**
 * @test Test function to set last inspection
 * @pre pointer to game NULL
 * @post Output == ERROR
 */
void test1_game_set_last_idesc();

/**
 * @test Test function to set last inspection
 * @pre pointer to game non NULL, pointer to textual inspection non NULL
 * @post game_last_idesc == Supplied_idesc
 */
void test2_game_set_last_idesc();

/**
 * @test Test function for recognizing existing dialogues_id
 * @pre pointer to game non NULL, id == existing_game_id
 * @post  Output == True
 */
void test1_game_existing_dialogue_id();

/**
 * @test Test function for recognizing existing dialogues_id
 * @pre pointer to game non NULL, id != existing_game_id
 * @post  Output == False
 */
void test2_game_existing_dialogue_id();

/**
 * @test Test function for recognizing existing dialogues_id
 * @pre pointer to game non NULL, id == NO_ID
 * @post  Output == False
 */
void test3_game_existing_dialogue_id();

/**
 * @test Test function for recognizing existing dialogues_id
 * @pre pointer to game NULL
 * @post  Output == False
 */
void test4_game_existing_dialogue_id();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game non NULL, dialogue_id != exsting_dialogue_id
 * @post  Output == OK
 */
void test1_game_add_dialogue();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game non NULL, dialogue_id == exsting_dialogue_id
 * @post  Output == ERROR
 */
void test2_game_add_dialogue();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game non NULL, pointer to dialogue NULL
 * @post  Output == ERROR
 */
void test3_game_add_dialogue();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game NULL
 * @post  Output == ERROR
 */
void test4_game_add_dialogue();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game non NULL, dialogue_id == exsting_dialogue_id
 * @post  Output == OK
 */
void test1_game_add_dialogue_rule();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game non NULL, dialogue_id != exsting_dialogue_id
 * @post  Output == ERROR
 */
void test2_game_add_dialogue_rule();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game non NULL, dialogue_id == NO_ID
 * @post  Output == ERROR
 */
void test3_game_add_dialogue_rule();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game non NULL, pointer to rule NULL
 * @post  Output == ERROR
 */
void test4_game_add_dialogue_rule();

/**
 * @test Test function for game_dialogues adding
 * @pre pointer to game NULL
 * @post  Output == ERROR
 */
void test5_game_add_dialogue_rule();

/**
 * @test Test function for game_dialogue_executed getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, one execution
 * @post Ouput == 1
 */
void test1_game_get_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed getting
 * @pre pointer to game NON NULL, dialogue_id != existing_id
 * @post Ouput == -1
 */
void test2_game_get_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed getting
 * @pre pointer to game NON NULL, dialogue_id != NO_ID
 * @post Ouput == -1
 */
void test3_game_get_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed getting
 * @pre pointer to game NULL
 * @post Ouput == -1
 */
void test4_game_get_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed increasing
 * @pre pointer to game NON NULL, dialogue_id == existing_id
 * @post Ouput == OK
 */
void test1_game_increase_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed increasing
 * @pre pointer to game NON NULL, dialogue_id != existing_id
 * @post Ouput == ERROR
 */
void test2_game_increase_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed increasing
 * @pre pointer to game NON NULL, dialogue_id != NO_ID
 * @post Ouput == ERROR
 */
void test3_game_increase_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed increasing
 * @pre pointer to game NULL
 * @post Ouput == ERROR
 */
void test4_game_increase_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed decreasing
 * @pre pointer to game NON NULL, dialogue_id == existing_id
 * @post Ouput == OK
 */
void test1_game_decrease_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed decreasing
 * @pre pointer to game NON NULL, dialogue_id != existing_id
 * @post Ouput == ERROR
 */
void test2_game_decrease_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed decreasing
 * @pre pointer to game NON NULL, dialogue_id != NO_ID
 * @post Ouput == ERROR
 */
void test3_game_decrease_dialogue_executed();

/**
 * @test Test function for game_dialogue_executed decreasing
 * @pre pointer to game NULL
 * @post Ouput == ERROR
 */
void test4_game_decrease_dialogue_executed();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position = existing_position, no arguments, success type
 * @post Ouput != NULL
 */
void test1_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position = existing_position, no arguments, error type
 * @post Ouput != NULL
 */
void test2_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position = existing_position, one argument, success type
 * @post Ouput != NULL
 */
void test3_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position = existing_position, one argument, error type
 * @post Ouput != NULL
 */
void test4_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position = existing_position, several arguments, success type
 * @post Ouput != NULL
 */
void test5_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position = existing_position, several arguments, error type
 * @post Ouput != NULL
 */
void test6_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position != existing_position, no arguments, success type
 * @post Ouput == NULL
 */
void test7_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id == existing_id, position != existing_position, no arguments, error type
 * @post Ouput == NULL
 */
void test8_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NON NULL, dialogue_id != existing_id
 * @post Ouput == NULL
 */
void test9_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_rule in printed format getting
 * @pre pointer to game NULL
 * @post Ouput == NULL
 */
void test10_game_get_printed_dialogue_rule();

/**
 * @test Test function for game_dialogue_repeated_error_rule in printed format getting
 * @pre pointer to game NON NULL, non_empty repeated_error_rules
 * @post Ouput != NULL
 */
void test1_game_get_printed_repeated_error_rule();

/**
 * @test Test function for game_dialogue_repeated_error_rule in printed format getting
 * @pre pointer to game NON NULL, num_times == 0
 * @post Ouput == NULL
 */
void test2_game_get_printed_repeated_error_rule();

/**
 * @test Test function for game_dialogue_repeated_error_rule in printed format getting
 * @pre pointer to game NULL
 * @post Ouput == NULL
 */
void test3_game_get_printed_repeated_error_rule();

/**
 * @test Test function for first success dialogue rule for move getting
 * @pre Correct move command, destination with light and no enemies
 * @post Ouput == correct_dialogue
 */
void test1_game_get_move_dialogue_rule();

/**
 * @test Test function for second success dialogue rule for move getting
 * @pre Correct move command, destination with light and an enemy
 * @post Ouput == correct_dialogue
 */
void test2_game_get_move_dialogue_rule();

/**
 * @test Test function for third success dialogue rule for move getting
 * @pre Correct move command, destination with no light and no enemies
 * @post Ouput == correct_dialogue
 */
void test3_game_get_move_dialogue_rule();

/**
 * @test Test function for fourth success dialogue rule for move getting
 * @pre Correct move command, destination with no light and an enemy
 * @post Ouput == correct_dialogue
 */
void test4_game_get_move_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for move getting
 * @pre Invalid move command, there's no link in that direction
 * @post Ouput == correct_dialogue
 */
void test5_game_get_move_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for move getting
 * @pre Invalid move command, there's no opened link in that direction
 * @post Ouput == correct_dialogue
 */
void test6_game_get_move_dialogue_rule();

/**
 * @test Test function for third error dialogue rule for move getting
 * @pre Invalid move command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test7_game_get_move_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for attack getting
 * @pre Correct attack command, the enemy gets hit
 * @post Ouput == correct_dialogue
 */
void test1_game_get_attack_dialogue_rule();

/**
 * @test Test function for second success dialogue rule for attack getting
 * @pre Correct attack command, the player gets hit
 * @post Ouput == correct_dialogue
 */
void test2_game_get_attack_dialogue_rule();

/**
 * @test Test function for third success dialogue rule for attack getting
 * @pre Correct attack command, the player gets killed
 * @post Ouput == correct_dialogue
 */
void test3_game_get_attack_dialogue_rule();

/**
 * @test Test function for fourth success dialogue rule for attack getting
 * @pre Correct attack command, the enemy gets killed
 * @post Ouput == correct_dialogue
 */
void test4_game_get_attack_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for take getting
 * @pre Correct take command, the player can take the object
 * @post Ouput == correct_dialogue
 */
void test1_game_get_take_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for take getting
 * @pre Invalid take command, object not in current space
 * @post Ouput == correct_dialogue
 */
void test2_game_get_take_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for take getting
 * @pre Invalid take command, inventory full
 * @post Ouput == correct_dialogue
 */
void test3_game_get_take_dialogue_rule();

/**
 * @test Test function for third error dialogue rule for take getting
 * @pre Invalid take command, the space has no light
 * @post Ouput == correct_dialogue
 */
void test4_game_get_take_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for take getting
 * @pre Invalid take command, the object is not movable
 * @post Ouput == correct_dialogue
 */
void test5_game_get_take_dialogue_rule();

/**
 * @test Test function for fifth error dialogue rule for take getting
 * @pre Invalid take command, the object has a dependency on an object that we don't have
 * @post Ouput == correct_dialogue
 */
void test6_game_get_take_dialogue_rule();

/**
 * @test Test function for fifth error dialogue rule for take getting
 * @pre Invalid take command, the object is already on the player's bag
 * @post Ouput == correct_dialogue
 */
void test7_game_get_take_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for take getting
 * @pre Invalid take command, the object doesn't exist
 * @post Ouput == correct_dialogue
 */
void test8_game_get_take_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for take getting
 * @pre Invalid take command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test9_game_get_take_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for drop getting
 * @pre Correct drop command, the object has no dependencies
 * @post Ouput == correct_dialogue
 */
void test1_game_get_drop_dialogue_rule();

/**
 * @test Test function for second success dialogue rule for drop getting
 * @pre Correct drop command, the object has dependencies
 * @post Ouput == correct_dialogue
 */
void test2_game_get_drop_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for drop getting
 * @pre Invalid drop command, the player's inventory is empty
 * @post Ouput == correct_dialogue
 */
void test3_game_get_drop_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for drop getting
 * @pre Invalid drop command, the player's inventory is empty
 * @post Ouput == correct_dialogue
 */
void test4_game_get_drop_dialogue_rule();

/**
 * @test Test function for third error dialogue rule for drop getting
 * @pre Invalid drop command, the player doesn't hold the object
 * @post Ouput == correct_dialogue
 */
void test5_game_get_drop_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for drop getting
 * @pre Invalid drop command, the object doesn't exist
 * @post Ouput == correct_dialogue
 */
void test6_game_get_drop_dialogue_rule();

/**
 * @test Test function for fifth error dialogue rule for drop getting
 * @pre Invalid drop command, invalid syntax
 * @post Ouput == correct_dialogue
 */
void test7_game_get_drop_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for inspect getting
 * @pre Correct inspect command, object in current space with t_description
 * @post Ouput == correct_dialogue
 */
void test1_game_get_inspect_dialogue_rule();

/**
 * @test Test function for second success dialogue rule for inspect getting
 * @pre Correct inspect command, current space with description
 * @post Ouput == correct_dialogue
 */
void test2_game_get_inspect_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for inspect getting
 * @pre Invalid inspect command, object doesn't exist or isn't in current_space or isn't in player's inventory
 * @post Ouput == correct_dialogue
 */
void test3_game_get_inspect_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for inspect getting
 * @pre Invalid inspect command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test4_game_get_inspect_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for turnon getting
 * @pre Correct turnon command, object which can be illuminated or turned off
 * @post Ouput == correct_dialogue
 */
void test1_game_get_turn_on_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for turnon getting
 * @pre Invalid turnon command, object which can't be illuminated or turned off
 * @post Ouput == correct_dialogue
 */
void test2_game_get_turn_on_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for turnon getting
 * @pre Invalid turnon command, both the player and the space have no light
 * @post Ouput == correct_dialogue
 */
void test3_game_get_turn_on_dialogue_rule();

/**
 * @test Test function for third error dialogue rule for turnon getting
 * @pre Invalid turnon command, the object doesn't exist
 * @post Ouput == correct_dialogue
 */
void test4_game_get_turn_on_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for turnon getting
 * @pre Invalid turnon command, the player doesn't have the object and the object isn't in current space
 * @post Ouput == correct_dialogue
 */
void test5_game_get_turn_on_dialogue_rule();

/**
 * @test Test function for fifth error dialogue rule for turnon getting
 * @pre Invalid turnon command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test6_game_get_turn_on_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for turnoff getting
 * @pre Correct turnoff command, object which can be illuminated or turned off
 * @post Ouput == correct_dialogue
 */
void test1_game_get_turn_off_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for turnoff getting
 * @pre Invalid turnoff command, object which can't be illuminated or turned off
 * @post Ouput == correct_dialogue
 */
void test2_game_get_turn_off_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for turnoff getting
 * @pre Invalid turnoff command, both the player and the space have no light
 * @post Ouput == correct_dialogue
 */
void test3_game_get_turn_off_dialogue_rule();

/**
 * @test Test function for third error dialogue rule for turnoff getting
 * @pre Invalid turnoff command, the object doesn't exist
 * @post Ouput == correct_dialogue
 */
void test4_game_get_turn_off_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for turnoff getting
 * @pre Invalid turnoff command, the player doesn't have the object and the object isn't in current space
 * @post Ouput == correct_dialogue
 */
void test5_game_get_turn_off_dialogue_rule();

/**
 * @test Test function for fifth error dialogue rule for turnoff getting
 * @pre Invalid turnoff command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test6_game_get_turn_off_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for open_link getting
 * @pre Correct open command, existing link and object capable of opening/closing it
 * @post Ouput == correct_dialogue
 */
void test1_game_get_open_link_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for open_link getting
 * @pre Invalid open command, the object is not capable of opening/closing the link
 * @post Ouput == correct_dialogue
 */
void test2_game_get_open_link_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for open_link getting
 * @pre Invalid open command, there's no link with that name and whose origin is in current space
 * @post Ouput == correct_dialogue
 */
void test3_game_get_open_link_dialogue_rule();

/**
 * @test Test function for third error dialogue rule for open_link getting
 * @pre Invalid open command, the object doesn't exist
 * @post Ouput == correct_dialogue
 */
void test4_game_get_open_link_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for open_link getting
 * @pre Invalid open command, the link doesn't exist
 * @post Ouput == correct_dialogue
 */
void test5_game_get_open_link_dialogue_rule();

/**
 * @test Test function for fifth error dialogue rule for open_link getting
 * @pre Invalid open command, the object isn't at player's inventory, nor current space
 * @post Ouput == correct_dialogue
 */
void test6_game_get_open_link_dialogue_rule();

/**
 * @test Test function for sixth error dialogue rule for open_link getting
 * @pre Invalid open command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test7_game_get_open_link_dialogue_rule();

/**
 * @test Test function for seventh error dialogue rule for open_link getting
 * @pre Invalid open command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test8_game_get_open_link_dialogue_rule();

/**
 * @test Test function for eighth error dialogue rule for open_link getting
 * @pre Invalid open command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test9_game_get_open_link_dialogue_rule();

/**
 * @test Test function for ninth error dialogue rule for open_link getting
 * @pre Invalid open command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test10_game_get_open_link_dialogue_rule();

/**
 * @test Test function for first success dialogue rule for close_link getting
 * @pre Correct close command, existing link and object capable of opening/closing it
 * @post Ouput == correct_dialogue
 */
void test1_game_get_close_link_dialogue_rule();

/**
 * @test Test function for first error dialogue rule for close_link getting
 * @pre Invalid close command, the object is not capable of opening/closing the link
 * @post Ouput == correct_dialogue
 */
void test2_game_get_close_link_dialogue_rule();

/**
 * @test Test function for second error dialogue rule for close_link getting
 * @pre Invalid close command, there's no link with that name and whose origin is in current space
 * @post Ouput == correct_dialogue
 */
void test3_game_get_close_link_dialogue_rule();

/**
 * @test Test function for third error dialogue rule for close_link getting
 * @pre Invalid close command, the object doesn't exist
 * @post Ouput == correct_dialogue
 */
void test4_game_get_close_link_dialogue_rule();

/**
 * @test Test function for fourth error dialogue rule for close_link getting
 * @pre Invalid close command, the link doesn't exist
 * @post Ouput == correct_dialogue
 */
void test5_game_get_close_link_dialogue_rule();

/**
 * @test Test function for fifth error dialogue rule for close_link getting
 * @pre Invalid close command, the object isn't at player's inventory, nor current space
 * @post Ouput == correct_dialogue
 */
void test6_game_get_close_link_dialogue_rule();

/**
 * @test Test function for sixth error dialogue rule for close_link getting
 * @pre Invalid close command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test7_game_get_close_link_dialogue_rule();

/**
 * @test Test function for seventh error dialogue rule for close_link getting
 * @pre Invalid close command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test8_game_get_close_link_dialogue_rule();

/**
 * @test Test function for eighth error dialogue rule for close_link getting
 * @pre Invalid close command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test9_game_get_close_link_dialogue_rule();

/**
 * @test Test function for ninth error dialogue rule for close_link getting
 * @pre Invalid close command, incorrect syntax
 * @post Ouput == correct_dialogue
 */
void test10_game_get_close_link_dialogue_rule();


/**
 * @test Test function for flooded dialogue rule getting
 * @pre Maximum number of commands until flood already executed
 * @post Ouput == correct_dialogue
 */
void test1_game_get_dialogue_of_game_rule();

/**
 * @test Test function for flooded dialogue rule getting
 * @pre Maximum number of commands until flood already executed twice
 * @post Ouput == correct_dialogue
 */
void test2_game_get_dialogue_of_game_rule();

/**
 * @test Test function for combine dialogue rule getting
 * @pre Player with the necessary number of objects to combine
 * @post Ouput == correct_dialogue
 */
void test3_game_get_dialogue_of_game_rule();

/**
 * @test Test function for dialogue of game_rules getting
 * @pre pointer to number of dialogues NULL
 * @post Ouput == NULL
 */
void test4_game_get_dialogue_of_game_rule();

/**
 * @test Test function for dialogue of game_rules getting
 * @pre pointer to game NULL
 * @post Ouput == NULL
 */
void test5_game_get_dialogue_of_game_rule();

/**
 * @test Test function for game_dialogues getting
 * @pre pointer to game NON NULL, pointer to num_dialogues NON NULL, game_dialogues non empty
 * @post Ouput != NULL
 */
void test1_game_get_all_dialogues();

/**
 * @test Test function for game_dialogues getting
 * @pre pointer to game NON NULL, pointer to num_dialogues NON NULL, game_dialogues empty
 * @post num_dialogues == 0
 */
void test2_game_get_all_dialogues();

/**
 * @test Test function for game_dialogues getting
 * @pre pointer to game NON NULL, pointer to num_dialogues NULL
 * @post Output == NULL
 */
void test3_game_get_all_dialogues();

/**
 * @test Test function for game_dialogues getting
 * @pre pointer to game NULL, pointer to num_dialogues NON NULL
 * @post Output == NULL
 */
void test4_game_get_all_dialogues();


/**
 * @test Test function for number of commands until flood getting
 * @pre pointer to game NON NULL, one command executed with success
 * @post Ouput == 1
 */
void test1_game_get_num_commands_till_flood();

/**
 * @test Test function for number of commands until flood getting
 * @pre pointer to game NON NULL, one command executed with error
 * @post Ouput == 2
 */
void test2_game_get_num_commands_till_flood();

/**
 * @test Test function for number of commands until flood getting
 * @pre pointer to game NULL
 * @post Ouput == -1
 */
void test3_game_get_num_commands_till_flood();

/**
 * @test Test function for game_rules getting
 * @pre pointer to game NON NULL, rule_id == existing_game_id
 * @post Ouput != NULL
 */
void test1_game_get_rule();

/**
 * @test Test function for game_rules getting
 * @pre pointer to game NON NULL, rule_id == existing_game_id
 * @post Ouput != NULL
 */
void test2_game_get_rule();

/**
 * @test Test function for game_rules getting
 * @pre pointer to game NON NULL, rule_id == NO_ID
 * @post Ouput == NULL
 */
void test3_game_get_rule();

/**
 * @test Test function for game_rules getting
 * @pre pointer to game NULL
 * @post Ouput == NULL
 */
void test4_game_get_rule();


/**
 * @test Test function for game_rules by their position in the array getting
 * @pre pointer to game NON NULL, valid position
 * @post Ouput == Valid_rule_id
 */
void test1_game_get_rule_id_at();

/**
 * @test Test function for game_rules by their position in the array getting
 * @pre pointer to game NON NULL, not valid position
 * @post Ouput == NO_ID
 */
void test2_game_get_rule_id_at();

/**
 * @test Test function for game_rules by their position in the array getting
 * @pre pointer to game NULL
 * @post Ouput == NO_ID
 */
void test3_game_get_rule_id_at();

/**
 * @test Test function for number of game_rules getting
 * @pre pointer to game NON NULL, game without rules
 * @post Ouput == 0
 */
void test1_game_get_num_rules();

/**
 * @test Test function for number of game_rules getting
 * @pre pointer to game NULL
 * @post Ouput == -1
 */
void test2_game_get_num_rules();

/**
 * @test Test function for game_rules adding
 * @pre pointer to game NON NULL, pointer to rule NON NULL
 * @post Ouput == OK
 */
void test1_game_add_rule();

/**
 * @test Test function for game_rules adding
 * @pre pointer to game NON NULL, pointer to rule NULL
 * @post Ouput == ERROR
 */
void test2_game_add_rule();

/**
 * @test Test function for game_rules adding
 * @pre pointer to game NULL, pointer to rule NON NULL
 * @post Ouput == ERROR
 */
void test3_game_add_rule();


/**
 * @test Test function for spawn_ground rule executing
 * @pre pointer to game NON NULL
 * @post Ouput == OK
 */
void test1_game_rule_spawn_ground();

/**
 * @test Test function for spawn_ground rule executing
 * @pre pointer to game NON NULL, invalid requested grounds
 * @post Ouput == ERROR
 */
void test2_game_rule_spawn_ground();

/**
 * @test Test function for spawn_ground rule executing
 * @pre pointer to game NULL
 * @post Ouput == ERROR
 */
void test3_game_rule_spawn_ground();

#endif