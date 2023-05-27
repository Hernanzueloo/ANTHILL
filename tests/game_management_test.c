/**
 * @brief It tests game_management module
 *
 * @file game_management_test.c
 * @author Javier San Andres
 * @version 3.0
 * @date 09/04/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_management.h"
#include "game_management_test.h"
#include "test.h"

#define MAX_TESTS 26                            /*!<Maximum number of test to be executed*/
#define GAMERDRFILE "game_management_test.txt"  /*!<Name to an auxiliary file for testing*/
#define GAMEWTRFILE "game_management_test2.txt" /*!<Name to a second auxiliary file for testing*/

/**
 * @brief Main function for game_management unit tests.
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
        printf("\n\nRunning all test for module game_management:\n");
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

    if (all || test == 1)
        test1_game_management_load();
    if (all || test == 2)
        test2_game_management_load();
    if (all || test == 3)
        test3_game_management_load();
    if (all || test == 4)
        test4_game_management_load();
    if (all || test == 5)
        test5_game_management_load();
    if (all || test == 6)
        test6_game_management_load();
    if (all || test == 7)
        test7_game_management_load();
    if (all || test == 8)
        test8_game_management_load();
    if (all || test == 9)
        test9_game_management_load();
    if (all || test == 10)
        test10_game_management_load();
    if (all || test == 11)
        test11_game_management_load();
    if (all || test == 12)
        test12_game_management_load();
    if (all || test == 13)
        test13_game_management_load();
    if (all || test == 14)
        test14_game_management_load();
    if (all || test == 15)
        test1_game_management_save();
    if (all || test == 16)
        test2_game_management_save();
    if (all || test == 17)
        test3_game_management_save();
    if (all || test == 18)
        test4_game_management_save();
    if (all || test == 19)
        test5_game_management_save();
    if (all || test == 20)
        test6_game_management_save();
    if (all || test == 21)
        test7_game_management_save();
    if (all || test == 22)
        test8_game_management_save();
    if (all || test == 23)
        test9_game_management_save();
    if (all || test == 24)
        test10_game_management_save();
    if (all || test == 25)
        test11_game_management_save();
    if (all || test == 26)
        test12_game_management_save();
    if (all || test == 27)
        test13_game_management_save();
    if (all || test == 28)
        test14_game_management_save();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_game_management_load()
{
    Game *game = NULL;

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == ERROR);
}

/*Game data*/
void test2_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:5|");
    fclose(f);

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
}

void test3_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:5|0.25|\n");
    fclose(f);
    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_get_num_executed_commands(game) == 5);
    game_destroy(game);
    remove(GAMERDRFILE);
}

/*Game spaces*/
void test4_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|");
    fclose(f);

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
}

void test5_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_get_space_id_at(game, 0) == 65);
    game_destroy(game);
    remove(GAMERDRFILE);
}

/*Game enemy*/
void test6_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|\n");
    fprintf(f, "%s", "#s:103|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#e:2|James|103|3|gdesc|");
    fclose(f);

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == OK);

    game_destroy(game);
    remove(GAMERDRFILE);
}

void test7_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|\n");
    fprintf(f, "%s", "#s:103|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#e:2|James|103|3|gdesc|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_get_enemy_id_at(game, 0) == 2);
    game_destroy(game);
    remove(GAMERDRFILE);
}

/*Game objects*/
void test8_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }


    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#o:37|Lantern|065|The lantern makes the darkness disappear|1|1|-1|-1|1|0|");
    fclose(f);

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == OK);
    game_destroy(game);

    remove(GAMERDRFILE);
}

void test9_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }
    
    
    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#o:37|Lantern|065|The lantern makes the darkness disappear|1|1|-1|-1|1|0|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_get_object_id_at(game, 0) == 37);
    game_destroy(game);
    remove(GAMERDRFILE);
}

/*Game link*/
void test10_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    
    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:101|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "%s", "#s:100|The OtherWorkshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");

    fprintf(f, "#l:32|Entry_r|101|100|0|1|");
    fclose(f);

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
}

void test11_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "#l:32|Entry_r|101|100|0|1|\n");
    fprintf(f, "%s", "#s:101|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "%s", "#s:100|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|");

    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_get_link_id_at(game, 0) == 32);
    game_destroy(game);
    remove(GAMERDRFILE);
}

/*Game player*/
void test12_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }


    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:100|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|");
    fprintf(f, "#p:1|Bug|100|5|3|0|");
    fclose(f);

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
}

void test13_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "#p:1|Bug|100|5|3|0|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_get_player(game) != NULL);
    game_destroy(game);
    remove(GAMERDRFILE);
}

/*General*/
void test14_game_management_load()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }


    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "#s:102|Entry     |1|0| __  ___  _  _|_ /  oo   _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/       /_/|__/  --oo8___/|The entry is the entrance to the nest|The entry, which is typically a small and inconspicuous opening, serves as the primary means of access for the inhabitants of the nest, allowing them to come and go as needed to gather food, care for their young, and carry out other essential tasks.|\n");
    fprintf(f, "#s:103|Entry other  |1|0| __  ___  _  _|_ /  oo   _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/       /_/|__/  --oo8___/|The entry is the entrance to the nest|The entry, which is typically a small and inconspicuous opening, serves as the primary means of access for the inhabitants of the nest, allowing them to come and go as needed to gather food, care for their young, and carry out other essential tasks.|\n");
    fprintf(f, "#p:1|Bug|102|5|3|0|\n");
    fprintf(f, "#o:21|Stick1|102|Sticks are useful for building ship masts.|1|1|-1|0|\n");
    fprintf(f, "#l:35|Corridor2|102|103|1|1|");
    fclose(f);

    PRINT_TEST_RESULT(game_management_load(game, GAMERDRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
}

/*Save*/
void test1_game_management_save()
{
    Game *game = NULL;

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == ERROR);
    remove(GAMEWTRFILE);
}

/*Game data*/
void test2_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }


    fprintf(f, "%s", "#G:0|0.25|\n");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == OK);
    game_destroy(game);
    remove(GAMEWTRFILE);
    remove(GAMERDRFILE);
}

void test3_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }


    fprintf(f, "%s", "#G:5|0.25|\n");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);
    (void)game_management_save(game, GAMEWTRFILE);
    game_destroy(game);
    
    game=game_create();
    (void)game_management_load(game, GAMEWTRFILE);

    PRINT_TEST_RESULT(game_get_num_executed_commands(game) == 5);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

/*Game spaces*/
void test4_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }


    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

void test5_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);
    (void)game_management_save(game, GAMEWTRFILE);
    game_destroy(game);
    
    game=game_create();
    (void)game_management_load(game, GAMEWTRFILE);

    PRINT_TEST_RESULT(game_get_space_id_at(game, 0) == 65);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

/*Game enemy*/
void test6_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:103|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#e:2|James|103|3|gdesc|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

void test7_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:103|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#e:2|James|103|3|gdesc|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);
    (void)game_management_save(game, GAMEWTRFILE);
    game_destroy(game);
    
    game=game_create();
    (void)game_management_load(game, GAMEWTRFILE);

    PRINT_TEST_RESULT(game_get_enemy_id_at(game, 0) == 2);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

/*Game objects*/
void test8_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#o:37|Lantern|065|The lantern makes the darkness disappear|1|1|-1|-1|1|0|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

void test9_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:065|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#o:37|Lantern|065|The lantern makes the darkness disappear|1|1|-1|-1|1|0|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);
    (void)game_management_save(game, GAMEWTRFILE);
    game_destroy(game);
    
    game=game_create();
    (void)game_management_load(game, GAMEWTRFILE);

    PRINT_TEST_RESULT(game_get_object_id_at(game, 0)==37);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

/*Game link*/
void test10_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:101|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "%s", "#s:100|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#l:32|Entry_r|101|100|0|1|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

void test11_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "#l:32|Entry_r|101|100|0|1|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);
    (void)game_management_save(game, GAMEWTRFILE);
    game_destroy(game);
    
    game=game_create();
    (void)game_management_load(game, GAMEWTRFILE);

    PRINT_TEST_RESULT(game_get_link_id_at(game, 0) == 32);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

/*Game player*/
void test12_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "%s", "#s:100|The Workshop|1|0| __  ___  _  _|_ /  oo  i _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/ i      /_/|__/  --oo8___/|A place for crafting and creation|The workshop is a spacious and well-lit area designed for artisans to create and repair a variety of tools, equipment, and other objects.|\n");
    fprintf(f, "#p:1|Bug|100|5|3|0|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

void test13_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }

    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "#p:1|Bug|100|5|3|0|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);
    (void)game_management_save(game, GAMEWTRFILE);
    game_destroy(game);
    
    game=game_create();
    (void)game_management_load(game, GAMEWTRFILE);

    PRINT_TEST_RESULT(game_get_player(game) != NULL);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}

/*General*/
void test14_game_management_save()
{
    Game *game;
    FILE *f;
    game = game_create();

    if ((f = fopen(GAMERDRFILE, "w")) == NULL)
    {
        return;
    }


    fprintf(f, "%s", "#G:0|0.25|\n");
    fprintf(f, "#s:100|Entry     |1|0| __  ___  _  _|_ /  oo   _/ |   _ /    o 0 |mo'__ 0 o8o  '|__/       /_/|__/  --oo8___/|The entry is the entrance to the nest|The entry, which is typically a small and inconspicuous opening, serves as the primary means of access for the inhabitants of the nest, allowing them to come and go as needed to gather food, care for their young, and carry out other essential tasks.|\n");
    fprintf(f, "#p:1|Bug|100|5|3|0|\n");
    fprintf(f, "#o:21|Stick1|100|Sticks are useful for building ship masts.|1|1|-1|0|\n");
    fprintf(f, "#l:35|Corridor2|102|103|1|1|");
    fclose(f);

    (void)game_management_load(game, GAMERDRFILE);

    PRINT_TEST_RESULT(game_management_save(game, GAMEWTRFILE) == OK);
    game_destroy(game);
    remove(GAMERDRFILE);
    remove(GAMEWTRFILE);
}