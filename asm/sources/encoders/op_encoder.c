/*
** EPITECH PROJECT, 2017
** sources/encoders/op_encoder.c
** File description:
** Op encoder
*/

#include <stdlib.h>
#include "asm.h"
#include "op.h"
#include "utils.h"

static const op_t op_tab[] = {
	{"live", 1, {2}, 1, 10, "alive"},
	{"ld", 2, {2 | 4, 1}, 2, 5, "load"},
	{"st", 2, {1, 4 | 1}, 3, 5, "store"},
	{"add", 3, {1, 1, 1}, 4, 10, "addition"},
	{"sub", 3, {1, 1, 1}, 5, 10, "soustraction"},
	{"and", 3, {1 | 2 | 4, 1 | 4 | 2, 1}, 6, 6,
	"et (and  r1, r2, r3   r1xorr2 -> r3"},
	{"or", 3, {1 | 4 | 2, 1 | 4 | 2, 1}, 7, 6,
	"ou  (or   r1, r2, r3   r1 | r2 -> r3"},
	{"xor", 3, {1 | 4 | 2, 1 | 4 | 2, 1}, 8, 6,
	"ou (xor  r1, r2, r3   r1xorr2 -> r3"},
	{"zjmp", 1, {2}, 9, 20, "jump if zero"},
	{"ldi", 3, {1 | 2 | 4, 2 | 1, 1}, 10, 25,
	"load index"},
	{"sti", 3, {1, 1 | 2 | 4, 2 | 1}, 11, 25,
	"store index"},
	{"fork", 1, {2}, 12, 800, "fork"},
	{"lld", 2, {2 | 4, 1}, 13, 10, "long load"},
	{"lldi", 3, {1 | 2 | 4, 2 | 1, 1}, 14, 50,
	"long load index"},
	{"lfork", 1, {2}, 15, 1000, "long fork"},
	{"aff", 1, {1}, 16, 2, "aff"},
	{0x0, 0, {0}, 0, 0, 0x0}
};

int check_coding_byte(char **params)
{
	int params_n = 0;
	int control = 0;

	for (int i = 0; params[i] && params[i][0] != '#'; i++, params_n++) {
		control = control << 2;
		if (params[i][0] == 'r') {
			control += 1;
		} else if (params[i][0] == '%' && params[i][1] != ':') {
			control += 2;
		} else {
			control += params[i][1] != ':' ? 3 : 2;
		}
	}
	control = control << 2 * (4 - params_n);
	return (control);
}

int get_label(char *param, label_t **labels, ins_t *op)
{
	int temp = 0;

	for (int i = 0; labels[i]; i++) {
		if (my_memcmp(param + 2, labels[i]->name)) {
			temp = labels[i]->id - op->index;
			return (temp);
		}
	}
	return (0);
}

/*
** Check params here
*/
int parse(ins_t *op, int control, char *param, label_t **labels)
{
	if (param == 0x0 || control == 0)
		return (0);
	if (control & 0b10 && param[1] == LABEL_CHAR) {
		return (get_label(param, labels, op));
	} else {
		if (control == 0b11)
			return (my_atoi(param));
		else
			return (my_atoi(param + 1));
	}
}

void parse_param(ins_t *op, char **params, int n, label_t **labels)
{
	int local_control = (op->control_byte >> (8 - (2 * n))) & 3;
	int parsed_param = 0;
	char *param = local_control ? params[n - 1] : 0x0;

	parsed_param = parse(op, local_control, param, labels);
	if (n == 1)
		op->param1 = parsed_param;
	else if (n == 2)
		op->param2 = parsed_param;
	else
		op->param3 = parsed_param;
}

ins_t *line_encoding(char const *line, label_t **labels, int index)
{
	char **params = split_spaces(line);
	ins_t *op = my_calloc(sizeof(ins_t));

	for (int i = 0; params[i]; i++)
		params[i] = clean_separator(params[i]);
	op->code = 0;
	for (int i = 0; i < 16 && !op->code; i++) {
		if (my_memcmp(params[0], op_tab[i].mnemonique)) {
			op->code = op_tab[i].code;
		}
	}
	op->index = index;
	op->control_byte = check_coding_byte(params + 1) & 255;
	parse_param(op, params + 1, 1, labels);
	parse_param(op, params + 1, 2, labels);
	parse_param(op, params + 1, 3, labels);
	return (op);
}
