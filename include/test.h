/**
 * @brief It defines the test interface
 *
 * @file test.h
 * @author Javier San Andrés
 * @version 3.0
 * @date 30/03/2023
 * @copyright GNU Public License
 */

#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
#define KRED  "\x1B[31m"            /*!< Red color for tests failing*/
#define KGRN  "\x1B[32m"            /*!< Green color for tests passing*/
#define KYEL  "\x1B[33m"            /*!< Yellow color for tests file printing*/
#define KCYN  "\x1B[36m"            /*!< Cyan color for tests name printing*/
#define RESET "\033[0m"             /*!< White color for test results printing*/
#else
#define KRED
#define KGRN
#define KYEL
#define KCYN
#define RESET
#endif

static int __test_counter = 0;    /*!< Number of executed tests*/
static int __test_passed  = 0;    /*!< Number of passed tests*/
static int __pass = 0;            /*!< Variable that stores the tests results*/

#define PRINT_TEST_RESULT(x) do{					\
    __test_counter++;							\
    __pass = (x);							\
    __test_passed = (__pass)? __test_passed + 1 : __test_passed;	\
    printf(KYEL "%s" RESET " line "  "%d " KCYN "%s" RESET ": %s\n",	\
	   __FILE__, __LINE__ , __FUNCTION__,	((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET));	\
  } while (0) /*!<Prints executed test and its result*/


#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter)) /*!<Prints percentage of passed tests*/

      

#endif
