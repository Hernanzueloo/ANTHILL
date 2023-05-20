/**
 * @brief It declares the tests for the rule module
 *
 * @file rule_test.h
 * @author Diego Rodríguez Ortiz
 * @version 3.0
 * @date 15-04-2023
 * @copyright GNU Public License
 */

#ifndef RULE_TEST_H
#define RULE_TEST_H

/**
 * @test Test rule creation
 * @pre id != NO_ID
 * @post Non NULL pointer to rule
 */
void test1_rule_create();
/**
 * @test Test rule creation
 * @pre id == NO_ID
 * @post NULL pointer to rule
 */
void test2_rule_create();

/**
 * @test Test rule get_id
 * @pre Non NULL pointer to a rule (ID)
 * @post Output == ID
 */
void test1_rule_get_id();

/**
 * @test Test rule get_id
 * @pre  NULL pointer to a rule
 * @post Output == NO_ID
 */
void test2_rule_get_id();

/**
 * @test Test rule get_condition
 * @pre Rule with one condition
 * @post Output != NULL
 */
void test1_rule_get_condition();

/**
 * @test Test rule get_condition
 * @pre NULL pointer to a rule
 * @post Output == NULL
 */
void test2_rule_get_condition();

/**
 * @test Test rule get_condition
 * @pre Non NULL pointer to a rule and a invalid index
 * @post Output == NULL
 */
void test3_rule_get_condition();

/**
 * @test Test rule get_action
 * @pre Rule with one action
 * @post Output != NULL
 */
void test1_rule_get_action();

/**
 * @test Test rule get_action
 * @pre NULL pointer to a rule
 * @post Output == NULL
 */
void test2_rule_get_action();

/**
 * @test Test rule get_action
 * @pre Non NULL pointer to a rule and a invalid index
 * @post Output == NULL
 */
void test3_rule_get_action();

/**
 * @test Test rule get_num_conditions
 * @pre Non NULL pointer to a rule with 1 condition
 * @post Output == 1
 */
void test1_rule_get_num_conditions();

/**
 * @test Test rule get_num_conditions
 * @pre  NULL pointer to a rule
 * @post Output == -1
 */
void test2_rule_get_num_conditions();

/**
 * @test Test rule get_num_actions
 * @pre Non NULL pointer to a rule with 1 action
 * @post Output == 1
 */
void test1_rule_get_num_actions();

/**
 * @test Test rule get_num_actions
 * @pre  NULL pointer to a rule
 * @post Output == -1
 */
void test2_rule_get_num_actions();

/**
 * @test Test rule action get Id args
 * @pre  No null pointer to action
 * @post Output !=NULL
 */
void test1_rule_action_get_argsId();

/**
 * @test Test rule action get Id args
 * @pre  Null pointer to action
 * @post Output ==NULL
 */
void test2_rule_action_get_argsId();

/**
 * @test Test rule action get Id args
 * @pre  No null pointer to action with first element = ID2
 * @post Output !=NULL with first element == ID2
 */
void test3_rule_action_get_argsId();

/**
 * @test Test rule action get number of Id args
 * @pre  No null pointer to action with n_ids
 * @post Output == n_ids
 */
void test1_rule_action_get_numId();
/**
 * @test Test rule action get number of Id args
 * @pre  Null pointer to action
 * @post Output ==-1
 */
void test2_rule_action_get_numId();

/**
 * @test Test rule action get integer argument
 * @pre  No null pointer to action with argint
 * @post Output == argint
 */
void test1_rule_action_get_argint();
/**
 * @test Test rule action get integer argument
 * @pre  Null pointer to action
 * @post Output ==-1
 */
void test2_rule_action_get_argint();

/**
 * @test Test rule action get char argument
 * @pre  No null pointer to action with argchar
 * @post Output !=NULL with the same value as arcgchar
 */
void test1_rule_action_get_argname();
/**
 * @test Test rule action get char argument
 * @pre  Null pointer to action
 * @post Output ==NULL
 */
void test2_rule_action_get_argname();

/**
 * @test Test rule action get action type
 * @pre  No null pointer to action with type == act
 * @post Output == act
 */
void test1_rule_action_get_type();

/**
 * @test Test rule action get action type
 * @pre  Null pointer to action
 * @post Output == NO_ACTION
 */
void test2_rule_action_get_type();

/**
 * @test Test rule condition get Id args
 * @pre  No null pointer to condition
 * @post Output !=NULL
 */
void test1_rule_condition_get_argsId();
/**
 * @test Test rule condition get Id args
 * @pre  Null pointer to condition
 * @post Output ==NULL
 */
void test2_rule_condition_get_argsId();

/**
 * @test Test rule condition get Id args
 * @pre  No null pointer to condition with first element = ID2
 * @post Output !=NULL with first element == ID2
 */
void test3_rule_condition_get_argsId();

/**
 * @test Test rule condition get number of Id args
 * @pre  No null pointer to condition with n_ids
 * @post Output == n_ids
 */
void test1_rule_condition_get_numId();
/**
 * @test Test rule condition get number of Id args
 * @pre  Null pointer to condition
 * @post Output ==-1
 */
void test2_rule_condition_get_numId();

/**
 * @test Test rule condition get integer argument
 * @pre  No null pointer to condition with argint
 * @post Output == argint
 */
void test1_rule_condition_get_argint();

/**
 * @test Test rule condition get integer argument
 * @pre  Null pointer to condition
 * @post Output ==-1
 */
void test2_rule_condition_get_argint();

/**
 * @test Test rule condition get char argument
 * @pre  No null pointer to condition with argchar
 * @post Output !=NULL with the same value as arcgchar
 */
void test1_rule_condition_get_argname();
/**
 * @test Test rule condition get char argument
 * @pre  Null pointer to condition
 * @post Output ==NULL
 */
void test2_rule_condition_get_argname();

/**
 * @test Test rule condition get condition type
 * @pre  No null pointer to condition with type == act
 * @post Output == act
 */
void test1_rule_condition_get_type();

/**
 * @test Test rule condition get condition type
 * @pre  Null pointer to condition
 * @post Output == NO_CONDITION
 */
void test2_rule_get_condition_type();

/**
 * @test Test rule add condition
 * @pre  Non Null pointer to rule and the rest valid parameters
 * @post Output == OK
 */
void test1_rule_add_condition();

/**
 * @test Test rule add condition
 * @pre  Null pointer to rule and the rest valid parameters
 * @post Output == ERROR
 */
void test2_rule_add_condition();

/**
 * @test Test rule add condition
 * @pre  Non NULL pointer to rule, a condition type == NO_CONDITION and the rest valid parameters
 * @post Output == ERROR
 */
void test3_rule_add_condition();

/**
 * @test Test rule add condition
 * @pre  Non NULL pointer to rule, an array of arguments == NULL and the rest valid parameters
 * @post Output == ERROR
 */
void test4_rule_add_condition();

/**
 * @test Test rule add condition
 * @pre  Non NULL pointer to rule, number of arguments == -1 and the rest valid parameters
 * @post Output == ERROR
 */
void test5_rule_add_condition();

/**
 * @test Test rule add condition
 * @pre  Non NULL pointer to rule, cahr argument == NULL and the rest valid parameters
 * @post Output == ERROR
 */
void test6_rule_add_condition();

/**
 * @test Test rule add action
 * @pre  Non Null pointer to rule and the rest valid parameters
 * @post Output == OK
 */
void test1_rule_add_action();

/**
 * @test Test rule add action
 * @pre  Null pointer to rule and the rest valid parameters
 * @post Output == ERROR
 */
void test2_rule_add_action();

/**
 * @test Test rule add action
 * @pre  Non NULL pointer to rule, a action type == NO_ACTION and the rest valid parameters
 * @post Output == ERROR
 */
void test3_rule_add_action();

/**
 * @test Test rule add action
 * @pre  Non NULL pointer to rule, an array of arguments == NULL and the rest valid parameters
 * @post Output == ERROR
 */
void test4_rule_add_action();

/**
 * @test Test rule add condition
 * @pre  Non NULL pointer to rule, number of arguments == -1 and the rest valid parameters
 * @post Output == ERROR
 */
void test5_rule_add_action();

/**
 * @test Test rule add action
 * @pre  Non NULL pointer to rule, cahr argument == NULL and the rest valid parameters
 * @post Output == ERROR
 */
void test6_rule_add_action();

#endif
