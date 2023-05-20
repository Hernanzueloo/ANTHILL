/**
 * @brief It tests commands module
 *
 * @file command_test.c
 * @author David Brenchley
 * @version 3.0
 * @date 29/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "command_test.h"
#include "test.h"

#define MAX_TESTS 27                   /*!<Maximum number of test to be executed*/
#define TESTFILE "command_test.txt"    /*!<Name to an auxiliary file for testing*/

/**
 * @brief Main function for COMMAND unit tests.
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
    printf("\n\nRunning all test for module commands:\n");
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

  if (all || test == 1) test1_commands_create();
  if (all || test == 2) test2_commands_create();
  if (all || test == 3) test3_commands_create();
  if (all || test == 4) test4_commands_create();
  if (all || test == 5) test1_commands_get_cmd();
  if (all || test == 6) test2_commands_get_cmd();
  if (all || test == 7) test3_commands_get_cmd();
  if (all || test == 8) test1_commands_get_args();
  if (all || test == 9) test2_commands_get_args();
  if (all || test == 10) test3_commands_get_args();
  if (all || test == 11) test1_commands_get_num_args();
  if (all || test == 12) test2_commands_get_num_args();
  if (all || test == 13) test1_commands_get_status();
  if (all || test == 14) test2_commands_get_status();
  if (all || test == 15) test1_commands_set_status();
  if (all || test == 16) test2_commands_set_status();
  if (all || test == 17) test1_commands_get_user_input();
  if (all || test == 18) test2_commands_get_user_input();
  if (all || test == 19) test1_commands_get_direction();
  if (all || test == 20) test2_commands_get_direction();
  if (all || test == 21) test3_commands_get_direction();
  if (all || test == 22) test1_commands_get_formatted_cmd();
  if (all || test == 23) test2_commands_get_formatted_cmd();
  if (all || test == 24) test3_commands_get_formatted_cmd();
  if (all || test == 25) test1_commands_get_formatted_direction();
  if (all || test == 26) test2_commands_get_formatted_direction();
  if (all || test == 27) test3_commands_get_formatted_direction();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

void test1_commands_create()
{
  Commands *cmds;
  cmds = commands_create();

  PRINT_TEST_RESULT(cmds != NULL);
  commands_destroy(cmds);
}

void test2_commands_create()
{
  Commands *cmds;
  cmds = commands_create();

  PRINT_TEST_RESULT(commands_get_cmd(cmds) == NO_CMD);
  commands_destroy(cmds);
}

void test3_commands_create()
{
  Commands *cmds;
  cmds = commands_create();

  PRINT_TEST_RESULT(commands_get_num_args(cmds) == 0);
  commands_destroy(cmds);
}

void test4_commands_create()
{
  Commands *cmds;
  cmds = commands_create();

  PRINT_TEST_RESULT(commands_get_args(cmds, 0) == NULL);
  commands_destroy(cmds);
}

void test1_commands_get_cmd()
{
  PRINT_TEST_RESULT(commands_get_cmd(NULL) == NO_CMD);
}

void test2_commands_get_cmd()
{
  Commands *cmds;
  FILE *f;

  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "Move w");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(commands_get_cmd(cmds) == MOVE);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);
  
}


void test3_commands_get_cmd()
{
  Commands *cmds;
  FILE *f;

  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "random words");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(commands_get_cmd(cmds) == UNKNOWN);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);
  
}

void test1_commands_get_args()
{
  PRINT_TEST_RESULT(commands_get_args(NULL, 0) == NULL);
}

void test2_commands_get_args()
{
  Commands *cmds;
  FILE *f;

  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "take grain");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(strcmp(commands_get_args(cmds, 0),"grain") == 0);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);
  
}

void test3_commands_get_args()
{
  Commands *cmds;
  FILE *f;

  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "take grain");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(commands_get_args(cmds, 2) == NULL);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);
  
}


void test1_commands_get_num_args()
{
  PRINT_TEST_RESULT(commands_get_num_args(NULL) == -1);
}

void test2_commands_get_num_args()
{
  
  Commands *cmds;
  FILE *f;

  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "take grain");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(commands_get_num_args(cmds) == 1);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);
  
}


void test1_commands_get_status()
{
    PRINT_TEST_RESULT(commands_get_status(NULL) == ERROR );

}

void test2_commands_get_status()
{
  
  Commands *cmds;

  cmds = commands_create();

  PRINT_TEST_RESULT(commands_get_status(cmds) == OK);

  commands_destroy(cmds);

}

void test1_commands_set_status()
{
    PRINT_TEST_RESULT(commands_set_status(NULL, OK) == ERROR );

}

void test2_commands_set_status()
{
  
  Commands *cmds;
  cmds = commands_create();

  commands_set_status(cmds, ERROR);
  PRINT_TEST_RESULT(commands_get_status(cmds) == ERROR);
  
  commands_destroy(cmds);

}


void test1_commands_get_user_input()
{
    FILE *f;

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    return;
  }

  fprintf(f, "take grain");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    return;
  }
  
  PRINT_TEST_RESULT(commands_get_user_input(NULL, f) == NO_CMD);

  fclose(f);

}

void test2_commands_get_user_input()
{
  T_Command cmd;
  Commands *cmds;
  FILE *f;
  

  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "take grain");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  cmd=commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(strcmp(commands_get_args(cmds, 0), "grain")==0 && 
                    commands_get_cmd(cmds)== TAKE && 
                    commands_get_num_args(cmds)== 1 &&
                    cmd == TAKE);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);

}


void test1_commands_get_direction()
{   
  PRINT_TEST_RESULT(commands_get_direction(NULL) == NO_DIR);
}


void test2_commands_get_direction()
{
  Commands *cmds;
  FILE *f;
  
  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "take pipe");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  (void)commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(commands_get_direction(cmds)==NO_DIR);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);


}

void test3_commands_get_direction()
{
  Commands *cmds;
  FILE *f;
  
  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "move south");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  (void)commands_get_user_input(cmds, f);

  PRINT_TEST_RESULT(commands_get_direction(cmds)==SOUTH);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);

}

void test1_commands_get_formatted_cmd()
{
    PRINT_TEST_RESULT(commands_get_formatted_cmd(NULL)==NULL);
}

void test2_commands_get_formatted_cmd()
{
  Commands *cmds;
  FILE *f;
  char *format;
  
  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "m s");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  (void)commands_get_user_input(cmds, f);
  format=commands_get_formatted_cmd(cmds);

  PRINT_TEST_RESULT(strcmp(format, "move south")==0);

  free(format);
  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);

}

void test3_commands_get_formatted_cmd()
{
  Commands *cmds;
  FILE *f;
  char *format;
  
  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "a");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  (void)commands_get_user_input(cmds, f);
  format=commands_get_formatted_cmd(cmds);

  PRINT_TEST_RESULT(strcmp(format, "attack")==0);

  free(format);
  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);

}



void test1_commands_get_formatted_direction()
{
    PRINT_TEST_RESULT(commands_get_formatted_direction(NULL)==NULL);
}

void test2_commands_get_formatted_direction()
{
  Commands *cmds;
  FILE *f;
  char *format;
  
  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "m s");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  (void)commands_get_user_input(cmds, f);
  format=commands_get_formatted_direction(cmds);

  PRINT_TEST_RESULT(strcmp(format, "south")==0);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);

}

void test3_commands_get_formatted_direction()
{
  Commands *cmds;
  FILE *f;
  char *format;
  
  cmds = commands_create();

  f = fopen(TESTFILE, "w");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  fprintf(f, "a");
  fclose(f);

  f = fopen(TESTFILE, "r");
  if (!f)
  {
    commands_destroy(cmds);
    return;
  }

  (void)commands_get_user_input(cmds, f);
  format=commands_get_formatted_direction(cmds);

  PRINT_TEST_RESULT(format==NULL);

  commands_destroy(cmds);
  fclose(f);
  remove(TESTFILE);

}
