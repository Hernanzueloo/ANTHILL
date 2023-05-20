/** 
 * @brief It tests object module
 * 
 * @file object_test.c
 * @author Diego Rodríguez Ortiz
 * @version 3.0 
 * @date 31/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 52                  /*!<Maximum number of test to be executed*/
#define ID 1                          /*!<Id for an object*/
#define OBJDESC "Objeto mágico"       /*!<Textual description for an object*/
#define OBJNAME "pepe"                /*!<Name for an object*/
#define ID_OBJ 5                      /*!<Id for an object*/
#define ID_OBJ2 7                     /*!<Id for an object*/
#define ID_OBJ3 11                    /*!<Id for an object*/
#define ID_LOC 4                      /*!<Id for a space location*/
#define MAX_OBJ 2                     /*!<Maximum number of objects for player's inventory*/
#define OBJFILE "object_test.txt"     /*!<Name to an auxiliary file for testing*/

/** 
 * @brief Main function for object unit tests. 
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
    printf("\n\nRunning all test for module object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_object_create();
  if (all || test == 2) test2_object_create();
  if (all || test == 3) test3_object_create();
  if (all || test == 4) test1_object_get_id();
  if (all || test == 5) test2_object_get_id();
  if (all || test == 6) test1_object_get_name();
  if (all || test == 7) test2_object_get_name();
  if (all || test == 8) test1_object_set_name();
  if (all || test == 9) test2_object_set_name();
  if (all || test == 10) test3_object_set_name();
  if (all || test == 11) test1_object_get_location();
  if (all || test == 12) test2_object_get_location();
  if (all || test == 13) test1_object_set_location();
  if (all || test == 14) test2_object_set_location();
  if (all || test == 15) test3_object_set_location();
  if (all || test == 16) test1_object_get_hidden();
  if (all || test == 17) test2_object_get_hidden();
  if (all || test == 18) test1_object_set_hidden();
  if (all || test == 19) test2_object_set_hidden();
  if (all || test == 20) test3_object_set_hidden();
  if (all || test == 21) test1_object_get_movable();
  if (all || test == 22) test2_object_get_movable();
  if (all || test == 23) test1_object_set_movable();
  if (all || test == 24) test2_object_set_movable();
  if (all || test == 25) test3_object_set_movable();
  if (all || test == 26) test1_object_get_dependency();
  if (all || test == 27) test2_object_get_dependency();
  if (all || test == 28) test1_object_set_dependency();
  if (all || test == 29) test2_object_get_dependency();
  if (all || test == 30) test1_object_get_open();
  if (all || test == 31) test2_object_get_open();
  if (all || test == 32) test1_object_set_open();
  if (all || test == 33) test2_object_set_open();
  if (all || test == 34) test3_object_set_open();
  if (all || test == 35) test1_object_get_illuminate();
  if (all || test == 36) test2_object_get_illuminate();
  if (all || test == 37) test1_object_set_illuminate();
  if (all || test == 38) test2_object_set_illuminate();
  if (all || test == 39) test3_object_set_illuminate();
  if (all || test == 40) test1_object_get_turnedon();
  if (all || test == 41) test2_object_get_turnedon();
  if (all || test == 42) test1_object_set_turnedon();
  if (all || test == 43) test2_object_set_turnedon();
  if (all || test == 44) test3_object_set_turnedon();
  if (all || test == 45) test1_object_get_description();
  if (all || test == 46) test2_object_get_description();
  if (all || test == 47) test1_object_set_description();
  if (all || test == 48) test2_object_set_description();
  if (all || test == 49) test3_object_set_description();
  if (all || test == 50) test1_object_print();
  if (all || test == 51) test2_object_print();
  if (all || test == 52) test3_object_print();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_object_create() {
    Object* object;
    object=object_create(ID);
    PRINT_TEST_RESULT(object != NULL);
    object_destroy(object);
}

void test2_object_create() {
    Object* object;
    object=object_create(ID);
    PRINT_TEST_RESULT(object_get_id(object) == ID);
    object_destroy(object);
}

void test3_object_create() {
    Object* object;
    object=object_create(NO_ID);
    PRINT_TEST_RESULT(object == NULL);
}

void test1_object_get_id() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_get_id(object) == ID);
  object_destroy(object);
}

void test2_object_get_id() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_id(object) == NO_ID);
}

void test1_object_get_name() {
  Object* object;
  object = object_create(ID);
  object_set_name(object,OBJNAME);
  PRINT_TEST_RESULT(strcmp(object_get_name(object), OBJNAME) == 0);
  object_destroy(object);
}

void test2_object_get_name() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_name(object) == NULL);
}

void test1_object_set_name() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_name(object, OBJNAME) == OK);
  object_destroy(object);
}

void test2_object_set_name() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_name(object,OBJNAME) == ERROR);
}

void test3_object_set_name() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_name(object, NULL) == ERROR);
  object_destroy(object);
}

void test1_object_get_location() {
  Object* object;
  object = object_create(ID);
  object_set_location(object, ID_LOC);
  PRINT_TEST_RESULT(object_get_location(object) == ID_LOC);
  object_destroy(object);
}

void test2_object_get_location() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_location(object) == NO_ID);
}

void test1_object_set_location() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_location(object, ID_LOC) == OK);
  object_destroy(object);
}

void test2_object_set_location() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_location(object, ID_LOC) == ERROR);
}

void test3_object_set_location() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_location(object, NO_ID) == ERROR);
  object_destroy(object);
}





void test1_object_get_hidden() {
  Object* object;
  object = object_create(ID);
  object_set_hidden(object, TRUE);
  PRINT_TEST_RESULT(object_get_hidden(object) == TRUE);
  object_destroy(object);
}

void test2_object_get_hidden() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_hidden(object) == FALSE);
}

void test1_object_set_hidden() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_hidden(object, TRUE) == OK);
  object_destroy(object);
}

void test2_object_set_hidden() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_hidden(object, TRUE) == ERROR);
}

void test3_object_set_hidden() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_hidden(object, FALSE) == OK);
  object_destroy(object);
}



void test1_object_get_movable() {
  Object* object;
  object = object_create(ID);
  object_set_movable(object, TRUE);
  PRINT_TEST_RESULT(object_get_movable(object) == TRUE);
  object_destroy(object);
}

void test2_object_get_movable() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_movable(object) == FALSE);
}

void test1_object_set_movable() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_movable(object, TRUE) == OK);
  object_destroy(object);
}

void test2_object_set_movable() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_movable(object, TRUE) == ERROR);
}

void test3_object_set_movable() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_movable(object, FALSE) == OK);
  object_destroy(object);
}




void test1_object_get_dependency() {
  Object* object;
  object = object_create(ID);
  object_set_dependency(object, (Id)5);
  PRINT_TEST_RESULT(object_get_dependency(object) == (Id)5);
  object_destroy(object);
}

void test2_object_get_dependency() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_dependency(object) == NO_ID);
}

void test1_object_set_dependency() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_dependency(object, (Id)5) == OK);
  object_destroy(object);
}

void test2_object_set_dependency() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_dependency(object, (Id)5) == ERROR);
}

void test3_object_set_dependency() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_dependency(object, NO_ID) == OK);
  object_destroy(object);
}




void test1_object_get_open() {
  Object* object;
  object = object_create(ID);
  object_set_open(object, (Id)5);
  PRINT_TEST_RESULT(object_get_open(object) == (Id)5);
  object_destroy(object);
}

void test2_object_get_open() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_open(object) == NO_ID);
}

void test1_object_set_open() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_open(object, (Id)5) == OK);
  object_destroy(object);
}

void test2_object_set_open() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_open(object, (Id)5) == ERROR);
}

void test3_object_set_open() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_open(object, NO_ID) == OK);
  object_destroy(object);
}




void test1_object_get_illuminate() {
  Object* object;
  object = object_create(ID);
  object_set_illuminate(object, TRUE);
  PRINT_TEST_RESULT(object_get_illuminate(object) == TRUE);
  object_destroy(object);
}

void test2_object_get_illuminate() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_illuminate(object) == FALSE);
}

void test1_object_set_illuminate() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_illuminate(object, TRUE) == OK);
  object_destroy(object);
}

void test2_object_set_illuminate() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_illuminate(object, TRUE) == ERROR);
}

void test3_object_set_illuminate() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_illuminate(object, FALSE) == OK);
  object_destroy(object);
}






void test1_object_get_turnedon() {
  Object* object;
  object = object_create(ID);
  object_set_turnedon(object, TRUE);
  PRINT_TEST_RESULT(object_get_turnedon(object) == TRUE);
  object_destroy(object);
}

void test2_object_get_turnedon() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_turnedon(object) == FALSE);
}

void test1_object_set_turnedon() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_turnedon(object, TRUE) == OK);
  object_destroy(object);
}

void test2_object_set_turnedon() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_turnedon(object, TRUE) == ERROR);
}

void test3_object_set_turnedon() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_turnedon(object, FALSE) == OK);
  object_destroy(object);
}

void test1_object_get_description() {
  Object* object;
  object = object_create(ID);
  object_set_tdesc(object, OBJDESC);
  PRINT_TEST_RESULT(strcmp(object_get_tdesc(object), OBJDESC) == 0);
  object_destroy(object);
}

void test2_object_get_description() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_get_tdesc(object) == NULL);
}

void test1_object_set_description() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_tdesc(object,  OBJDESC) == OK);
  object_destroy(object);
}

void test2_object_set_description() {
  Object* object = NULL;
  PRINT_TEST_RESULT(object_set_tdesc(object,OBJDESC) == ERROR);
}

void test3_object_set_description() {
  Object* object;
  object = object_create(ID);
  PRINT_TEST_RESULT(object_set_tdesc(object, NULL) == ERROR);
  object_destroy(object);
}

void test1_object_print() {
  Object* object;
  FILE *f;
  if ((f = fopen(OBJFILE, "w")) == NULL)
    return;
  object = object_create(ID);
  object_set_tdesc(object, OBJDESC);
  object_set_name(object, OBJNAME);
  PRINT_TEST_RESULT(object_print(object, f) == OK);
  object_destroy(object);
  fclose(f);
  remove(OBJFILE);
}

void test2_object_print() {
  Object* object = NULL;
  FILE *f;
  if ((f = fopen(OBJFILE, "w")) == NULL)
    return;
  PRINT_TEST_RESULT(object_print(object, f) == ERROR);
  fclose(f);
  remove(OBJFILE);
}

void test3_object_print() {
  Object* object = NULL;
  object=object_create(ID);
  PRINT_TEST_RESULT(object_print(object, NULL) == ERROR);
  object_destroy(object);
}
