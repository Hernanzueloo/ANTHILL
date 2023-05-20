/**
 * @brief It implements the dialogue interface
 *
 * @file dialogue.h
 * @author Javier San Andrés
 * @version 3.0
 * @date 10/03/2023
 * @copyright GNU Public License
 */

#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "types.h"

#define MAX_DIALOGUE_RULES 10     /*!< Maximum number of dialogue rules for a single command*/

/**
 * @brief Dialogue struct 
 */
typedef struct _Dialogue Dialogue;


/**
 * @brief Initializes the dialog structure 
 * @author Javier San Andrés
 * @param id Id of the dialog to be created
 * @return Pointer to Dialog or NULL in case of error
 */
Dialogue *dialogue_create(Id id);


/**
 * @brief It destroys a dialogue structure 
 * @author Javier San Andrés
 * @param dialogue pointer to the dialog structure
 */
void dialogue_destroy(Dialogue *dialogue);

/**
 * @brief It gets the command type of a dialog
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @return Id of the dialog or NO_ID if it failes
 */
Id dialogue_get_id(Dialogue *dialogue);

/**
 * @brief It sets a new rule for a command
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @param rule string containing the new rule
 * @param rule_type type of rule to be implemented
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS dialogue_set_rule(Dialogue *dialogue, char *rule, DTYPE rule_type);

/**
 * @brief It gets the last position occupied in the array of success rules
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @return last occupied index or -2 in case of error
 */
int dialogue_get_last_rule_position(Dialogue *dialogue);

/**
 * @brief It gets the last position occupied in the array of error rules
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @return last occupied index or -2 in case of error
 */
int dialogue_get_last_error_rule_position(Dialogue *dialogue);

/**
 * @brief It gets the dialogue rule in that position in the success array
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @param position index of the rule to be got
 * @return String wiht the dialogue rule or NULL if there was some mistake
 */
char *dialogue_get_rule(Dialogue *dialogue, int position);

/**
 * @brief It gets the dialogue rule in that position in the error array
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @param position index of the rule to be got
 * @return String wiht the dialogue rule or NULL if there was some mistake
 */
char *dialogue_get_error_rule(Dialogue *dialogue, int position);


/**
 * @brief It increases in one the number of error executions for an specific command
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS dialogue_increase_executed(Dialogue *dialogue);

/**
 * @brief It decreases in one the number of error executions for an specific dialogue
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS dialogue_decrease_executed(Dialogue *dialogue);

/**
 * @brief It gets the number of error executions for an specific dialogue
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @return the number of executions or 0 if there was some mistake
 */
int dialogue_get_executed(Dialogue *dialogue);

/**
 * @brief It prints the dialog rule whose index coincides with that position in the array
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @param file Pointer to file in which the message will be printed
 * @param position index in the array of the rule to be printed
 * @param args arguments of the command executed and for which the dialog response is
 * @param command_status Status of the command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS dialogue_print_rule(Dialogue *dialogue, FILE *file, int position, char *args, STATUS command_status);


/**
 * @brief It gives the dialog rule with the printed format
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @param position index in the array of the rule to be printed
 * @param args arguments of the command executed and for which the dialog response is
 * @param command_status Status of the command
 * @return pointer to the string or NULL in case of ERROR.
 */
char *dialogue_get_printed_rule(Dialogue *dialogue, int position, char *args, STATUS command_status);


/**
 * @brief It prints a dialogue information
 * @author Javier San Andrés
 * @param dialogue Pointer to dialogue
 * @param file Pointer to file in which the message will be printed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
STATUS dialogue_print(Dialogue *dialogue, FILE *file);

#endif