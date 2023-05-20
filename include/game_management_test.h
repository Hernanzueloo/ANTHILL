/** 
 * @brief It declares the tests for the game_management module
 * 
 * @file game_management_test.h
 * @author Javier San Andres
 * @version 3.0 
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef game_MANAGEMENT_TEST_H
#define game_MANAGEMENT_TEST_H

/**
 * @test Test game_management loading
 * @pre pointer to game NULL
 * @post game_management_load(game, GAMERDRFILE) == ERROR
 */
void test1_game_management_load();

/**
 * @test Test game_management loading of spaces
 * @pre pointer to game NON NULL, file with space
 * @post game_management_load(game, GAMERDRFILE) == OK
 */
void test2_game_management_load();

/**
 * @test Test game_management load of spaces
 * @pre pointer to game NON NULL, file with space
 * @post game_get_num_executed_commands(game) == 5
 */
void test3_game_management_load();

/**
 * @test Test game_management loading of spaces
 * @pre pointer to game NON NULL, file with space with all its fields
 * @post game_management_load(game, GAMERDRFILE) == OK
 */
void test4_game_management_load();

/**
 * @test Test game_management loading of spaces
 * @pre pointer to game NON NULL, file with space with all its fields
 * @post game_get_space_id_at(game, 0) == 11
 */
void test5_game_management_load();

/**
 * @test Test game_management loading of enemies
 * @pre pointer to game NON NULL, file with enemy
 * @post game_management_load(game, GAMERDRFILE) == OK
 */
void test6_game_management_load();

/**
 * @test Test game_management loading of enemies
 * @pre pointer to game NON NULL, file with enemy
 * @post game_get_enemy_id_at(game, 0) == 2
 */
void test7_game_management_load();

/**
 * @test Test game_management loading of objects
 * @pre pointer to game NON NULL, file with object
 * @post game_management_load(game, GAMERDRFILE) == OK
 */
void test8_game_management_load();

/**
 * @test Test game_management loading of objects
 * @pre pointer to game NON NULL, file with object
 * @post game_get_object_id_at(game, 0) == 37
 */
void test9_game_management_load();

/**
 * @test Test game_management loading of links
 * @pre pointer to game NON NULL, file with link
 * @post game_management_load(game, GAMERDRFILE) == OK
 */
void test10_game_management_load();

/**
 * @test Test game_management loading of links
 * @pre pointer to game NON NULL, file with link
 * @post game_get_link_id_at(game, 0) == 32
 */
void test11_game_management_load();

/**
 * @test Test game_management loading of player
 * @pre pointer to game NON NULL, file with player
 * @post game_management_load(game, GAMERDRFILE) == OK
 */
void test12_game_management_load();

/**
 * @test Test game_management loading of player
 * @pre pointer to game NON NULL, file with player
 * @post game_get_player(game) != NULL
 */
void test13_game_management_load();

/**
 * @test Test game_management loading of general game data
 * @pre pointer to game NON NULL, file with all game data
 * @post game_management_load(game, GAMERDRFILE) == OK
 */
void test14_game_management_load();

/**
 * @test Test game_management saving of the spaces
 * @pre pointer to game NULL
 * @post game_management_save(game, GAMEWTRFILE) == ERROR
 */
void test1_game_management_save();

/**
 * @test Test game_management saving of spaces
 * @pre pointer to game NON NULL, file with space
 * @post game_management_save(game, GAMEWTRFILE) == OK
 */
void test2_game_management_save();

/**
 * @test Test game_management saving of spaces
 * @pre pointer to game NON NULL, file with space
 * @post game_get_num_executed_commands(game) == 5
 */
void test3_game_management_save();

/**
 * @test Test game_management saving of spaces
 * @pre pointer to game NON NULL, file with space
 * @post game_management_save(game, GAMEWTRFILE) == OK
*/
void test4_game_management_save();

/**
* @test Test game_management saving of spaces
* @pre pointer to game NON NULL, file with space
* @post game_get_space_id_at(game, 0) == 11
*/
void test5_game_management_save();

/**
* @test Test game_management saving of enemies
* @pre pointer to game NON NULL, file with enemy
* @post game_management_save(game, GAMEWTRFILE) == OK
*/
void test6_game_management_save();

/**
* @test Test game_management saving of enemies
* @pre pointer to game NON NULL, file with enemy
* @post game_get_enemy_id_at(game, 0) == 2
*/
void test7_game_management_save();

/**
* @test Test game_management saving of objects
* @pre pointer to game NON NULL, file with object
* @post game_management_save(game, GAMEWTRFILE) == OK
*/
void test8_game_management_save();

/**
* @test Test game_management saving of objects
* @pre pointer to game NON NULL, file with object
* @post game_get_object_id_at(game, 0) == 37
*/
void test9_game_management_save();

/**
* @test Test game_management saving of links
* @pre pointer to game NON NULL, file with link
* @post game_management_save(game, GAMEWTRFILE) == OK
*/
void test10_game_management_save();

/**
* @test Test game_management saving of link
* @pre pointer to game NON NULL, file with link
* @post game_get_link_id_at(game, 0) == 32
*/
void test11_game_management_save();

/**
* @test Test game_management saving of player
* @pre pointer to game NON NULL, file with player
* @post game_management_save(game, GAMEWTRFILE) == OK
*/
void test12_game_management_save();

/**
* @test Test game_management saving of player
* @pre pointer to game NON NULL, file with player
* @post game_get_player(game) != NULL
*/
void test13_game_management_save();

/**
* @test Test game_management saving of general data
* @pre pointer to game NON NULL, file with general data
* @post game_management_save(game, GAMEWTRFILE) == OK
*/
void test14_game_management_save();

#endif