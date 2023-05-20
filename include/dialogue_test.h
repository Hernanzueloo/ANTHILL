/** 
 * @brief It declares the tests for the dialogue module
 * 
 * @file dialogue_test.h
 * @author Javier San Andres
 * @version 3.0 
 * @date 29-03-2023
 * @copyright GNU Public License
 */

#ifndef dialogue_TEST_H
#define dialogue_TEST_H

/**
 * @test Test dialogue creation
 * @pre id != NO_ID
 * @post Non NULL pointer to dialogue
 */
void test1_dialogue_create();

/**
 * @test Test dialogue creation
 * @pre Dialogue_id
 * @post dialogue_id == Supplied dialogue id
 */
void test2_dialogue_create();

/**
 * @test Test dialogue creation
 * @pre id == NO_ID
 * @post NULL pointer to dialogue
 */
void test3_dialogue_create();

/**
 * @test Test function for dialogue_command getting
 * @pre pointer to dialogue NON NULL, dialogue ID != NO_ID
 * @post dialogue_ID == Supplied dialogue Id
 */
void test1_dialogue_get_id();

/**
 * @test Test function for dialogue_id getting
 * @pre pointer to dialogue NULL
 * @post dialogue_ID == NO_ID
 */
void test2_dialogue_get_id();

/**
 * @test Test function for dialogue_rule setting
 * @pre pointer to dialogue, pointer to rule non NULL
 * @post Output==OK
 */
void test1_dialogue_set_rule();

/**
 * @test Test function for dialogue_rule setting
 * @pre pointer to dialogue NON NULL, pointer to rule non NULL, full rule_space
 * @post Output==ERROR
 */
void test2_dialogue_set_rule();

/**
 * @test Test function for dialogue_rule setting
 * @pre pointer to dialogue, pointer to rule NULL
 * @post Output==ERROR
 */
void test3_dialogue_set_rule();

/**
 * @test Test function for dialogue_rule setting
 * @pre pointer to dialogue NULL, pointer to rule NON NULL
 * @post Output==ERROR
 */
void test4_dialogue_set_rule();

/**
 * @test Test function for dialogue_last_success_rule getting
 * @pre pointer to dialogue NON NULL, empty array of success rules 
 * @post Ouput==-1
 */
void test1_dialogue_get_last_rule_position();

/**
 * @test Test function for dialogue_last_success_rule getting
 * @pre pointer to dialogue NON NULL, non-empty array of success rules 
 * @post Ouput==0
 */
void test2_dialogue_get_last_rule_position();

/**
 * @test Test function for dialogue_last_success_rule getting
 * @pre pointer to dialogue NULL
 * @post Ouput==-2
 */
void test3_dialogue_get_last_rule_position();

/**
 * @test Test function for dialogue_last_error_rule getting
 * @pre pointer to dialogue NON NULL, empty array of error rules 
 * @post Ouput==0
 */
void test1_dialogue_get_last_error_rule_position();

/**
 * @test Test function for dialogue_last_error_rule getting
 * @pre pointer to dialogue NON NULL, non-empty array of error rules 
 * @post Ouput==1
 */
void test2_dialogue_get_last_error_rule_position();

/**
 * @test Test function for dialogue_last_error_rule getting
 * @pre pointer to dialogue NULL
 * @post Ouput==-2
 */
void test3_dialogue_get_last_error_rule_position();

/**
 * @test Test function for dialogue_success_rule getting
 * @pre pointer to dialogue NON NULL, non_empty rule array
 * @post Ouput!= NULL
 */
void test1_dialogue_get_rule();

/**
 * @test Test function for dialogue_success_rule getting
 * @pre pointer to dialogue NON NULL, empty rule array
 * @post Ouput == NULL
 */
void test2_dialogue_get_rule();

/**
 * @test Test function for dialogue_success_rule getting
 * @pre pointer to dialogue NON NULL, position > last_rule_index
 * @post Ouput == NULL
 */
void test3_dialogue_get_rule();

/**
 * @test Test function for dialogue_success_rule getting
 * @pre pointer to dialogue NULL
 * @post Ouput == NULL
 */
void test4_dialogue_get_rule();

/**
 * @test Test function for dialogue_error_rule getting
 * @pre pointer to dialogue NON NULL, non_empty rule array
 * @post Ouput!= NULL
 */
void test1_dialogue_get_error_rule();

/**
 * @test Test function for dialogue_error_rule getting
 * @pre pointer to dialogue NON NULL, empty rule array
 * @post Ouput == NULL
 */
void test2_dialogue_get_error_rule();

/**
 * @test Test function for dialogue_error_rule getting
 * @pre pointer to dialogue NON NULL, position > last_error_rule_index
 * @post Ouput == NULL
 */
void test3_dialogue_get_error_rule();

/**
 * @test Test function for dialogue_error_rule getting
 * @pre pointer to dialogue NULL
 * @post Ouput == NULL
 */
void test4_dialogue_get_error_rule();

/**
 * @test Test function for dialogue_executed increasing
 * @pre pointer to dialogue NON NULL
 * @post Ouput == OK
 */
void test1_dialogue_increase_executed();

/**
 * @test Test function for dialogue_executed increasing
 * @pre pointer to dialogue NULL
 * @post Ouput == ERROR
 */
void test2_dialogue_increase_executed();

/**
 * @test Test function for dialogue_executed decreasing
 * @pre pointer to dialogue NON NULL
 * @post Ouput == OK
 */
void test1_dialogue_decrease_executed();

/**
 * @test Test function for dialogue_executed decreasing
 * @pre pointer to dialogue NULL
 * @post Ouput == ERROR
 */
void test2_dialogue_decrease_executed();


/**
 * @test Test function for dialogue_executed getting
 * @pre pointer to dialogue NON NULL
 * @post Ouput == OK
 */
void test1_dialogue_get_executed();

/**
 * @test Test function for dialogue_executed getting
 * @pre pointer to dialogue NULL
 * @post Ouput == ERROR
 */
void test2_dialogue_get_executed();


/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position = existing_position, no arguments, success type
 * @post Ouput == OK
 */
void test1_dialogue_print_rule();


/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position = existing_position, no arguments, error type
 * @post Ouput == OK
 */
void test2_dialogue_print_rule();


/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position = existing_position, one argument, success type
 * @post Ouput == OK
 */
void test3_dialogue_print_rule();


/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position = existing_position, one argument, error type
 * @post Ouput == OK
 */
void test4_dialogue_print_rule();


/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position = existing_position, several arguments, success type
 * @post Ouput == OK
 */
void test5_dialogue_print_rule();


/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position = existing_position, several arguments, error type
 * @post Ouput == OK
 */
void test6_dialogue_print_rule();


/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position != existing_position, no arguments, success type
 * @post Ouput == ERROR
 */
void test7_dialogue_print_rule();

/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, position != existing_position, no arguments, error type
 * @post Ouput == ERROR
 */
void test8_dialogue_print_rule();

/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NON NULL, pointer to file NULL
 * @post Ouput == ERROR
 */
void test9_dialogue_print_rule();

/**
 * @test Test function for dialogue_rule printing
 * @pre pointer to dialogue NULL, pointer to file NON NULL
 * @post Ouput == ERROR
 */
void test10_dialogue_print_rule();


/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position = existing_position, no arguments, success type
 * @post Ouput != NULL
 */
void test1_dialogue_get_printed_rule();


/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position = existing_position, no arguments, error type
 * @post Ouput != NULL
 */
void test2_dialogue_get_printed_rule();


/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position = existing_position, one argument, success type
 * @post Ouput != NULL
 */
void test3_dialogue_get_printed_rule();


/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position = existing_position, one argument, error type
 * @post Ouput != NULL
 */
void test4_dialogue_get_printed_rule();


/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position = existing_position, several arguments, success type
 * @post Ouput != NULL
 */
void test5_dialogue_get_printed_rule();


/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position = existing_position, several arguments, error type
 * @post Ouput != NULL
 */
void test6_dialogue_get_printed_rule();


/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position != existing_position, no arguments, success type
 * @post Ouput == NULL
 */
void test7_dialogue_get_printed_rule();

/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position != existing_position, no arguments, error type
 * @post Ouput == NULL
 */
void test8_dialogue_get_printed_rule();

/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NON NULL, position != existing_position
 * @post Ouput == NULL
 */
void test9_dialogue_get_printed_rule();

/**
 * @test Test function for dialogue_rule in printed format getting
 * @pre pointer to dialogue NULL
 * @post Ouput == NULL
 */
void test10_dialogue_get_printed_rule();



/**
 * @test Test function for dialogue printing
 * @pre pointer to dialogue NON NULL
 * @post Output==OK
 */
void test1_dialogue_print();

/**
 * @test Test function for dialogue printing
 * @pre pointer to dialogue NULL
 * @post Output==ERROR
 */
void test2_dialogue_print();

/**
 * @test Test function for dialogue printing
 * @pre pointer to dialogue NON NULL, file NON NULL
 * @post Output==ERROR
 */
void test3_dialogue_print();

#endif