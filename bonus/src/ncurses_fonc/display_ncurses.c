/*
** EPITECH PROJECT, 2021
** utils for args parsing
** File description:
** parsing_utils
*/

#include "corewar.h"

static void count_proprio(mem_t mem, size_t *red, size_t *blue, size_t *green)
{
    if (mem.proprio == 1)
        (*red)++;
    if (mem.proprio == 2)
        (*blue)++;
    if (mem.proprio == 3)
        (*green)++;
}

void display_info(mem_t **mem, int nb_cycle, int y, int x)
{
    size_t i = 0;
    size_t red = 0;
    size_t blue = 0;
    size_t green = 0;
    size_t yellow = 0;

    mvprintw(y, x, "Nombre de cycle : ");
    x += 18;
    mvprintw(y, x, bitoa(nb_cycle));
    for (size_t compt = 0; compt < IDX_NBR; compt++) {
        for (i = 0; i < IDX_MOD; i++) {
            count_proprio(mem[compt][i], &red, &blue, &green);
            if (mem[compt][i].proprio == 4)
                yellow++;
        }
    }
    display_count_proprio(&x, red, blue, green);
    if (yellow != 0)
        mvprintw(y, x, "Le joueur 2 a %d cases.", yellow);
}

void print_color_ncurses(int x, int y, mem_t mem)
{
    char *ret = NULL;
    int hex = mem.cas;

    find_color(mem);
    ret = bitoa_base(hex, HEXA_BASE);
    if (bstrlen(ret) == 1)
        mvprintw(y, x, "0%s ", ret);
    else
        mvprintw(y, x, "%s ", ret);
    free(ret);
    del_color(mem);
}

static void print_mem_ncurse_spl(int *x, int *y, size_t *i, mem_t *mem)
{
    print_color_ncurses(*x, *y, mem[*i]);
    (*i)++;
    if (*i == 513) {
        mvprintw(*y, *x, "\n");
        *x = (COLS / 2) - (64 + 32);
    }
    else if (*i % 64 == 0) {
        mvprintw(*y, *x, "\n");
        *y += 1;
        *x = COLS / 2 - (64 + 32);
    }
    else
        *x += 3;
}

void print_mem_ncurse(vm_t *vm, int nb_cycle)
{
    size_t i = 0;
    int x = (COLS / 2) - (64 + 32);
    int y = 2;

    clear();
    display_info(vm->memory, nb_cycle, 0, x);
    for (size_t compt = 0; compt < IDX_NBR; compt++) {
        while (i != IDX_MOD)
            print_mem_ncurse_spl(&x, &y, &i, vm->memory[compt]);
        i = 0;
    }
    refresh();
    usleep(70000);
}