/** 
 * @brief It declares the tests for the command module
 * 
 * @file command_test.h
 * @author David Brenchley
 * @version 3.0 
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H

/**
 * @test Test command creation
 * @post cmds != NULL
 */
void test1_commands_create();
/**
 * @test Test command creation
 * @pre cmds != NULL
 * @post Executed command == NO_CMD
 */
void test2_commands_create();
/**
 * @test Test command creation
 * @pre cmds != NULL
 * @post Num of arguments == 0
 */
void test3_commands_create();
/**
 * @test Test command creation
 * @pre cmds != NULL
 * @post Command arguments == NO_CMD
 */
void test4_commands_create();
/**
 * @test Test get executed command
 * @pre cmds == NULL
 * @post executed command == NO_CMD
 */
void test1_commands_get_cmd();
/**
 * @test Test get executed command
 * @pre cmds != NULL, pointer to file != NULL
 * @post executed command == MOVE
 */
void test2_commands_get_cmd();
/**
 * @test Test get executed command
 * @pre cmds != NULL, pointer to file != NULL
 * @post executed command == UNKOWN
 */
void test3_commands_get_cmd();
/**
 * @test Test get command arguments
 * @pre cmds == NULL
 * @post command argument == NULL
 */
void test1_commands_get_args();
/**
 * @test Test get command arguments
 * @pre cmds != NULL, pointer to file !=NULL
 * @post command argument == grain
 */
void test2_commands_get_args();
/**
 * @test Test get command arguments
 * @pre cmds != NULL, pointer to file !=NULL
 * @post command argument == NULL
 */
void test3_commands_get_args();
/**
 * @test Test get command number of arguments
 * @pre cmds == NULL
 * @post command num of argument == -1
 */
void test1_commands_get_num_args();
/**
 * @test Test get command number of arguments
 * @pre cmds != NULL, pointer to file !=NULL
 * @post command num of argument == 1
 */
void test2_commands_get_num_args();
/**
 * @test Test get command status
 * @pre cmds == NULL
 * @post command status == ERROR
 */
void test1_commands_get_status();
/**
 * @test Test get command status
 * @pre cmds != NULL,
 * @post command status == OK
 */
void test2_commands_get_status();
/**
 * @test Test set command status
 * @pre cmds == NULL
 * @post command status == ERROR
 */
void test1_commands_set_status();
/**
 * @test Test set command status
 * @pre cmds != NULL,
 * @post command status == ERROR
 */
void test2_commands_set_status();
/**
 * @test Test get user's input
 * @pre cmds != NULL, pointer to file !=NULL
 * @post executed command == NO_CMD
 */
void test1_commands_get_user_input();
/**
 * @test Test get user's input
 * @pre cmds != NULL, pointer to file !=NULL
 * @post argument = grain, executed command == TAKE, num of args == 1
 */
void test2_commands_get_user_input();
/**
 * @test Test get command direction
 * @pre cmds == NULL
 * @post command direction == NO_DIR
 */
void test1_commands_get_direction();
/**
 * @test Test get command direction
 * @pre cmds != NULL, pointer to file !=NULL
 * @post command direction == NO_DIR
 */
void test2_commands_get_direction();
/**
 * @test Test get command direction
 * @pre cmds != NULL, pointer to file !=NULL
 * @post command direction == SOUTH
 */
void test3_commands_get_direction();
/**
 * @test Test get formatted command
 * @pre cmds == NULL
 * @post formatted command == NULL
 */
void test1_commands_get_formatted_cmd();
/**
 * @test Test get formatted command
 * @pre cmds != NULL, pointer to file !=NULL
 * @post formatted command == move south
 */
void test2_commands_get_formatted_cmd();
/**
 * @test Test get formatted command
 * @pre cmds != NULL, pointer to file !=NULL
 * @post formatted command == attack
 */
void test3_commands_get_formatted_cmd();

/**
 * @test Test get formatted direction
 * @pre cmds == NULL
 * @post formatted direction == NULL
 */
void test1_commands_get_formatted_direction();
/**
 * @test Test get formatted direction
 * @pre cmds != NULL, pointer to file !=NULL
 * @post formatted direction == south
 */
void test2_commands_get_formatted_direction();
/**
 * @test Test get formatted direction
 * @pre cmds != NULL, pointer to file !=NULL
 * @post formatted direction == NULL
 */
void test3_commands_get_formatted_direction();
#endif