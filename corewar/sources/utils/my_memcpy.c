/*
** EPITECH PROJECT, 2017
** sources/utils/memory/my_memcpy.c
** File description:
** my_memcpy function's file
*/

#include "unistd.h"
#include "corewar.h"
#include "op.h"
#include "my_printf.h"
#include "utils.h"

void my_memcpy(void *mem_dest, const void *mem_src, int len)
{
	while (len) {
		*((unsigned char *)mem_dest) = *((unsigned char *)mem_src);
		(unsigned char *)mem_dest++;
		(unsigned char *)mem_src++;
		len--;
	}
}

int is_equal_id(process_t *process, int id)
{
	process_t *tmp = process;

	for (; tmp != NULL; tmp = tmp->next)
		if (tmp->id == id)
			return (tmp->parent->number);
	return (-1);
}

int get_number_from_id(core_t *core, int id)
{
	process_t *tmp;
	int val;

	for (int i = 0; i < core->nb_progs; i++) {
		tmp = core->program_tab[i].process_l;
		if ((val = is_equal_id(tmp, id)) != -1)
			return (val);
	}
	return (0);
}

void dump_virtual_mem_color(byte_t memory[], byte_t owner_table[], core_t *core)
{
	char color[5][10] = {
		"\e[0m",
		"\e[1;32m",
		"\e[1;33m",
		"\e[1;34m",
		"\e[1;35m"
	};

	write(1, "0x000000 : ", 11);
	for (int i = 1; i <= MEM_SIZE; ++i) {
		my_printf("%s%#04x \e[0m", color[get_number_from_id(core, \
		owner_table[i - 1])], memory[i - 1]);
		if ((i % (MEM_SIZE / 500)) == 0 && i < MEM_SIZE)
			my_printf("\n%#08x : ", i - 1);
	}
	write(1, "\n", 1);
}
