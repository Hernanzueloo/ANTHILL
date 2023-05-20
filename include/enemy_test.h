/** 
 * @brief It declares the tests for the enemy module
 * 
 * @file enemy_test.h
 * @author Javier San Andres
 * @version 3.0 
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef ENEMY_TEST_H
#define ENEMY_TEST_H

/**
 * @test Test enemy creation
 * @pre id != NO_ID
 * @post Non NULL pointer to enemy
 */
void test1_enemy_create();

/**
 * @test Test enemy creation
 * @pre Enemy ID 
 * @post Enemy_ID == Supplied Enemy Id
 */
void test2_enemy_create();

/**
 * @test Test enemy creation
 * @pre id == NO_ID
 * @post NULL pointer to enemy
 */
void test3_enemy_create();

/**
 * @test Test function for enemy_id getting
 * @pre pointer to enemy NON NULL, enemy ID NON NULL
 * @post enemy_ID == Supplied enemy Id
 */
void test1_enemy_get_id();

/**
 * @test Test function for enemy_id getting
 * @pre pointer to enemy NULL
 * @post enemy_ID == NO_ID
 */
void test2_enemy_get_id();

/**
 * @test Test function for enemy_name getting
 * @pre pointer to enemy, enemy_name NON NULL both
 * @post Output==enemy_name
 */
void test1_enemy_get_name();

/**
 * @test Test function for enemy_name getting
 * @pre pointer to enemy NON NULL, enemy_name NULL
 * @post Output==NULL
 */
void test2_enemy_get_name();

/**
 * @test Test function for enemy_name setting
 * @pre String with enemy name
 * @post Ouput==OK 
 */
void test1_enemy_set_name();

/**
 * @test Test function for enemy_name setting
 * @pre pointer to enemy = NULL 
 * @post Output==ERROR
 */
void test2_enemy_set_name();

/**
 * @test Test function for enemy_name setting
 * @pre pointer to enemy_name = NULL (pointer to enemy = NON NULL) 
 * @post Output==ERROR
 */
void test3_enemy_set_name();

/**
 * @test Test function for enemy_location setting
 * @pre pointer to enemy NON NULL
 * @post Output==OK
 */
void test1_enemy_set_location();

/**
 * @test Test function for enemy_location setting
 * @pre pointer to enemy NULL
 * @post Output==ERROR
 */
void test2_enemy_set_location();

/**
 * @test Test function for enemy_location setting
 * @pre pointer to enemy NON NULL, space_id = NO_ID
 * @post Output==ERROR
 */
void test3_enemy_set_location();

/**
 * @test Test function for enemy_location getting
 * @pre pointer to enemy NON NULL
 * @post Output==Supplied ID
 */
void test1_enemy_get_location();

/**
 * @test Test function for enemy_location getting
 * @pre pointer to enemy NULL
 * @post Output==NO_ID
 */
void test2_enemy_get_location();

/**
 * @test Test function for enemy_health getting
 * @pre pointer to enemy NON NULL
 * @post Output==Supplied Health
 */
void test1_enemy_get_health();

/**
 * @test Test function for enemy_health getting
 * @pre pointer to enemy NULL
 * @post Output==-1
 */
void test2_enemy_get_health();

/**
 * @test Test function for enemy_health setting
 * @pre pointer to enemy NON NULL, new_enemy_health >= 0
 * @post Output==OK
 */
void test1_enemy_set_health();

/**
 * @test Test function for enemy_health setting
 * @pre pointer to enemy NULL, new_enemy_health >=0
 * @post Output==ERROR
 */
void test2_enemy_set_health();

/**
 * @test Test function for enemy_health setting
 * @pre pointer to enemy NON NULL, new_enemy_health < 0
 * @post Output==ERROR
 */
void test3_enemy_set_health();

/**
 * @test Test function for enemy printing
 * @pre pointer to enemy NON NULL
 * @post Output==OK
 */
void test1_enemy_print();

/**
 * @test Test function for enemy printing
 * @pre pointer to enemy NULL
 * @post Output==ERROR
 */
void test2_enemy_print();

/**
 * @test Test function for enemy printing
 * @pre pointer to enemy NON NULL, file NON NULL
 * @post Output==ERROR
 */
void test3_enemy_print();

/**
 * @test Test function for enemy_edesc setting
 * @pre pointer to enemy NON NULL, pointer to edesc NON NULL
 * @post Output==OK
 */
void test1_enemy_set_edesc();

/**
 * @test Test function for enemy_edesc setting
 * @pre pointer to enemy NON NULL, pointer to edesc NULL
 * @post Output==ERROR
 */
void test2_enemy_set_edesc();

/**
 * @test Test function for enemy_edesc setting
 * @pre pointer to enemy NULL, pointer to edesc NON NULL
 * @post Output==ERROR
 */
void test3_enemy_set_edesc();

/**
 * @test Test function for enemy_edesc getting
 * @pre pointer to enemy NON NULL with edesc in it
 * @post Output!=NULL
 */
void test1_enemy_get_edesc();

/**
 * @test Test function for enemy_edesc getting
 * @pre pointer to enemy NON NULL with no edesc in it
 * @post Output==NULL
 */
void test2_enemy_get_edesc();

/**
 * @test Test function for enemy_edesc getting
 * @pre pointer to enemy NULL
 * @post Output==NULL
 */
void test3_enemy_get_edesc();


#endif