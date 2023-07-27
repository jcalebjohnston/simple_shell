#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>

#define READ_SIZE 1024
#define PATH_COMMAND 3

#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 * struct builtin_cmd - Represents a built-in command name and its function.
 *
 * @cmd: The name of the command.
 * @func: The function that executes the command.
 */
typedef struct builtin_cmd
{
        char *cmd;
        void (*func)(char **command);
} builtin_cmd;

extern char **environ;
extern char *line;
extern char **commands;
extern char *my_shell;
extern int status;

void handle_ctrl_c(int signum);
void remove_comments(char *input);
int custom_strspn(char *s1, char *s2);
int custom_strcmp(char *s1, char *s2);
int custom_strcspn(char *s1, char *s2);

char *custom_strchr(char *s1, char s2);
char *custom_strcat(char *str1, char *str2);
int str_length(char *str);

extern void non_interactive_mode(void);
extern void initialize_shell(char **current_command, int type_command);
int _atoi(char *s);

void remove_newline(char *str);
char **tokenize_string(char *cmd, char *delim);
void string_copy(char *src, char *dest);
void print_to_stdout(char *str);
int parse_command(char *cmd);

void execute_command(char **current_command, int type_command);
char *my_strtok(char *string, char *delim, char **save_ptr);
char *path_inspect(char *cmd);
void (*get_builtin_function(char *cmd))(char **);
char *get_environ_var(char *var);
void print_env(char **cmd_tokens);
void quit_shell(char **cmd_tokens);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);

ssize_t fill_buffer(void);
ssize_t read_data_from_buffer(char *line, ssize_t *bytes_read, size_t *n);
ssize_t _getline(char **lineptr, size_t *n);
#endif
