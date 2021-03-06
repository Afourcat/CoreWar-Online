/*
** EPITECH PROJECT, 2018
** corewar.h
** File description:
** corewar header
*/

#ifndef COREWAR_H_
#define COREWAR_H_

#include "op.h"

typedef unsigned char byte_t;

#include "process.h"
#include "args.h"

#define ADRESS(x) ((x) % 6144)
static const int CHAMPIONS = 4;
#define UNUSED __attribute__((unused))

/*
** Core_t: Main corewar structure.
**
** Virtual cpu: with virtual register defined in op.h.
** Virtual memory: size defined in op.h.
*/
typedef struct core_s {
	byte_t memory[6144];
	byte_t owner_table[6144];
	program_t program_tab[4];
	int cycle_to_die;
	int nbr_cycle;
	int nb_live;
	int nb_progs;
	int nb_dump;
} core_t;

core_t *create_core(void);
int corewar_init(core_t *core);
int cycle(core_t *core);
int bitwise_value(int val);

#endif /* COREWAR_H_ */
