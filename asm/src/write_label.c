/*
** EPITECH PROJECT, 2021
** asm
** File description:
** main
*/

#include "asm.h"

int get_com_pos(command_t *com, size_t id, list_t *list)
{
    list_node_t *temp = NULL;
    command_t *temp_com = NULL;
    int res = 0;

    foreach(list->head, temp) {
        temp_com = temp->data;
        res++;
        if (barray_len(temp_com->params) != 1)
            res++;
        for (size_t i = 0; i < barray_len(temp_com->params); i++) {
            if (temp_com == com && i == id)
                return res;
            res += get_size(temp_com->params[i], list, get_id(temp_com->name));
        }
    }
    return res;
}

int get_label_pos(char *label, list_t *list)
{
    list_node_t *temp = NULL;
    command_t *temp_com = NULL;
    int res = 0;

    foreach(list->head, temp) {
        temp_com = temp->data;
        res++;
        if (barray_len(temp_com->params) != 1)
            res++;
        for (size_t i = 0; i < barray_len(temp_com->params); i++) {
            if (temp_com->label && !bstrcmp(temp_com->label, label))
                return res;
            res += get_size(temp_com->params[i], list, get_id(temp_com->name));
        }
    }
    return res;
}

void write_label(int fd, command_t *com, size_t i, list_t *list)
{
    int label_pos = get_label_pos(com->params[i] + 2, list);
    int com_pos = get_com_pos(com, i, list);
    int res = label_pos - com_pos;

    if (res > 0)
        res += 2;
    res = swap_endian_2(res);
    write(fd, &res, 2);
}