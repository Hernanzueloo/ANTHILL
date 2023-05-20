/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Javier San Andres
 * @version 3.0 
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Non NULL pointer to space 
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID 
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_id getting
 * @pre Space ID
 * @post Space_ID == Supplied Space Id
 */
void test1_space_get_id();

/**
 * @test Test function for space_name getting
 * @pre pointer to space_name NON NULL
 * @post Space_ID == NO_ID
 */
void test2_space_get_id();


/**
 * @test Test function for space_name getting
 * @pre pointer to space_name NON NULL 
 * @post Output==0
 */
void test1_space_get_name();

/**
 * @test Test function for space_name getting
 * @pre pointer to space_name NULL
 * @post Output==NULL
 */
void test2_space_get_name();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Ouput==OK 
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space_name = NULL (point to space = NON NULL) 
 * @post Output==ERROR
 */
void test3_space_set_name();



/**
 * @test Test function for space_light getting
 * @pre pointer to space_light NON NULL 
 * @post Output==TRUE
 */
void test1_space_get_light();

/**
 * @test Test function for space_light getting
 * @pre pointer to space_light NULL
 * @post Output==False
 */
void test2_space_get_light();

/**
 * @test Test function for space_light setting
 * @pre pointer to space not NULL
 * @post Ouput==OK 
 */
void test1_space_set_light();

/**
 * @test Test function for space_light setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_light();

/**
 * @test Test function for space_light setting
 * @pre pointer to space not NULL 
 * @post Output==OK
 */
void test3_space_set_light();



/**
 * @test Test function for space_flooded getting
 * @pre pointer to space_flooded NON NULL 
 * @post Output==TRUE
 */
void test1_space_get_flooded();

/**
 * @test Test function for space_flooded getting
 * @pre pointer to space_light NULL
 * @post Output==False
 */
void test2_space_get_flooded();

/**
 * @test Test function for space_flooded setting
 * @pre pointer to space not NULL
 * @post Ouput==OK 
 */
void test1_space_set_flooded();

/**
 * @test Test function for space_flooded setting
 * @pre pointer to space = NULL 
 * @post Output==ERROR
 */
void test2_space_set_flooded();

/**
 * @test Test function for space_flooded setting
 * @pre pointer to space not NULL 
 * @post Output==OK
 */
void test3_space_set_flooded();






/**
 * @test Test function for space_object adding
 * @pre pointer to space NON NULL and id != NO_ID
 * @post Output==OK
 */
void test1_space_add_object();

/**
 * @test Test function for space_object adding
 * @pre pointer to space NULL and id != NO_ID
 * @post Output==ERROR
 */
void test2_space_add_object();

/**
 * @test Test function for space_object adding
 * @pre pointer to space NON NULL and id = NO_ID
 * @post Output==ERROR
 */
void test3_space_add_object();


/**
 * @test Test function for space_object removing
 * @pre pointer to space NON NULL and one object added
 * @post Output==OK
 */
void test1_space_remove_object();


/**
 * @test Test function for space_object removing
 * @pre pointer to space NON NULL and no object added
 * @post Output==OK
 */
void test2_space_remove_object();

/**
 * @test Test function for space_object removing
 * @pre pointer to space NON NULL with one object and remove a non-existing object
 * @post Output==OK
 */
void test3_space_remove_object();

/**
 * @test Test function for space_object removing
 * @pre pointer to space NON NULL and id = NO_ID
 * @post Output==ERROR
 */
void test4_space_remove_object();

/**
 * @test Test function for space_object removing
 * @pre pointer to space NULL
 * @post Output==ERROR
 */
void test5_space_remove_object();

/**
 * @test Test function for space_object containing
 * @pre pointer to space NON NULL and one object added
 * @post Output==ERROR
 */
void test1_space_contains_object();

/**
 * @test Test function for space_object containing
 * @pre pointer to space NON NULL and no object added
 * @post Output==ERROR
 */
void test2_space_contains_object();

/**
 * @test Test function for space_object containing
 * @pre pointer to space NON NULL and id = NO_ID
 * @post Output==ERROR
 */
void test3_space_contains_object();

/**
 * @test Test function for space_object containing
 * @pre pointer to space NULL
 * @post Output==ERROR
 */
void test4_space_contains_object();

/**
 * @test Test function for space_object getting
 * @pre pointer to space NON NULL, space with an object
 * @post Output!=NULL
 */
void test1_space_get_objects();

/**
 * @test Test function for space_object getting
 * @pre pointer to space NON NULL with no objects
 * @post Output==NULL
 */
void test2_space_get_objects();

/**
 * @test Test function for space_object getting
 * @pre pointer to space NON NULL with one object
 * @post Output==1
 */
void test3_space_get_objects();

/**
 * @test Test function for space_object getting
 * @pre pointer to space NULL
 * @post Output==NULL
 */
void test4_space_get_objects();

/**
 * @test Test function for space_gdesc setting
 * @pre pointer to space NON NULL, pointer to gdesc NON NULL
 * @post Output==OK
 */
void test1_space_set_gdesc();

/**
 * @test Test function for space_gdesc setting
 * @pre pointer to space NON NULL, gdesc NON NULL with incorrect rows
 * @post Output==ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test function for space_gdesc setting
 * @pre pointer to space NON NULL, pointer to gdesc NULL
 * @post Output==ERROR
 */
void test3_space_set_gdesc();

/**
 * @test Test function for space_gdesc setting
 * @pre pointer to space NULL
 * @post Output==ERROR
 */
void test4_space_set_gdesc();


/**
 * @test Test function for space_gdesc getting
 * @pre pointer to space NON NULL with gdesc in it
 * @post Output!=NULL
 */
void test1_space_get_gdesc();

/**
 * @test Test function for space_gdesc getting
 * @pre pointer to space NON NULL with no gdesc in it
 * @post Output==NULL
 */
void test2_space_get_gdesc();

/**
 * @test Test function for space_gdesc getting
 * @pre pointer to space NULL
 * @post Output==NULL
 */
void test3_space_get_gdesc();


/**
 * @test Test function for space_tdescr setting
 * @pre pointer to space NON NULL, pointer to tdescr NON NULL
 * @post Output==OK
 */
void test1_space_set_tdesc();

/**
 * @test Test function for space_tdescr setting
 * @pre pointer to space NON NULL, pointer to tdescr NULL
 * @post Output==ERROR
 */
void test2_space_set_tdesc();

/**
 * @test Test function for space_tdescr setting
 * @pre pointer to space NULL, pointer to tdescr NON NULL
 * @post Output==ERROR
 */
void test3_space_set_tdesc();

/**
 * @test Test function for space_tdescr getting
 * @pre pointer to space NON NULL with tdescr in it
 * @post Output!=NULL
 */
void test1_space_get_tdesc();

/**
 * @test Test function for space_tdescr getting
 * @pre pointer to space NON NULL with no tdescr in it
 * @post Output==NULL
 */
void test2_space_get_tdesc();

/**
 * @test Test function for space_tdescr getting
 * @pre pointer to space NULL
 * @post Output==NULL
 */
void test3_space_get_tdesc();

/**
 * @test Test function for space printing
 * @pre pointer to space NON NULL
 * @post Output==OK
 */
void test1_space_print();

/**
 * @test Test function for space printing
 * @pre pointer to space NULL
 * @post Output==ERROR
 */
void test2_space_print();

/**
 * @test Test function for space printing
 * @pre pointer to space NON NULL, file NON NULL
 * @post Output==ERROR
 */
void test3_space_print();

#endif
