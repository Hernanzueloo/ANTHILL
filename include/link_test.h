/** 
 * @brief It declares the tests for the link module
 * 
 * @file link_test.h
 * @author Javier San Andres
 * @version 3.0 
 * @date 19-03-2023
 * @copyright GNU Public License
 */

#ifndef link_TEST_H
#define link_TEST_H

/**
 * @test Test link creation
 * @pre id != NO_ID
 * @post Non NULL pointer to link
 */
void test1_link_create();

/**
 * @test Test link creation
 * @pre id != NO_ID
 * @post Link_id == Supplied ID
 */
void test2_link_create();

/**
 * @test Test link creation
 * @pre id == NO_ID
 * @post NULL pointer to link
 */
void test3_link_create();

/**
 * @test Test function for link_id getting
 * @pre pointer to link NON NULL
 * @post link_ID == Supplied link Id
 */
void test1_link_get_id();

/**
 * @test Test function for link_id getting
 * @pre pointer to link NULL
 * @post link_ID == NO_ID
 */
void test2_link_get_id();

/**
 * @test Test function for link_name getting
 * @pre pointer to link, link_name NON NULL both
 * @post Output==link_name
 */
void test1_link_get_name();

/**
 * @test Test function for link_name getting
 * @pre pointer to link NON NULL, link_name NULL
 * @post Output==NULL
 */
void test2_link_get_name();

/**
 * @test Test function for link_name setting
 * @pre String with link name NON NULL
 * @post Ouput==OK 
 */
void test1_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre pointer to link = NULL 
 * @post Output==ERROR
 */
void test2_link_set_name();

/**
 * @test Test function for link_name setting
 * @pre pointer to link_name = NULL (pointer to link = NON NULL) 
 * @post Output==ERROR
 */
void test3_link_set_name();

/**
 * @test Test function for link_origin setting
 * @pre pointer to link NON NULL, origin_id != NO_ID
 * @post Output==OK
 */
void test1_link_set_origin();

/**
 * @test Test function for link_origin setting
 * @pre pointer to link NULL
 * @post Output==ERROR
 */
void test2_link_set_origin();

/**
 * @test Test function for link_origin setting
 * @pre pointer to link NON NULL, origin_id = NO_ID
 * @post Output==ERROR
 */
void test3_link_set_origin();

/**
 * @test Test function for link_origin getting
 * @pre pointer to link NON NULL
 * @post Output==Supplied ID
 */
void test1_link_get_origin();

/**
 * @test Test function for link_origin getting
 * @pre pointer to link NULL
 * @post Output==NO_ID
 */
void test2_link_get_origin();

/**
 * @test Test function for link_destination setting
 * @pre pointer to link NON NULL, destination_id != NO_ID
 * @post Output==OK
 */
void test1_link_set_destination();

/**
 * @test Test function for link_destination setting
 * @pre pointer to link NULL
 * @post Output==ERROR
 */
void test2_link_set_destination();

/**
 * @test Test function for link_destination setting
 * @pre pointer to link NON NULL, destination_id = NO_ID
 * @post Output==ERROR
 */
void test3_link_set_destination();

/**
 * @test Test function for link_destination getting
 * @pre pointer to link NON NULL
 * @post Output==Supplied ID
 */
void test1_link_get_destination();

/**
 * @test Test function for link_destination getting
 * @pre pointer to link NULL
 * @post Output==NO_ID
 */
void test2_link_get_destination();

/**
 * @test Test function for link_direction getting
 * @pre pointer to link NON NULL
 * @post Output==Supplied direction
 */
void test1_link_get_direction();

/**
 * @test Test function for link_direction getting
 * @pre pointer to link NULL
 * @post Output==NO_DIR
 */
void test2_link_get_direction();

/**
 * @test Test function for link_direction setting
 * @pre pointer to link NON NULL, link_direction != NO_DIR
 * @post Output==OK
 */
void test1_link_set_direction();

/**
 * @test Test function for link_direction setting
 * @pre pointer to link NULL, link_direction != NO_DIR
 * @post Output==ERROR
 */
void test2_link_set_direction();

/**
 * @test Test function for link_direction setting
 * @pre pointer to link NON NULL, link_direction == NO_DIR
 * @post Output==ERROR
 */
void test3_link_set_direction();


/**
 * @test Test function for link_status getting
 * @pre pointer to link NON NULL
 * @post Output==Supplied status
 */
void test1_link_get_status();

/**
 * @test Test function for link_status getting
 * @pre pointer to link NULL
 * @post Output==CLOSE
 */
void test2_link_get_status();

/**
 * @test Test function for link_status setting
 * @pre pointer to link NON NULL, link_status == CLOSE
 * @post Output==OK
 */
void test1_link_set_status();

/**
 * @test Test function for link_status setting
 * @pre pointer to link NON NULL, link_status == OPEN
 * @post Output==OK
 */
void test2_link_set_status();

/**
 * @test Test function for link_status setting
 * @pre pointer to link NULL
 * @post Output==ERROR
 */
void test3_link_set_status();


/**
 * @test Test function for link printing
 * @pre pointer to link NON NULL
 * @post Output==OK
 */
void test1_link_print();

/**
 * @test Test function for link printing
 * @pre pointer to link NULL
 * @post Output==ERROR
 */
void test2_link_print();

/**
 * @test Test function for link printing
 * @pre pointer to link NON NULL, file NON NULL
 * @post Output==ERROR
 */
void test3_link_print();

#endif