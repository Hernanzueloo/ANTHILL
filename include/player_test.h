/** 
 * @brief It declares the tests for the player module
 * 
 * @file player_test.h
 * @author Diego Rodríguez Ortiz
 * @version 3.0 
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @test Test player creation
 * @pre id != NO_ID
 * @post Non NULL pointer to player
 */
void test1_player_create();

/**
 * @test Test player creation
 * @pre player ID 
 * @post player_ID == Supplied player Id
 */
void test2_player_create();

/**
 * @test Test player creation
 * @pre id == NO_ID
 * @post NULL pointer to player
 */
void test3_player_create();

/**
 * @test Test function for player_id getting
 * @pre pointer to player NON NULL, valid player ID
 * @post player_ID == Supplied player Id
 */
void test1_player_get_id();

/**
 * @test Test function for player_id getting
 * @pre pointer to player NULL
 * @post player_ID == NO_ID
 */
void test2_player_get_id();

/**
 * @test Test function for player_name getting
 * @pre pointer to player, player_name NON NULL both
 * @post Output==player_name
 */
void test1_player_get_name();

/**
 * @test Test function for player_name getting
 * @pre pointer to player NULL
 * @post Output==NULL
 */
void test2_player_get_name();

/**
 * @test Test function for player_name setting
 * @pre pointer to player, player_name NON NULL both
 * @post Ouput==OK 
 */
void test1_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre pointer to player = NULL 
 * @post Output==ERROR
 */
void test2_player_set_name();

/**
 * @test Test function for player_name setting
 * @pre pointer to player_name = NULL (pointer to player = NON NULL) 
 * @post Output==ERROR
 */
void test3_player_set_name();

/**
 * @test Test function for player_location setting
 * @pre pointer to player NON NULL and valid location
 * @post Output==OK
 */
void test1_player_set_location();

/**
 * @test Test function for player_location setting
 * @pre pointer to player NULL and valid location
 * @post Output==ERROR
 */
void test2_player_set_location();

/**
 * @test Test function for player_location setting
 * @pre pointer to player NON NULL, space_id = NO_ID
 * @post Output==ERROR
 */
void test3_player_set_location();

/**
 * @test Test function for player_location getting
 * @pre pointer to player NON NULL
 * @post Output==Supplied ID
 */
void test1_player_get_location();

/**
 * @test Test function for player_location getting
 * @pre pointer to player NULL
 * @post Output==NO_ID
 */
void test2_player_get_location();

/**
 * @test Test function for player_health getting
 * @pre pointer to player NON NULL
 * @post Output==Supplied Health
 */
void test1_player_get_health();

/**
 * @test Test function for player_health getting
 * @pre pointer to player NULL
 * @post Output==-1 ( NO_HEALTH)
 */
void test2_player_get_health();

/**
 * @test Test function for player_health setting
 * @pre pointer to player NON NULL, new_player_health >= 0
 * @post Output==OK
 */
void test1_player_set_health();

/**
 * @test Test function for player_health setting
 * @pre pointer to player NULL, new_player_health >=0
 * @post Output==ERROR
 */
void test2_player_set_health();

/**
 * @test Test function for player_health setting
 * @pre pointer to player NON NULL, new_player_health < 0
 * @post Output==ERROR
 */
void test3_player_set_health();

/**
 * @test Test function for player_objects getting
 * @pre pointer to player NON NULL with one object (ID_OBJ)
 * @post Output==ID_OBJ (Array with ID_OBJ as first element)
 */
void test1_player_get_objects();

/**
 * @test Test function for player_objects getting
 * @pre pointer to player NON NULL with no object
 * @post Output==NULL
 */
void test2_player_get_objects();

/**
 * @test Test function for player_objects getting
 * @pre pointer to player NULL 
 * @post Output==NULL
 */
void test3_player_get_objects();

/**
 * @test Test function for player_objects getting
 * @pre pointer to player NON NULL and a NULL pointer to the number of elemnts returned
 * @post Output==NULL
 */
void test4_player_get_objects();

/**
 * @test Test function for player_objects adding
 * @pre pointer to player NON NULL and a valid ID
 * @post Output==OK
 */
void test1_player_add_objects();

/**
 * @test Test function for player_objects adding
 * @pre pointer to player NON NULL and a valid ID
 * @post Output==OK and object_get_objects returns the ID added
 */
void test2_player_add_objects();

/**
 * @test Test function for player_objects adding
 * @pre pointer to player NON NULL and a repited ID
 * @post Output==OK
 */
void test3_player_add_objects();

/**
 * @test Test function for player_objects adding
 * @pre pointer to player NON NULL and a invalid ID
 * @post Output==ERROR
 */
void test4_player_add_objects();

/**
 * @test Test function for player_objects adding
 * @pre pointer to player NULL and a invalid ID
 * @post Output==ERROR
 */
void test5_player_add_objects();

/**
 * @test Test function for player_objects adding
 * @pre pointer to player NON NULL and a valid ID twice
 * @post Output==OK and numbero of objects == 2
 */
void test6_player_add_objects();

/**
 * @test Test function for player_objects adding
 * @pre pointer to player NON NULL with a max object 2 and a valid diferent ID three times
 * @post Output==ERROR
 */
void test7_player_add_objects();

/**
 * @test Test function for player_objects removing
 * @pre pointer to player NON NULL with a an Object and a valid ID
 * @post Output==OK and num_objects = 0
 */
void test1_player_remove_objects();

/**
 * @test Test function for player_objects removing
 * @pre pointer to player NULL and a valid ID (previously added to the player)
 * @post Output==ERROR and num_objects = 1
 */
void test2_player_remove_objects();

/**
 * @test Test function for player_objects removing
 * @pre pointer to player NON NULL and a invalid ID 
 * @post Output==ERROR
 */
void test3_player_remove_objects();

/**
 * @test Test function for player_objects removing
 * @pre pointer to player NON NULL and a valid ID (not previously added to the player)
 * @post Output==OK  and num_objects = 1
 */
void test4_player_remove_objects();

/**
 * @test Test function for player_objects removing
 * @pre pointer to player NON NULL without objects and a valid ID (not previously added to the player)
 * @post Output==OK  and num_objects = 0
 */
void test5_player_remove_objects();

/**
 * @test Test function for player_objects set max
 * @pre pointer to player NON NULL and a valid max value (MAX_OBJ)
 * @post Output==OK  and max_objects = MAX_OBJ
 */
void test1_player_set_max_objects();

/**
 * @test Test function for player_objects set max
 * @pre pointer to player NON NULL with a max objects of MAX_OBJ and a invalid max value (-1)
 * @post Output==ERROR  and max_objects = MAX_OBJ
 */
void test2_player_set_max_objects();

/**
 * @test Test function for player_objects set max
 * @pre pointer to player NULL and a valid max value (MAX_OBJ)
 * @post Output==ERROR 
 */
void test3_player_set_max_objects();

/**
 * @test Test function for player_objects get max
 * @pre pointer to player NON NULL with max objects = MAX_OBJ 
 * @post Output== MAX_OBJ
 */
void test1_player_get_max_objects();

/**
 * @test Test function for player_objects get max
 * @pre pointer to player NULL 
 * @post Output== -1 (ERROR)
 */
void test2_player_get_max_objects();

/**
 * @test Test function for player  get num of objects
 * @pre pointer to player NON NULL with one objects
 * @post Output== 1
 */
void test1_player_get_num_objects();

/**
 * @test Test function for player  get num of objects
 * @pre pointer to player NULL 
 * @post Output== -1 (ERROR)
 */
void test2_player_get_num_objects();

/**
 * @test Test function for player printing
 * @pre pointer to player NON NULL
 * @post Output==OK
 */
void test1_player_print();

/**
 * @test Test function for player printing
 * @pre pointer to player NULL
 * @post Output==ERROR
 */
void test2_player_print();

/**
 * @test Test function for player printing
 * @pre pointer to player NON NULL, file NON NULL
 * @post Output==ERROR
 */
void test3_player_print();

/**
 * @test Test function for player_type getting
 * @pre pointer to player NON NULL
 * @post Output==Supplied Type
 */
void test1_player_get_type();

/**
 * @test Test function for player_type getting
 * @pre pointer to player NULL
 * @post Output==-1 ( NO_TYPE)
 */
void test2_player_get_type();

/**
 * @test Test function for player_type setting
 * @pre pointer to player NON NULL, new_player_type >= 0
 * @post Output==OK
 */
void test1_player_set_type();

/**
 * @test Test function for player_type setting
 * @pre pointer to player NULL, new_player_type >=0
 * @post Output==ERROR
 */
void test2_player_set_type();

/**
 * @test Test function for player_type setting
 * @pre pointer to player NON NULL, new_player_type < 0
 * @post Output==ERROR
 */
void test3_player_set_type();


#endif