/** 
 * @brief It declares the tests for the object module
 * 
 * @file object_test.h
 * @author Diego Rodríguez Ortiz
 * @version 3.0 
 * @date 19-03-2023
 * @copyright GNU Public License
 */

#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

/**
 * @test Test object creation
 * @pre id != NO_ID
 * @post Non NULL pointer to object
 */
void test1_object_create();

/**
 * @test Test object creation
 * @pre object ID 
 * @post object_ID == Supplied object Id
 */
void test2_object_create();

/**
 * @test Test object creation
 * @pre id == NO_ID
 * @post NULL pointer to object
 */
void test3_object_create();

/**
 * @test Test function for object_id getting
 * @pre pointer to object NON NULL, valid object ID 
 * @post object_ID == Supplied object Id
 */
void test1_object_get_id();

/**
 * @test Test function for object_id getting
 * @pre pointer to object NULL
 * @post object_ID == NO_ID
 */
void test2_object_get_id();

/**
 * @test Test function for object_name getting
 * @pre pointer to object NON NULL
 * @post Output==object_name
 */
void test1_object_get_name();

/**
 * @test Test function for object_name getting
 * @pre pointer to object NULL
 * @post Output==NULL
 */
void test2_object_get_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object, object_name NON NULL both
 * @post Ouput==OK 
 */
void test1_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object = NULL, object_name NON NULL
 * @post Output==ERROR
 */
void test2_object_set_name();

/**
 * @test Test function for object_name setting
 * @pre pointer to object_name = NULL (pointer to object = NON NULL) 
 * @post Output==ERROR
 */
void test3_object_set_name();

/**
 * @test Test function for object_location getting
 * @pre pointer to object NON NULL
 * @post Output==Supplied ID
 */
void test1_object_get_location();

/**
 * @test Test function for object_location getting
 * @pre pointer to object NULL
 * @post Output==NO_ID
 */
void test2_object_get_location();

/**
 * @test Test function for object_location setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_set_location();

/**
 * @test Test function for object_location setting
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_set_location();

/**
 * @test Test function for object_location setting
 * @pre pointer to object NON NULL, space_id = NO_ID
 * @post Output==ERROR
 */
void test3_object_set_location();



/**
 * @test Test function for object_hidden getting
 * @pre pointer to object NON NULL
 * @post Output== TRUE
 */
void test1_object_get_hidden();

/**
 * @test Test function for object_hidden getting
 * @pre pointer to object NULL
 * @post Output==FALSE
 */
void test2_object_get_hidden();

/**
 * @test Test function for object_hidden setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_set_hidden();

/**
 * @test Test function for object_hidden setting
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_set_hidden();

/**
 * @test Test function for object_hidden setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test3_object_set_hidden();


/**
 * @test Test function for object_movable getting
 * @pre pointer to object NON NULL
 * @post Output== TRUE
 */
void test1_object_get_movable();

/**
 * @test Test function for object_movable getting
 * @pre pointer to object NULL
 * @post Output==FALSE
 */
void test2_object_get_movable();

/**
 * @test Test function for object_movable setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_set_movable();

/**
 * @test Test function for object_hidden setting
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_set_movable();

/**
 * @test Test function for object_hidden setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test3_object_set_movable();


/**
 * @test Test function for object_dependency getting
 * @pre pointer to object NON NULL
 * @post Output== Supplied ID
 */
void test1_object_get_dependency();

/**
 * @test Test function for object_dependency getting
 * @pre pointer to object NULL
 * @post Output==NO_ID
 */
void test2_object_get_dependency();

/**
 * @test Test function for object_dependency setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_set_dependency();

/**
 * @test Test function for object_dependency setting
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_set_dependency();

/**
 * @test Test function for object_dependency setting
 * @pre pointer to object NON NULL, dependency=NO_ID
 * @post Output==OK
 */
void test3_object_set_dependency();





/**
 * @test Test function for object_open getting
 * @pre pointer to object NON NULL
 * @post Output== Supplied ID
 */
void test1_object_get_open();

/**
 * @test Test function for object_open getting
 * @pre pointer to object NULL
 * @post Output==NO_ID
 */
void test2_object_get_open();

/**
 * @test Test function for object_open setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_set_open();

/**
 * @test Test function for object_open setting
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_set_open();

/**
 * @test Test function for object_open setting
 * @pre pointer to object NON NULL, open=NO_ID
 * @post Output==OK
 */
void test3_object_set_open();




/**
 * @test Test function for object_illuminate getting
 * @pre pointer to object NON NULL
 * @post Output== TRUE
 */
void test1_object_get_illuminate();

/**
 * @test Test function for object_illuminate getting
 * @pre pointer to object NULL
 * @post Output==FALSE
 */
void test2_object_get_illuminate();

/**
 * @test Test function for object_illuminate setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_set_illuminate();

/**
 * @test Test function for object_illuminate setting
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_set_illuminate();

/**
 * @test Test function for object_illuminate setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test3_object_set_illuminate();




/**
 * @test Test function for object_turnedon getting
 * @pre pointer to object NON NULL
 * @post Output== TRUE
 */
void test1_object_get_turnedon();

/**
 * @test Test function for object_turnedon getting
 * @pre pointer to object NULL
 * @post Output==FALSE
 */
void test2_object_get_turnedon();

/**
 * @test Test function for object_turnedon setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_set_turnedon();

/**
 * @test Test function for object_turnedon setting
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_set_turnedon();

/**
 * @test Test function for object_turnedon setting
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test3_object_set_turnedon();



/**
 * @test Test function for object_description getting
 * @pre pointer to object NON NULL and NON NULL description
 * @post Output==Supplied description
 */
void test1_object_get_description();

/**
 * @test Test function for object_description getting
 * @pre pointer to object NULL
 * @post Output==NULL
 */
void test2_object_get_description();

/**
 * @test Test function for object_description setting
 * @pre pointer to object NON NULL, new_object_description NON NULL
 * @post Output==OK
 */
void test1_object_set_description();

/**
 * @test Test function for object_description setting
 * @pre pointer to object NULL,  new_object_description NON NULL
 * @post Output==ERROR
 */
void test2_object_set_description();

/**
 * @test Test function for object_description setting
 * @pre pointer to object NON NULL, new_object_description NULL
 * @post Output==ERROR
 */
void test3_object_set_description();

/**
 * @test Test function for object printing
 * @pre pointer to object NON NULL
 * @post Output==OK
 */
void test1_object_print();

/**
 * @test Test function for object printing
 * @pre pointer to object NULL
 * @post Output==ERROR
 */
void test2_object_print();

/**
 * @test Test function for object printing
 * @pre pointer to object NON NULL, file NON NULL
 * @post Output==ERROR
 */
void test3_object_print();

#endif