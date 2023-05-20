/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Javier San Andres
 * @version 3.0 
 * @date 19/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <strings.h>
#include "space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 51                         /*!<Maximum number of test to be executed*/
#define ID 1                                 /*!<Id for a space*/
#define SPCNAME "adios"                      /*!<Name for a space*/
#define SPCTDESC "Great place to chill"      /*!<Textual description for a space*/
#define ID_OBJ 3                             /*!<Id of an object to place in a space*/
#define ID_OBJ2 5                            /*!<Id of an object to place in a space*/
#define SPC_FILE "space_test.txt"            /*!<Name of an auxiliary file for testing*/

/** 
 * @brief Main function for SPACE unit tests. 
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
    printf("\n\nRunning all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_space_create();
  if (all || test == 2) test2_space_create();
  if (all || test == 3) test1_space_get_id();
  if (all || test == 4) test2_space_get_id();
  if (all || test == 5) test1_space_get_name();
  if (all || test == 6) test2_space_get_name();
  if (all || test == 7) test1_space_set_name();
  if (all || test == 8) test2_space_set_name();
  if (all || test == 9) test3_space_set_name();
  if (all || test == 10) test1_space_get_light();
  if (all || test == 11) test2_space_get_light();
  if (all || test == 12) test1_space_set_light();
  if (all || test == 13) test2_space_set_light();
  if (all || test == 14) test3_space_set_light();
  if (all || test == 15) test1_space_get_flooded();
  if (all || test == 16) test2_space_get_flooded();
  if (all || test == 17) test1_space_set_flooded();
  if (all || test == 18) test2_space_set_flooded();
  if (all || test == 19) test3_space_set_flooded();
  if (all || test == 20) test1_space_add_object();
  if (all || test == 21) test2_space_add_object();
  if (all || test == 22) test3_space_add_object();
  if (all || test == 23) test1_space_remove_object();
  if (all || test == 24) test2_space_remove_object();
  if (all || test == 25) test3_space_remove_object();
  if (all || test == 26) test4_space_remove_object();
  if (all || test == 27) test5_space_remove_object();
  if (all || test == 28) test1_space_contains_object();
  if (all || test == 29) test2_space_contains_object();
  if (all || test == 30) test3_space_contains_object();
  if (all || test == 31) test4_space_contains_object();
  if (all || test == 32) test1_space_get_objects();
  if (all || test == 33) test2_space_get_objects();
  if (all || test == 34) test3_space_get_objects();
  if (all || test == 35) test4_space_get_objects();
  if (all || test == 36) test1_space_set_gdesc();
  if (all || test == 37) test2_space_set_gdesc();
  if (all || test == 38) test3_space_set_gdesc();
  if (all || test == 39) test4_space_set_gdesc();
  if (all || test == 40) test1_space_get_gdesc();
  if (all || test == 41) test2_space_get_gdesc();
  if (all || test == 42) test3_space_get_gdesc();  
  if (all || test == 43) test1_space_set_tdesc();
  if (all || test == 44) test2_space_set_tdesc();
  if (all || test == 45) test3_space_set_tdesc();
  if (all || test == 46) test1_space_get_tdesc();
  if (all || test == 47) test2_space_get_tdesc();
  if (all || test == 48) test3_space_get_tdesc();
  if (all || test == 49) test1_space_print();
  if (all || test == 50) test2_space_print();
  if (all || test == 51) test3_space_print();


  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_space_create() {
  int result;
  Space *s;
  s = space_create(ID);
  result=s!=NULL ;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_get_id(s) == ID);
  space_destroy(s);
}

void test1_space_get_id() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_get_id(s) == ID);
  space_destroy(s);
}

void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_get_name() {
  Space *s;
  s = space_create(ID);
  space_set_name(s, SPCNAME);
  PRINT_TEST_RESULT(strcasecmp(space_get_name(s), SPCNAME) == 0);
  space_destroy(s);
}

void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_set_name() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_set_name(s,SPCNAME) == OK);
  space_destroy(s);
}

void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, SPCNAME) == ERROR);
}

void test3_space_set_name() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}


void test1_space_get_light() {
  Space *s;
  s = space_create(ID);
  space_set_light(s, TRUE);
  PRINT_TEST_RESULT(space_get_light(s) == TRUE);
  space_destroy(s);
}

void test2_space_get_light() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_light(s) == FALSE);
}

void test1_space_set_light() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_set_light(s,TRUE) == OK);
  space_destroy(s);
}

void test2_space_set_light() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_light(s, FALSE) == ERROR);
}

void test3_space_set_light() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_set_light(s, FALSE) == OK);
  space_destroy(s);
}

void test1_space_get_flooded() {
  Space *s;
  s = space_create(ID);
  space_set_flooded(s, SAFE);
  PRINT_TEST_RESULT(space_get_flooded(s) == SAFE);
  space_destroy(s);
}

void test2_space_get_flooded() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_flooded(s) == SUNK);
}

void test1_space_set_flooded() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_set_flooded(s, FLOODED) == OK);
  space_destroy(s);
}

void test2_space_set_flooded() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_flooded(s, SAFE) == ERROR);
}

void test3_space_set_flooded() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_set_flooded(s, SUNK) == OK);
  space_destroy(s);
}



void test1_space_add_object() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_add_object(s, ID_OBJ) == OK);
  space_destroy(s);
}

void test2_space_add_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object(s, ID_OBJ) == ERROR);
}

void test3_space_add_object() {
  Space *s;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_add_object(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test1_space_remove_object() {
  Space *s;
  s=space_create(ID);
  space_add_object(s, ID_OBJ);
  PRINT_TEST_RESULT(space_remove_object(s, ID_OBJ) == OK);
  space_destroy(s);
}

void test2_space_remove_object() {
  Space *s;
  s=space_create(ID);
  PRINT_TEST_RESULT(space_remove_object(s, ID_OBJ) == OK);
  space_destroy(s);
}

void test3_space_remove_object() {
  Space *s;
  s=space_create(ID);
  space_add_object(s, ID_OBJ);
  PRINT_TEST_RESULT(space_remove_object(s, ID_OBJ2) == OK);
  space_destroy(s);
}

void test4_space_remove_object() {
  Space *s;
  s=space_create(ID);
  PRINT_TEST_RESULT(space_remove_object(s, NO_ID) == ERROR);
  space_destroy(s);
}

void test5_space_remove_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_remove_object(s, ID_OBJ) == ERROR);
}

void test1_space_contains_object() {
  Space *s = NULL;
  s=space_create(ID);
  space_add_object(s, ID_OBJ);
  PRINT_TEST_RESULT(space_contains_object(s, ID_OBJ) == TRUE);
  space_destroy(s);
}

void test2_space_contains_object() {
  Space *s = NULL;
  s=space_create(1);
  space_add_object(s, ID_OBJ);
  PRINT_TEST_RESULT(space_contains_object(s, ID_OBJ2) == FALSE);
  space_destroy(s);
}

void test3_space_contains_object() {
  Space *s = NULL;
  s=space_create(ID);
  PRINT_TEST_RESULT(space_contains_object(s, ID_OBJ) == FALSE);
  space_destroy(s);
}

void test4_space_contains_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_contains_object(s, ID_OBJ) == FALSE);
}

void test1_space_get_objects() {
  Space *s = NULL;
  Id *id;
  int num = 0;
  s = space_create(ID);
  space_add_object(s, ID_OBJ);
  id = space_get_objects(s, &num);
  PRINT_TEST_RESULT(id != NULL);
  space_destroy(s);
  free(id);
}

void test2_space_get_objects() {
  Space *s = NULL;
  int num = 0;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_get_objects(s, &num) == NULL);
  space_destroy(s);
}

void test3_space_get_objects() {
  Space *s = NULL;
  Id *id;
  int num = 0;
  s = space_create(ID);
  space_add_object(s, ID_OBJ);
  id = space_get_objects(s, &num);
  PRINT_TEST_RESULT(num == 1);
  space_destroy(s);
  free(id);
}

void test4_space_get_objects() {
  Space *s = NULL;
  int num = 0;
  space_add_object(s, ID_OBJ);
  PRINT_TEST_RESULT(space_get_objects(s, &num) == NULL);
}

void test1_space_set_gdesc() {
  char *gdesc[GRAPHIC_ROWS];
  int i = 0;
  Space *s = NULL;
  s = space_create(ID);

  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if ((gdesc[i] = (char *)calloc(GRAPHIC_COLS, sizeof(char))) == NULL)
    {
      for (; i>=0; i--)
        free(gdesc[i]);
      return;
    }
  }

  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);

  for (i = 0; i < GRAPHIC_ROWS; i++)
    free(gdesc[i]);
  space_destroy(s);
}

void test2_space_set_gdesc() {
  char *gdesc[GRAPHIC_ROWS];
  int i = 0;
  Space *s = NULL;
  s = space_create(ID);

  for (i = 0; i < GRAPHIC_ROWS-1; i++)
  {
    if ((gdesc[i] = (char *)calloc(GRAPHIC_COLS, sizeof(char))) == NULL)
    {
      for (; i>=0; i--)
        free(gdesc[i]);
      return;
    }
  }
  gdesc[GRAPHIC_ROWS-1] = NULL;

  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
  for (i = 0; i < GRAPHIC_ROWS-1; i++)
    free(gdesc[i]);
  space_destroy(s);
}

void test3_space_set_gdesc() {
  Space *s = NULL;
  char **gdesc = NULL;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
  space_destroy(s);
}

void test4_space_set_gdesc() {
  Space *s = NULL;
  char *gdesc[GRAPHIC_ROWS];
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == ERROR);
}

void test1_space_get_gdesc() {
  char *gdesc[GRAPHIC_ROWS];
  int i = 0;
  Space *s = NULL;
  s = space_create(ID);

  for (i = 0; i < GRAPHIC_ROWS; i++)
  {
    if ((gdesc[i] = (char *)calloc(GRAPHIC_COLS, sizeof(char))) == NULL)
    {
      for (; i>=0; i--)
        free(gdesc[i]);
      return;
    }
  }

  space_set_gdesc(s, gdesc);
  PRINT_TEST_RESULT(space_get_gdesc(s) != NULL);
  for (i = 0; i < GRAPHIC_ROWS; i++)
    free(gdesc[i]);
  space_destroy(s);
}

void test2_space_get_gdesc() {
  Space *s = NULL;
  s = space_create(ID);
  PRINT_TEST_RESULT(space_get_gdesc(s) == NULL);
  space_destroy(s);
}

void test3_space_get_gdesc() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_gdesc(s) == NULL);
}


void test1_space_set_tdesc() {
  Space *s = NULL;
  s=space_create(ID);
  PRINT_TEST_RESULT(space_set_tdesc(s, SPCTDESC) == OK);
  space_destroy(s);
}

void test2_space_set_tdesc() {
  Space *s = NULL;
  s=space_create(ID);
  PRINT_TEST_RESULT(space_set_tdesc(s, NULL) == ERROR);
  space_destroy(s);
}

void test3_space_set_tdesc() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_tdesc(s, SPCTDESC) == ERROR);
}

void test1_space_get_tdesc() {
  Space *s = NULL;
  s=space_create(ID);
  space_set_tdesc(s, SPCTDESC);
  PRINT_TEST_RESULT(space_get_tdesc(s) != NULL);
  space_destroy(s);
}

void test2_space_get_tdesc() {
  Space *s = NULL;
  s=space_create(ID);
  PRINT_TEST_RESULT(space_get_tdesc(s) == NULL);
  space_destroy(s);
}

void test3_space_get_tdesc() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_tdesc(s) == NULL);
}


void test1_space_print() {
  Space *space;
  FILE *f;
  if ((f = fopen(SPC_FILE, "w")) == NULL)
    return;
  space = space_create(ID);
  space_set_tdesc(space, SPCTDESC);
  space_set_name(space, SPCNAME);
  PRINT_TEST_RESULT(space_print(space, f) == OK);
  space_destroy(space);
  fclose(f);
  remove(SPC_FILE);
}

void test2_space_print() {
  Space *space = NULL;
  FILE *f;
  if ((f = fopen(SPC_FILE, "w")) == NULL)
    return;
  PRINT_TEST_RESULT(space_print(space, f) == ERROR);
  fclose(f);
  remove(SPC_FILE);
}

void test3_space_print() {
  Space *space = NULL;
  space=space_create(ID);
  PRINT_TEST_RESULT(space_print(space, NULL) == ERROR);
  space_destroy(space);
}