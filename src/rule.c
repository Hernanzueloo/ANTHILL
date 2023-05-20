/**
 * @brief It implements the rule module
 *
 * @file rule.c
 * @author Diego Rodríguez
 * @version 3.0
 * @date 14/04/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "rule.h"


/**
 * @brief Action
 *
 * This struct stores all the information of a Action.
 */
struct _Action
{
    T_ACTION Taction;        /*!<Type of action*/
    int num_id_args;         /*!<Number of id arguments*/
    Id ids[MAX_ARGS];        /*!<Array of Ids arguments for an action*/
    int argint;              /*!<Integer argument for an action*/
    char name[WORD_SIZE];    /*!<String argument for an action*/
};

/**
 * @brief Condition
 *
 * This struct stores all the information of a condition.
 */
struct _Condition
{
    T_CONDITION Tcond;               /*!<Type of condition*/
    int n_id_args;                    /*!<Number of id arguments*/
    Id ids[MAX_ARGS];           /*!<Array of Ids arguments for an condition*/
    int argint;                 /*!<Integer argument for an condition*/
    char name[WORD_SIZE];        /*!<String argument for an condition*/
};

/**
 * @brief Rule
 *
 * This struct stores all the information of a rule.
 */
struct _Rule
{
    Id id;                                    /*!< The id of the Rule*/
    BOOL executed;                             /*!< Just executed */
    int n_actions;                            /*!< The number of the actions in the rule*/
    int n_conditions;                         /*!<  The number of conditions in the rule*/
    Action act[MAX_ACTIONS];                  /*!< An array of actions of the rule*/
    Condition condi[MAX_CONDITIONS];          /*!< An array of conditions of the rule*/
};



/**
 * @brief Array of the posible actions that the rule have
 */
char *action_to_str[N_ACTIONS] = {"no action",
                                  "attack player",
                                  "heal player",
                                  "attack enemy",
                                  "heal enemy",
                                  "open link",
                                  "close link",
                                  "inundation",
                                  "save space",
                                  "spawn ground",
                                  "combine",
                                  "set movable",
                                  "victory act",
                                  "defeat act"};

/**
 * @brief Array of the posible codition that the rules have
 */
char *condition_to_str[N_CONDITIONS] = {"no condition",
                                        "in space",
                                        "has object",
                                        "heath player",
                                        "health enemy",
                                        "N comands",
                                        "drop object",
                                        "same object",
                                        "player type",
                                        "has sunk"};


/**
 * @brief It initializes an action
 * @author Diego Rodríguez Ortiz
 * @param act Pointer to the action
 * @return The name of the upgraded object
 */
STATUS action_init(Action *act);
/**
 * @brief It initializes a condition
 * @author Diego Rodríguez Ortiz
 * @param cond Pointer to the condition
 * @return The name of the upgraded object
 */
STATUS condition_init(Condition *cond);


STATUS action_init(Action *act)
{
    int i;

    if(act==NULL)
        return ERROR;
    
    act->argint=0;
    act->num_id_args=0;
    act->Taction=NO_ACTION;
    act->name[0]='\0';

    for(i=0; i<MAX_ARGS; i++)
    {
        act->ids[i]=NO_ID;
    }

    return OK;
}

STATUS condition_init(Condition *cond)
{
    int i;

    if(cond==NULL)
        return ERROR;
    
    cond->argint=0;
    cond->n_id_args=0;
    cond->Tcond=NO_CONDITION;
    cond->name[0]='\0';

    for(i=0; i<MAX_ARGS; i++)
    {
        cond->ids[i]=NO_ID;
    }

    return OK;
}

Rule *rule_create(Id id)
{
    Rule *rule;
    int i;
    if(id == NO_ID)
        return NULL;
    rule = (Rule *)malloc(sizeof(Rule));
    if (!rule)
        return NULL;

    rule->n_actions = 0;
    rule->n_conditions = 0;
    rule->id = id;
    rule->executed = FALSE;
    
    for(i=0; i<MAX_ACTIONS; i++)
        action_init(&(rule->act[i]));

    for(i=0; i<MAX_CONDITIONS; i++)
        condition_init(&(rule->condi[i]));

    return rule;
}

void rule_destroy(Rule *rule)
{
    if (rule)
        free(rule);
}

Id rule_get_id(Rule *rule)
{
    if (!rule)
        return NO_ID;

    return rule->id;
}


BOOL rule_get_executed(Rule *rule)
{
    if (!rule)
        return FALSE;

    return rule->executed;
}

STATUS rule_set_executed(Rule *rule, BOOL val)
{
    if (!rule)
        return ERROR;

     rule->executed = val;
    return OK;
}

int rule_get_num_actions(Rule* rule){
    if(!rule)
        return -1;
    return rule->n_actions;
}

int rule_get_num_conditions(Rule* rule){
    if(!rule)
        return -1;
    return rule->n_conditions;
}

Action *rule_get_action(Rule *rule, int index)
{
    if (!rule || index < 0 || index > MAX_ACTIONS)
        return NULL;

    if (rule->n_actions <= index)
        return NULL;
        
    return &rule->act[index];
}


Id *rule_action_get_argsId(Action *act)
{
    if (!act)
        return NULL;
        
    return act->ids;
}

int rule_action_get_numId(Action *act)
{
    if (!act)
        return -1;
    return act->num_id_args;
}

int rule_action_get_argint(Action *act){
    if(!act)
        return -1;

    return act->argint;
}

char * rule_action_get_argname(Action *act){
    if(!act)
        return NULL;

    return act->name;
}

T_ACTION rule_action_get_type(Action *act){
    if(!act)
        return NO_ACTION;
    
    return act->Taction;
}

Condition * rule_get_condition(Rule *rule, int index)
{
    if (!rule || index < 0)
        return NULL;
    if (rule->n_conditions <= index)
        return NULL;
    return &rule->condi[index];
}

Id *rule_condition_get_argsId(Condition *cond)
{
    if (!cond)
        return NULL;

    return cond->ids;
}

int rule_condition_get_numId(Condition *cond){
    if(!cond)
        return -1;
    
    return cond->n_id_args;
}

T_CONDITION rule_condition_get_type(Condition *cond){
    if(!cond)
        return NO_CONDITION;
    
    return cond->Tcond;
}

int rule_condition_get_argint(Condition *condi){
    if(!condi)
        return -1;

    return condi->argint;
}

char * rule_condition_get_argname(Condition *cond){
    if(!cond)
        return NULL;

    return cond->name;
}

STATUS rule_add_action(Rule* rule, T_ACTION act,Id *ids, int n_ids, int agrint, char * name){
    int i;
    if(!rule|| !ids || n_ids < 0|| !name || act == NO_ACTION){
        return ERROR;
    }
    for(i=0;i<n_ids;i++){
        rule->act[rule->n_actions].ids[i] = ids[i];
    }
    rule->act[rule->n_actions].num_id_args = n_ids;
    rule->act[rule->n_actions].Taction = act;
    rule->act[rule->n_actions].argint = agrint;
    strcpy(rule->act[rule->n_actions].name, name);
    rule->n_actions++;

    return OK;
}

STATUS rule_add_condition(Rule* rule, T_CONDITION cond,Id *ids, int n_ids, int agrint, char * name){
    int i;
    if(!rule|| !ids || n_ids < 0|| !name|| cond == NO_CONDITION){
        return ERROR;
    }
    for(i=0;i<n_ids;i++){
        rule->condi[rule->n_conditions].ids[i] = ids[i];
    }
    rule->condi[rule->n_conditions].n_id_args = n_ids;
    rule->condi[rule->n_conditions].Tcond = cond;
    rule->condi[rule->n_conditions].argint = agrint;
    strcpy(rule->condi[rule->n_conditions].name, name);
    rule->n_conditions++;

    return OK;
}


T_ACTION rule_translate_action(char *action)
{
    T_ACTION act = NO_ACTION;
    int i = 0;
    while (act == NO_ACTION && i < N_ACTIONS)
    {
        if (!strcasecmp(action, action_to_str[i]))
            act = i + NO_ACTION;
        i++;
    }
    return act;
}

T_CONDITION rule_translate_condition(char *condition)
{
    T_CONDITION cond = NO_CONDITION;
    int i = 0;
    if (!condition)
        return cond;

    while (cond == NO_CONDITION && i < N_CONDITIONS)
    {
        if (!strcasecmp(condition, condition_to_str[i]))
            cond = i + NO_CONDITION;
        i++;
    }
    return cond;
}

char * rule_translate_Taction(T_ACTION action){
    if(action==NO_ACTION)
     return NULL;
    return action_to_str[action-NO_ACTION];
}

char* rule_translate_Tcondition(T_CONDITION condition){
    if(condition==NO_CONDITION)
     return NULL;
    return condition_to_str[condition-NO_CONDITION];
}