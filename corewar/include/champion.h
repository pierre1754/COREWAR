/*
** EPITECH PROJECT, 2020
** blib.c
** File description:
** 24/03/2021
*/

#ifndef CHAMPION_H
#define CHAMPION_H

#include <stdio.h>

#include "op.h"

#include "linked_list.h"
#include "process.h"

// CHAMPION LIST
typedef struct {
    size_t id;
    char *name;
    bool is_alive;
    list_t *process_list;
} champion_t;

#endif // CHAMPION_H