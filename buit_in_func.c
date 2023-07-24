#include "shell.h"

/**
 * print_env - A program that Prints out the current environment variables.
 * @cmd_tokens: Command passed.
 */
void print_env(char **cmd_tokens)
{

	int ind;

	for (ind = 0; environ[ind] != NULL; ind++)
	{
		print_to_stdout(environ[ind]);
		print_to_stdout("\n");
	}
	(void)cmd_tokens;
}

/**
 * quit_shell - A built-in function to exit the shell.
 * @cmd_tokens: Command passed.
 */
void quit_shell(char **cmd_tokens)
{
	int num_tokens = 0, exit_status;

	for (; cmd_tokens[num_tokens] != NULL; num_tokens++)
	{
		;
	}
	if (num_tokens == 1)
	{
		free(cmd_tokens), free(line), free(commands);
		exit(status);
	}
	else if (num_tokens == 2)
	{
		exit_status = _atoi(cmd_tokens[1]);
		if (exit_status == -1)
		{
			print_to_stdout(my_shell);
			print_to_stdout(": 1: exit: Illegal number: ");
			print_to_stdout(cmd_tokens[1]);
			print_to_stdout("\n");
			status = 2;
		}
		else
		{
			free(line), free(cmd_tokens), free(commands);
			exit(exit_status);
		}
	}
	else
	{
		print_to_stdout("$: exit doesn't take more than one argument\n");
	}
}
/**
 * initialize_shell - This function starts executing our code.
 * @current_command: The recent token used.
 * @type_command: Represents the parsed token.
 *
 * Return: void.
 */
void initialize_shell(char **current_command, int type_command)
{
	pid_t PID;

	if (type_command == EXTERNAL_COMMAND || type_command == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
		{
			execute_command(current_command, type_command);
		}
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(current_command, type_command);
}

