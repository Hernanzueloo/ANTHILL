/** 
 * @brief It tests dialogue module
 * 
 * @file dialogue_test.c
 * @author Javier San Andres
 * @version 3.0 
 * @date 09/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "dialogue.h"
#include "dialogue_test.h"
#include "test.h"

#define MAX_TESTS 52                                                                        /*!<Maximum number of test to be executed*/        
#define ID 1                                                                                /*!<Id for initializing a dialogue*/
#define RULE "opps, sorry"                                                                  /*!<Rule to be set to a dialogue*/
#define RULE_W_ARG "you made <something>"                                                   /*!<Rule with an argument to be substituted*/
#define RULE_W_ARGS "you made <something> and also picked <that other thing>. Good luck."   /*!<Rule with two arguments to be substituted*/
#define ARG1 "the right decission"                                                          /*!<Argument for the rules*/
#define ARG2 "enemies"                                                                      /*!<Argument for the rules*/
#define DIALFILE "dialogue_test.txt"                                                        /*!<Name to an auxiliary file for testing*/

/** 
 * @brief Main function for dialogue unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("\n\nRunning all test for module dialogue:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_dialogue_create();
  if (all || test == 2) test2_dialogue_create();
  if (all || test == 3) test3_dialogue_create();
  if (all || test == 4) test1_dialogue_get_id();
  if (all || test == 5) test2_dialogue_get_id();
  if (all || test == 6) test1_dialogue_set_rule();
  if (all || test == 7) test2_dialogue_set_rule();
  if (all || test == 8) test3_dialogue_set_rule();
  if (all || test == 9) test4_dialogue_set_rule();
  if (all || test == 10) test1_dialogue_get_last_rule_position();
  if (all || test == 11) test2_dialogue_get_last_rule_position();
  if (all || test == 12) test3_dialogue_get_last_rule_position();
  if (all || test == 13) test1_dialogue_get_last_error_rule_position();
  if (all || test == 14) test2_dialogue_get_last_error_rule_position();
  if (all || test == 15) test3_dialogue_get_last_error_rule_position();
  if (all || test == 16) test1_dialogue_get_rule();
  if (all || test == 17) test2_dialogue_get_rule();
  if (all || test == 18) test3_dialogue_get_rule();
  if (all || test == 19) test4_dialogue_get_rule();
  if (all || test == 20) test1_dialogue_get_error_rule();
  if (all || test == 21) test2_dialogue_get_error_rule();
  if (all || test == 22) test3_dialogue_get_error_rule();
  if (all || test == 23) test4_dialogue_get_error_rule();
  if (all || test == 24) test1_dialogue_increase_executed();
  if (all || test == 25) test2_dialogue_increase_executed();
  if (all || test == 26) test1_dialogue_decrease_executed();
  if (all || test == 27) test2_dialogue_decrease_executed();
  if (all || test == 28) test1_dialogue_get_executed();
  if (all || test == 29) test2_dialogue_get_executed();
  if (all || test == 30) test1_dialogue_print_rule();
  if (all || test == 31) test2_dialogue_print_rule();
  if (all || test == 32) test3_dialogue_print_rule();
  if (all || test == 33) test4_dialogue_print_rule();
  if (all || test == 34) test5_dialogue_print_rule();
  if (all || test == 35) test6_dialogue_print_rule();
  if (all || test == 36) test7_dialogue_print_rule();
  if (all || test == 37) test8_dialogue_print_rule();
  if (all || test == 38) test9_dialogue_print_rule();
  if (all || test == 39) test10_dialogue_print_rule();
  if (all || test == 40) test1_dialogue_get_printed_rule();
  if (all || test == 41) test2_dialogue_get_printed_rule();
  if (all || test == 42) test3_dialogue_get_printed_rule();
  if (all || test == 43) test4_dialogue_get_printed_rule();
  if (all || test == 44) test5_dialogue_get_printed_rule();
  if (all || test == 45) test6_dialogue_get_printed_rule();
  if (all || test == 46) test7_dialogue_get_printed_rule();
  if (all || test == 47) test8_dialogue_get_printed_rule();
  if (all || test == 48) test9_dialogue_get_printed_rule();
  if (all || test == 49) test10_dialogue_get_printed_rule();
  if (all || test == 50) test1_dialogue_print();
  if (all || test == 51) test2_dialogue_print();
  if (all || test == 52) test3_dialogue_print();


  PRINT_PASSED_PERCENTAGE;

  return 0;
}


void test1_dialogue_create()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);
    PRINT_TEST_RESULT(dialogue != NULL);

    dialogue_destroy(dialogue);
}

void test2_dialogue_create()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);
    PRINT_TEST_RESULT(dialogue_get_id(dialogue) == ID);
    
    dialogue_destroy(dialogue);
}

void test3_dialogue_create()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(NO_ID);
    PRINT_TEST_RESULT(dialogue == NULL);
}

void test1_dialogue_get_id()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);
    PRINT_TEST_RESULT(dialogue_get_id(dialogue) == ID);
    
    dialogue_destroy(dialogue);
}

void test2_dialogue_get_id()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_get_id(dialogue) == NO_ID);
    
    dialogue_destroy(dialogue);
}

void test1_dialogue_set_rule()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_set_rule(dialogue, RULE, SUCCESS) == OK);

    dialogue_destroy(dialogue);
}

void test2_dialogue_set_rule()
{
    int i;
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);

    for (i = 0; i < MAX_DIALOGUE_RULES; i++)
        dialogue_set_rule(dialogue, RULE, SUCCESS);

    PRINT_TEST_RESULT(dialogue_set_rule(dialogue, RULE, SUCCESS) == ERROR);

    dialogue_destroy(dialogue);
}

void test3_dialogue_set_rule()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_set_rule(dialogue, NULL, SUCCESS) == ERROR);

    dialogue_destroy(dialogue);
}


void test4_dialogue_set_rule()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_set_rule(dialogue, RULE, SUCCESS) == ERROR);
}


void test1_dialogue_get_last_rule_position()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_get_last_rule_position(dialogue) == -1);

    dialogue_destroy(dialogue);
}

void test2_dialogue_get_last_rule_position()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, SUCCESS);

    PRINT_TEST_RESULT(dialogue_get_last_rule_position(dialogue) == 0);

    dialogue_destroy(dialogue);
}

void test3_dialogue_get_last_rule_position()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_get_last_rule_position(dialogue) == -2);
}

void test1_dialogue_get_last_error_rule_position()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_get_last_error_rule_position(dialogue) == -1);

    dialogue_destroy(dialogue);
}

void test2_dialogue_get_last_error_rule_position()
{
    Dialogue *dialogue;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, FAILURE);

    PRINT_TEST_RESULT(dialogue_get_last_error_rule_position(dialogue) == 0);

    dialogue_destroy(dialogue);
}

void test3_dialogue_get_last_error_rule_position()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_get_last_error_rule_position(dialogue) == -2);
}

void test1_dialogue_get_rule()
{
    Dialogue *dialogue = NULL;
    
    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, SUCCESS);

    PRINT_TEST_RESULT(dialogue_get_rule(dialogue, 0) != NULL);

    dialogue_destroy(dialogue);
}


void test2_dialogue_get_rule()
{
    Dialogue *dialogue = NULL;
    
    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_get_rule(dialogue, 0) == NULL);

    dialogue_destroy(dialogue);
}

void test3_dialogue_get_rule()
{
    Dialogue *dialogue = NULL;
    
    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, SUCCESS);

    PRINT_TEST_RESULT(dialogue_get_rule(dialogue, 1) == NULL);

    dialogue_destroy(dialogue);
}

void test4_dialogue_get_rule()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_get_rule(dialogue, 0) == NULL);
}


void test1_dialogue_get_error_rule()
{
    Dialogue *dialogue = NULL;
    
    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, FAILURE);

    PRINT_TEST_RESULT(dialogue_get_error_rule(dialogue, 0) != NULL);

    dialogue_destroy(dialogue);
}


void test2_dialogue_get_error_rule()
{
    Dialogue *dialogue = NULL;
    
    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_get_error_rule(dialogue, 0) == NULL);

    dialogue_destroy(dialogue);
}

void test3_dialogue_get_error_rule()
{
    Dialogue *dialogue = NULL;
    
    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, FAILURE);

    PRINT_TEST_RESULT(dialogue_get_error_rule(dialogue, 1) == NULL);

    dialogue_destroy(dialogue);
}

void test4_dialogue_get_error_rule()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_get_error_rule(dialogue, 0) == NULL);
}

void test1_dialogue_increase_executed()
{
    Dialogue *dialogue = NULL;

    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_increase_executed(dialogue) == OK);

    dialogue_destroy(dialogue);
}

void test2_dialogue_increase_executed()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_increase_executed(dialogue) == ERROR);

}

void test1_dialogue_decrease_executed()
{
    Dialogue *dialogue = NULL;

    dialogue = dialogue_create(ID);

    PRINT_TEST_RESULT(dialogue_increase_executed(dialogue) == OK);

    dialogue_destroy(dialogue);
}

void test2_dialogue_decrease_executed()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_increase_executed(dialogue) == ERROR);

}

void test1_dialogue_get_executed()
{
    Dialogue *dialogue = NULL;

    dialogue = dialogue_create(ID);

    dialogue_increase_executed(dialogue);

    PRINT_TEST_RESULT(dialogue_get_executed(dialogue) == 1);

    dialogue_destroy(dialogue);
}

void test2_dialogue_get_executed()
{
    Dialogue *dialogue = NULL;

    PRINT_TEST_RESULT(dialogue_get_executed(dialogue) == 0);
}

void test1_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;

    dialogue_set_rule(dialogue, RULE, SUCCESS);
    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 0, NULL, OK) == OK);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}

void test2_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;

    dialogue_set_rule(dialogue, RULE, FAILURE);
    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 0, NULL, ERROR) == OK);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}

void test3_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;

    dialogue_set_rule(dialogue, RULE_W_ARG, SUCCESS);

    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 0, ARG1, OK) == OK);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}

void test4_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;

    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);
    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 0, ARG1, ERROR) == OK);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}

void test5_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;
    char aux[WORD_SIZE]="";

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;
    
    strcat(aux, ARG1);
    strcat(aux, "|");
    strcat(aux, ARG2);

    dialogue_set_rule(dialogue, RULE_W_ARGS, SUCCESS);
    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 0, aux, OK) == OK);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}

void test6_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;
    char aux[WORD_SIZE]="";

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;
    
    strcat(aux, ARG1);
    strcat(aux, "|");
    strcat(aux, ARG2);

    dialogue_set_rule(dialogue, RULE_W_ARGS, FAILURE);
    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 0, aux, ERROR) == OK);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}

void test7_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;

    dialogue_set_rule(dialogue, RULE_W_ARG, SUCCESS);

    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 2, NULL, OK) == ERROR);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}

void test8_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    dialogue = dialogue_create(ID);

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;

    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 2, NULL, OK) == ERROR);

    dialogue_destroy(dialogue);
    fclose(f);
    remove(DIALFILE);
}


void test9_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 0, NULL, FAILURE) == ERROR);

    dialogue_destroy(dialogue);
}


void test10_dialogue_print_rule()
{
    Dialogue *dialogue = NULL;
    FILE *f = NULL;

    if ((f = fopen(DIALFILE, "w")) == NULL)
        return;

    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

    PRINT_TEST_RESULT(dialogue_print_rule(dialogue, f, 2, NULL, OK) == ERROR);

    fclose(f);
    remove(DIALFILE);
}


void test1_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;
    char *aux;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, SUCCESS);
    aux = dialogue_get_printed_rule(dialogue, 0, NULL, OK);
    PRINT_TEST_RESULT(aux != NULL);

    dialogue_destroy(dialogue);
    free(aux);
}

void test2_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;
    char *aux;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE, FAILURE);
    aux = dialogue_get_printed_rule(dialogue, 0, NULL, ERROR);
    PRINT_TEST_RESULT(aux != NULL);

    dialogue_destroy(dialogue);
    free(aux);
}

void test3_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;
    char *aux;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE_W_ARG, SUCCESS);

    aux = dialogue_get_printed_rule(dialogue, 0, ARG1, OK);
    PRINT_TEST_RESULT(aux != NULL);

    dialogue_destroy(dialogue);
    free(aux);
}

void test4_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;
    char *aux;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);
    aux = dialogue_get_printed_rule(dialogue, 0, ARG1, ERROR);
    PRINT_TEST_RESULT(aux != NULL);

    dialogue_destroy(dialogue);
    free(aux);
}

void test5_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;
    char aux[WORD_SIZE]="", *aux2;

    dialogue = dialogue_create(ID);
    
    strcat(aux, ARG1);
    strcat(aux, "|");
    strcat(aux, ARG2);

    dialogue_set_rule(dialogue, RULE_W_ARGS, SUCCESS);
    aux2 = dialogue_get_printed_rule(dialogue, 0, aux, OK);
    PRINT_TEST_RESULT(aux2 != NULL);

    dialogue_destroy(dialogue);
    free(aux2);
}

void test6_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;
    char aux[WORD_SIZE]="", *aux2;

    dialogue = dialogue_create(ID);
    
    strcat(aux, ARG1);
    strcat(aux, "|");
    strcat(aux, ARG2);

    dialogue_set_rule(dialogue, RULE_W_ARGS, FAILURE);
    aux2 = dialogue_get_printed_rule(dialogue, 0, aux, ERROR);
    PRINT_TEST_RESULT(aux2 != NULL);

    dialogue_destroy(dialogue);
    free(aux2);
}

void test7_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE_W_ARG, SUCCESS);

    PRINT_TEST_RESULT(dialogue_get_printed_rule(dialogue, 2, NULL, OK) == NULL);

    dialogue_destroy(dialogue);
}

void test8_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;

    dialogue = dialogue_create(ID);

    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

    PRINT_TEST_RESULT(dialogue_get_printed_rule(dialogue, 2, NULL, OK) == NULL);

    dialogue_destroy(dialogue);
}


void test9_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;

    dialogue = dialogue_create(ID);
    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

    PRINT_TEST_RESULT(dialogue_get_printed_rule(dialogue, 0, NULL, OK) == NULL);

    dialogue_destroy(dialogue);
}


void test10_dialogue_get_printed_rule()
{
    Dialogue *dialogue = NULL;


    dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

    PRINT_TEST_RESULT(dialogue_get_printed_rule(dialogue, 2, NULL, OK) == NULL);

}



void test1_dialogue_print() {
  Dialogue *dialogue;
  FILE *f;
  if ((f = fopen(DIALFILE, "w")) == NULL)
    return;

  dialogue = dialogue_create(ID);

  dialogue_set_rule(dialogue, RULE, SUCCESS);
  dialogue_set_rule(dialogue, RULE_W_ARG, SUCCESS);

  PRINT_TEST_RESULT(dialogue_print(dialogue, f) == OK);

  dialogue_destroy(dialogue);
  fclose(f);
  remove(DIALFILE);
}

void test2_dialogue_print() {
  Dialogue *dialogue = NULL;
  FILE *f;

  if ((f = fopen(DIALFILE, "w")) == NULL)
    return;

  PRINT_TEST_RESULT(dialogue_print(dialogue, f) == ERROR);

  fclose(f);
  remove(DIALFILE);
}

void test3_dialogue_print() {
  Dialogue *dialogue = NULL;

  dialogue=dialogue_create(ID);

  PRINT_TEST_RESULT(dialogue_print(dialogue, NULL) == ERROR);

  dialogue_destroy(dialogue);
}
