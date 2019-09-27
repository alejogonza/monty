#include "monty.h"

/**
 * validate_and_open - validates input
 * @argc: argument count
 * @filename: file to opened
 */
void validate_and_open(int argc, char *filename)
{
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	info.monty_file = fopen(filename, "r");
	if (!info.monty_file)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
}

/**
 * read_lines - reads instructions
 */
void read_lines(void)
{
	size_t len = 0;
	ssize_t read;
	char *opcode, *value;

	while ((read = getline(&info.line, &len, info.monty_file)) != -1)
	{
		opcode = strtok(info.line, " ");
		if (*opcode == '#' || *opcode == '\n')
		{
			info.line_number++;
			continue;
		}
		if (strcmp(opcode, "push") == 0)
		{
			value = strtok(NULL, " ");
			info.queue_status
				? push_add_node_end(value)
				: push_add_node(value);
			info.line_number++;
			continue;
		}
		op_helper(&info.stack, opcode);
		info.line_number++;
	}
}

/**
 * op_helper - finds and executes function
 * ptbl: functions
 * @stack: head of stack
 * @opcode: command to executed
 */
void op_helper(stack_t **stack, char *opcode)
{
	register int i;
	char *command;
	instruction_t itbl[] = {
		{"pall", pall_list},
		{"pint", pint_list},
		{"pop", pop_list},
		{"swap", swap_list},
		{"add", add_list},
		{"nop", nop_list},
		{NULL, NULL}
	};

	command = strtok(opcode, "\n");
	for (i = 0; itbl[i].opcode; i++)
		if (strcmp(command, itbl[i].opcode) == 0)
		{
			itbl[i].f(stack, info.line_number);
			return;
		}
	dprintf(STDERR_FILENO, "L%d: ", info.line_number);
	dprintf(STDERR_FILENO, "unknown instruction %s\n", opcode);
	garbage_collection();
	exit(EXIT_FAILURE);
}

/**
 * free_stack - frees a list
 * @head: head of list
 */
void free_stack(stack_t *head)
{
	stack_t *tmp, *current = head;

	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
}

/**
 * garbage_collection - frees all
 */
void garbage_collection(void)
{
	fclose(info.monty_file);
	free(info.line);
	free_stack(info.stack);
}
