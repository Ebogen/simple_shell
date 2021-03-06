#include "main.h"

/**
 * get_built - a function that checks if input is a built-in command
 *             and if so, executes its associated function
 * @input_list: represents the list of input command
 * @shell_name: represents the name of shell program
 * @envir_list: represents the list of environment variables
 *
 * Return: integer, the value of -1 if built-in does not exist
 */
int get_built(list_t *input_list, char *shell_name, list_t *envir_list)
{
	char *name;
	int i;

	built_s built_ins[] = {
		{"exit", exit_shell},
		{"envir", envir_fun},
		{"setenv", setenv_fun},
		{"unsetenv", unsetenv_fun},
		{NULL, NULL}
	};

	name = input_list->name;

	for (i = 0; built_ins[i].name; i++)
	{
		if (_strcmp(name, built_ins[i].name) == 0)
			return (built_ins[i].fun(input_list, shell_name, &envir_list));
	}

	return (-1);
}

/**
 * exit_shell - a function that implements the exit built-in
 *                functionality
 * @input_list: represents the list of command and arguments
 * @shell_name: represents the name of shell program
 * @envir_list_p:represents pointer to list of environment variables
 *
 * Return: exit or return the value of -2
 */
int exit_shell(list_t *input_list, char *shell_name, list_t **envir_list_p)
{
	int number;
	char *error_message[4];

	error_message_init(error_message, shell_name, input_list->name);

	if (input_list->next == NULL)
		return (0);

	number = _atoi(input_list->next->name);

	if (number == -1)
	{
		error_message[2] = "Illegal number";
		error_message[3] = input_list->next->name;
		print_error(error_message);
		return (-2);
	}

	(void)envir_list_p;
	return (number);
}

/**
 * envir_fun - a function that implements the environment built-
 *                in functionality
 * @input_list: represents a list of command and arguments
 * @shell_name: represents the name of shell program
 * @envir_list_p: represents a pointer list of environment variables
 *
 * Return: the value of -2
 */

int envir_fun(list_t *input_list, char *shell_name, list_t **envir_list_p)
{
	print_environ(*envir_list_p);
	(void)input_list;
	(void)shell_name;
	return (-2);
}

/**
 * setenv_fun - a function that implements the setenv built-in
 *               functionality
 * @input_list: represents the list of command and arguments
 * @shell_name: represents the name of shell program
 * @envir_list_p: represents pointer list of environment variables
 *
 * Return: the value of -2
 */

int setenv_fun(list_t *input_list, char *shell_name, list_t **envir_list_p)
{
	char *name, *value;
	char *error_message[4];

	error_message_init(error_message, shell_name, input_list->name);

	if (input_list->next == NULL || input_list->next->next == NULL)
	{
		error_message[2] = "invalid number of arguments";
		print_error(error_message);
		return (-2);
	}

	name = input_list->next->name;
	value = input_list->next->next->name;

	if (_setenv(*envir_list_p, name, value, 1) == -1)
	{
		error_message[2] = "error";
		print_error(error_message);
	}

	return (-2);
}

/**
 * unsetenv_fun - a function that implements the unsetenv built-in
 *                 functionality
 * @input_list: represents the list of command and arguments
 * @shell_name: represents the name of shell program
 * @envir_list_p: represents a pointer list of environment
 *                variables
 *
 * Return: the value of -2
 */
int unsetenv_fun(list_t *input_list, char *shell_name, list_t **envir_list_p)
{
	char *name;
	char *error_message[4];

	error_message_init(error_message, shell_name, input_list->name);

	if (input_list->next == NULL)
	{
		error_message[2] = "invalid number of arguments";
		print_error(error_message);
		return (-2);
	}

	name = input_list->next->name;

	if (_unsetenv(*envir_list_p, name) == -1)
	{
		error_message[2] = "error";
		print_error(error_message);
	}

	return (-2);
}
