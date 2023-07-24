#include "shell.h"

/**
 * non_interactive_mode - A funct that executes the shell in non-interac mode
 *
 */
void non_interactive_mode(void)
{
	int index;
	int entered_cmd = 0;
	size_t line_len = 0;
	char **present_cmd_tokens = NULL;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &line_len, stdin) != -1)
		{
			remove_newline(line);
			remove_comments(line);
			commands = tokenize_string(line, ";");
			for (index = 0; commands[index] != NULL; index++)
			{
				present_cmd_tokens = tokenize_string
					(commands[index], " ");
				if (present_cmd_tokens[0] == NULL)
				{
					free(present_cmd_tokens);
					break;
				}
				entered_cmd = parse_command
					(present_cmd_tokens[0]);
				initialize_shell
					(present_cmd_tokens, entered_cmd);
				free(present_cmd_tokens);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}

