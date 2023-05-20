/** 
 * @brief It tests rule module
 * 
 * @file rule_test.c
 * @author Diego Rodríguez Ortiz
 * @version 3.0 
 * @date 15/04/2023
 * @copyright GNU Public License
 */
#include "test.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <string.h> 
#include "rule.h"
#include "rule_test.h"


#define MAX_TESTS 47                    /*!<Maximum number of test to be executed*/
#define FIRST 0                         /*!<First position of an array*/
#define INVALID_INDEX -1                 /*!<Invalid index*/

#define ID 1                            /*!<Example Id */
#define ID2 5                        /*!<Id2 */
#define ID3 7                       /*!<Id3 */
#define ID4 11                      /*!<Id4 */


/** 
 * @brief Main function for rule unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv){

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("\n\nRunning all test for module rule:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_rule_create();
  if (all || test == 2) test2_rule_create();
  if (all || test == 3)  test1_rule_get_id();
  if (all || test == 4) test1_rule_get_condition();
  if (all || test == 5) test2_rule_get_condition();
  if (all || test == 6) test3_rule_get_condition();
  if (all || test == 7)  test1_rule_get_action();
  if (all || test == 8)  test2_rule_get_action();
  if (all || test == 9)  test3_rule_get_action();
  if (all || test == 10) test1_rule_get_num_conditions();
  if (all || test == 11) test2_rule_get_num_conditions();
  if (all || test == 12) test1_rule_get_num_actions();
  if (all || test == 13) test2_rule_get_num_actions();
  if (all || test == 14) test1_rule_action_get_argsId();
  if (all || test == 15) test2_rule_action_get_argsId();
  if (all || test == 16) test3_rule_action_get_argsId();
  if (all || test == 17) test1_rule_action_get_numId();
  if (all || test == 18) test2_rule_action_get_numId();
  if (all || test == 19) test1_rule_action_get_argint();
  if (all || test == 20) test2_rule_action_get_argint();
  if (all || test == 21) test1_rule_action_get_argname();
  if (all || test == 22) test2_rule_action_get_argname();
  if (all || test == 23) test1_rule_action_get_type();
  if (all || test == 24) test2_rule_action_get_type();
  if (all || test == 25) test1_rule_condition_get_argsId();
  if (all || test == 26) test2_rule_condition_get_argsId();
  if (all || test == 27) test3_rule_condition_get_argsId();
  if (all || test == 28) test1_rule_condition_get_numId();
  if (all || test == 29) test2_rule_condition_get_numId();
  if (all || test == 30) test1_rule_condition_get_argint();
  if (all || test == 31) test2_rule_condition_get_argint();
  if (all || test == 32) test1_rule_condition_get_argname();
  if (all || test == 33) test2_rule_condition_get_argname();
  if (all || test == 34) test1_rule_condition_get_type();
  if (all || test == 35) test2_rule_get_condition_type();
  if (all || test == 36) test1_rule_add_condition();
  if (all || test == 37) test2_rule_add_condition();
  if (all || test == 38) test3_rule_add_condition();
  if (all || test == 39) test4_rule_add_condition();
  if (all || test == 40) test5_rule_add_condition();
  if (all || test == 41) test6_rule_add_condition();
  if (all || test == 42) test1_rule_add_action();
  if (all || test == 43) test2_rule_add_action();
  if (all || test == 44) test3_rule_add_action();
  if (all || test == 45) test4_rule_add_action();
  if (all || test == 46) test5_rule_add_action();
  if (all || test == 47) test6_rule_add_action();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_rule_create() {
    Rule *rule;
    rule=rule_create(ID);
    PRINT_TEST_RESULT(rule != NULL);
    rule_destroy(rule);
}

void test2_rule_create() {
    Rule *rule;
    rule=rule_create(NO_ID);
    PRINT_TEST_RESULT(rule == NULL);
}

void test1_rule_get_id() {
  Rule *rule;
   rule=rule_create(ID);
  PRINT_TEST_RESULT(rule_get_id(rule)==ID);
  rule_destroy(rule);
}

void test2_rule_get_id() {
  PRINT_TEST_RESULT(rule_get_id(NULL)==NO_ID);
}

void test1_rule_get_condition() {
  Rule *rule=NULL;
  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(rule_get_condition(rule,FIRST)!=NULL);
  rule_destroy(rule);

}

void test2_rule_get_condition() {
  PRINT_TEST_RESULT(rule_get_condition(NULL,FIRST)==NULL);
}

void test3_rule_get_condition() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(rule_get_condition(rule,-1)==NULL);
  rule_destroy(rule);

}
void test1_rule_get_action() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(rule_get_action(rule,FIRST)!=NULL);
  rule_destroy(rule);

}

void test2_rule_get_action() {
  PRINT_TEST_RESULT(rule_get_action(NULL,FIRST)==NULL);
}

void test3_rule_get_action() {
  Rule *rule=NULL;

  T_ACTION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(rule_get_action(rule,-1)==NULL);
  rule_destroy(rule);

}

void test1_rule_get_num_conditions() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(rule_get_num_conditions(rule)==1);
  rule_destroy(rule);

}

void test2_rule_get_num_conditions() {
  PRINT_TEST_RESULT(rule_get_num_conditions(NULL)==-1);
}


void test1_rule_get_num_actions() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(rule_get_num_actions(rule)==1);
  rule_destroy(rule);

}

void test2_rule_get_num_actions() {
  PRINT_TEST_RESULT(rule_get_num_actions(NULL)==-1);
}


void test1_rule_action_get_argsId() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_action_get_argsId(rule_get_action(rule, FIRST)))!=NULL);
  rule_destroy(rule);

}

void test2_rule_action_get_argsId() {
  PRINT_TEST_RESULT(rule_action_get_argsId(NULL)==NULL);
}

void test3_rule_action_get_argsId() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS], *newids;
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  newids= rule_action_get_argsId(rule_get_action(rule, FIRST));
  PRINT_TEST_RESULT(newids[FIRST]==ids[FIRST]);
  rule_destroy(rule);

}

void test1_rule_action_get_numId() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_action_get_numId(rule_get_action(rule, FIRST)))==n_ids);
  rule_destroy(rule);

}

void test2_rule_action_get_numId() {
  PRINT_TEST_RESULT(rule_action_get_numId(NULL)==-1);
}

void test1_rule_action_get_argint() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_action_get_argint(rule_get_action(rule, FIRST)))==argint);
  rule_destroy(rule);

}

void test2_rule_action_get_argint() {
  PRINT_TEST_RESULT(rule_action_get_argint(NULL)==-1);
}


void test1_rule_action_get_argname() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(strcmp((rule_action_get_argname(rule_get_action(rule, FIRST))),argchar)==0);
  rule_destroy(rule);

}

void test2_rule_action_get_argname() {
  PRINT_TEST_RESULT(rule_action_get_argname(NULL)==NULL);
}

void test1_rule_action_get_type() {
  Rule *rule=NULL;

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_action_get_type(rule_get_action(rule, FIRST)))==act);
  rule_destroy(rule);

}

void test2_rule_action_get_type() {
  PRINT_TEST_RESULT(rule_action_get_type(NULL)==NO_ACTION);
}


void test1_rule_condition_get_argsId() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_condition_get_argsId(rule_get_condition(rule, FIRST)))!=NULL);
  rule_destroy(rule);

}

void test2_rule_condition_get_argsId() {
  PRINT_TEST_RESULT(rule_condition_get_argsId(NULL)==NULL);
}

void test3_rule_condition_get_argsId() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE;
  Id ids[MAX_ARGS], *newids;
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  newids= rule_condition_get_argsId(rule_get_condition(rule, FIRST));
  PRINT_TEST_RESULT(newids[FIRST]==ids[FIRST]);
  rule_destroy(rule);

}

void test1_rule_condition_get_numId() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_condition_get_numId(rule_get_condition(rule, FIRST)))==n_ids);
  rule_destroy(rule);

}

void test2_rule_condition_get_numId() {
  PRINT_TEST_RESULT(rule_condition_get_numId(NULL)==-1);
}

void test1_rule_condition_get_argint() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_condition_get_argint(rule_get_condition(rule, FIRST)))==argint);
  rule_destroy(rule);

}

void test2_rule_condition_get_argint() {
  PRINT_TEST_RESULT(rule_condition_get_argint(NULL)==-1);
}


void test1_rule_condition_get_argname() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(strcmp((rule_condition_get_argname(rule_get_condition(rule, FIRST))),argchar)==0);
  rule_destroy(rule);

}

void test2_rule_condition_get_argname() {
  PRINT_TEST_RESULT(rule_condition_get_argname(NULL)==NULL);
}

void test1_rule_condition_get_type() {
  Rule *rule=NULL;

  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT((rule_condition_get_type(rule_get_condition(rule, FIRST)))==cond);
  rule_destroy(rule);

}

void test2_rule_get_condition_type() {
  PRINT_TEST_RESULT(rule_condition_get_type(NULL)==NO_CONDITION);
}

void test1_rule_add_condition() {
  Rule *rule=NULL;
  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_condition(rule,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == OK);
  rule_destroy(rule);

}

void test2_rule_add_condition() {


  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;

  st = rule_add_condition(NULL,cond,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);


}

void test3_rule_add_condition() {
  Rule *rule=NULL;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_condition(rule,NO_CONDITION,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}


void test4_rule_add_condition() {
  Rule *rule=NULL;
  T_CONDITION cond = IN_SPACE ;
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  rule=rule_create(ID);
  st = rule_add_condition(rule,cond,NULL,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}



void test5_rule_add_condition() {
  Rule *rule=NULL;
  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int  argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_condition(rule,cond,ids,-1,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}



void test6_rule_add_condition() {
  Rule *rule=NULL;
  T_CONDITION cond = IN_SPACE ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_condition(rule,cond,ids,n_ids,argint,NULL);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}


void test1_rule_add_action() {
  Rule *rule=NULL;
  T_ACTION act = ATTACK_P ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_action(rule,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == OK);
  rule_destroy(rule);

}

void test2_rule_add_action() {

  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;

  st = rule_add_action(NULL,act,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);


}

void test3_rule_add_action() {
  Rule *rule=NULL;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_action(rule,NO_ACTION,ids,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}


void test4_rule_add_action() {
  Rule *rule=NULL;
  T_ACTION act = ATTACK_E ;
  int n_ids = 1, argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  rule=rule_create(ID);
  st = rule_add_action(rule,act,NULL,n_ids,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}



void test5_rule_add_action() {
  Rule *rule=NULL;
  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int  argint =2;
  char argchar[WORD_SIZE] = "texto";
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_action(rule,act,ids,-1,argint,argchar);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}


void test6_rule_add_action() {
  Rule *rule=NULL;
  T_ACTION act = ATTACK_E ;
  Id ids[MAX_ARGS];
  int n_ids = 1, argint =2;
  STATUS st;
  ids[FIRST] = ID2;
  rule=rule_create(ID);
  st = rule_add_action(rule,act,ids,n_ids,argint,NULL);
  PRINT_TEST_RESULT(st == ERROR);
  rule_destroy(rule);

}




