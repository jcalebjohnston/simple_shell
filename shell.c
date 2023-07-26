#include "shell.h"
/**
 * main - The beginning of the shell program.
 *
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success.
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	int status = 0;
	char **commands = NULL;
	char *my_shell = NULL;
	size_t buff_size = 0;
	char **cmd_tokens = NULL;
	int index;
	int entered_cmd = 0;

	signal(SIGINT, handle_ctrl_c);
	my_shell = argv[0];
	while (1)
	{
		non_interactive_mode();
		print_to_stdout(" :) ");
		if (getline(&line, &buff_size, stdin) == -1)
		{
			free(line);
			exit(status);
		}
		remove_newline(line);
		remove_comments(line);
		commands = tokenize_string(line, ";");

		for (index = 0; commands[index] != NULL; index++)
		{
			cmd_tokens = tokenize_string(commands[index], " ");
			if (cmd_tokens[0] == NULL)
			{
				free(cmd_tokens);
				break;
			}
			entered_cmd = parse_command(cmd_tokens[0]);
			initialize_shell(cmd_tokens, entered_cmd);
			free(cmd_tokens);
		}
		free(commands);
	}
	free(line);
	return (status);
}
