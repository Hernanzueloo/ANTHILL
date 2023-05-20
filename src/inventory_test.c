/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @author Alejandro Garcia
 * @version 3.0
 * @date 24/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 37                            /*!<Maximum number of test to be executed*/
#define ID 3                                    /*!<Id to be added in the inventory*/
#define ID2 4                                   /*!<Id to be added in the inventory*/
#define INV_FILE "inventory_test.txt"           /*!<Name to an auxiliary file for testing*/

/**
 * @brief Main function for INVENTORY unit tests.
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
        printf("\n\nRunning all test for module inventory:\n");
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

    if (all || test == 1) test1_inventory_create();
    if (all || test == 2) test1_inventory_is_empty();
    if (all || test == 3) test2_inventory_is_empty();
    if (all || test == 4) test3_inventory_is_empty();
    if (all || test == 5) test1_inventory_add_id();
    if (all || test == 6) test2_inventory_add_id();
    if (all || test == 7) test3_inventory_add_id();
    if (all || test == 8) test4_inventory_add_id();
    if (all || test == 9) test5_inventory_add_id();
    if (all || test == 15) test1_inventory_delete_id();
    if (all || test == 16) test2_inventory_delete_id();
    if (all || test == 17) test3_inventory_delete_id();
    if (all || test == 18) test4_inventory_delete_id();
    if (all || test == 19) test5_inventory_delete_id();
    if (all || test == 20) test1_inventory_get_number_ids();
    if (all || test == 21) test2_inventory_get_number_ids();
    if (all || test == 22) test1_inventory_contains_id();
    if (all || test == 23) test2_inventory_contains_id();
    if (all || test == 24) test3_inventory_contains_id();
    if (all || test == 25) test4_inventory_contains_id();
    if (all || test == 26) test1_inventory_get_all_ids();
    if (all || test == 27) test2_inventory_get_all_ids();
    if (all || test == 28) test3_inventory_get_all_ids();
    if (all || test == 29) test4_inventory_get_all_ids();
    if (all || test == 30) test1_inventory_print();
    if (all || test == 31) test2_inventory_print();
    if (all || test == 32) test3_inventory_print();
    if (all || test == 33) test1_inventory_get_max_objs();
    if (all || test == 34) test2_inventory_get_max_objs();
    if (all || test == 35) test3_inventory_get_max_objs();
    if (all || test == 36) test1_inventory_set_max_objs();
    if (all || test == 37) test2_inventory_set_max_objs();

    

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_inventory_create()
{
    Inventory *inv;

    inv = inventory_create();
    PRINT_TEST_RESULT(inv != NULL);
    inventory_destroy(inv);
}

void test1_inventory_is_empty()
{
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_is_empty(s) == TRUE);
    inventory_destroy(s);
}

void test2_inventory_is_empty()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    PRINT_TEST_RESULT(inventory_is_empty(s) == FALSE);
    inventory_destroy(s);
}

void test3_inventory_is_empty()
{
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_is_empty(s) == TRUE);
}

void test1_inventory_add_id()
{
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_add_id(s, ID) == OK);
    inventory_destroy(s);
}

void test2_inventory_add_id()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    inventory_delete_id(s, ID);
    PRINT_TEST_RESULT(inventory_add_id(s, ID) == OK);
    inventory_destroy(s);
}

void test3_inventory_add_id()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    inventory_delete_id(s, ID);
    inventory_add_id(s, ID2);
    PRINT_TEST_RESULT(inventory_get_number_ids(s) == 1);

    inventory_destroy(s);
}

void test4_inventory_add_id()
{
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_add_id(s, NO_ID) == ERROR);
    inventory_destroy(s);
}

void test5_inventory_add_id()
{
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_add_id(s, ID) == ERROR);
}

void test1_inventory_delete_id()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    PRINT_TEST_RESULT(inventory_delete_id(s, ID) == OK);
    inventory_destroy(s);
}

void test2_inventory_delete_id()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    PRINT_TEST_RESULT(inventory_delete_id(s, ID2) == OK);
    inventory_destroy(s);
}

void test3_inventory_delete_id()
{
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_delete_id(s, ID) == OK);
    inventory_destroy(s);
}

void test4_inventory_delete_id()
{
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_delete_id(s, ID) == ERROR);
}

void test5_inventory_delete_id()
{
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_delete_id(s, NO_ID) == ERROR);
    inventory_destroy(s);
}

void test1_inventory_get_number_ids()
{
    Inventory *s;
    int n;
    s = inventory_create();
    inventory_add_id(s, ID);
    n = inventory_get_number_ids(s);
    PRINT_TEST_RESULT(n == 1);
    inventory_destroy(s);
}

void test2_inventory_get_number_ids()
{
    Inventory *s = NULL;
    int n;
    n = inventory_get_number_ids(s);
    PRINT_TEST_RESULT(n == -1);
}

void test1_inventory_contains_id()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    PRINT_TEST_RESULT(inventory_contains_id(s, ID) == TRUE);
    inventory_destroy(s);
}

void test2_inventory_contains_id()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    PRINT_TEST_RESULT(inventory_contains_id(s, ID2) == FALSE);
    inventory_destroy(s);
}

void test3_inventory_contains_id()
{
    Inventory *s;
    s = inventory_create();
    PRINT_TEST_RESULT(inventory_contains_id(s, NO_ID) == FALSE);
    inventory_destroy(s);
}

void test4_inventory_contains_id()
{
    Inventory *s = NULL;
    PRINT_TEST_RESULT(inventory_contains_id(s, ID2) == FALSE);
}

void test1_inventory_get_all_ids()
{
    Inventory *s;
    Id *id;
    int num;
    s = inventory_create();
    inventory_add_id(s, ID);
    id = inventory_get_all_ids(s, &num);
    PRINT_TEST_RESULT(id != NULL);
    inventory_destroy(s);
    free(id);
}

void test2_inventory_get_all_ids()
{
    Inventory *s;
    Id *id;
    int num;
    s = inventory_create();
    id = inventory_get_all_ids(s, &num);
    PRINT_TEST_RESULT(id == NULL);
    inventory_destroy(s);
}

void test3_inventory_get_all_ids()
{
    Inventory *s = NULL;
    Id *id;
    int num;
    s = inventory_create();
    id = inventory_get_all_ids(s, &num);
    PRINT_TEST_RESULT(id == NULL);
    inventory_destroy(s);
}

void test4_inventory_get_all_ids()
{
    Inventory *s = NULL;
    Id *id;
    s = inventory_create();
    inventory_add_id(s, ID);
    id = inventory_get_all_ids(s, NULL);
    PRINT_TEST_RESULT(id == NULL);
    inventory_destroy(s);
}

void test1_inventory_print()
{
    Inventory *s;
    FILE *f;
    if ((f = fopen(INV_FILE, "w")) == NULL)
        return;
    s = inventory_create();
    inventory_add_id(s, ID);
    PRINT_TEST_RESULT(inventory_print(s, f) == OK);
    inventory_destroy(s);
    fclose(f);
    remove(INV_FILE);
}

void test2_inventory_print()
{
    Inventory *s = NULL;
    FILE *f;
    if ((f = fopen(INV_FILE, "w")) == NULL)
        return;
    PRINT_TEST_RESULT(inventory_print(s, f) == ERROR);
    fclose(f);
    remove(INV_FILE);
}

void test3_inventory_print()
{
    Inventory *s;
    s = inventory_create();
    inventory_add_id(s, ID);
    PRINT_TEST_RESULT(inventory_print(s, NULL) == ERROR);
    inventory_destroy(s);
}

void test1_inventory_get_max_objs()
{
    Inventory *s;
    s = inventory_create();

    PRINT_TEST_RESULT(inventory_get_max_objs(s) == MAX_OBJS_INIT);
    inventory_destroy(s);
}

void test2_inventory_get_max_objs()
{
    Inventory *s;
    int i, maxObjs;

    s = inventory_create();
    maxObjs = inventory_get_max_objs(s);

    for (i = 0; i < maxObjs - 1; i++)
    {
        if (inventory_add_id(s, i) == ERROR)
        {
            PRINT_TEST_RESULT(ERROR);
            return;
        }
    }

    PRINT_TEST_RESULT(inventory_add_id(s, i));
    inventory_destroy(s);

}

void test3_inventory_get_max_objs()
{
    Inventory *s;
    int i, maxObjs;

    s = inventory_create();
    maxObjs = inventory_get_max_objs(s);

    for (i = 0; i < maxObjs; i++)
    {
        if (inventory_add_id(s, i) == ERROR)
        {
            PRINT_TEST_RESULT(1 == 0);
            return;
        }
    }

    PRINT_TEST_RESULT(inventory_add_id(s, i) == ERROR);
    inventory_destroy(s);
}

void test1_inventory_set_max_objs()
{
    Inventory *s;
    int maxObjs;

    s = inventory_create();
    maxObjs = inventory_get_max_objs(s);
    if (inventory_set_max_objs(s, maxObjs+1) == ERROR)
    {
        PRINT_TEST_RESULT(1 == 0);
        return;
    }

    PRINT_TEST_RESULT(inventory_get_max_objs(s) == maxObjs+1);
    inventory_destroy(s);
}

void test2_inventory_set_max_objs()
{
    Inventory *s;

    s = inventory_create();
    inventory_add_id(s, ID);
    inventory_add_id(s, ID2);

    PRINT_TEST_RESULT(inventory_set_max_objs(s, 1) == ERROR);
    inventory_destroy(s);
}