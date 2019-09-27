#include "monty.h"

info_t info;

/**
 * main - entry point
 * @argc: argument count
 * @argv: list of arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	init_info();
	validate_and_open(argc, argv[1]);
	read_lines();
	garbage_collection();
	return (EXIT_SUCCESS);
}

/**
 * init_info - initializes info struct
 */
void init_info(void)
{
	info.monty_file = NULL;
	info.line = NULL;
	info.stack = NULL;
	info.line_number = 1;
	info.queue_status = false;
}
