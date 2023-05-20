/** 
 * @brief It declares the tests for the inventory module
 * 
 * @file inventory_test.h
 * @author Alejandro Garcia
 * @version 3.0 
 * @date 24-03-2023
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @test Test inventory creation
 * @pre anything needed
 * @post Non NULL pointer to inventory 
 */
void test1_inventory_create();

/**
 * @test Test function for the inventory's emptiness
 * @pre pointer to inventory NON NULL
 * @post Output==TRUE
 */
void test1_inventory_is_empty();

/**
 * @test Test function for the inventory's emptiness
 * @pre pointer to inventory NON NULL and inventory with one element
 * @post Output==FALSE
 */
void test2_inventory_is_empty();

/**
 * @test Test function for the inventory's emptiness
 * @pre pointer to inventory NULL
 * @post Output==TRUE
 */
void test3_inventory_is_empty();

/**
 * @test Test function for inventory_id adding
 * @pre pointer to inventory NON NULL and id != NO_ID
 * @post Output==OK
 */
void test1_inventory_add_id();

/**
 * @test Test function for inventory_id adding
 * @pre pointer to inventory NON NULL with an element and id == contained id
 * @post Output==OK
 */
void test2_inventory_add_id();

/**
 * @test Test function for inventory_id adding
 * @pre pointer to inventory NON NULL with an element and id == contained id
 * @post Output==1
 */
void test3_inventory_add_id();

/**
 * @test Test function for inventory_id adding
 * @pre pointer to inventory NULL 
 * @post Output==ERROR
 */
void test4_inventory_add_id();

/**
 * @test Test function for inventory_id adding
 * @pre pointer to inventory NON NULL and id == NO_ID
 * @post Output==ERROR
 */
void test5_inventory_add_id();


/**
 * @test Test function for inventory_id deletion
 * @pre pointer to inventory NON NULL, id = contained Id
 * @post Output==OK
 */
void test1_inventory_delete_id();

/**
 * @test Test function for inventory_id deletion
 * @pre pointer to inventory NON NULL, id != contained Id
 * @post Output==OK
 */
void test2_inventory_delete_id();

/**
 * @test Test function for inventory_id deletion
 * @pre pointer to inventory NON NULL with no elements, id != NO_ID
 * @post Output==OK
 */
void test3_inventory_delete_id();

/**
 * @test Test function for inventory_id deletion
 * @pre pointer to inventory NULL
 * @post Output==ERROR
 */
void test4_inventory_delete_id();

/**
 * @test Test function for inventory_id deletion
 * @pre pointer to inventory NON NULL, id == NO_iD
 * @post Output==ERROR
 */
void test5_inventory_delete_id();

/**
 * @test Test function for inventory_id number of ids
 * @pre pointer to inventory NON NULL with an element
 * @post Output==1
 */
void test1_inventory_get_number_ids();

/**
 * @test Test function for inventory_id number of ids
 * @pre pointer to inventory NULL
 * @post Output==-1
 */
void test2_inventory_get_number_ids();

/**
 * @test Test function for inventory_id containing
 * @pre pointer to inventory NON NULL, id = contained id
 * @post Output==TRUE
 */
void test1_inventory_contains_id();

/**
 * @test Test function for inventory_id containing
 * @pre pointer to inventory NON NULL, id != contained id
 * @post Output==FALSE
 */
void test2_inventory_contains_id();

/**
 * @test Test function for inventory_id containing
 * @pre pointer to inventory NON NULL, id == NO_ID
 * @post Output==FALSE
 */
void test3_inventory_contains_id();

/**
 * @test Test function for inventory_id containing
 * @pre pointer to inventory NULL
 * @post Output==FALSE
 */
void test4_inventory_contains_id();

/**
 * @test Test function for inventory_id getting all
 * @pre pointer to non-empty inventory NON NULL, pointer to num NON NULL
 * @post Output!=NULL
 */
void test1_inventory_get_all_ids();

/**
 * @test Test function for inventory_id getting all
 * @pre pointer to empty inventory NON NULL, pointer to num NON NULL
 * @post Output==NULL
 */
void test2_inventory_get_all_ids();

/**
 * @test Test function for inventory_id getting all
 * @pre pointer to inventory NULL
 * @post Output==NULL
 */
void test3_inventory_get_all_ids();

/**
 * @test Test function for inventory_id getting all
 * @pre pointer to inventory NON NULL, pointer to num NULL
 * @post Output==NULL
 */
void test4_inventory_get_all_ids();

/**
 * @test Test function for inventory printing
 * @pre pointer to inventory NON NULL, pointer to file NON NULL
 * @post Output==OK
 */
void test1_inventory_print();

/**
 * @test Test function for inventory printing
 * @pre pointer to inventory NULL
 * @post Output==ERROR
 */
void test2_inventory_print();

/**
 * @test Test function for inventory printing
 * @pre pointer to inventory NON NULL, pointer to file NULL
 * @post Output==ERROR
 */
void test3_inventory_print();

/**
 * @test Test function for inventory getting maximum number of objects it can hold
 * @pre pointer to inventory NON NULL, pointer to file NULL
 * @post Output==MAX_OBJECTS
 */
void test1_inventory_get_max_objs();

/**
 * @test Test function for inventory getting maximum number of objects it can hold
 * @pre pointer to inventory NON NULL, pointer to file NULL
 * @post Output==OK
 */
void test2_inventory_get_max_objs();

/**
 * @test Test function for inventory getting maximum number of objects it can hold
 * @pre pointer to inventory NON NULL, pointer to file NULL
 * @post Output==ERROR
 */
void test3_inventory_get_max_objs();

/**
 * @test Test function for inventory setting a newmmaximum number of objects it can hold
 * @pre pointer to inventory NON NULL, pointer to file NULL
 * @post Output==OK
 */
void test1_inventory_set_max_objs();

/**
 * @test Test function for inventory setting a newmmaximum number of objects it can hold
 * @pre pointer to inventory NON NULL, pointer to file NULL
 * @post Output==ERROR
 */
void test2_inventory_set_max_objs();

#endif