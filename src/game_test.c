/**
 * @brief It tests game module
 *
 * @file game_test.c
 * @author Alejandro García Hernando - Diego Rodríguez Ortiz - David Brenchley Uriol - Javier San Andrés de Pedro
 * @version 3.0
 * @date 26/03/2023
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "game_test.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "space.h"
#include "test.h"
#include "rule.h"

#define MAX_TESTS 277                                           /*!<Maximum number of test to be executed*/
#define ID 29                                                   /*!<Id to be set to different Eds*/
#define ID_OBJECT 21                                            /*!<Id of an object*/
#define ID_LOC 122                                              /*!<Id of a space*/
#define ID_LOC2 123                                             /*!<Id of a space*/
#define ID_LINK 1                                               /*!<Id of a link*/
#define ID_SPACE 1                                              /*!<Id of a space*/
#define RULE "You have done this once before without success."                              /*!<Rule to be set to a dialogue*/
#define RULE_W_ARG "you made <something>"                                                   /*!<Rule with an argument to be substituted*/
#define RULE_W_ARGS "you made <something> and also picked <that other thing>. Good luck."   /*!<Rule with two arguments to be substituted*/
#define ARG1 "the right decission"                                                          /*!<Argument for the rules*/
#define ARG2 "enemies"                                                                      /*!<Argument for the rules*/
#define GAMEFILE "anthillGame.dat"                                  /*!<Name of the file which contains the game*/
#define TESTFILE "game_test.txt"                                /*!<Name to an auxiliary file for testing*/
#define DIALTESTFILE "bin/game_dialogues_test.dat"              /*!<Name of an auxiliary file for dialogue testing*/
#define DIALRTESTFILE "bin/game_rules_dialogues_test.dat"       /*!<Name of an auxiliary file for rule dialogues testing*/

/**
 * @brief Main function for game unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

  int test = 0;
  int all = 1;

  if (argc < 2)
  {
    printf("\n\nRunning all test for module game:\n");
  }
  else
  {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS)
    {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }


  if (all || test == 1) test1_game_create();
  if (all || test == 2) test2_game_create();
  if (all || test == 3) test1_game_create_dup();
  if (all || test == 4) test2_game_create_dup();
  if (all || test == 5) test1_game_create_from_file();
  if (all || test == 6) test2_game_create_from_file();
  if (all || test == 7) test1_game_update();
  if (all || test == 8) test2_game_update();
  if (all || test == 9) test3_game_update();
  if (all || test == 10) test1_game_is_over();
  if (all || test == 11) test2_game_is_over();
  if (all || test == 12) test1_game_print_data();
  if (all || test == 13) test2_game_print_data();
  if (all || test == 14) test3_game_print_data();
  if (all || test == 15) test1_game_get_player();
  if (all || test == 16) test2_game_get_player();
  if (all || test == 17) test1_game_set_player();
  if (all || test == 18) test2_game_set_player();
  if (all || test == 19) test3_game_set_player();
  if (all || test == 20) test1_game_get_player_objects();
  if (all || test == 21) test2_game_get_player_objects();
  if (all || test == 22) test3_game_get_player_objects();
  if (all || test == 23) test1_game_get_player_location();
  if (all || test == 24) test2_game_get_player_location();
  if (all || test == 25) test3_game_get_player_location();
  if (all || test == 26) test1_game_set_player_location();
  if (all || test == 27) test2_game_set_player_location();
  if (all || test == 28) test3_game_set_player_location();
  if (all || test == 29) test1_game_get_player_health();
  if (all || test == 30) test2_game_get_player_health();
  if (all || test == 31) test1_game_set_player_health();
  if (all || test == 32) test2_game_set_player_health();
  if (all || test == 33) test3_game_set_player_health();
  if (all || test == 34) test1_game_player_has_light();
  if (all || test == 35) test2_game_player_has_light();
  if (all || test == 36) test3_game_player_has_light();
  if (all || test == 37) test4_game_player_has_light();
  if (all || test == 38) test1_game_get_enemy();
  if (all || test == 39) test2_game_get_enemy();
  if (all || test == 40) test1_game_add_enemy();
  if (all || test == 41) test2_game_add_enemy();
  if (all || test == 42) test3_game_add_enemy();
  if (all || test == 43) test4_game_add_enemy();
  if (all || test == 44) test1_game_get_enemy_id_at();
  if (all || test == 45) test2_game_get_enemy_id_at();
  if (all || test == 46) test1_game_get_num_enemies();
  if (all || test == 47) test2_game_get_num_enemies();
  if (all || test == 48) test1_game_get_object();
  if (all || test == 49) test2_game_get_object();
  if (all || test == 50) test3_game_get_object();
  if (all || test == 51) test1_game_add_object();
  if (all || test == 52) test1_game_add_object();
  if (all || test == 53) test2_game_add_object();
  if (all || test == 54) test3_game_add_object();
  if (all || test == 55) test1_game_delete_object();
  if (all || test == 56) test2_game_delete_object();
  if (all || test == 57) test3_game_delete_object();
  if (all || test == 58) test1_game_get_object_id_at();
  if (all || test == 59) test2_game_get_object_id_at();
  if (all || test == 60) test1_game_get_num_objects();
  if (all || test == 61) test2_game_get_num_objects();
  if (all || test == 62) test3_game_get_num_objects();
  if (all || test == 63) test1_game_get_object_name();
  if (all || test == 64) test2_game_get_object_name();
  if (all || test == 65) test3_game_get_object_name();
  if (all || test == 66) test4_game_get_object_name();
  if (all || test == 67) test1_game_get_object_location();
  if (all || test == 68) test2_game_get_object_location();
  if (all || test == 69) test3_game_get_object_location();
  if (all || test == 70) test4_game_get_object_location();
  if (all || test == 71) test1_game_set_object_location();
  if (all || test == 72) test2_game_set_object_location();
  if (all || test == 73) test3_game_set_object_location();
  if (all || test == 74) test1_game_get_space();
  if (all || test == 75) test2_game_get_space();
  if (all || test == 76) test3_game_get_space();
  if (all || test == 77) test1_game_add_space();
  if (all || test == 78) test2_game_add_space();
  if (all || test == 79) test3_game_add_space();
  if (all || test == 80) test1_game_delete_space();
  if (all || test == 81) test2_game_delete_space();
  if (all || test == 82) test3_game_delete_space();
  if (all || test == 83) test1_game_get_space_id_at();
  if (all || test == 84) test2_game_get_space_id_at();
  if (all || test == 85) test3_game_get_space_id_at();
  if (all || test == 86) test1_game_get_num_of_spaces();
  if (all || test == 87) test2_game_get_num_of_spaces();  
  if (all || test == 88) test1_game_add_link();
  if (all || test == 89) test2_game_add_link();
  if (all || test == 90) test3_game_add_link();
  if (all || test == 91) test1_game_delete_link();
  if (all || test == 92) test2_game_delete_link();
  if (all || test == 93) test3_game_delete_link();
  if (all || test == 94) test1_game_get_link();
  if (all || test == 95) test2_game_get_link();
  if (all || test == 96) test3_game_get_link();
  if (all || test == 97) test1_game_get_link_id();
  if (all || test == 98) test2_game_get_link_id();
  if (all || test == 99) test3_game_get_link_id();
  if (all || test == 100) test1_game_get_link_id_at();
  if (all || test == 101) test2_game_get_link_id_at();
  if (all || test == 102) test3_game_get_link_id_at();
  if (all || test == 103) test1_game_get_link_name();
  if (all || test == 104) test2_game_get_link_name();
  if (all || test == 105) test3_game_get_link_name();
  if (all || test == 106) test4_game_get_link_name();
  if (all || test == 107) test1_game_set_link_origin();
  if (all || test == 108) test2_game_set_link_origin();
  if (all || test == 109) test3_game_set_link_origin();
  if (all || test == 110) test4_game_set_link_origin();
  if (all || test == 111) test5_game_set_link_origin();
  if (all || test == 112) test6_game_set_link_origin();
  if (all || test == 113) test1_game_set_link_destination();
  if (all || test == 114) test2_game_set_link_destination();
  if (all || test == 115) test3_game_set_link_destination();
  if (all || test == 116) test4_game_set_link_destination();
  if (all || test == 117) test5_game_set_link_destination();
  if (all || test == 118) test6_game_set_link_destination();
  if (all || test == 119) test1_game_get_connection();
  if (all || test == 120) test2_game_get_connection();
  if (all || test == 121) test3_game_get_connection();
  if (all || test == 122) test1_game_get_connection_status();
  if (all || test == 123) test2_game_get_connection_status();
  if (all || test == 124) test3_game_get_connection_status();
  if (all || test == 125) test1_game_get_open_link();
  if (all || test == 126) test2_game_get_open_link();
  if (all || test == 127) test3_game_get_open_link();
  if (all || test == 128) test1_game_get_num_links();
  if (all || test == 129) test2_game_get_num_links();
  if (all || test == 130) test3_game_get_num_links();
  if (all || test == 131) test1_game_get_last_command();
  if (all || test == 132) test2_game_get_last_command();
  if (all || test == 133) test1_game_get_last_command_cmd();
  if (all || test == 134) test2_game_get_last_command_cmd();
  if (all || test == 135) test3_game_get_last_command_cmd();
  if (all || test == 136) test1_game_get_last_command_status();  
  if (all || test == 137) test2_game_get_last_command_status();
  if (all || test == 138) test1_game_get_num_executed_commands();
  if (all || test == 139) test2_game_get_num_executed_commands();
  if (all || test == 140) test1_game_set_num_executed_commands();
  if (all || test == 141) test2_game_set_num_executed_commands();
  if (all || test == 142) test1_game_get_last_tdesc();
  if (all || test == 143) test2_game_get_last_tdesc();
  if (all || test == 144) test1_game_set_last_tdesc();
  if (all || test == 145) test2_game_set_last_tdesc();
  if (all || test == 146) test1_game_get_last_idesc();
  if (all || test == 147) test2_game_get_last_idesc();
  if (all || test == 148) test1_game_set_last_idesc();
  if (all || test == 149) test2_game_set_last_idesc();
  if (all || test == 150) test1_game_existing_dialogue_id();
  if (all || test == 151) test2_game_existing_dialogue_id();
  if (all || test == 152) test3_game_existing_dialogue_id();
  if (all || test == 153) test4_game_existing_dialogue_id();
  if (all || test == 154) test1_game_add_dialogue();
  if (all || test == 155) test2_game_add_dialogue();
  if (all || test == 156) test3_game_add_dialogue();
  if (all || test == 157) test4_game_add_dialogue();
  if (all || test == 158) test1_game_add_dialogue_rule();
  if (all || test == 159) test2_game_add_dialogue_rule();
  if (all || test == 160) test3_game_add_dialogue_rule();
  if (all || test == 161) test4_game_add_dialogue_rule();
  if (all || test == 162) test5_game_add_dialogue_rule();
  if (all || test == 163) test1_game_get_dialogue_executed();
  if (all || test == 164) test2_game_get_dialogue_executed();
  if (all || test == 165) test3_game_get_dialogue_executed();
  if (all || test == 166) test4_game_get_dialogue_executed();
  if (all || test == 167) test1_game_increase_dialogue_executed();
  if (all || test == 168) test2_game_increase_dialogue_executed();
  if (all || test == 169) test3_game_increase_dialogue_executed();
  if (all || test == 170) test4_game_increase_dialogue_executed();
  if (all || test == 171) test1_game_decrease_dialogue_executed();
  if (all || test == 172) test2_game_decrease_dialogue_executed();
  if (all || test == 173) test3_game_decrease_dialogue_executed();
  if (all || test == 174) test4_game_decrease_dialogue_executed();
  if (all || test == 175) test1_game_get_printed_dialogue_rule();
  if (all || test == 176) test2_game_get_printed_dialogue_rule();
  if (all || test == 177) test3_game_get_printed_dialogue_rule();
  if (all || test == 178) test4_game_get_printed_dialogue_rule();
  if (all || test == 179) test5_game_get_printed_dialogue_rule();
  if (all || test == 180) test6_game_get_printed_dialogue_rule();
  if (all || test == 181) test7_game_get_printed_dialogue_rule();
  if (all || test == 182) test8_game_get_printed_dialogue_rule();
  if (all || test == 183) test9_game_get_printed_dialogue_rule();
  if (all || test == 184) test10_game_get_printed_dialogue_rule();
  if (all || test == 185) test1_game_get_printed_repeated_error_rule();
  if (all || test == 186) test2_game_get_printed_repeated_error_rule();
  if (all || test == 187) test3_game_get_printed_repeated_error_rule();
  if (all || test == 188) test1_game_get_move_dialogue_rule();
  if (all || test == 189) test2_game_get_move_dialogue_rule();
  if (all || test == 190) test3_game_get_move_dialogue_rule();
  if (all || test == 191) test4_game_get_move_dialogue_rule();
  if (all || test == 192) test5_game_get_move_dialogue_rule();
  if (all || test == 193) test6_game_get_move_dialogue_rule();
  if (all || test == 194) test7_game_get_move_dialogue_rule();
  if (all || test == 195) test1_game_get_attack_dialogue_rule();
  if (all || test == 196) test2_game_get_attack_dialogue_rule();
  if (all || test == 197) test3_game_get_attack_dialogue_rule();
  if (all || test == 198) test4_game_get_attack_dialogue_rule();
  if (all || test == 199) test1_game_get_take_dialogue_rule();
  if (all || test == 200) test2_game_get_take_dialogue_rule();
  if (all || test == 201) test3_game_get_take_dialogue_rule();
  if (all || test == 202) test4_game_get_take_dialogue_rule();
  if (all || test == 203) test5_game_get_take_dialogue_rule();
  if (all || test == 204) test6_game_get_take_dialogue_rule();
  if (all || test == 205) test7_game_get_take_dialogue_rule();
  if (all || test == 206) test8_game_get_take_dialogue_rule();
  if (all || test == 207) test9_game_get_take_dialogue_rule();
  if (all || test == 208) test1_game_get_drop_dialogue_rule();
  if (all || test == 209) test2_game_get_drop_dialogue_rule();
  if (all || test == 210) test3_game_get_drop_dialogue_rule();
  if (all || test == 211) test4_game_get_drop_dialogue_rule();
  if (all || test == 212) test5_game_get_drop_dialogue_rule();
  if (all || test == 213) test6_game_get_drop_dialogue_rule();
  if (all || test == 214) test7_game_get_drop_dialogue_rule();
  if (all || test == 215) test1_game_get_inspect_dialogue_rule();
  if (all || test == 216) test2_game_get_inspect_dialogue_rule();
  if (all || test == 217) test3_game_get_inspect_dialogue_rule();
  if (all || test == 218) test4_game_get_inspect_dialogue_rule();
  if (all || test == 219) test1_game_get_turn_on_dialogue_rule();
  if (all || test == 220) test2_game_get_turn_on_dialogue_rule();
  if (all || test == 221) test3_game_get_turn_on_dialogue_rule();
  if (all || test == 222) test4_game_get_turn_on_dialogue_rule();
  if (all || test == 223) test5_game_get_turn_on_dialogue_rule();
  if (all || test == 224) test6_game_get_turn_on_dialogue_rule();
  if (all || test == 225) test1_game_get_turn_off_dialogue_rule();
  if (all || test == 226) test2_game_get_turn_off_dialogue_rule();
  if (all || test == 227) test3_game_get_turn_off_dialogue_rule();
  if (all || test == 228) test4_game_get_turn_off_dialogue_rule();
  if (all || test == 229) test5_game_get_turn_off_dialogue_rule();
  if (all || test == 230) test6_game_get_turn_off_dialogue_rule();
  if (all || test == 231) test1_game_get_open_link_dialogue_rule();
  if (all || test == 232) test2_game_get_open_link_dialogue_rule();
  if (all || test == 233) test3_game_get_open_link_dialogue_rule();
  if (all || test == 234) test4_game_get_open_link_dialogue_rule();
  if (all || test == 235) test5_game_get_open_link_dialogue_rule();
  if (all || test == 236) test6_game_get_open_link_dialogue_rule();
  if (all || test == 237) test7_game_get_open_link_dialogue_rule();
  if (all || test == 238) test8_game_get_open_link_dialogue_rule();
  if (all || test == 239) test9_game_get_open_link_dialogue_rule();
  if (all || test == 240) test10_game_get_open_link_dialogue_rule();
  if (all || test == 241) test1_game_get_close_link_dialogue_rule();
  if (all || test == 242) test2_game_get_close_link_dialogue_rule();
  if (all || test == 243) test3_game_get_close_link_dialogue_rule();
  if (all || test == 244) test4_game_get_close_link_dialogue_rule();
  if (all || test == 245) test5_game_get_close_link_dialogue_rule();
  if (all || test == 246) test6_game_get_close_link_dialogue_rule();
  if (all || test == 247) test7_game_get_close_link_dialogue_rule();
  if (all || test == 248) test8_game_get_close_link_dialogue_rule();
  if (all || test == 249) test9_game_get_close_link_dialogue_rule();
  if (all || test == 250) test10_game_get_close_link_dialogue_rule();
  if (all || test == 251) test1_game_get_dialogue_of_game_rule();
  if (all || test == 252) test2_game_get_dialogue_of_game_rule();
  if (all || test == 253) test3_game_get_dialogue_of_game_rule();
  if (all || test == 254) test4_game_get_dialogue_of_game_rule();
  if (all || test == 255) test5_game_get_dialogue_of_game_rule();
  if (all || test == 256) test1_game_get_num_commands_till_flood();
  if (all || test == 257) test2_game_get_num_commands_till_flood();
  if (all || test == 258) test3_game_get_num_commands_till_flood();
  if (all || test == 259) test1_game_get_rule();
  if (all || test == 260) test2_game_get_rule();
  if (all || test == 261) test3_game_get_rule();
  if (all || test == 262) test4_game_get_rule();
  if (all || test == 263) test1_game_get_rule_id_at();
  if (all || test == 264) test2_game_get_rule_id_at();
  if (all || test == 265) test3_game_get_rule_id_at();
  if (all || test == 266) test1_game_get_num_rules();
  if (all || test == 267) test2_game_get_num_rules();
  if (all || test == 268) test1_game_add_rule();
  if (all || test == 269) test2_game_add_rule();
  if (all || test == 270) test3_game_add_rule();
  if (all || test == 271) test1_game_rule_spawn_ground();
  if (all || test == 272) test2_game_rule_spawn_ground();  
  if (all || test == 273) test3_game_rule_spawn_ground();  
  if (all || test == 274) test1_game_get_all_dialogues();  
  if (all || test == 275) test2_game_get_all_dialogues();  
  if (all || test == 276) test3_game_get_all_dialogues();  
  if (all || test == 277) test4_game_get_all_dialogues();
  

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/*Extra destroy functions are addded in case the items are not added properly to the game*/
void test1_game_create()
{
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game != NULL);
  game_destroy(game);
}

void test2_game_create()
{

  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_get_num_objects(game) == 0);
  game_destroy(game);
}

void test1_game_create_dup()
{
  Game *game, *gamedup;
  game = game_create();
  gamedup=game_create_dup(game);
  PRINT_TEST_RESULT(gamedup != NULL);
  game_destroy_dup(gamedup);
  game_destroy(game);
}

void test2_game_create_dup()
{

  Game *game, *gamedup;
  game = game_create();
  gamedup=game_create_dup(game);
  PRINT_TEST_RESULT(game_get_num_objects(game) == game_get_num_objects(gamedup));
  game_destroy_dup(gamedup);
  game_destroy(game);
}


void test1_game_create_from_file()
{
  Game *game;
  game = game_create_from_file(NULL);

  PRINT_TEST_RESULT(game == NULL);

  game_destroy(game);
}

void test2_game_create_from_file()
{
  Game *game;
  game = game_create_from_file(GAMEFILE);
  PRINT_TEST_RESULT(game != NULL);
  game_destroy(game);
}

void test1_game_update()
{
  Game *game=NULL;
  
  PRINT_TEST_RESULT( game_update(game)==ERROR);

}

void test2_game_update()
{
  Game *game;
  Player *ply;
  Space *spc;
  Object *obj;
  FILE *f = NULL;

  game = game_create();
  ply=player_create(ID);
  spc=space_create(ID_SPACE);
  obj=object_create(ID_OBJECT);

  game_add_space(game, spc);
  game_set_player(game, ply);
  game_add_object(game, obj);
  
  space_add_object(spc, ID_OBJECT);
  player_set_location(ply, ID_SPACE);
  object_set_location(obj, ID_SPACE);
  object_set_name(obj, "pepe");
  
  if (!game)
    return;

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  fprintf(f, "t pepe");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  commands_get_user_input(game_get_last_command(game), f);

  PRINT_TEST_RESULT(game_update(game)==OK);
    
  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test3_game_update()
{
  Game *game;
  Player *ply;
  Space *spc;
  FILE *f = NULL;

  game = game_create();
  ply=player_create(ID);
  spc=space_create(ID_SPACE);

  game_add_space(game, spc);
  game_set_player(game, ply);
  
  space_set_idesc(spc, "hola");
  player_set_location(ply, ID_SPACE);
  
  if (!game)
    return;

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  fprintf(f, "i s");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  commands_get_user_input(game_get_last_command(game), f);

  PRINT_TEST_RESULT( game_update(game)==OK);

  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test1_game_is_over()
{
  Game *game = NULL;
  PRINT_TEST_RESULT(game_is_over(game) == TRUE);
}

void test2_game_is_over()
{
  Game *game;
  Player *ply;

  game = game_create();
  ply=player_create(ID);
  player_set_health(ply, 2);

  game_set_player(game, ply);
  

  PRINT_TEST_RESULT(game_is_over(game) == FALSE);

  game_destroy(game);
}


void test1_game_print_data()
{
  Game *game = NULL;
  FILE *f = NULL;

  game = game_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  PRINT_TEST_RESULT(game_print_data(game, f) == OK);

  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_print_data()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_print_data(game, NULL) == ERROR);

  game_destroy(game);
}

void test3_game_print_data()
{
  Game *game = NULL;
  FILE *f = NULL;

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    return;
  }

  PRINT_TEST_RESULT(game_print_data(game, f) == ERROR);

  fclose(f);
  remove(TESTFILE);
}


/*GAME PLAYER TESTS*/

void test1_game_get_player()
{
  Game *game = NULL;
  game = game_create();

  PRINT_TEST_RESULT(game_get_player(game) == NULL);

  game_destroy(game);
}

void test2_game_get_player()
{
  Game *game = NULL;
  Player *ply;

  game = game_create();
  ply=player_create(ID);

  game_set_player(game, ply);

  PRINT_TEST_RESULT(game_get_player(game) == ply);

  game_destroy(game);
}

void test1_game_set_player()
{
  Game *game = NULL;
  Player *player;

  player = player_create(ID);

  PRINT_TEST_RESULT(game_set_player(game, player) == ERROR);

  game_destroy(game);
  player_destroy(player);
}

void test2_game_set_player()
{
  Game *game;
  Player *player = NULL;

  game = game_create();
  PRINT_TEST_RESULT(game_set_player(game, player) == ERROR);

  game_destroy(game);
  player_destroy(player);
}

void test3_game_set_player()
{
  Game *game;
  Player *player;

  game = game_create();
  player = player_create(ID);
  (void)game_set_player(game, player);

  PRINT_TEST_RESULT(game_get_player(game) == player);

  game_destroy(game);
}

void test1_game_get_player_objects()
{
  int num;
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_player_objects(game, &num) == NULL);
}

void test2_game_get_player_objects()
{
  int num;
  Game *game = NULL;
  game = game_create();

  PRINT_TEST_RESULT(game_get_player_objects(game, &num) == NULL);

  game_destroy(game);
}

void test3_game_get_player_objects()
{
  int num;
  Game *game = NULL;
  Object *obj;
  Player *ply;
  Id *ids;

  game = game_create();
  obj=object_create(ID_OBJECT);
  ply=player_create(ID);

  game_set_player(game, ply);
  game_add_object(game, obj);
  player_add_object(game_get_player(game), ID_OBJECT);

  ids = game_get_player_objects(game, &num);

  if(ids==NULL)
    return;

  PRINT_TEST_RESULT(ids[0]==ID_OBJECT);

  game_destroy(game);
  free(ids);
}

void test1_game_get_player_location()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_player_location(game) == NO_ID);
}

void test2_game_get_player_location()
{
  Game *game;
  Player *player;

  game = game_create();
  player = player_create(ID);

  game_set_player(game, player);
  player_set_location(player, NO_ID);

  PRINT_TEST_RESULT(game_get_player_location(game) == NO_ID);

  game_destroy(game);
}

void test3_game_get_player_location()
{
  Game *game;
  Player *player;

  game = game_create();
  player = player_create(ID);

  game_set_player(game, player);
  player_set_location(player, ID_LOC);

  PRINT_TEST_RESULT(game_get_player_location(game) == ID_LOC);

  game_destroy(game);
}

void test1_game_set_player_location()
{
  Game *game = NULL;
  Player *player = NULL;

  game = game_create();

  PRINT_TEST_RESULT(player_set_location(player, ID_LOC) == ERROR);

  game_destroy(game);
}

void test2_game_set_player_location()
{
  Game *game;
  Player *player;

  game = game_create();
  player = player_create(6);

  game_set_player(game, player);
  player_set_location(player, NO_ID);

  PRINT_TEST_RESULT(game_get_player_location(game) == NO_ID);

  game_destroy(game);
}

void test3_game_set_player_location()
{
  Game *game;
  Player *player;

  game = game_create();
  player = player_create(ID);

  game_set_player(game, player);
  player_set_location(player, ID_LOC);

  PRINT_TEST_RESULT(game_get_player_location(game) == ID_LOC);

  game_destroy(game);
}

void test1_game_get_player_health()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_player_health(game) == -1);
}

void test2_game_get_player_health()
{
  Game *game;
  Player *ply;

  game = game_create();
  ply=player_create(ID);
  game_set_player(game, ply);
  game_set_player_health(game, 1);

  PRINT_TEST_RESULT(game_get_player_health(game) == 1);

  game_destroy(game);
}

void test1_game_set_player_health()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_set_player_health(game, 3) == ERROR);
}

void test2_game_set_player_health()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_set_player_health(game, -1) == ERROR);

  game_destroy(game);
}

void test3_game_set_player_health()
{
  Game *game;
  Player *ply;

  game = game_create();
  ply=player_create(ID);
  game_set_player(game, ply);

  PRINT_TEST_RESULT( game_set_player_health(game, 1) == OK);

  game_destroy(game);
}


void test1_game_player_has_light()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_player_has_light(game) == FALSE);
}

void test2_game_player_has_light()
{
  Game *game;
  Player *player;

  game = game_create();
  player=player_create(1);

  game_set_player(game, player);
  player_set_type(game_get_player(game), FIREFLY);
  PRINT_TEST_RESULT(game_player_has_light(game) == TRUE);

  game_destroy(game);
}

void test3_game_player_has_light()
{
  Game *game;
  Player *player;

  game = game_create();
  player=player_create(1);

  game_set_player(game, player);
  player_set_type(game_get_player(game), SNAIL);
  PRINT_TEST_RESULT(game_player_has_light(game) == FALSE);

  game_destroy(game);
}

void test4_game_player_has_light()
{
  Game *game;
  Player *player;
  Object *obj;

  Id objid=6;

  game = game_create();
  player=player_create(1);
  obj=object_create(objid);


  game_set_player(game, player);
  game_add_object(game, obj);

  object_set_illuminate(obj, TRUE);
  object_set_turnedon(obj, TRUE);
  player_add_object(player, objid);

  player_set_type(game_get_player(game), SNAIL);
  PRINT_TEST_RESULT(game_player_has_light(game) == TRUE);

  game_destroy(game);
}




/*GAME ENEMY TESTS*/

void test1_game_get_enemy()
{
  Game *game = NULL;
  PRINT_TEST_RESULT(game_get_enemy(game, game_get_enemy_id_at(game, 0)) == NULL);
}

void test2_game_get_enemy()
{
  Game *game;
  game = game_create();

  PRINT_TEST_RESULT(game_get_enemy(game, game_get_enemy_id_at(game, 0)) == NULL);

  game_destroy(game);
}

void test1_game_add_enemy()
{
  Game *game = NULL;
  Enemy *enemy = NULL;

  PRINT_TEST_RESULT(game_add_enemy(game, enemy) == ERROR);
}

void test2_game_add_enemy()
{
  Game *game;
  Enemy *enemy = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_add_enemy(game, enemy) == ERROR);

  game_destroy(game);
}

void test3_game_add_enemy()
{
  Game *game;
  Enemy *enemy;

  game = game_create();
  enemy = enemy_create(ID);

  PRINT_TEST_RESULT(game_add_enemy(game, enemy) == OK);

  game_destroy(game);
}

void test4_game_add_enemy()
{
  Game *game;
  Enemy *enemy;

  game = game_create();
  enemy = enemy_create(ID);
  (void)game_add_enemy(game, enemy);

  PRINT_TEST_RESULT(game_get_enemy_id_at(game, 0) == ID);

  game_destroy(game);
}

void test1_game_get_enemy_id_at()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_enemy_id_at(game, 0)==NO_ID);
}

void test2_game_get_enemy_id_at()
{
  Game *game;
  Enemy *enemy;

  game = game_create();
  enemy = enemy_create(ID);

  game_add_enemy(game, enemy);
  enemy_set_location(enemy, NO_ID);

  PRINT_TEST_RESULT(game_get_enemy_id_at(game, 0)==ID);

  game_destroy(game);
}


void test1_game_get_num_enemies()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_num_enemies(game)==-1);
}

void test2_game_get_num_enemies()
{
  Game *game;
  Enemy *enmy1, *enmy2;

  game = game_create();
  enmy1=enemy_create(1);
  enmy2=enemy_create(2);

  game_add_enemy(game, enmy1);
  game_add_enemy(game, enmy2);


  PRINT_TEST_RESULT(game_get_num_enemies(game)==2);

  game_destroy(game);
}


/*GAME OBJECT TESTS*/

void test1_game_get_object()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_object(game, ID) == NULL);
}

void test2_game_get_object()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_object(game, NO_ID) == NULL);

  game_destroy(game);
}

void test3_game_get_object()
{
  Game *game;
  Object *obj;

  game = game_create();

  obj=object_create(ID_OBJECT);
  game_add_object(game, obj);

  PRINT_TEST_RESULT(game_get_object(game, ID_OBJECT) == obj);

  game_destroy(game);
}


void test1_game_add_object()
{
  Game *game = NULL;
  Object *obj = NULL;

  PRINT_TEST_RESULT(game_add_object(game, obj) == ERROR);
}

void test2_game_add_object()
{
  Game *game;
  Object *obj = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_add_object(game, obj) == ERROR);

  game_destroy(game);
}

void test3_game_add_object()
{
  Game *game;
  Object *obj;

  game = game_create();
  obj = object_create(ID_OBJECT);

  PRINT_TEST_RESULT(game_add_object(game, obj) == OK);

  game_destroy(game);
}


void test1_game_delete_object()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_delete_object(game, ID_OBJECT) == ERROR);
}
void test2_game_delete_object()
{
  Game *game;
  Object *obj = NULL;

  game = game_create();
  obj=object_create(ID_OBJECT);

  game_add_object(game, obj);

  PRINT_TEST_RESULT(game_delete_object(game, ID_OBJECT) == OK);

  game_destroy(game);
}

void test3_game_delete_object()
{
  Game *game;

  game = game_create();
  PRINT_TEST_RESULT(game_delete_object(game, NO_ID) == ERROR);

  game_destroy(game);
}


void test1_game_get_object_id_at()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_object_id_at(game, 0) == NO_ID);
}

void test2_game_get_object_id_at()
{
  Game *game;
  Object *obj;

  game = game_create();
  obj = object_create(ID_OBJECT);
  (void)game_add_object(game, obj);

  PRINT_TEST_RESULT(game_get_object_id_at(game, 0) == ID_OBJECT);

  game_destroy(game);
}

void test1_game_get_num_objects()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_num_objects(game) == -1);
}

void test2_game_get_num_objects()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_num_objects(game) == 0);

  game_destroy(game);
}

void test3_game_get_num_objects()
{
  Game *game;
  Object *obj;

  game = game_create();
  obj = object_create(ID_OBJECT);
  (void)game_add_object(game, obj);

  PRINT_TEST_RESULT(game_get_num_objects(game) == 1);

  game_destroy(game);
}

void test1_game_get_object_name()
{
  Game *game;
  Object *obj;

  game = game_create();
  obj = object_create(ID_OBJECT);
  (void)game_add_object(game, obj);

  object_set_name(obj, "pepe");

  PRINT_TEST_RESULT(strcmp(game_get_object_name(game, ID_OBJECT), "pepe")==0);

  game_destroy(game);
}

void test2_game_get_object_name()
{
  Game *game;
  Object *obj;
  char *name;

  game = game_create();
  obj = object_create(ID_OBJECT);
  (void)game_add_object(game, obj);

  name = game_get_object_name(game, ID_OBJECT);

  PRINT_TEST_RESULT(name[0] == '\0');

  game_destroy(game);
}

void test3_game_get_object_name()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_object_name(game, NO_ID) == NULL);

  game_destroy(game);
}

void test4_game_get_object_name()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_object_name(game, ID_OBJECT) == NULL);
}

void test1_game_get_object_location()
{
  Game *game = NULL;
  Object *obj;

  obj = object_create(ID_OBJECT);

  PRINT_TEST_RESULT(game_get_object_location(game, ID_OBJECT) == NO_ID);

  object_destroy(obj);
}

void test2_game_get_object_location()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_get_object_location(game, ID_OBJECT) == NO_ID);

  game_destroy(game);
}

void test3_game_get_object_location()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_object_location(game, NO_ID) == NO_ID);

  game_destroy(game);
}

void test4_game_get_object_location()
{
  Game *game;
  Object *obj;

  game = game_create();
  obj = object_create(ID_OBJECT);
  (void)game_add_object(game, obj);
  (void)game_set_object_location(game, ID_OBJECT, ID_LOC);

  PRINT_TEST_RESULT(game_get_object_location(game, ID_OBJECT) == ID_LOC);

  game_destroy(game);
}

void test1_game_set_object_location()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_set_object_location(game, NO_ID, NO_ID) == ERROR);
}

void test2_game_set_object_location()
{
  Game *game;
  Object *obj;

  game = game_create();
  obj = object_create(ID_OBJECT);
  (void)game_add_object(game, obj);

  PRINT_TEST_RESULT(game_set_object_location(game, ID, ID_LOC) == ERROR);

  game_destroy(game);
}

void test3_game_set_object_location()
{
  Game *game;
  Object *obj;

  game = game_create();
  obj = object_create(ID_OBJECT);
  (void)game_add_object(game, obj);
  (void)game_set_object_location(game, ID_OBJECT, ID_LOC);

  PRINT_TEST_RESULT(game_get_object_location(game, ID_OBJECT) == ID_LOC);

  game_destroy(game);
}

/*GAME SPACE TESTS*/

void test1_game_get_space()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_space(game, ID_LOC) == NULL);
}

void test2_game_get_space()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_space(game, NO_ID) == NULL);

  game_destroy(game);
}

void test3_game_get_space()
{
  Game *game;
  Space *spc;

  game = game_create();
  spc=space_create(ID_SPACE);

  game_add_space(game, spc);

  PRINT_TEST_RESULT(game_get_space(game, ID_SPACE) == spc);

  game_destroy(game);
}

void test1_game_add_space()
{
  Game *game = NULL;
  Space *space = NULL;

  PRINT_TEST_RESULT(game_add_space(game, space) == ERROR);
}

void test2_game_add_space()
{
  Game *game;
  Space *space;

  game = game_create();
  space = space_create(ID_LOC);

  PRINT_TEST_RESULT(game_add_space(game, space) == OK);

  game_destroy(game);
}

void test3_game_add_space()
{
  Game *game;
  Space *space;

  game = game_create();
  space = space_create(ID_LOC);
  (void)game_add_space(game, space);

  PRINT_TEST_RESULT(game_get_space_id_at(game, 0) == ID_LOC);

  game_destroy(game);
}


void test1_game_delete_space()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_delete_space(game, ID_SPACE) == ERROR);
}

void test2_game_delete_space()
{
  Game *game;
  Space *spc = NULL;

  game = game_create();
  spc=space_create(ID_SPACE);

  game_add_space(game, spc);

  PRINT_TEST_RESULT(game_delete_space(game, ID_SPACE) == OK);

  game_destroy(game);
}

void test3_game_delete_space()
{
  Game *game;
  Space *spc = NULL;
  Object *obj1, *obj2;
  STATUS sts;

  game = game_create();
  spc=space_create(ID_SPACE);
  obj1=object_create(ID_OBJECT);

  game_add_space(game, spc);
  game_add_object(game, obj1);

  space_add_object(spc, ID_OBJECT);


  sts=game_delete_space(game, ID_SPACE);
  obj2=game_get_object(game, ID_OBJECT);

  PRINT_TEST_RESULT(sts==OK && obj2==NULL);

  game_destroy(game);
}


void test1_game_get_space_id_at()
{
  Game *game = NULL;
  PRINT_TEST_RESULT(game_get_space_id_at(game, 0) == NO_ID);
}

void test2_game_get_space_id_at()
{
  Game *game;
  game = game_create();
  PRINT_TEST_RESULT(game_get_space_id_at(game, 0) == NO_ID);
  game_destroy(game);
}

void test3_game_get_space_id_at()
{
  Game *game;
  Space *space;

  game = game_create();
  space = space_create(ID_LOC);
  (void)game_add_space(game, space);

  PRINT_TEST_RESULT(game_get_space_id_at(game, 0) == ID_LOC);

  game_destroy(game);
}


void test1_game_get_num_of_spaces()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_num_of_spaces(game) == -1);
}

void test2_game_get_num_of_spaces()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_num_of_spaces(game) == 0);

  game_destroy(game);
}

void test3_game_get_num_of_spaces()
{
  Game *game;
  Space *space;

  game = game_create();
  space = space_create(ID_LOC);
  game_add_space(game, space);

  PRINT_TEST_RESULT(game_get_num_of_spaces(game) == 1);

  game_destroy(game);
}


/*GAME LINK TESTS*/


void test1_game_add_link()
{
  Game *game;
  Link *link = NULL;
  game = game_create();
  PRINT_TEST_RESULT(game_add_link(game, link) == ERROR);
  game_destroy(game);
}

void test2_game_add_link()
{
  Game *game = NULL;
  Link *link;

  link = link_create(ID_LINK);

  PRINT_TEST_RESULT(game_add_link(game, link) == ERROR);

  link_destroy(link);
}

void test3_game_add_link()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);

  PRINT_TEST_RESULT(game_add_link(game, link) == OK);

  game_destroy(game);
}

void test1_game_delete_link()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_delete_link(game, ID_LINK) == ERROR);
}

void test2_game_delete_link()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_delete_link(game, ID_LINK) == ERROR);

  game_destroy(game);
}

void test3_game_delete_link()
{
  Game *game;
  Link *link = NULL;

  game = game_create();
  link=link_create(ID_LINK);

  game_add_link(game, link);

  PRINT_TEST_RESULT(game_delete_link(game, ID_LINK) == OK);

  game_destroy(game);
}

void test1_game_get_link()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_link(game, ID_LINK) == NULL);
}

void test2_game_get_link()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);

  PRINT_TEST_RESULT(game_get_link(game, ID_LINK) == NULL);

  link_destroy(link);
  game_destroy(game);
}

void test3_game_get_link()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);
  (void)game_add_link(game, link);

  PRINT_TEST_RESULT(game_get_link(game, ID_LINK) == link);

  game_destroy(game);
}

void test1_game_get_link_id()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_link_id(game, ID_LOC, NORTH) == NO_ID);
}

void test2_game_get_link_id()
{
  Game *game = NULL;

  game=game_create();

  PRINT_TEST_RESULT(game_get_link_id(game, ID_LOC, UP) == NO_ID);

  game_destroy(game);
}

void test3_game_get_link_id()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);

  link_set_origin(link, ID_LOC);
  link_set_direction(link, NORTH);
  game_add_link(game, link);

  PRINT_TEST_RESULT(game_get_link_id(game, ID_LOC, NORTH) ==ID_LINK);

  game_destroy(game);
}

void test1_game_get_link_id_at()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_link_id_at(game, 0) == NO_ID);
}

void test2_game_get_link_id_at()
{
  Game *game = NULL;

  game=game_create();

  PRINT_TEST_RESULT(game_get_link_id_at(game, 0) == NO_ID);

  game_destroy(game);

}

void test3_game_get_link_id_at()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);

  link_set_origin(link, ID_LOC);
  link_set_direction(link, NORTH);
  game_add_link(game, link);

  PRINT_TEST_RESULT(game_get_link_id_at(game, 0) == ID_LINK);

  game_destroy(game);
}


void test1_game_get_link_name()
{
  Game *game;
  Link *link;

  game = game_create();
  link =link_create(ID_LINK);
  (void)game_add_link(game, link);

  link_set_name(link, "pepe");

  PRINT_TEST_RESULT(strcmp(game_get_link_name(game, ID_LINK), "pepe")==0);

  game_destroy(game);
}

void test2_game_get_link_name()
{
  Game *game;
  Link *link;
  char *name;

  game = game_create();
  link =link_create(ID_LINK);
  (void)game_add_link(game, link);

  name = game_get_link_name(game, ID_LINK);

  PRINT_TEST_RESULT(name[0] == '\0');

  game_destroy(game);
}

void test3_game_get_link_name()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_link_name(game, NO_ID) == NULL);

  game_destroy(game);
}

void test4_game_get_link_name()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_link_name(game, ID_LINK) == NULL);
}



void test1_game_set_link_origin()
{
  Game *game;
  Link *link;
  Space *origin;

  game = game_create();
  link = link_create(ID_LINK);
  origin = space_create(ID);
  
  game_add_link(game, link);
  game_add_space(game, origin);

  PRINT_TEST_RESULT(game_set_link_origin(game, ID_LINK, ID) == OK);

  game_destroy(game);  
}

void test2_game_set_link_origin()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);
  
  game_add_link(game, link);

  PRINT_TEST_RESULT(game_set_link_origin(game, ID_LINK, ID) == ERROR);

  game_destroy(game);  
}

void test3_game_set_link_origin()
{
  Game *game;
  Space *origin;

  game = game_create();
  origin = space_create(ID_LOC);
  
  game_add_space(game, origin);

  PRINT_TEST_RESULT(game_set_link_origin(game, ID_LINK, ID_LOC) == ERROR);

  game_destroy(game);  

}

void test4_game_set_link_origin()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);
  
  game_add_link(game, link);

  PRINT_TEST_RESULT(game_set_link_origin(game, ID_LINK, NO_ID) == ERROR);

  game_destroy(game);  

}

void test5_game_set_link_origin()
{
  Game *game;
  Space *origin;

  game = game_create();
  origin = space_create(ID);
  
  game_add_space(game, origin);

  PRINT_TEST_RESULT(game_set_link_origin(game, NO_ID, ID) == ERROR);

  game_destroy(game);  
}

void test6_game_set_link_origin()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_set_link_origin(game, ID_LINK, ID) == ERROR);

}

void test1_game_set_link_destination()
{
  Game *game;
  Link *link;
  Space *destination;

  game = game_create();
  link = link_create(ID_LINK);
  destination = space_create(ID);
  
  game_add_link(game, link);
  game_add_space(game, destination);

  PRINT_TEST_RESULT(game_set_link_destination(game, ID_LINK, ID) == OK);

  game_destroy(game);  
}

void test2_game_set_link_destination()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);
  
  game_add_link(game, link);

  PRINT_TEST_RESULT(game_set_link_destination(game, ID_LINK, ID) == ERROR);

  game_destroy(game);  
}

void test3_game_set_link_destination()
{
  Game *game;
  Space *destination;

  game = game_create();
  destination = space_create(ID);
  
  game_add_space(game, destination);

  PRINT_TEST_RESULT(game_set_link_destination(game, ID_LINK, ID) == ERROR);

  game_destroy(game);  
}

void test4_game_set_link_destination()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);
  
  game_add_link(game, link);

  PRINT_TEST_RESULT(game_set_link_destination(game, ID_LINK, NO_ID) == ERROR);

  game_destroy(game);  
}

void test5_game_set_link_destination()
{
  Game *game;
  Space *destination;

  game = game_create();
  destination = space_create(ID);
  
  game_add_space(game, destination);

  PRINT_TEST_RESULT(game_set_link_destination(game, NO_ID, ID) == ERROR);

  game_destroy(game);  
}

void test6_game_set_link_destination()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_set_link_destination(game, ID_LINK, ID) == ERROR);
  
}

void test1_game_get_connection_status()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_connection_status(game, NO_ID, NO_DIR) == CLOSE);
}

void test2_game_get_connection_status()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_connection_status(game, NO_ID, NO_DIR) == CLOSE);

  game_destroy(game);
}

void test3_game_get_connection_status()
{
  Game *game;
  Link *link;

  game = game_create();
  link=link_create(ID_LINK);

  link_set_origin(link,ID_LOC);
  link_set_direction(link,SOUTH);
  link_set_status(link, OPEN);

  game_add_link(game, link);

  PRINT_TEST_RESULT(game_get_connection_status(game, ID_LOC, SOUTH) == OPEN);

  game_destroy(game);
}

void test1_game_get_connection()
{
  Game *game;
  Link *link;

  game = game_create();
  link = link_create(ID_LINK);
  link_set_origin(link, ID_LOC);
  link_set_destination(link, ID_LOC2);
  link_set_direction(link, SOUTH);

  game_add_link(game, link);

  PRINT_TEST_RESULT(game_get_connection(game, ID_LOC, SOUTH) == ID_LOC2);

  game_destroy(game);
}

void test2_game_get_connection()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_connection(game, ID_LOC, NORTH) == NO_ID);

  game_destroy(game);
}

void test3_game_get_connection()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_connection(game, ID_LOC, NORTH) == NO_ID);
}

void test1_game_get_open_link()
{
  Game *game = NULL;
  Id space = ID_LOC;
  DIRECTION dir = NO_DIR;

  PRINT_TEST_RESULT(game_get_open_link(game, space, dir) == NO_ID);
}

void test2_game_get_open_link()
{
  Game *game;
  Id space = ID_LOC;
  DIRECTION dir = SOUTH;

  game = game_create();

  PRINT_TEST_RESULT(game_get_open_link(game, space, dir) == NO_ID);

  game_destroy(game);
}

void test3_game_get_open_link()
{
  Game *game;
  Space *spc1, *spc2;
  Link *link;

  game = game_create();
  spc1=space_create(ID_LOC);
  spc2=space_create(ID_LOC2);
  link=link_create(ID_LINK);

  game_add_space(game, spc1);
  game_add_space(game, spc2);
  game_add_link(game, link);

  link_set_origin(link, ID_LOC);
  link_set_destination(link, ID_LOC2);
  link_set_direction(link, NORTH);
  link_set_status(link, OPEN);


  PRINT_TEST_RESULT(game_get_open_link(game, ID_LOC, NORTH) == ID_LOC2);

  game_destroy(game);
}


void test1_game_get_num_links()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_num_links(game) == -1);
}

void test2_game_get_num_links()
{
  Game *game;

  game = game_create();

  PRINT_TEST_RESULT(game_get_num_links(game) == 0);

  game_destroy(game);
}

void test3_game_get_num_links()
{
  Game *game;
  Link *link;

  game = game_create();
  link=link_create(ID_LINK);
  (void)game_add_link(game, link);

  PRINT_TEST_RESULT(game_get_num_links(game) == 1);

  game_destroy(game);
}


/*GAME COMMAND FUNCTIONS*/

void test1_game_get_last_command()
{
  Game *game = NULL;
  FILE *f = NULL;

  game = game_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }
  
  fprintf(f, "e");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  commands_get_user_input(game_get_last_command(game), f);

  PRINT_TEST_RESULT(game_get_last_command(game) != NULL);

  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_last_command()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_last_command(game) == NULL);
}


void test1_game_get_last_command_cmd()
{
  Game *game = NULL;
  FILE *f = NULL;

  game = game_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }
  fprintf(f, "e");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  commands_get_user_input(game_get_last_command(game), f);

  PRINT_TEST_RESULT(game_get_last_command_cmd(game) == EXIT);

  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_last_command_cmd()
{
  Game *game = NULL;
  FILE *f = NULL;

  game = game_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }
  fprintf(f, "Move w");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  commands_get_user_input(game_get_last_command(game), f);

  PRINT_TEST_RESULT(game_get_last_command_cmd(game) == MOVE);

  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test3_game_get_last_command_cmd()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_get_last_command_cmd(game) == LOAD);

  game_destroy(game);
}

void test1_game_get_last_command_status()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(  game_get_last_command_status(game) == OK);

  game_destroy(game);
}

void test2_game_get_last_command_status()
{
  Game *game = NULL;
  FILE *f = NULL;

  game = game_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }
  fprintf(f, "Move w");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  PRINT_TEST_RESULT(game_get_last_command_status(game) == ERROR);

  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}



void test1_game_get_num_executed_commands()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_num_executed_commands(game) == -1);
}

void test2_game_get_num_executed_commands()
{
  Game *game = NULL;
  FILE *f = NULL;
  Space *spc;
  Player *ply;

  game = game_create();
  ply=player_create(ID);
  spc=space_create(ID_LOC);

  game_set_player(game, ply);
  game_add_space(game, spc);

  player_set_location(ply, ID_LOC);
  space_set_idesc(spc, "idesc mágico");

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    game_destroy(game);
    return;
  }
  fprintf(f, "i s");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    game_destroy(game);
    return;
  }

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  PRINT_TEST_RESULT(game_get_num_executed_commands(game) == 1);

  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}


void test1_game_set_num_executed_commands()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_set_num_executed_commands(game, 3) == ERROR);
}


void test2_game_set_num_executed_commands()
{
  Game *game = NULL;
  STATUS sts;

  game = game_create();

  sts=game_set_num_executed_commands(game, 3);
  PRINT_TEST_RESULT(game_get_num_executed_commands(game) == 3 && sts==OK);

  game_destroy(game);
}


/*TDESC FUNCTIONS*/


void test1_game_get_last_tdesc()
{
  
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_last_tdesc(game) == NULL);

}

void test2_game_get_last_tdesc()
{
  char *tdesc;
  Game *game = NULL;

  if((tdesc=(char *)calloc(4,sizeof(char)))==NULL)
    return;

  game = game_create();
  

  game_set_last_tdesc(game, tdesc);
  PRINT_TEST_RESULT(game_get_last_tdesc(game) == tdesc);

  free(tdesc);
  game_destroy(game);

}

void test1_game_set_last_tdesc()
{
  
  Game *game = NULL;

  PRINT_TEST_RESULT(game_set_last_tdesc(game, NULL) == ERROR);

}

void test2_game_set_last_tdesc()
{
  char *tdesc;
  Game *game = NULL;

  if((tdesc=(char *)calloc(4,sizeof(char)))==NULL)
    return;

  game = game_create();
  

  game_set_last_tdesc(game, tdesc);
  PRINT_TEST_RESULT(game_get_last_tdesc(game) == tdesc);

  free(tdesc);
  game_destroy(game);

}



void test1_game_get_last_idesc()
{
  
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_last_idesc(game) == NULL);

}

void test2_game_get_last_idesc()
{
  char *idesc;
  Game *game = NULL;

  if((idesc=(char *)calloc(4,sizeof(char)))==NULL)
    return;

  game = game_create();
  

  game_set_last_idesc(game, idesc);
  PRINT_TEST_RESULT(game_get_last_idesc(game) == idesc);

  free(idesc);
  game_destroy(game);

}

void test1_game_set_last_idesc()
{
  
  Game *game = NULL;

  PRINT_TEST_RESULT(game_set_last_idesc(game, NULL) == ERROR);

}

void test2_game_set_last_idesc()
{
  char *idesc;
  Game *game = NULL;

  if((idesc=(char *)calloc(4,sizeof(char)))==NULL)
    return;

  game = game_create();
  

  game_set_last_idesc(game, idesc);
  PRINT_TEST_RESULT(game_get_last_idesc(game) == idesc);

  free(idesc);
  game_destroy(game);

}


/*DIALOGUE TESTS*/


void test1_game_existing_dialogue_id()
{
  Game *game = NULL;
  Dialogue *dialogue;

  game = game_create();
  dialogue = dialogue_create(ID);

  game_add_dialogue(game, dialogue);
  PRINT_TEST_RESULT(game_existing_dialogue_id(game, ID) == TRUE);

  game_destroy(game);
}

void test2_game_existing_dialogue_id()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_existing_dialogue_id(game, ID) == FALSE);

  game_destroy(game);
}

void test3_game_existing_dialogue_id()
{
  Game *game = NULL;

  game = game_create();
  
  PRINT_TEST_RESULT(game_existing_dialogue_id(game, NO_ID) == FALSE);

  game_destroy(game);
}

void test4_game_existing_dialogue_id()
{
  Game *game = NULL;
  
  PRINT_TEST_RESULT(game_existing_dialogue_id(game, ID) == FALSE);

}


void test1_game_add_dialogue()
{
  Game *game = NULL;
  Dialogue *dialogue;

  game = game_create();
  dialogue = dialogue_create(ID);

  PRINT_TEST_RESULT(game_add_dialogue(game, dialogue) == OK);

  game_destroy(game);
}

void test2_game_add_dialogue()
{
  Game *game = NULL;
  Dialogue *dialogue;

  game = game_create();
  dialogue = dialogue_create(ID);

  game_add_dialogue(game, dialogue);
  PRINT_TEST_RESULT(game_add_dialogue(game, dialogue) == ERROR);

  game_destroy(game);
}

void test3_game_add_dialogue()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_add_dialogue(game, dialogue) == ERROR);

  game_destroy(game);
}

void test4_game_add_dialogue()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;

  dialogue = dialogue_create(ID);

  PRINT_TEST_RESULT(game_add_dialogue(game, dialogue) == ERROR);

  dialogue_destroy(dialogue);
}

void test1_game_add_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue;

  game = game_create();
  dialogue = dialogue_create(ID);

  game_add_dialogue(game, dialogue);

  PRINT_TEST_RESULT(game_add_dialogue_rule(game, ID, RULE, SUCCESS) == OK);

  game_destroy(game);
}

void test2_game_add_dialogue_rule()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_add_dialogue_rule(game, ID, RULE, SUCCESS) == ERROR);

  game_destroy(game);
}

void test3_game_add_dialogue_rule()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_add_dialogue_rule(game, NO_ID, RULE, SUCCESS) == ERROR);

  game_destroy(game);
}

void test4_game_add_dialogue_rule()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_add_dialogue_rule(game, NO_ID, RULE, SUCCESS) == ERROR);

  game_destroy(game);
}

void test5_game_add_dialogue_rule()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_add_dialogue_rule(game, ID, RULE, SUCCESS) == ERROR);

  game_destroy(game);
}

void test1_game_get_dialogue_executed()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;

  game = game_create();
  dialogue = dialogue_create(ID);

  game_add_dialogue(game, dialogue);

  game_increase_dialogue_executed(game, ID);

  PRINT_TEST_RESULT(game_get_dialogue_executed(game, ID) == 1);

  game_destroy(game);
}

void test2_game_get_dialogue_executed()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_get_dialogue_executed(game, ID) == -1);

  game_destroy(game);
}

void test3_game_get_dialogue_executed()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_get_dialogue_executed(game, NO_ID) == -1);

  game_destroy(game);
}

void test4_game_get_dialogue_executed()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_dialogue_executed(game, ID) == -1);
}

void test1_game_increase_dialogue_executed()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;

  game = game_create();
  dialogue = dialogue_create(ID);

  game_add_dialogue(game, dialogue);

  PRINT_TEST_RESULT(game_increase_dialogue_executed(game, ID) == OK);

  game_destroy(game);
}

void test2_game_increase_dialogue_executed()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_increase_dialogue_executed(game, ID) == ERROR);

  game_destroy(game);
}

void test3_game_increase_dialogue_executed()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_increase_dialogue_executed(game, NO_ID) == ERROR);

  game_destroy(game);
}

void test4_game_increase_dialogue_executed()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_increase_dialogue_executed(game, ID) == ERROR);
}

void test1_game_decrease_dialogue_executed()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;

  game = game_create();
  dialogue = dialogue_create(ID);

  game_add_dialogue(game, dialogue);
  game_increase_dialogue_executed(game, ID);

  PRINT_TEST_RESULT(game_decrease_dialogue_executed(game, ID) == OK);

  game_destroy(game);
}

void test2_game_decrease_dialogue_executed()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_decrease_dialogue_executed(game, ID) == ERROR);

  game_destroy(game);
}

void test3_game_decrease_dialogue_executed()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_decrease_dialogue_executed(game, NO_ID) == ERROR);

  game_destroy(game);
}

void test4_game_decrease_dialogue_executed()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_decrease_dialogue_executed(game, ID) == ERROR);
}


void test1_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;
  char *aux;

  game = game_create();
  dialogue = dialogue_create(ID);

  dialogue_set_rule(dialogue, RULE, SUCCESS);

  game_add_dialogue(game, dialogue);
  
  aux = game_get_printed_dialogue_rule(game, 0, NULL, ID, OK);

  PRINT_TEST_RESULT(aux != NULL);

  game_destroy(game);
  free(aux);
}

void test2_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;
  char *aux;

  game = game_create();
  dialogue = dialogue_create(ID);

  dialogue_set_rule(dialogue, RULE, FAILURE);
  game_add_dialogue(game, dialogue);

  aux = game_get_printed_dialogue_rule(game, 0, NULL, ID, ERROR);
  PRINT_TEST_RESULT(aux != NULL);

  game_destroy(game);
  free(aux);
}

void test3_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;
  char *aux;

  game = game_create();
  dialogue = dialogue_create(ID);
  dialogue_set_rule(dialogue, RULE_W_ARG, SUCCESS);

  game_add_dialogue(game, dialogue);

  aux = game_get_printed_dialogue_rule(game, 0, ARG1, ID, OK);
  PRINT_TEST_RESULT(aux != NULL);

  game_destroy(game);
  free(aux);
}

void test4_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;
  char *aux;

  game = game_create();
  dialogue = dialogue_create(ID);
  dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

  game_add_dialogue(game, dialogue);

  aux = game_get_printed_dialogue_rule(game, 0, ARG1, ID, ERROR);
  PRINT_TEST_RESULT(aux != NULL);

  game_destroy(game);
  free(aux);
}

void test5_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;
  char aux[WORD_SIZE]="", *aux2;

  game = game_create();
  dialogue = dialogue_create(ID);
  dialogue_set_rule(dialogue, RULE_W_ARGS, SUCCESS);

  game_add_dialogue(game, dialogue);

  strcat(aux, ARG1);
  strcat(aux, "|");
  strcat(aux, ARG2);

  aux2 = game_get_printed_dialogue_rule(game, 0, aux, ID, OK);
  PRINT_TEST_RESULT(aux2 != NULL);

  game_destroy(game);
  free(aux2);
}

void test6_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;
  char aux[WORD_SIZE]="", *aux2;

  game = game_create();
  dialogue = dialogue_create(ID);

  dialogue_set_rule(dialogue, RULE_W_ARGS, FAILURE);
  game_add_dialogue(game, dialogue);

  strcat(aux, ARG1);
  strcat(aux, "|");
  strcat(aux, ARG2);

  aux2 = game_get_printed_dialogue_rule(game, 0, aux, ID, ERROR);
  PRINT_TEST_RESULT(aux2 != NULL);

  game_destroy(game);
  free(aux2);
}

void test7_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;

  game = game_create();
  dialogue = dialogue_create(ID);

  dialogue_set_rule(dialogue, RULE_W_ARG, SUCCESS);
  game_add_dialogue(game, dialogue);


  PRINT_TEST_RESULT(game_get_printed_dialogue_rule(game, 2, NULL, ID, OK) == NULL);

  game_destroy(game);
}

void test8_game_get_printed_dialogue_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;

  game = game_create();
  dialogue = dialogue_create(ID);
  dialogue_set_rule(dialogue, RULE_W_ARG, FAILURE);

  game_add_dialogue(game, dialogue);


  PRINT_TEST_RESULT(game_get_printed_dialogue_rule(game, 2, NULL, ID, OK) == NULL);

  game_destroy(game);
}


void test9_game_get_printed_dialogue_rule()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_get_printed_dialogue_rule(game, 0, NULL, ID, OK) == NULL);

  game_destroy(game);
}


void test10_game_get_printed_dialogue_rule()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_printed_dialogue_rule(game, 2, NULL, ID, OK) == NULL);

}


void test1_game_get_printed_repeated_error_rule()
{
  Game *game = NULL;
  Dialogue *dialogue = NULL;
  char *rule = NULL;

  game = game_create();
  dialogue = dialogue_create(REPEATED_ERROR_ID);

  dialogue_set_rule(dialogue, RULE, FAILURE);
  dialogue_set_rule(dialogue, RULE, FAILURE);
  game_add_dialogue(game, dialogue);

  rule = game_get_printed_repeated_error_rule(game, 1);
  PRINT_TEST_RESULT(rule != NULL);

  game_destroy(game);
  free(rule);
}

void test2_game_get_printed_repeated_error_rule()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_get_printed_repeated_error_rule(game, 0) == NULL);

  game_destroy(game);
}

void test3_game_get_printed_repeated_error_rule()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_printed_repeated_error_rule(game, 1) == NULL);
}


void test1_game_get_move_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move west\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_move_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You've moved west. Now you're in Corridor 4") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_move_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move east\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_move_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You've gone east. Be careful in Corridor 3, you're in James's lair") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test3_game_get_move_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move south\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_move_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You've moved south. There's no light in this space.") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test4_game_get_move_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move north\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_move_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You've gone north. There's no light in this space. Be careful with Jamie") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test5_game_get_move_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move up\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_move_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot move up. Try another action.") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test6_game_get_move_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move south\n");
  fprintf(f, "Move north\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_move_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Oops, it seems this link is closed") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test7_game_get_move_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_move_dialogue_rule(game, FAILURE);

  PRINT_TEST_RESULT(strcmp(rule, "Error while using the move command. You must specify a direction. Syntax: move <direction>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test1_game_get_attack_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;
  int player_health = 0;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move north\n");

  fclose(f);


  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  fclose(f);

  player_health = game_get_player_health(game);
  
  while (player_health > 0)
  {
    if ((f = fopen(TESTFILE, "w")) == NULL)
      return;

    fprintf(f, "Attack\n");

    fclose(f);
    
    if ((f = fopen(TESTFILE, "r")) == NULL)
      return;

    commands_get_user_input(game_get_last_command(game), f);
    game_update(game);

    fclose(f);

    if (player_health == game_get_player_health(game))
    {
      rule = game_get_attack_dialogue_rule(game);

      PRINT_TEST_RESULT(strcmp(rule, "You've made Jamie lost one point of life, but it's still alive! Nevermind, keep on trying!") == 0);

      game_destroy(game);
      free(rule);
      remove(TESTFILE);
      
      return;
    }

    player_health = game_get_player_health(game);
  }

  game_destroy(game);
  free(rule);
  remove(TESTFILE);
}

void test2_game_get_attack_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;
  int player_health = 0;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move east\n");

  fclose(f);


  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  fclose(f);

  player_health = game_get_player_health(game);

  while (player_health > 0 && game_get_last_command_status(game) == OK)
  {
    if ((f = fopen(TESTFILE, "w")) == NULL)
      return;

    fprintf(f, "Attack\n");

    fclose(f);

    if ((f = fopen(TESTFILE, "r")) == NULL)
      return;
    commands_get_user_input(game_get_last_command(game), f);
    game_update(game);

    fclose(f);

    if (player_health != game_get_player_health(game))
    {
      rule = game_get_attack_dialogue_rule(game);
      PRINT_TEST_RESULT(strcmp(rule, "You've lost one point of life while attacking James. Nevermind, keep on trying!") == 0);

      game_destroy(game);
      free(rule);
      remove(TESTFILE);
      
      return;
    }

    player_health = game_get_player_health(game);
  }

  game_destroy(game);
  free(rule);
  remove(TESTFILE);
}


void test3_game_get_attack_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;
  int player_health = 0;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move north\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  fclose(f);

  player_health = game_get_player_health(game);
  
  while (player_health > 0)
  {
    if ((f = fopen(TESTFILE, "w")) == NULL)
      return;

    fprintf(f, "Attack\n");
    fclose(f);

    if ((f = fopen(TESTFILE, "r")) == NULL)
      return;
    commands_get_user_input(game_get_last_command(game), f);
    game_update(game);

    fclose(f);

    if (enemy_get_health(game_get_enemy(game, 3)) == 0)
    {
      rule = game_get_attack_dialogue_rule(game);
      PRINT_TEST_RESULT(strcmp(rule, "You killed Jamie! Good job!") == 0);

      game_destroy(game);
      free(rule);
      remove(TESTFILE);
      
      return;
    }

    player_health = game_get_player_health(game);
  }

  game_destroy(game);
  free(rule);
  remove(TESTFILE);
}


void test4_game_get_attack_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;
  int player_health = 0;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "Move east\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  fclose(f);

  player_health = game_get_player_health(game);

  while (player_health > 0 && game_get_last_command_status(game) == OK)
  {
    if ((f = fopen(TESTFILE, "w")) == NULL)
      return;
    fprintf(f, "Attack\n");
    fclose(f);

    if ((f = fopen(TESTFILE, "r")) == NULL)
      return;
    commands_get_user_input(game_get_last_command(game), f);
    game_update(game);
    fclose(f);

    player_health = game_get_player_health(game);
  }

  if (player_health == 0)
  {
    rule = game_get_attack_dialogue_rule(game);
    PRINT_TEST_RESULT(strcmp(rule, "You were killed by James. God gives the worst battles to his best warriors. Good luck, soldier.") == 0);
  }

  game_destroy(game);
  free(rule);
  remove(TESTFILE);
}


void test1_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You've taken Stick1. See its utilities in the description or use the inspect command for more information") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test2_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take leaf1\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot take leaf1. Object not in your current space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test3_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");
  fprintf(f, "take Stick2\n");
  fprintf(f, "take Stick3\n");
  fprintf(f, "take leaf2\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot take leaf2. Your inventory is already full. Please drop one object") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test4_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "move north\n");
  fprintf(f, "take leaf1\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot take leaf1. There's no light in the current space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test5_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take leaf3\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot take leaf3. The object is not movable") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test6_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick3\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot take Stick3. You need Stick1 first in orther to take it") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test7_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");
  fprintf(f, "take Stick1\n");

  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot take Stick1. The object is already on your bag") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test8_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick4\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot take Stick4. The object doesn't exist") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test9_game_get_take_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_take_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the take command. You must specify the object you take. Syntax: take <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test1_game_get_drop_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Rope\n");
  fprintf(f, "drop Rope\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_drop_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You dropped Rope, it will remain in Entry waiting for you to take it again") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_drop_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");
  fprintf(f, "take Stick2\n");
  fprintf(f, "drop Stick1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_drop_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You dropped Stick1. As a result, Stick2 has also been dropped") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test3_game_get_drop_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");
  fprintf(f, "take Stick2\n");
  fprintf(f, "take Stick3\n");
  fprintf(f, "drop Stick1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_drop_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You dropped Stick1. As a result, Stick2, Stick3 have also been dropped") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test4_game_get_drop_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "drop Stick1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_drop_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot drop Stick1. Your inventory is empty. Go grab some objects") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test5_game_get_drop_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");
  fprintf(f, "drop Stick2\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_drop_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot drop Stick2. You don't have Stick2 in the inventory") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test6_game_get_drop_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "drop Stick4\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_drop_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot drop Stick4. That object doesn't exist in this game") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test7_game_get_drop_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "drop\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_drop_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the drop command. You must specify the object you drop. Syntax: drop <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test1_game_get_inspect_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "inspect Stick1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_inspect_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "So you're a curious player. Inspecting the object: Stick1") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_inspect_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "inspect space\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_inspect_dialogue_rule(game, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "So you're a curious player. Inspecting the space: Entry") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test3_game_get_inspect_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "inspect Stick4\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_inspect_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Sorry, Stick4 doesn't exist or isn't in the current space or in your inventory") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test4_game_get_inspect_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "inspect\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_inspect_dialogue_rule(game, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the inspect command. You must specify the object to be inspected or use space or s to inspect the space you're in") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test1_game_get_turn_on_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnon leaf3\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNON, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "Turning leaf3 on") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_turn_on_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnon Stick1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNON, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Sorry, you cannot illuminate with Stick1") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test3_game_get_turn_on_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "move north\n");
  fprintf(f, "turnon leaf1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNON, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Sorry, couldn't turn on leaf1: you have no light and the space has no light") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test4_game_get_turn_on_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnon Stick4\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNON, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "The object doesn't exist") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test5_game_get_turn_on_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnon leaf1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNON, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You don't have leaf1 in your inventory and the object is not in this space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test6_game_get_turn_on_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnon\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNON, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the turn-on command. You must specify the object you're illuminating. Syntax: turnon <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test1_game_get_turn_off_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnoff leaf3\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "Turning leaf3 off") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_turn_off_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnoff Stick1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Sorry, you cannot turn the light off with Stick1") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test3_game_get_turn_off_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "move north\n");
  fprintf(f, "turnoff leaf1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Sorry, couldn't turn off leaf1: you have no light and the space has no light") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test4_game_get_turn_off_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnoff Stick4\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "The object doesn't exist") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test5_game_get_turn_off_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnoff leaf1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You don't have leaf1 in your inventory and the object is not in this space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test6_game_get_turn_off_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "turnoff\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_turn_on_off_dialogue_rule(game, TURNOFF, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the turn-off command. You must specify the object you're turning-off. Syntax: turnoff <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test1_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "move south\n");
  fprintf(f, "open Corridor1_r with Rope");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You opened Corridor1_r with Rope from Corridor 1 to Entry") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open Corridor1 with Rope");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot open Corridor1 with Rope") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test3_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open Corridor2_r with Rope");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "There's no link with that name whose origin is in this space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test4_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open Corridor1 with Stick4");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "The object doesn't exist") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test5_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open Corridor_7 with Stick3");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "The link doesn't exist") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test6_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open Corridor1 with leaf1");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You don't have leaf1 in your inventory and the object is not in this space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test7_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open Corridor leaf3");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the open_link command. You must write \"with\" in between of <link_name> and <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test8_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open Corridor with");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the open_link command. You forgot to specify the object you're using") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test9_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open with Stick1");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the open_link command. You forgot to specify the link you're opening") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test10_game_get_open_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "open\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, OPENLINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the open_link command. Syntax: open/op <link_name> with <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}



void test1_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "move south\n");
  fprintf(f, "close Corridor1_r with Rope");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, SUCCESS);
  PRINT_TEST_RESULT(strcmp(rule, "You closed Corridor1_r with Rope from Corridor 1 to Entry") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close Corridor1 with Rope");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You cannot close Corridor1 with Rope") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test3_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close Corridor2_r with Rope");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "There's no link with that name whose origin is in this space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test4_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close Corridor1 with Stick4");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "The object doesn't exist") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test5_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close Corridor_7 with Stick3");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "The link doesn't exist") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test6_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close Corridor1 with leaf1");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "You don't have leaf1 in your inventory and the object is not in this space") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test7_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close Corridor leaf3");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the close_link command. You must write \"with\" in between of <link_name> and <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test8_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close Corridor with");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the close_link command. You forgot to specify the object you're using") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test9_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close with Stick1");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the close_link command. You forgot to specify the link you're closing") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test10_game_get_close_link_dialogue_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char *rule = NULL;

  game = game_create_from_file(DIALTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "close\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_open_close_link_dialogue_rule(game, CLOSELINK, FAILURE);
  PRINT_TEST_RESULT(strcmp(rule, "Error while using the close_link command. Syntax: close/cl <link_name> with <object_name>") == 0);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test1_game_get_dialogue_of_game_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char **rule = NULL;
  int num_dialogues = 0, i;

  game = game_create_from_file(DIALRTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "move east\n");
  fprintf(f, "move west\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_dialogue_of_game_rule(game, &num_dialogues);
  PRINT_TEST_RESULT(strcmp(rule[0], "The spaces The Workshop(Id:100), Corridor 1(Id:101), Corridor 2(Id:102), Corridor 3(Id:103), Corridor 4(Id:104), Pantry(Id:105) have flooded") == 0);

  for (i = 0; i < num_dialogues; i++)
    free(rule[i]);


  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_dialogue_of_game_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char **rule = NULL;
  int num_dialogues = 0, i;

  game = game_create_from_file(DIALRTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "move east\n");
  fprintf(f, "move west\n");
  fprintf(f, "move east\n");
  fprintf(f, "move west\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_dialogue_of_game_rule(game, &num_dialogues);
  PRINT_TEST_RESULT(strcmp(rule[0], "You are in a space that has sunk. That's a game over") == 0);

  for (i = 0; i < num_dialogues; i++)
    free(rule[i]);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test3_game_get_dialogue_of_game_rule()
{
  Game *game = NULL;
  FILE *f = NULL;
  char **rule = NULL;
  int num_dialogues = 0, i;

  game = game_create_from_file(DIALRTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");
  fprintf(f, "take Stick2\n");
  fprintf(f, "take Stick3\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);
  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  rule = game_get_dialogue_of_game_rule(game, &num_dialogues);
  PRINT_TEST_RESULT(strcmp(rule[0], "You have combined 3 Stick into one Boat_Mast") == 0);

  for (i = 0; i < num_dialogues; i++)
    free(rule[i]);

  game_destroy(game);
  free(rule);
  fclose(f);
  remove(TESTFILE);
}


void test4_game_get_dialogue_of_game_rule()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_get_dialogue_of_game_rule(game, NULL) == NULL);

  game_destroy(game);
}

void test5_game_get_dialogue_of_game_rule()
{
  Game *game = NULL;
  int num_dialogues = 0;

  PRINT_TEST_RESULT(game_get_dialogue_of_game_rule(game, &num_dialogues) == NULL);
}


void test1_game_get_all_dialogues()
{
  Game *game = NULL;
  int num_dialogues = 0;

  game = game_create_from_file(DIALTESTFILE);

  PRINT_TEST_RESULT(game_get_all_dialogues(game, &num_dialogues)!= NULL);

  game_destroy(game);
}

void test2_game_get_all_dialogues()
{
  Game *game = NULL;
  int num_dialogues = 0;

  game = game_create();

  (void)game_get_all_dialogues(game, &num_dialogues);
  PRINT_TEST_RESULT(num_dialogues == 0);
  
  game_destroy(game);
}

void test3_game_get_all_dialogues()
{
  Game *game = NULL;
  int num_dialogues = 0;
  
  PRINT_TEST_RESULT(game_get_all_dialogues(game, &num_dialogues) == NULL);
}

void test4_game_get_all_dialogues()
{
  Game *game = NULL;
  
  game = game_create();
  
  PRINT_TEST_RESULT(game_get_all_dialogues(game, NULL) == NULL);
  
  game_destroy(game);
}


/*GAME RULE FUNCTIONS*/

void test1_game_get_num_commands_till_flood()
{
  Game *game = NULL;
  FILE *f = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take Stick1\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  PRINT_TEST_RESULT(game_get_num_commands_till_flood(game) == 1);


  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test2_game_get_num_commands_till_flood()
{
  Game *game = NULL;
  FILE *f = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  if ((f = fopen(TESTFILE, "w")) == NULL)
    return;

  fprintf(f, "take leaf\n");
  fclose(f);

  if ((f = fopen(TESTFILE, "r")) == NULL)
    return;

  commands_get_user_input(game_get_last_command(game), f);
  game_update(game);

  PRINT_TEST_RESULT(game_get_num_commands_till_flood(game) == 2);


  game_destroy(game);
  fclose(f);
  remove(TESTFILE);
}

void test3_game_get_num_commands_till_flood()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_num_commands_till_flood(game) == -1);
}


void test1_game_get_rule()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_get_rule(game, 11) != NULL);

  game_destroy(game);
}

void test2_game_get_rule()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_get_rule(game, 3) == NULL);

  game_destroy(game);
}

void test3_game_get_rule()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_get_rule(game, NO_ID) == NULL);

  game_destroy(game);
}

void test4_game_get_rule()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_rule(game, 0) == NULL);
}

void test1_game_get_rule_id_at()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_get_rule_id_at(game, 0) == 11);

  game_destroy(game);
}

void test2_game_get_rule_id_at()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_get_rule_id_at(game, -1) == NO_ID);

  game_destroy(game);
}

void test3_game_get_rule_id_at()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_rule_id_at(game, 0) == NO_ID);
}


void test1_game_get_num_rules()
{
  Game *game = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_get_num_rules(game) == 0);

  game_destroy(game);
}


void test2_game_get_num_rules()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_get_num_rules(game) == -1);
}

void test1_game_add_rule()
{
  Game *game = NULL;
  Rule *rule = NULL;

  game = game_create();
  rule = rule_create(ID);

  PRINT_TEST_RESULT(game_add_rule(game, rule) == OK);

  game_destroy(game);
}

void test2_game_add_rule()
{
  Game *game = NULL;
  Rule *rule = NULL;

  game = game_create();

  PRINT_TEST_RESULT(game_add_rule(game, rule) == ERROR);

  game_destroy(game);
}

void test3_game_add_rule()
{
  Game *game = NULL;
  Rule *rule = NULL;

  rule = rule_create(ID);

  PRINT_TEST_RESULT(game_add_rule(game, rule) == ERROR);

  rule_destroy(rule);
}

void test1_game_rule_spawn_ground()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_rule_spawn_ground(game, 3) == OK);

  game_destroy(game);
}


void test2_game_rule_spawn_ground()
{
  Game *game = NULL;

  game = game_create_from_file(DIALRTESTFILE);

  PRINT_TEST_RESULT(game_rule_spawn_ground(game, -1) == ERROR);

  game_destroy(game);
}

void test3_game_rule_spawn_ground()
{
  Game *game = NULL;

  PRINT_TEST_RESULT(game_rule_spawn_ground(game, 1) == ERROR);
}




