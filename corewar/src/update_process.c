/*
** EPITECH PROJECT, 2021
** utils for args parsing
** File description:
** parsing_utils
*/

#include "corewar.h"

void update_process(process_t *process)
{
    if (process->goal_it != 0)
        process->current_it++;
}