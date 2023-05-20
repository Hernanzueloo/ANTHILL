/** 
 * @brief It declares the tests for the set module
 * 
 * @file set_test.h
 * @author Javier San Andres
 * @version 3.0 
 * @date 19-03-2023
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @test Test set creation
 * @pre anything needed
 * @post Non NULL pointer to set 
 */
void test1_set_create();

/**
 * @test Test function for the set's emptiness
 * @pre pointer to set NON NULL
 * @post Output==TRUE
 */
void test1_set_is_empty();

/**
 * @test Test function for the set's emptiness
 * @pre pointer to set NON NULL and set with one element
 * @post Output==FALSE
 */
void test2_set_is_empty();

/**
 * @test Test function for the set's emptiness
 * @pre pointer to set NULL
 * @post Output==TRUE
 */
void test3_set_is_empty();

/**
 * @test Test function for set_id adding
 * @pre pointer to set NON NULL and id != NO_ID
 * @post Output==OK
 */
void test1_set_add_id();

/**
 * @test Test function for set_id adding
 * @pre pointer to set NON NULL with an element and id == contained id
 * @post Output==OK
 */
void test2_set_add_id();

/**
 * @test Test function for set_id adding
 * @pre pointer to set NON NULL with an element and id == contained id
 * @post Output==1
 */
void test3_set_add_id();

/**
 * @test Test function for set_id adding
 * @pre pointer to set NULL 
 * @post Output==ERROR
 */
void test4_set_add_id();

/**
 * @test Test function for set_id adding
 * @pre pointer to set NON NULL and id == NO_ID
 * @post Output==ERROR
 */
void test5_set_add_id();

/**
 * @test Test function for set_id massive adding
 * @pre pointer to set NON NULL, pointer to Id NON NULL, num_ids > 0
 * @post Output==OK
 */
void test1_set_massive_add();

/**
 * @test Test function for set_id massive adding
 * @pre pointer to set NON NULL, pointer to Id NON NULL, num_ids > 0, 10 different ids
 * @post Output==10
 */
void test2_set_massive_add();

/**
 * @test Test function for set_id massive adding
 * @pre pointer to set NULL
 * @post Output==ERROR
 */
void test3_set_massive_add();

/**
 * @test Test function for set_id massive adding
 * @pre pointer to set NON NULL, pointer to Id NULL
 * @post Output==ERROR
 */
void test4_set_massive_add();

/**
 * @test Test function for set_id massive adding
 * @pre pointer to set NON NULL, pointer to Id NON NULL, num_ids < 0
 * @post Output==ERROR
 */
void test5_set_massive_add();

/**
 * @test Test function for set_id deletion
 * @pre pointer to set NON NULL, id = contained Id
 * @post Output==OK
 */
void test1_set_delete_id();

/**
 * @test Test function for set_id deletion
 * @pre pointer to set NON NULL, id != contained Id
 * @post Output==OK
 */
void test2_set_delete_id();

/**
 * @test Test function for set_id deletion
 * @pre pointer to set NON NULL with no elements, id != NO_ID
 * @post Output==OK
 */
void test3_set_delete_id();

/**
 * @test Test function for set_id deletion
 * @pre pointer to set NULL
 * @post Output==ERROR
 */
void test4_set_delete_id();

/**
 * @test Test function for set_id deletion
 * @pre pointer to set NON NULL, id == NO_iD
 * @post Output==ERROR
 */
void test5_set_delete_id();

/**
 * @test Test function for set_id number of ids
 * @pre pointer to set NON NULL with an element
 * @post Output==1
 */
void test1_set_get_number_ids();

/**
 * @test Test function for set_id number of ids
 * @pre pointer to set NULL
 * @post Output==-1
 */
void test2_set_get_number_ids();

/**
 * @test Test function for set_id containing
 * @pre pointer to set NON NULL, id = contained id
 * @post Output==TRUE
 */
void test1_set_contains_id();

/**
 * @test Test function for set_id containing
 * @pre pointer to set NON NULL, id != contained id
 * @post Output==FALSE
 */
void test2_set_contains_id();

/**
 * @test Test function for set_id containing
 * @pre pointer to set NON NULL, id == NO_ID
 * @post Output==FALSE
 */
void test3_set_contains_id();

/**
 * @test Test function for set_id containing
 * @pre pointer to set NULL
 * @post Output==FALSE
 */
void test4_set_contains_id();

/**
 * @test Test function for set_id getting all
 * @pre pointer to non-empty set NON NULL, pointer to num NON NULL
 * @post Output!=NULL
 */
void test1_set_get_all_ids();

/**
 * @test Test function for set_id getting all
 * @pre pointer to empty set NON NULL, pointer to num NON NULL
 * @post Output==NULL
 */
void test2_set_get_all_ids();

/**
 * @test Test function for set_id getting all
 * @pre pointer to set NULL
 * @post Output==NULL
 */
void test3_set_get_all_ids();

/**
 * @test Test function for set_id getting all
 * @pre pointer to set NON NULL, pointer to num NULL
 * @post Output==NULL
 */
void test4_set_get_all_ids();

/**
 * @test Test function for set printing
 * @pre pointer to set NON NULL, pointer to file NON NULL
 * @post Output==OK
 */
void test1_set_print();

/**
 * @test Test function for set printing
 * @pre pointer to set NULL
 * @post Output==ERROR
 */
void test2_set_print();

/**
 * @test Test function for set printing
 * @pre pointer to set NON NULL, pointer to file NULL
 * @post Output==ERROR
 */
void test3_set_print();


#endif