/** 
 * @brief It tests enemy module
 * 
 * @file enemy_test.c
 * @author Javier San Andres
 * @version 3.0 
 * @date 09/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "enemy.h"
#include "enemy_test.h"
#include "test.h"

#define MAX_TESTS 29                 /*!<Maximum number of test to be executed*/        
#define ID 1                         /*!<Id for initializing an enemy*/
#define HEALTH 3                     /*!<Number of life points for an enemy*/
#define ENMYNAME "pepe"              /*!<Name to be set to an enemy*/
#define ENMYDESC "/oo\\"             /*!<Graphical descriptor for the enemy*/
#define ID_LOC 4                     /*!<enemy location to assing to an enemy*/
#define ENMYFILE "enemy_test.txt"    /*!<Name to an auxiliary file for testing*/

/** 
 * @brief Main function for ENEMY unit tests. 
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
    printf("\n\nRunning all test for module enemy:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_enemy_create();
  if (all || test == 2) test2_enemy_create();
  if (all || test == 3) test3_enemy_create();
  if (all || test == 4) test1_enemy_get_id();
  if (all || test == 5) test2_enemy_get_id();
  if (all || test == 6) test1_enemy_get_name();
  if (all || test == 7) test2_enemy_get_name();
  if (all || test == 8) test1_enemy_set_name();
  if (all || test == 9) test2_enemy_set_name();
  if (all || test == 10) test3_enemy_set_name();
  if (all || test == 11) test1_enemy_set_location();
  if (all || test == 12) test2_enemy_set_location();
  if (all || test == 13) test3_enemy_set_location();
  if (all || test == 14) test1_enemy_get_location();
  if (all || test == 15) test2_enemy_get_location();
  if (all || test == 16) test1_enemy_get_health();
  if (all || test == 17) test2_enemy_get_health();
  if (all || test == 18) test1_enemy_set_health();
  if (all || test == 19) test2_enemy_set_health();
  if (all || test == 20) test3_enemy_set_health();
  if (all || test == 21) test1_enemy_print();
  if (all || test == 22) test2_enemy_print();
  if (all || test == 23) test3_enemy_print();
  if (all || test == 24) test1_enemy_set_edesc();
  if (all || test == 25) test2_enemy_set_edesc();
  if (all || test == 26) test3_enemy_set_edesc();
  if (all || test == 27) test1_enemy_get_edesc();
  if (all || test == 28) test2_enemy_get_edesc();
  if (all || test == 29) test3_enemy_get_edesc();


  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_enemy_create() {
    Enemy *enemy;
    enemy=enemy_create(ID);
    PRINT_TEST_RESULT(enemy != NULL);
    enemy_destroy(enemy);
}

void test2_enemy_create() {
    Enemy *enemy;
    enemy=enemy_create(ID);
    PRINT_TEST_RESULT(enemy_get_id(enemy) == ID);
    enemy_destroy(enemy);
}

void test3_enemy_create() {
    Enemy *enemy;
    enemy=enemy_create(NO_ID);
    PRINT_TEST_RESULT(enemy == NULL);
}

void test1_enemy_get_id() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  PRINT_TEST_RESULT(enemy_get_id(enemy) == ID);
  enemy_destroy(enemy);
}

void test2_enemy_get_id() {
  Enemy *enemy = NULL;
  PRINT_TEST_RESULT(enemy_get_id(enemy) == NO_ID);
}

void test1_enemy_get_name() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  enemy_set_name(enemy, ENMYNAME);
  PRINT_TEST_RESULT(strcmp(enemy_get_name(enemy), ENMYNAME) == 0);
  enemy_destroy(enemy);
}

void test2_enemy_get_name() {
  Enemy *enemy = NULL;
  PRINT_TEST_RESULT(enemy_get_name(enemy) == NULL);
}

void test1_enemy_set_name() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  PRINT_TEST_RESULT(enemy_set_name(enemy, ENMYNAME) == OK);
  enemy_destroy(enemy);
}

void test2_enemy_set_name() {
  Enemy *enemy = NULL;
  PRINT_TEST_RESULT(enemy_set_name(enemy,ENMYNAME) == ERROR);
}

void test3_enemy_set_name() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  PRINT_TEST_RESULT(enemy_set_name(enemy, NULL) == ERROR);
  enemy_destroy(enemy);
}

void test1_enemy_set_location() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  PRINT_TEST_RESULT(enemy_set_location(enemy, ID_LOC) == OK);
  enemy_destroy(enemy);
}

void test2_enemy_set_location() {
  Enemy *enemy = NULL;
  PRINT_TEST_RESULT(enemy_set_location(enemy, ID_LOC) == ERROR);
}

void test3_enemy_set_location() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  PRINT_TEST_RESULT(enemy_set_location(enemy, NO_ID) == ERROR);
  enemy_destroy(enemy);
}

void test1_enemy_get_location() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  enemy_set_location(enemy, ID_LOC);
  PRINT_TEST_RESULT(enemy_get_location(enemy) == ID_LOC);
  enemy_destroy(enemy);
}

void test2_enemy_get_location() {
  Enemy *enemy = NULL;
  PRINT_TEST_RESULT(enemy_get_location(enemy) == NO_ID);
}

void test1_enemy_get_health() {
  Enemy *enemy;
  enemy = enemy_create(ID);
  enemy_set_health(enemy, HEALTH);
  PRINT_TEST_RESULT(enemy_get_health(enemy) == HEALTH);
  enemy_destroy(enemy);
}

void test2_enemy_get_health() {
  Enemy *enemy = NULL;
  PRINT_TEST_RESULT(enemy_get_health(enemy) == NO_HEALTH);
}

void test1_enemy_set_health() {
  Enemy *enemy;
  enemy = enemy_create(5);
  PRINT_TEST_RESULT(enemy_set_health(enemy, HEALTH) == OK);
  enemy_destroy(enemy);
}

void test2_enemy_set_health() {
  Enemy *enemy = NULL;
  PRINT_TEST_RESULT(enemy_set_health(enemy, HEALTH) == ERROR);
}

void test3_enemy_set_health() {
  Enemy *enemy;
  enemy = enemy_create(5);
  PRINT_TEST_RESULT(enemy_set_health(enemy, NO_HEALTH) == OK);
  enemy_destroy(enemy);
}

void test1_enemy_print() {
  Enemy *enemy;
  FILE *f;
  if ((f = fopen(ENMYFILE, "w")) == NULL)
    return;
  enemy = enemy_create(ID);
  enemy_set_health(enemy, HEALTH);
  enemy_set_name(enemy, ENMYNAME);
  PRINT_TEST_RESULT(enemy_print(enemy, f) == OK);
  enemy_destroy(enemy);
  fclose(f);
  remove(ENMYFILE);
}

void test2_enemy_print() {
  Enemy *enemy = NULL;
  FILE *f;
  if ((f = fopen(ENMYFILE, "w")) == NULL)
    return;
  PRINT_TEST_RESULT(enemy_print(enemy, f) == ERROR);
  fclose(f);
  remove(ENMYFILE);
}

void test3_enemy_print() {
  Enemy *enemy = NULL;
  enemy=enemy_create(ID);
  PRINT_TEST_RESULT(enemy_print(enemy, NULL) == ERROR);
  enemy_destroy(enemy);
}


void test1_enemy_set_edesc() {
  Enemy *enmy = NULL;
  enmy=enemy_create(ID);
  PRINT_TEST_RESULT(enemy_set_edesc(enmy, ENMYDESC) == OK);
  enemy_destroy(enmy);
}

void test2_enemy_set_edesc() {
  Enemy *enmy = NULL;
  enmy=enemy_create(ID);
  PRINT_TEST_RESULT(enemy_set_edesc(enmy, NULL) == ERROR);
  enemy_destroy(enmy);
}

void test3_enemy_set_edesc() {
  Enemy *enmy = NULL;
  PRINT_TEST_RESULT(enemy_set_edesc(enmy, ENMYDESC) == ERROR);
}

void test1_enemy_get_edesc() {
  Enemy *enmy = NULL;
  enmy=enemy_create(ID);
  enemy_set_edesc(enmy, ENMYDESC);
  PRINT_TEST_RESULT(enemy_get_edesc(enmy) != NULL);
  enemy_destroy(enmy);
}

void test2_enemy_get_edesc() {
  Enemy *enmy = NULL;
  enmy=enemy_create(ID);
  PRINT_TEST_RESULT(enemy_get_edesc(enmy) == NULL);
  enemy_destroy(enmy);
}

void test3_enemy_get_edesc() {
  Enemy *enmy = NULL;
  PRINT_TEST_RESULT(enemy_get_edesc(enmy) == NULL);
}
