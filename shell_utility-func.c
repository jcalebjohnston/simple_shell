#include "shell.h"

/**
 * parse_command - This function decides the kind of the command.
 * @cmd: Command to be parsed.
 *
 * Return: The constant representing the kind of the command
 * Description - EXTERNAL_COMMAND (1) represents commands such as /bin/ls.
 *		 INTERNAL_COMMAND (2) represents commands such as env, exit, et
 *		 PATH_COMMAND (3) represents commands tha
 *		 t are found in the PATH e.g ls.
 *		 INVALID_COMMAND (-1) represents all invali
 *		 d commands in this code.
 */
int parse_command(char *cmd)
{
	char *internal_cmds[] = {"env", "exit", NULL};
	char *path = NULL;
	int index;

	for (index = 0; cmd[index] != '\0'; index++)
	{
		if (cmd[index] == '/')
			return (EXTERNAL_COMMAND);
	}

	for (index = 0; internal_cmds[index] != NULL; index++)
	{
		if (custom_strcmp(cmd, internal_cmds[index]) == 0)
			return (INTERNAL_COMMAND);
	}

	path = path_inspect(cmd);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_command - This executes a command based on its kind.
 * @cmd_tokens: Form of the command that has been tokenized.
 * @cmd_type: Type of the command.
 *
 * Return: void.
 */
void execute_command(char **cmd_tokens, int cmd_type)
{
	void (*func)(char **command);

	if (cmd_type == EXTERNAL_COMMAND)
	{
		if (execve(cmd_tokens[0], cmd_tokens, NULL) == -1)
		{
			perror(get_environ_var("PWD"));
			exit(2);
		}
	}

	if (cmd_type == PATH_COMMAND)
	{
		if (execve(path_inspect(cmd_tokens[0]), cmd_tokens, NULL) == -1)
		{
			perror(get_environ_var("PWD"));
			exit(2);
		}
	}

	if (cmd_type == INTERNAL_COMMAND)
	{
		func = get_builtin_function(cmd_tokens[0]);
		func(cmd_tokens);
	}

	if (cmd_type == INVALID_COMMAND)
	{
		print_to_stdout(my_shell);
		print_to_stdout(": 1: ");
		print_to_stdout(cmd_tokens[0]);
		print_to_stdout(": not found\n");
		status = 127;
	}
}

/**
 * path_inspect - This confirms if a command is found in the PATH.
 * @cmd: Command to be implemented.
 *
 * Return: Path where the command is found, else, NULL if not found.
 */
char *path_inspect(char *cmd)
{
	char *temp, *temp2, *path_cpy;
	char **path_array = NULL;
	char *path = get_environ_var("PATH");
	int index;

	if (path == NULL || str_length(path) == 0)
		return (NULL);

	path_cpy = malloc(sizeof(*path_cpy) * (str_length(path) + 1));
	string_copy(path, path_cpy);
	path_array = tokenize_string(path_cpy, ":");

	for (index = 0; path_array[index] != NULL; index++)
	{
		temp2 = custom_strcat(path_array[index], "/");
		temp = custom_strcat(temp2, cmd);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}

	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_builtin_function - Gets a function based on the command given.
 * @cmd: The string to check against the mapping.
 *
 * Return: Pointer to the proper function, or NULL on failure.
 */
void (*get_builtin_function(char *cmd))(char **)
{
	int index;
	builtin_cmd tracking[] = {
		{"env", print_env}, {"exit", quit_shell}
	};

	for (index = 0; index < 2; index++)
	{
		if (custom_strcmp(cmd, tracking[index].cmd) == 0)
			return (tracking[index].func);
	}

	return (NULL);
}

/**
 * get_environ_var - Tracks the value of an environment variable.
 * @var: The name of the environment variable.
 *
 * Return: The value of the variable as a string.
 */
char *get_environ_var(char *var)
{
	char *pair_ptr;
	char **our_environ_var;
	char *nameCopy;

	for (our_environ_var = environ; *our_environ_var != NULL
			; our_environ_var++)
	{
		for (pair_ptr = *our_environ_var, nameCopy = var;
		     *pair_ptr == *nameCopy; pair_ptr++, nameCopy++)
		{
			if (*pair_ptr == '=')
				break;
		}

		if ((*pair_ptr == '=') && (*nameCopy == '\0'))
			return (pair_ptr + 1);
	}

	return (NULL);
}

