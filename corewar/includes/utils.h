/*
** EPITECH PROJECT, 2018
** utils.h
** File description:
** utils
*/

#ifndef UTILS_H_
#define UTILS_H_

#include "corewar.h"

void my_putchar(char c);
int my_getnbr(char *str);
void *my_calloc(int size);
int my_strcmp(const char *test, const char *res);
int my_strlen(char *str);
char *my_strcpy(char *to, char *from);
void my_memcpy(void *mem_set, const void *mem_src, int len);
void dump_virtual_mem(byte_t memory[]);
void dump_virtual_mem_color(byte_t memory[], byte_t own_tab[], core_t *core);
void my_putnbr_hexa(long long nbr);


#endif /* UTILS_H_ */
