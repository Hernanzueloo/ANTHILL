/**
 * @brief It implements the dialogue module
 *
 * @file dialogue.c
 * @author Javier San Andrés
 * @version 3.0
 * @date 10/03/2023
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dialogue.h"


/**
 * @brief Dialogue
 *
 * This struct stores all the information of a Dialogue.
 */
struct _Dialogue
{
    Id id;                                              /*!< Id of the dialogue*/
    char rules[MAX_DIALOGUE_RULES][WORD_SIZE];          /*!< An array of stings with the diferent no errro messages*/
    char error_rules[MAX_DIALOGUE_RULES][WORD_SIZE];     /*!< An array of stings with the diferent error messages*/
    int last_rule;                                        /*!< An index of the last rule added*/
    int last_error_rule;                                  /*!< An index of the last error rule added*/
    int executed;                                            /*!< An int that refers to the number of executions of a rule*/
};


Dialogue *dialogue_create(Id id)
{
    Dialogue *dialogue;

    if (id == NO_ID)
        return NULL;

    if ((dialogue = (Dialogue *)calloc(1, sizeof(Dialogue))) == NULL)
        return NULL;

    dialogue->id = id;
    dialogue->last_rule = -1;
    dialogue->last_error_rule = -1;
    dialogue->executed = 0;

    return dialogue;
}

void dialogue_destroy(Dialogue *dialogue)
{
    free(dialogue);
}

Id dialogue_get_id(Dialogue *dialogue)
{
    if (dialogue == NULL)
        return NO_ID;

    return dialogue->id;
}

STATUS dialogue_set_rule(Dialogue *dialogue, char *rule, DTYPE rule_type)
{
    if (dialogue == NULL || rule == NULL)
        return ERROR;

    if (rule_type == SUCCESS && dialogue->last_rule != MAX_DIALOGUE_RULES-1)
    {
        dialogue->last_rule++;

        if (strcpy(dialogue->rules[dialogue->last_rule], rule) != dialogue->rules[dialogue->last_rule])
            return ERROR;
        else
            return OK;
    }
    else if (rule_type == FAILURE && dialogue->last_error_rule != MAX_DIALOGUE_RULES-1)
    {
        dialogue->last_error_rule++;

        if (strcpy(dialogue->error_rules[dialogue->last_error_rule], rule) != dialogue->error_rules[dialogue->last_error_rule])
            return ERROR;
        else
            return OK;
    }
    
    return ERROR;
}

int dialogue_get_last_rule_position(Dialogue *dialogue)
{
    if (dialogue == NULL)
        return -2;

    return dialogue->last_rule;
}

int dialogue_get_last_error_rule_position(Dialogue *dialogue)
{
    if (dialogue == NULL)
        return -2;

    return dialogue->last_error_rule;
}

char *dialogue_get_rule(Dialogue *dialogue, int position)
{
    if (dialogue == NULL || position < 0 || position > dialogue->last_rule)
        return NULL;

    return dialogue->rules[position];
}

char *dialogue_get_error_rule(Dialogue *dialogue, int position)
{
    if (dialogue == NULL || position < 0 || position > dialogue->last_error_rule)
        return NULL;

    return dialogue->error_rules[position];
}


STATUS dialogue_increase_executed(Dialogue *dialogue)
{
    if (dialogue == NULL)
        return ERROR;
    
    dialogue->executed++;
    return OK;
}

STATUS dialogue_decrease_executed(Dialogue *dialogue)
{
    if (dialogue == NULL || dialogue->executed == 0)
        return ERROR;
    
    dialogue->executed--;
    return OK;
}


int dialogue_get_executed(Dialogue *dialogue)
{
    if (dialogue == NULL)
        return 0;
    
    return dialogue->executed;
}

STATUS dialogue_print_rule(Dialogue *dialogue, FILE *file, int position, char *args, STATUS command_status)
{
    int prev1 = 0, prev2 = 0;
    char instruction[WORD_SIZE] = "", rule[WORD_SIZE] = "";
    char *arguments;
    char *instruct;


    if (dialogue == NULL || position < 0 || file == NULL)
        return ERROR;

    if (command_status == OK)
    {
        if (position > dialogue->last_rule)
            return ERROR;

        if (args != NULL)
        {
            strcpy(rule, dialogue->rules[position]);

            while (TRUE)
            {
                instruct = strtok(rule + prev1, "<");

                if (instruct != NULL)
                {
                    strcat(instruction, instruct);
                    prev1+= strlen(instruct) + 1;

                    if ((instruct = strtok(NULL, ">")) != NULL)
                    {
                        prev1+= strlen(instruct) + 1;
                    }
                }
                else
                {
                    break;
                }

                if (instruct != NULL)
                {
                    arguments = strtok(args + prev2, "|");
                
                    if (arguments != NULL)
                    {
                        prev2+= strlen(arguments) + 1;
                        strcat(instruction, arguments);
                    }
                    else
                    {
                        break;    
                    }
                }
        
            }
        }
        else
        {
            strcpy(instruction, dialogue->rules[position]);
        }
    }
    else if (command_status == ERROR)
    {
        if (position > dialogue->last_error_rule)
            return ERROR;

        if (args != NULL)
        {
            strcpy(rule, dialogue->error_rules[position]);
        
            while (TRUE)
            {
                instruct = strtok(rule + prev1, "<");

                if (instruct != NULL)
                {
                    strcat(instruction, instruct);
                    prev1+= strlen(instruct) + 1;

                    if ((instruct = strtok(NULL, ">")) != NULL)
                    {
                        prev1+= strlen(instruct) + 1;
                    }
                }
                else
                {
                    break;
                }

                if (instruct != NULL)
                {
                    arguments = strtok(args + prev2, "|");
                
                    if (arguments != NULL)
                    {
                        prev2+= strlen(arguments) + 1;
                        strcat(instruction, arguments);
                    }
                    else
                    {
                        break;    
                    }
                }
            }
        }
        else
        {
            strcpy(instruction, dialogue->error_rules[position]);
        }
    }

    fprintf(file, "%s\n", instruction);
           
    return OK;

}


char *dialogue_get_printed_rule(Dialogue *dialogue, int position, char *args, STATUS command_status)
{
    int prev1 = 0, prev2 = 0;
    char instruction[WORD_SIZE] = "", rule[WORD_SIZE] = "";
    char *arguments, *instruct, *retorno;


    if (dialogue == NULL || position < 0)
        return NULL;

    if (command_status == OK)
    {
        if (position > dialogue->last_rule)
            return NULL;

        if (args != NULL)
        {
            strcpy(rule, dialogue->rules[position]);

            while (TRUE)
            {
                instruct = strtok(rule + prev1, "<");

                if (instruct != NULL)
                {
                    strcat(instruction, instruct);
                    prev1+= strlen(instruct) + 1;

                    if ((instruct = strtok(NULL, ">")) != NULL)
                    {
                        prev1+= strlen(instruct) + 1;
                    }
                }
                else
                {
                    break;
                }

                if (instruct != NULL)
                {
                    arguments = strtok(args + prev2, "|");
                
                    if (arguments != NULL)
                    {
                        prev2+= strlen(arguments) + 1;
                        strcat(instruction, arguments);
                    }
                    else
                    {
                        break;    
                    }
                }
        
            }
        }
        else
        {
            strcpy(instruction, dialogue->rules[position]);
        }
        
    }
    else if (command_status == ERROR)
    {
        if (position > dialogue->last_error_rule)
            return NULL;

        if (args != NULL)
        {
            strcpy(rule, dialogue->error_rules[position]);
        
            while (TRUE)
            {
                instruct = strtok(rule + prev1, "<");

                if (instruct != NULL)
                {
                    strcat(instruction, instruct);
                    prev1+= strlen(instruct) + 1;

                    if ((instruct = strtok(NULL, ">")) != NULL)
                    {
                        prev1+= strlen(instruct) + 1;
                    }
                }
                else
                {
                    break;
                }

                if (instruct != NULL)
                {
                    arguments = strtok(args + prev2, "|");
                
                    if (arguments != NULL)
                    {
                        prev2+= strlen(arguments) + 1;
                        strcat(instruction, arguments);
                    }
                    else
                    {
                        break;    
                    }
                }
            }
        }
        else
        {
            strcpy(instruction, dialogue->error_rules[position]);
        }

        
    }

    if ((retorno = (char *)calloc(strlen(instruction)+1, sizeof(char))) == NULL)
        return NULL;

    strcpy(retorno, instruction);

    return retorno;    
}


STATUS dialogue_print(Dialogue *dialogue, FILE *file)
{  
    int i = 0;

    if (dialogue == NULL || file == NULL)
        return ERROR;

    fprintf(file, "\n--> Dialogue %ld: \n", dialogue->id);
    
    if (dialogue->last_rule >= 0)
    {
        fprintf(file, "Success dialogue rules: \n");

        for (i = 0; i <= dialogue->last_rule; i++)
            fprintf(file, "%s\n", dialogue->rules[i]);
        fprintf(file, "\n");
    }

    if (dialogue->last_error_rule >= 0)
    {
        fprintf(file, "Error dialogue rules: \n");

        for (i = 0; i <= dialogue->last_error_rule; i++)
            fprintf(file, "%s\n", dialogue->error_rules[i]);
        fprintf(file, "\n");
    }

    fprintf(file, "Número de veces seguidas ejecutado sin éxito: %d\n", dialogue->executed);

    return OK;
}
