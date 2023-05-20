/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Javier San Andres
 * @version 3.0 
 * @date 19/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 32               /*!<Maximum number of test to be executed*/
#define ID 3                       /*!<Id to be added in a set*/
#define MASSIVE_INSERT 20          /*!<Number of ids to be inserted all at once*/
#define SET_FILE "set_test.txt"    /*!<Name to an auxiliary file for testing*/

/** 
 * @brief Main function for SET unit tests. 
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
    printf("\n\nRunning all test for module set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_set_create();
  if (all || test == 2) test1_set_is_empty();
  if (all || test == 3) test2_set_is_empty();
  if (all || test == 4) test3_set_is_empty();
  if (all || test == 5) test1_set_add_id();
  if (all || test == 6) test2_set_add_id();
  if (all || test == 7) test3_set_add_id();
  if (all || test == 8) test4_set_add_id();
  if (all || test == 9) test5_set_add_id();
  if (all || test == 10) test1_set_massive_add();
  if (all || test == 11) test2_set_massive_add();
  if (all || test == 12) test3_set_massive_add();
  if (all || test == 13) test4_set_massive_add();
  if (all || test == 14) test5_set_massive_add();
  if (all || test == 15) test1_set_delete_id();
  if (all || test == 16) test2_set_delete_id();
  if (all || test == 17) test3_set_delete_id();
  if (all || test == 18) test4_set_delete_id();
  if (all || test == 19) test5_set_delete_id();
  if (all || test == 20) test1_set_get_number_ids();
  if (all || test == 21) test2_set_get_number_ids();
  if (all || test == 22) test1_set_contains_id();
  if (all || test == 23) test2_set_contains_id();
  if (all || test == 24) test3_set_contains_id();
  if (all || test == 25) test4_set_contains_id();
  if (all || test == 26) test1_set_get_all_ids();
  if (all || test == 27) test2_set_get_all_ids();
  if (all || test == 28) test3_set_get_all_ids();
  if (all || test == 29) test4_set_get_all_ids();
  if (all || test == 30) test1_set_print();
  if (all || test == 31) test2_set_print();
  if (all || test == 32) test3_set_print();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_set_create() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}

void test1_set_is_empty() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_is_empty(s) == TRUE);
  set_destroy(s);
}

void test2_set_is_empty() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_is_empty(s) == FALSE);
  set_destroy(s);
}

void test3_set_is_empty() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_is_empty(s) == TRUE);
}

void test1_set_add_id() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_add_id(s, ID) == OK);
  set_destroy(s);
}

void test2_set_add_id() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_add_id(s, ID) == OK);
  set_destroy(s);
}

void test3_set_add_id() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_get_number_ids(s) == 1);
  set_destroy(s);
}

void test4_set_add_id() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_add_id(s, NO_ID) == ERROR);
  set_destroy(s);
}

void test5_set_add_id() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add_id(s, ID) == ERROR);
}

void test1_set_massive_add() {
  Set *s;
  Id id[20];
  long i;
  s = set_create();
  for (i = 0; i < 20; i++)
    id[i] = i;
  PRINT_TEST_RESULT(set_massive_add(s, id, 20) == OK);
  set_destroy(s);
}

void test2_set_massive_add() {
  Set *s;
  Id id[MASSIVE_INSERT];
  long i;
  s = set_create();
  for (i = 0; i < MASSIVE_INSERT; i++)
    id[i] = i % 10;
  set_massive_add(s, id, MASSIVE_INSERT);
  i = set_get_number_ids(s);
  PRINT_TEST_RESULT(i == 10);
  set_destroy(s);
}

void test3_set_massive_add() {
  Set *s = NULL;
  Id id[1];
  PRINT_TEST_RESULT(set_massive_add(s, id, 1) == ERROR);
}

void test4_set_massive_add() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_massive_add(s, NULL, 3) == ERROR);
  set_destroy(s);
}

void test5_set_massive_add() {
  Set *s = NULL;
  Id id[1];
  s = set_create();
  PRINT_TEST_RESULT(set_massive_add(s, id, 0) == ERROR);
  set_destroy(s);
}

void test1_set_delete_id() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_delete_id(s, ID) == OK);
  set_destroy(s);
}

void test2_set_delete_id() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_delete_id(s, ID+1) == OK);
  set_destroy(s);
}

void test3_set_delete_id() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_delete_id(s, ID) == OK);
  set_destroy(s);
}

void test4_set_delete_id() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_delete_id(s, ID) == ERROR);
}

void test5_set_delete_id() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_delete_id(s, NO_ID) == ERROR);
  set_destroy(s);
}

void test1_set_get_number_ids() {
  Set *s;
  int n;
  s = set_create();
  set_add_id(s, ID);
  n = set_get_number_ids(s);
  PRINT_TEST_RESULT(n == 1);
  set_destroy(s);
}

void test2_set_get_number_ids() {
  Set *s = NULL;
  int n;
  n = set_get_number_ids(s);
  PRINT_TEST_RESULT(n == -1);
}

void test1_set_contains_id() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_contains_id(s, ID) == TRUE);
  set_destroy(s);
}

void test2_set_contains_id() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_contains_id(s, ID+1) == FALSE);
  set_destroy(s);
}

void test3_set_contains_id() {
  Set *s;
  s = set_create();
  PRINT_TEST_RESULT(set_contains_id(s, NO_ID) == FALSE);
  set_destroy(s);
}

void test4_set_contains_id() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_contains_id(s, ID+1) == FALSE);
}

void test1_set_get_all_ids() {
  Set *s;
  Id *id;
  int num;
  s = set_create();
  set_add_id(s, ID);
  id = set_get_all_ids(s, &num);
  PRINT_TEST_RESULT(id != NULL);
  set_destroy(s);
  free(id);
}

void test2_set_get_all_ids() {
  Set *s;
  Id *id;
  int num;
  s = set_create();
  id = set_get_all_ids(s, &num);
  PRINT_TEST_RESULT(id == NULL);
  set_destroy(s);
}

void test3_set_get_all_ids() {
  Set *s = NULL;
  Id *id;
  int num;
  s = set_create();
  id = set_get_all_ids(s, &num);
  PRINT_TEST_RESULT(id == NULL);
  set_destroy(s);
}

void test4_set_get_all_ids() {
  Set *s = NULL;
  Id *id;
  s = set_create();
  set_add_id(s, ID);
  id = set_get_all_ids(s, NULL);
  PRINT_TEST_RESULT(id == NULL);
  set_destroy(s);
}

void test1_set_print() {
  Set *s;
  FILE *f;
  if ((f = fopen(SET_FILE, "w")) == NULL)
    return;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_print(s, f) == OK);
  set_destroy(s);
  fclose(f);
  remove(SET_FILE);
}

void test2_set_print() {
  Set *s = NULL;
  FILE *f;
  if ((f = fopen(SET_FILE, "w")) == NULL)
    return;
  PRINT_TEST_RESULT(set_print(s, f) == ERROR);
  fclose(f);
  remove(SET_FILE);
}

void test3_set_print() {
  Set *s;
  s = set_create();
  set_add_id(s, ID);
  PRINT_TEST_RESULT(set_print(s, NULL) == ERROR);
  set_destroy(s);
}