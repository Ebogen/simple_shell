#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * struct list_s - a function for singly linked list of values
 *                 for the node structure
 * @value: represents a string
 * @name: represents a string
 * @next: this represents the next node
 *
 */
typedef struct list_s
{
	char *name;
	char *value;
	struct list_s *next;
} list_t;

/**
 * struct built_s - this is a function that represent builtin
 *                  shell command
 * @name: represents our shell command
 * @fun: this represents the function of our shell
 *
 * Description: struct representing shell built-in command
 */
typedef struct built_s
{
	char *name;
	int (*fun)(list_t *input_list, char *shell_name, list_t **envir_list_p);
} built_s;

/* The function used for main.c */
void sig_handler(int sig);

/* environ_list.c represnts the environment list */
list_t *create_environ(char **environ, list_t *environ_list);
char *_getenv(list_t *environ_list, char *name);
void print_environ(list_t *environ_list);
int _setenv(list_t *environ_list, const char *name, const char *value, int ow);
int _unsetenv(list_t *environ_list, const char *name);

/* function lists.c */
list_t *add_node_end(list_t **head, const char *name, const char *value);
list_t *create_node(const char *name, const char *value);
list_t *split_string(char *str, char *delim);
void free_node(list_t *h);
void free_list(list_t *h);
size_t list_len(const list_t *h);
char **list_to_array(const list_t *h);
void free_array(char **arr);
int find_name(list_t *h, const char *name);
int update_value(list_t *h, int index, const char *value);
int delete_node_index(list_t **head, int index);

/* shell.c */
int shell(list_t *environ_list, char *shell_name);
char *get_input(void);
void print_error(char **error_message);
void prompt(void);
void free_input(char *input, list_t *input_list, char **input_array);
int execute(char **input_array, char *command, char *shell_name);
void error_message_init(char **error_message, char *shell_name, char *command);

/* built.c */
int get_built(list_t *input_list, char *shell_name, list_t *envir_list);
int exit_shell(list_t *input_list, char *shell_name, list_t **envir_list_p);
int environ_fun(list_t *input_list, char *shell_name, list_t **envir_list_p);
int setenv_fun(list_t *input_list, char *shell_name, list_t **envir_list_p);
int unsetenv_fun(list_t *input_list, char *shell_name, list_t **envir_list_p);

/* which.c */
char *get_full_name(char *name, list_t *environ_list);
char *get_full_path(char *filename, list_t *path_list);
char *create_path(char *dir, char *filename);
int valid_command(char *filename);

/* strings.c */
char *_strcpy(char *dest, const char *src);
unsigned int _strlen(const char *string);
int _strcmp(const char *string1, const char *string2);
char *_strdup(const char *string);
char *_strtok(char *string, const char *delimeter);
int is_in_str(const char *string, char c);
int _atoi(char *string);
void str_rep(char *string);

#endif
