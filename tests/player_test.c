/** 
 * @brief It tests player module
 * 
 * @file player_test.c
 * @author Diego Rodríguez Ortiz
 * @version 3.0 
 * @date 31/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 50                    /*!<Maximum number of test to be executed*/
#define ID 1                            /*!<Id for a player*/
#define HEALTH 3                        /*!<Number of life points for a player*/
#define PLYNAME "pepe"                  /*!<Name for the player*/
#define ID_OBJ 5                        /*!<Id of an object to be held by the player*/
#define ID_OBJ2 7                       /*!<Id of an object to be held by the player*/
#define ID_OBJ3 11                      /*!<Id of an object to be held by the player*/
#define ID_LOC 4                        /*!<Id of a space to locate the player at*/
#define MAX_OBJ 2                       /*!<Maximum number of objects in the player's inventory*/  
#define PLYFILE "player_test.txt"       /*!<Name of an auxiliary file for testing*/

/** 
 * @brief Main function for player unit tests. 
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
    printf("\n\nRunning all test for module player:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_player_create();
  if (all || test == 2) test2_player_create();
  if (all || test == 3) test3_player_create();
  if (all || test == 4) test1_player_get_id();
  if (all || test == 5) test2_player_get_id();
  if (all || test == 6) test1_player_get_name();
  if (all || test == 7) test2_player_get_name();
  if (all || test == 8) test1_player_set_name();
  if (all || test == 9) test2_player_set_name();
  if (all || test == 10) test3_player_set_name();
  if (all || test == 11) test1_player_set_location();
  if (all || test == 12) test2_player_set_location();
  if (all || test == 13) test3_player_set_location();
  if (all || test == 14) test1_player_get_location();
  if (all || test == 15) test2_player_get_location();
  if (all || test == 16) test1_player_get_health();
  if (all || test == 17) test2_player_get_health();
  if (all || test == 18) test1_player_set_health();
  if (all || test == 19) test2_player_set_health();
  if (all || test == 20) test3_player_set_health();
  if (all || test == 21) test1_player_get_objects();
  if (all || test == 22) test2_player_get_objects();
  if (all || test == 23) test3_player_get_objects();
  if (all || test == 24) test4_player_get_objects();
  if (all || test == 25) test1_player_add_objects();
  if (all || test == 26) test2_player_add_objects();
  if (all || test == 27) test3_player_add_objects();
  if (all || test == 28) test4_player_add_objects();
  if (all || test == 29) test5_player_add_objects();
  if (all || test == 29) test6_player_add_objects();
  if (all || test == 30) test7_player_add_objects();
  if (all || test == 31) test1_player_remove_objects();
  if (all || test == 32) test2_player_remove_objects();
  if (all || test == 33) test3_player_remove_objects();
  if (all || test == 34) test4_player_remove_objects();
  if (all || test == 35) test5_player_remove_objects();
  if (all || test == 36) test1_player_set_max_objects();
  if (all || test == 37) test2_player_set_max_objects();
  if (all || test == 38) test3_player_set_max_objects();
  if (all || test == 39) test1_player_get_max_objects();
  if (all || test == 40) test2_player_get_max_objects();
  if (all || test == 41) test1_player_get_num_objects();
  if (all || test == 42) test2_player_get_num_objects();
  if (all || test == 43) test1_player_print();
  if (all || test == 44) test2_player_print();
  if (all || test == 45) test3_player_print();
  if (all || test == 46) test1_player_get_type();
  if (all || test == 47) test2_player_get_type();
  if (all || test == 48) test1_player_set_type();
  if (all || test == 49) test2_player_set_type();
  if (all || test == 50) test3_player_set_type();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_player_create() {
    Player *player;
    player=player_create(ID);
    PRINT_TEST_RESULT(player != NULL);
    player_destroy(player);
}

void test2_player_create() {
    Player *player;
    player=player_create(ID);
    PRINT_TEST_RESULT(player_get_id(player) == ID);
    player_destroy(player);
}

void test3_player_create() {
    Player *player;
    player=player_create(NO_ID);
    PRINT_TEST_RESULT(player == NULL);
}

void test1_player_get_id() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_get_id(player) == ID);
  player_destroy(player);
}

void test2_player_get_id() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_id(player) == NO_ID);
}

void test1_player_get_name() {
  Player *player;
  player = player_create(ID);
  player_set_name(player,PLYNAME);
  PRINT_TEST_RESULT(strcmp(player_get_name(player), PLYNAME) == 0);
  player_destroy(player);
}

void test2_player_get_name() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_name(player) == NULL);
}

void test1_player_set_name() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_name(player, PLYNAME) == OK);
  player_destroy(player);
}

void test2_player_set_name() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_set_name(player,PLYNAME) == ERROR);
}

void test3_player_set_name() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_name(player, NULL) == ERROR);
  player_destroy(player);
}

void test1_player_set_location() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_location(player, ID_LOC) == OK);
  player_destroy(player);
}

void test2_player_set_location() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_set_location(player, ID_LOC) == ERROR);
}

void test3_player_set_location() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_location(player, NO_ID) == ERROR);
  player_destroy(player);
}

void test1_player_get_location() {
  Player *player;
  player = player_create(ID);
  player_set_location(player, ID_LOC);
  PRINT_TEST_RESULT(player_get_location(player) == ID_LOC);
  player_destroy(player);
}

void test2_player_get_location() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_location(player) == NO_ID);
}

void test1_player_get_health() {
  Player *player;
  player = player_create(ID);
  player_set_health(player, HEALTH);
  PRINT_TEST_RESULT(player_get_health(player) == HEALTH);
  player_destroy(player);
}

void test2_player_get_health() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_health(player) == NO_HEALTH);
}

void test1_player_set_health() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_health(player, HEALTH) == OK);
  player_destroy(player);
}

void test2_player_set_health() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_set_health(player, HEALTH) == ERROR);
}

void test3_player_set_health() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_health(player, NO_HEALTH) == ERROR);
  player_destroy(player);
}

void test1_player_get_objects(){
    Player * player = NULL;
    int num;
    Id*objs;
    player = player_create(ID);   
    player_add_object(player,ID_OBJ); 
    num = player_get_num_objects(player);
    objs = player_get_objects(player, &num);
    PRINT_TEST_RESULT(objs[0] == ID_OBJ);
    player_destroy(player);
    free(objs);
}

void test2_player_get_objects(){
    Player * player = NULL;
    int num;
    player = player_create(ID);
    player_add_object(player,NO_ID);
    num = player_get_num_objects(player);
    PRINT_TEST_RESULT(player_get_objects(player, &num)== NULL);
    player_destroy(player);
}

void test3_player_get_objects(){
    int num=1;
    PRINT_TEST_RESULT(player_get_objects(NULL, &num) == NULL);
}

void test4_player_get_objects(){
    Player * player = NULL;
    player = player_create(ID);   
    player_add_object(player,ID_OBJ); 
    PRINT_TEST_RESULT(player_get_objects(player, NULL) == NULL);
    player_destroy(player);
}

void test1_player_add_objects(){
    Player * player = NULL;
    player = player_create(ID);   
    PRINT_TEST_RESULT(player_add_object(player,ID_OBJ) == OK);
    player_destroy(player);
}

void test2_player_add_objects(){
    Player * player = NULL;
    int num;
    Id  *objs;
    STATUS st;
    player = player_create(ID);   
    st = player_add_object(player,ID_OBJ); 
    num = player_get_num_objects(player);
    objs= player_get_objects(player, &num);
    PRINT_TEST_RESULT(objs[num-1] == ID_OBJ && st == OK);
    player_destroy(player);
    free(objs);
}

void test3_player_add_objects(){
    Player * player = NULL;
    player = player_create(ID);   
    player_add_object(player,ID_OBJ);
    PRINT_TEST_RESULT(player_add_object(player,ID_OBJ) == OK);
    player_destroy(player);
}

void test4_player_add_objects(){
    Player * player = NULL;
    player = player_create(ID);  
    PRINT_TEST_RESULT(player_add_object(player,NO_ID)==ERROR );
    player_destroy(player);
}

void test5_player_add_objects(){
    PRINT_TEST_RESULT(player_add_object(NULL,ID_OBJ)==ERROR );
}

void test6_player_add_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID);   
    st = player_add_object(player,ID_OBJ);
    st  = player_add_object(player,ID_OBJ2);
    PRINT_TEST_RESULT(st == OK && player_get_num_objects(player) == 2 );
    player_destroy(player);
}
void test7_player_add_objects(){
    Player * player = NULL;
    player = player_create(ID);  
    player_set_max_objects(player,MAX_OBJ);
    player_add_object(player,ID_OBJ);
    player_add_object(player,ID_OBJ2);
    PRINT_TEST_RESULT(player_add_object(player,ID_OBJ3)==ERROR );
    player_destroy(player);
}

void test1_player_remove_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID);   
    st = player_add_object(player,ID_OBJ);
    st  = player_remove_object(player,ID_OBJ);
    PRINT_TEST_RESULT(st == OK && player_get_num_objects(player) == 0 );
    player_destroy(player);
}

void test2_player_remove_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID);   
    st = player_add_object(player,ID_OBJ);
    st  = player_remove_object(NULL,ID_OBJ);
    PRINT_TEST_RESULT(st == ERROR && player_get_num_objects(player) == 1 );
    player_destroy(player);
}

void test3_player_remove_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID);   
    st = player_add_object(player,ID_OBJ);
    st  = player_remove_object(player,NO_ID);
    PRINT_TEST_RESULT(st == ERROR );
    player_destroy(player);
}

void test4_player_remove_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID);   
    st = player_add_object(player,ID_OBJ);
    st  = player_remove_object(player,ID_OBJ2);
    PRINT_TEST_RESULT(st == OK && player_get_num_objects(player) == 1 );
    player_destroy(player);
}

void test5_player_remove_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID);   
    st  = player_remove_object(player,ID_OBJ);
    PRINT_TEST_RESULT(st == OK && player_get_num_objects(player) == 0 );
    player_destroy(player);
}

void test1_player_set_max_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID);   
    st = player_set_max_objects(player,MAX_OBJ);
    PRINT_TEST_RESULT(st == OK && player_get_max_objects(player) == MAX_OBJ );
    player_destroy(player);
}

void test2_player_set_max_objects(){
    Player * player = NULL;
    STATUS st;
    player = player_create(ID); 
    st = player_set_max_objects(player,MAX_OBJ);  
    st = player_set_max_objects(player,-1);
    PRINT_TEST_RESULT(st == ERROR && player_get_max_objects(player) == MAX_OBJ );
    player_destroy(player);
}

void test3_player_set_max_objects(){
    STATUS st;
    st = player_set_max_objects(NULL,MAX_OBJ);  
    PRINT_TEST_RESULT(st == ERROR );
}

void test1_player_get_max_objects(){
    Player * player = NULL;
    player = player_create(ID);   
    player_set_max_objects(player,MAX_OBJ);
    PRINT_TEST_RESULT( player_get_max_objects(player) == MAX_OBJ );
    player_destroy(player);
}

void test2_player_get_max_objects(){
    PRINT_TEST_RESULT(player_get_max_objects(NULL) == -1 );
}

void test1_player_get_num_objects(){
    Player * player = NULL;
    player = player_create(ID);   
    player_add_object(player,ID_OBJ);
    PRINT_TEST_RESULT( player_get_num_objects(player) == 1 );
    player_destroy(player);
}

void test2_player_get_num_objects(){
    PRINT_TEST_RESULT(player_get_num_objects(NULL) == -1 );
}

void test1_player_print() {
  Player *player;
  FILE *f;
  if ((f = fopen(PLYFILE, "w")) == NULL)
    return;
  player = player_create(ID);
  player_set_health(player, HEALTH);
  player_set_name(player, PLYNAME);
  PRINT_TEST_RESULT(player_print(player, f) == OK);
  player_destroy(player);
  fclose(f);
  remove(PLYFILE);
}

void test2_player_print() {
  Player *player = NULL;
  FILE *f;
  if ((f = fopen(PLYFILE, "w")) == NULL)
    return;
  PRINT_TEST_RESULT(player_print(player, f) == ERROR);
  fclose(f);
  remove(PLYFILE);
}

void test3_player_print() {
  Player *player = NULL;
  player=player_create(ID);
  PRINT_TEST_RESULT(player_print(player, NULL) == ERROR);
  player_destroy(player);
}

void test1_player_get_type() {
  Player *player;
  player = player_create(ID);
  player_set_type(player, ANT);
  PRINT_TEST_RESULT(player_get_type(player) == ANT);
  player_destroy(player);
}

void test2_player_get_type() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_get_type(player) == UNDEFPLY);
}

void test1_player_set_type() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_type(player, ANT) == OK);
  player_destroy(player);
}

void test2_player_set_type() {
  Player *player = NULL;
  PRINT_TEST_RESULT(player_set_type(player, ANT) == ERROR);
}

void test3_player_set_type() {
  Player *player;
  player = player_create(ID);
  PRINT_TEST_RESULT(player_set_type(player, -1) == ERROR);
  player_destroy(player);
}