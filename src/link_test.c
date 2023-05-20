/** 
 * @brief It tests link module
 * 
 * @file link_test.c
 * @author Javier San Andres
 * @version 3.0 
 * @date 29/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 33                /*!<Maximum number of test to be executed*/
#define ID 1                        /*!<Id for a link*/
#define LNKNAME "pepe"              /*!<Name for a link*/
#define ID_LOC 5                    /*!<Id of the space to locate the origin or destination at*/
#define DIR NORTH                   /*!<Direction for a link*/
#define LINK_FILE "link_test.txt"   /*!<Name to an auxiliary file for testing*/


/** 
 * @brief Main function for link unit tests. 
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
    printf("\n\nRunning all test for module link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test3_link_create();
  if (all || test == 4) test1_link_get_id();
  if (all || test == 5) test2_link_get_id();
  if (all || test == 6) test1_link_get_name();
  if (all || test == 7) test2_link_get_name();
  if (all || test == 8) test1_link_set_name();
  if (all || test == 9) test2_link_set_name();
  if (all || test == 10) test3_link_set_name();
  if (all || test == 11) test1_link_set_origin();
  if (all || test == 12) test2_link_set_origin();
  if (all || test == 13) test3_link_set_origin();
  if (all || test == 14) test1_link_get_origin();
  if (all || test == 15) test2_link_get_origin();
  if (all || test == 16) test1_link_set_destination();
  if (all || test == 17) test2_link_set_destination();
  if (all || test == 18) test3_link_set_destination();
  if (all || test == 19) test1_link_get_destination();
  if (all || test == 20) test2_link_get_destination();
  if (all || test == 21) test1_link_set_direction();
  if (all || test == 22) test2_link_set_direction();
  if (all || test == 23) test3_link_set_direction();
  if (all || test == 24) test1_link_get_direction();
  if (all || test == 25) test2_link_get_direction();
  if (all || test == 26) test1_link_set_status();
  if (all || test == 27) test2_link_set_status();
  if (all || test == 28) test3_link_set_status();
  if (all || test == 29) test1_link_get_status();
  if (all || test == 30) test2_link_get_status();
  if (all || test == 31) test1_link_print();
  if (all || test == 32) test2_link_print();
  if (all || test == 33) test3_link_print();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_link_create() {
    Link *link;
    link=link_create(ID);
    PRINT_TEST_RESULT(link != NULL);
    link_destroy(link);
}

void test2_link_create() {
    Link *link;
    link=link_create(ID);
    PRINT_TEST_RESULT(link_get_id(link) == ID);
    link_destroy(link);
}

void test3_link_create() {
    Link *link;
    link=link_create(NO_ID);
    PRINT_TEST_RESULT(link == NULL);
}

void test1_link_get_id() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_get_id(link) == ID);
  link_destroy(link);
}

void test2_link_get_id() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_id(link) == NO_ID);
}

void test1_link_get_name() {
  Link *link;
  link = link_create(ID);
  link_set_name(link, LNKNAME);
  PRINT_TEST_RESULT(strcmp(link_get_name(link), LNKNAME) == 0);
  link_destroy(link);
}

void test2_link_get_name() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_name(link) == NULL);
}

void test1_link_set_name() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_name(link, LNKNAME) == OK);
  link_destroy(link);
}

void test2_link_set_name() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_name(link, LNKNAME) == ERROR);
}

void test3_link_set_name() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
  link_destroy(link);
}

void test1_link_set_origin() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_origin(link, ID_LOC) == OK);
  link_destroy(link);
}

void test2_link_set_origin() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_origin(link, ID_LOC) == ERROR);
}

void test3_link_set_origin() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_origin(link, NO_ID) == ERROR);
  link_destroy(link);
}

void test1_link_get_origin() {
  Link *link;
  link = link_create(ID);
  link_set_origin(link, ID_LOC);
  PRINT_TEST_RESULT(link_get_origin(link) == ID_LOC);
  link_destroy(link);
}

void test2_link_get_origin() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_origin(link) == NO_ID);
}

void test1_link_set_destination() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_destination(link, ID_LOC) == OK);
  link_destroy(link);
}

void test2_link_set_destination() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_destination(link, ID_LOC) == ERROR);
}

void test3_link_set_destination() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_destination(link, NO_ID) == ERROR);
  link_destroy(link);
}

void test1_link_get_destination() {
  Link *link;
  link = link_create(ID);
  link_set_destination(link, ID_LOC);
  PRINT_TEST_RESULT(link_get_destination(link) == ID_LOC);
  link_destroy(link);
}

void test2_link_get_destination() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_destination(link) == NO_ID);
}

void test1_link_set_direction() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_direction(link, DIR) == OK);
  link_destroy(link);
}

void test2_link_set_direction() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_direction(link, DIR) == ERROR);
}

void test3_link_set_direction() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_direction(link, NO_DIR) == ERROR);
  link_destroy(link);
}

void test1_link_get_direction() {
  Link *link;
  link = link_create(ID);
  link_set_direction(link, DIR);
  PRINT_TEST_RESULT(link_get_direction(link) == DIR);
  link_destroy(link);
}

void test2_link_get_direction() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_direction(link) == NO_DIR);
}

void test1_link_set_status() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_status(link, CLOSE) == OK);
  link_destroy(link);
}

void test2_link_set_status() {
  Link *link;
  link = link_create(ID);
  PRINT_TEST_RESULT(link_set_status(link, OPEN) == OK);
  link_destroy(link);
}

void test3_link_set_status() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_set_status(link, CLOSE) == ERROR);
}

void test1_link_get_status() {
  Link *link;
  link = link_create(ID);
  link_set_status(link, OPEN);
  PRINT_TEST_RESULT(link_get_status(link) == OPEN);
  link_destroy(link);
}

void test2_link_get_status() {
  Link *link = NULL;
  PRINT_TEST_RESULT(link_get_status(link) == CLOSE);
  link_destroy(link);
}



void test1_link_print() {
  Link *link;
  FILE *f;
  if ((f = fopen(LINK_FILE, "w")) == NULL)
    return;
  link = link_create(ID);
  link_set_name(link, LNKNAME);
  PRINT_TEST_RESULT(link_print(link, f) == OK);
  link_destroy(link);
  fclose(f);
  remove(LINK_FILE);
}

void test2_link_print() {
  Link *link = NULL;
  FILE *f;
  if ((f = fopen(LINK_FILE, "w")) == NULL)
    return;
  PRINT_TEST_RESULT(link_print(link, f) == ERROR);
  fclose(f);
  remove(LINK_FILE);
}

void test3_link_print() {
  Link *link = NULL;
  link=link_create(2);
  PRINT_TEST_RESULT(link_print(link, NULL) == ERROR);
  link_destroy(link);
}