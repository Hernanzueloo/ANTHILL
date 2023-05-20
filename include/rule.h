/**
 * @brief It defines the rule interface
 *
 * @file rule.h
 * @author Diego Rodriguez Ortiz
 * @version 3.0
 * @date 14-04-2023
 * @copyright GNU Public License
 */

#ifndef RULE_H
#define RULE_H

#include "types.h"
/**
 * @brief rule structure
 *
 */
typedef struct _Rule Rule;

/**
 * @brief action structure
 *
 */
typedef struct _Action Action;

/**
 * @brief condition structure
 *
 */
typedef struct _Condition Condition;

#define N_CONDITIONS 10 /*!<Number of posible conditions*/
#define N_ACTIONS 14   /*!<Number of possible actions*/

#define MAX_ACTIONS N_ACTIONS       /*!<Max number of actions in a rule*/
#define MAX_CONDITIONS N_CONDITIONS /*!<Max number of conditions in a rule*/
#define MAX_ARGS 3                  /*!<Max number of argumements in an action or condition*/
#define RULE_SIZE 1000              /*!<Size of a rule description*/

/**
 * @brief CONDITION data type to evaluate rules
 */
typedef enum
{
  NO_CONDITION = -1,
  IN_SPACE,        /*!<If the player is in a Space*/
  HAS_OBJECT,      /*!<If the player has an Object*/
  HEALTH_POINTS_P, /*!< If the Player have a given number of health points*/
  HEALTH_POINTS_E, /*!< If a given enemy have a given number of health points*/
  N_COMANDS,       /*!< It evaluates true every N spaces*/
  DROP_OBJ,            /*!< It evlauates if the last comand was droping a object*/
  SAME_OBJECT,     /*!< It evaluates if the player has N objects with the same first n letters*/
  PLAYER_TYPE,      /*!< It evaluates if the player is of a given type */
  HAS_SUNK           /*!< It evaluates if a space has sunk i*/
} T_CONDITION;

/**
 * @brief ACTION data type to execute rules
 */
typedef enum
{
  NO_ACTION = -1,
  ATTACK_P,     /*!<Reduce the health of the player*/
  HEAL_P,       /*!<Heal the player*/
  ATTACK_E,     /*!<Reduce the health of an enemy*/
  HEAL_E,       /*!< Heal an enemy*/
  OPEN_LINK,    /*!< Opens a link*/
  CLOSE_LINK,   /*!< Closes a link*/
  INUNDATION,   /*!< Inundate N spaces*/
  SAVE_SPACE,   /*!< Saves the current space*/
  SPAWN_GROUND, /*!< It creates N ground objects*/
  COMBINE,      /*!< It combines N objects into a special one*/
  SET_MOVABLE,  /*!< It set movable all object in a space to hidden*/
  VICTORY_ACT,  /*!< Terminate game victoriously*/
  DEFEAT_ACT    /*!< Terminate game in defeat*/
} T_ACTION;

/**
 * @brief It allocates memory for a rule
 * @author Diego Rodríguez Ortiz
 * @param id the if of the rule
 * @return A rule pointer or a NULL pointer if error
 */
Rule *rule_create(Id id);

/**
 * @brief It frees allocated memory for a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 */
void rule_destroy(Rule *rule);

/**
 * @brief It gets the id of a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 * @return The Id of the rule
 */
Id rule_get_id(Rule *rule);

/**
 * @brief It gets the bool value of execute of a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 * @return The bool value of execute
 */
BOOL rule_get_executed(Rule *rule);

/**
 * @brief It sets the execution to a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 * @param val the Boolean value to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS rule_set_executed(Rule *rule, BOOL val);

/**
 * @brief It gets an action of a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 * @param index the index-th action of the rule
 * @return The index-th action
 */
Action *rule_get_action(Rule *rule, int index);

/**
 * @brief It gets an condition of a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 * @param index the index-th action of the rule
 * @return The index-th condition
 */
Condition *rule_get_condition(Rule *rule, int index);

/**
 * @brief It gets num of condirions of a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 * @return The number of condition condition
 */
int rule_get_num_conditions(Rule *rule);

/**
 * @brief It gets num of action of a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to the rule
 * @return The number of condition condition
 */
int rule_get_num_actions(Rule *rule);

/**
 * @brief It gets the argsId of action of a rule
 * @author Diego Rodríguez Ortiz
 * @param act Pointer to an action
 * @return An array of Ids with the arguments
 */
Id *rule_action_get_argsId(Action *act);
/**
 * @brief It gets the number of argsId of action of a rule
 * @author Diego Rodríguez Ortiz
 * @param act Pointer to an action
 * @return A number of arguments in Ids
 */
int rule_action_get_numId(Action *act);
/**
 * @brief It gets the argint of action of a rule
 * @author Diego Rodríguez Ortiz
 * @param act Pointer to an action
 * @return The integer argument
 */
int rule_action_get_argint(Action *act);

/**
 * @brief It gets the char argument of action of a rule
 * @author Diego Rodríguez Ortiz
 * @param act Pointer to an action
 * @return The char argument
 */
char *rule_action_get_argname(Action *act);

/**
 * @brief It gets the type of the action of a rule
 * @author Diego Rodríguez Ortiz
 * @param act Pointer to an action
 * @return The type of action
 */
T_ACTION rule_action_get_type(Action *act);

/**
 * @brief It gets the argsId of condition of a rule
 * @author Diego Rodríguez Ortiz
 * @param cond Pointer to an condtition
 * @return An array of Ids with the arguments
 */
Id *rule_condition_get_argsId(Condition *cond);

/**
 * @brief It gets the number of argsId of condition of a rule
 * @author Diego Rodríguez Ortiz
 * @param cond Pointer to an condition
 * @return A number of arguments in Ids
 */
int rule_condition_get_numId(Condition *cond);
/**
 * @brief It gets the type of the condition of a rule
 * @author Diego Rodríguez Ortiz
 * @param cond Pointer to an condition
 * @return The type of action
 */
T_CONDITION rule_condition_get_type(Condition *cond);

/**
 * @brief It gets the argint of condition of a rule
 * @author Diego Rodríguez Ortiz
 * @param condi Pointer to an condition
 * @return The integer argument
 */
int rule_condition_get_argint(Condition *condi);

/**
 * @brief It gets the char argument of action of a rule
 * @author Diego Rodríguez Ortiz
 * @param cond Pointer to an condition
 * @return The char argument
 */
char *rule_condition_get_argname(Condition *cond);

/**
 * @brief It adds an action to a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to an rule
 * @param act Type of action
 * @param ids Pointer to an array of Ids
 * @param n_ids number of ids
 * @param argint integer argument of the action
 * @param name char argument of the action
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS rule_add_action(Rule *rule, T_ACTION act, Id *ids, int n_ids, int argint, char *name);

/**
 * @brief It adds a condition to a rule
 * @author Diego Rodríguez Ortiz
 * @param rule Pointer to an rule
 * @param cond Type of condition
 * @param ids Pointer to an array of Ids
 * @param n_ids number of ids
 * @param argint integer argument of the condition
 * @param name char argument of the condition
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS rule_add_condition(Rule *rule, T_CONDITION cond, Id *ids, int n_ids, int argint, char *name);

/**
 * @brief It given a string it translates it to an action
 * @author Diego Rodríguez Ortiz
 * @param action a string with the action
 * @return A Type of action if ok and NO_ACTION if error
 */
T_ACTION rule_translate_action(char *action);

/**
 * @brief It given a string it translates it to an action
 * @author Diego Rodríguez Ortiz
 * @param condition a string with the condition
 * @return A type of condition if ok and NO_CONDITION if error
 */
T_CONDITION rule_translate_condition(char *condition);


/**
 * @brief It given a T actions it translates it to an string
 * @author Diego Rodríguez Ortiz
 * @param action a T action
 * @return a string with the condition or NULL
 */
char * rule_translate_Taction(T_ACTION action);

/**
 * @brief It given a T condition it translates it to an string
 * @author Diego Rodríguez Ortiz
 * @param condition a T condition
 * @return a string with the condition or NULL
 */
char* rule_translate_Tcondition(T_CONDITION condition);
#endif
