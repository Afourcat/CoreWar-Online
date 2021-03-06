/*
** EPITECH PROJECT, 2017
** cycle.c
** File description:
** cycle handling
*/

#include <stdlib.h>
#include "corewar.h"
#include "instructions.h"
#include "my_printf.h"
#include "mem_manage.h"
#include "utils.h"

void get_ins_args(byte_t byte, int *args)
{
	char val[8];
	int ret = 0;

	val[0] = (byte & 0x80) ? '1' : '0';
	val[1] = (byte & 0x40) ? '1' : '0';
	val[2] = (byte & 0x20) ? '1' : '0';
	val[3] = (byte & 0x10) ? '1' : '0';
	val[4] = (byte & 0x08) ? '1' : '0';
	val[5] = (byte & 0x04) ? '1' : '0';
	val[6] = (byte & 0x02) ? '1' : '0';
	val[7] = (byte & 0x01) ? '1' : '0';
	for (int i = 0; i < 6; i += 2, ret++) {
		if (val[i] == '0' && val[i + 1] == '1')
			args[ret] = T_REG;
		if (val[i] == '1' && val[i + 1] == '0')
			args[ret] = T_DIR;
		if (val[i] == '1' && val[i + 1] == '1')
			args[ret] = T_IND;
	}
}

int exec_process(process_t *pross, core_t *cor)
{
	int args[3] = {0, 0, 0};
	int inst = 0;

	if (pross->pc >= (unsigned int) MEM_SIZE + 1)
		pross->pc = ADRESS(pross->pc);
	if (--pross->turn_to_exec > 0)
		return (-1);
	get_ins_args(cor->memory[ADRESS(pross->pc + 1)], args);
	inst = cor->memory[ADRESS(pross->pc)];
	if (pross->was_waiting) {
#ifdef DEBUG_MODE
		my_printf("instruction = %d\nprocess id: %d\nprocess pc %d\n",
		inst, pross->id, pross->pc);
#endif
		pross->was_waiting = 0;
		INSTRUCTION_ARRAY[(inst <= 0x0f) ? inst : 0](cor, pross, args);
	} else if (!pross->was_waiting) {
		pross->turn_to_exec = cycle_x[(inst <= 0x0f) ? inst : 0];
		pross->was_waiting = 1;
	}
	return (0);
}

void exec_all_process(process_t *process, core_t *core)
{
	while (process != NULL) {
		exec_process(process, core);
		process = process->next;
	}
}

void set_dead(core_t *core)
{
	for (int i = 0; i < core->nb_progs; ++i) {
		if (core->program_tab[i].last_live_cycle == -1)
			core->program_tab[i].is_alive = 0;
		core->program_tab[i].last_live_cycle = -1;
	}
}

int cycle(core_t *core)
{
	for (int i = 0; i < core->nb_progs; ++i) {
		if (core->program_tab[i].is_alive)
			exec_all_process(core->program_tab[i].process_l, core);
	}
	if (core->nbr_cycle >= core->cycle_to_die) {
		if (core->nb_live >= NBR_LIVE)
			core->cycle_to_die -= CYCLE_DELTA;
		set_dead(core);
		core->nbr_cycle = 0;
		core->nb_live = 0;
	}
	core->nbr_cycle++;
	return (1);
}
