#include "main.h"
void error_message_init(char **error_message, char *shell_name, char *command);

/**
 * shell - a function that implement shell functionality
 * @environ_list: represents the list of environment variables
 * @shell_name: represents the name of shell program
 * Return: 0 success. Non-zero otherwise
 */
int shell(list_t *environ_list, char *shell_name)
{
	char *input, *full_name;
	list_t *input_list;
	char **input_array;
	int built_ret, exec_ret;
	char *error_message[4];

	error_message_init(error_message, shell_name, NULL);

	while (1)
	{
		input = get_input();
		if (input == NULL)
			return (0);
		input_list = split_string(input, " ");
		if (input_list == NULL)
		{
			free(input);
			continue;
		}
		built_ret = get_built(input_list, shell_name, environ_list);
		if (built_ret != -1)
		{
			free_input(input, input_list, NULL);
			if (built_ret < -1)
				continue;
			else
				return (built_ret);
		}
		error_message[1] = input_list->name;
		full_name = get_full_name(input_list->name, environ_list);
		if (full_name == NULL)
		{
			error_message[2] = "not found";
			print_error(error_message);
			free_input(input, input_list, NULL);
			continue;
		}
		input_array = list_to_array(input_list);
		if (input_array == NULL)
		{
			error_message[2] = "malloc failed";
			print_error(error_message);
			free(full_name);
			free_input(input, input_list, NULL);
			continue;
		}
		exec_ret = execute(input_array, full_name, shell_name);
		if (exec_ret < 0)
		{
			free_input(input, input_list, input_array);
			free(full_name);
			return (-exec_ret);
		}
		free(full_name);
		free_input(input, input_list, input_array);
	}
	return (0);
}
/**
 * get_input - function that gets the input from the terminal
 * Return: the value of string input, Otherwise NULL
 */
char *get_input(void)
{
	char *buffer = NULL;
	size_t bufferSize = 0;

	if (isatty(STDIN_FILENO))
		prompt();

	if (getline(&buffer, &bufferSize, stdin) == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 2);

		free(buffer);
		return (NULL);
	}
	str_rep(buffer);
	return (buffer);
}

/**
 * print_error - a function that prints given error message
 *               to stderr
 * @error_message: array of strings composing error message
 */
void print_error(char **error_message)
{
	int i;
	char *string;

	for (i = 0; i < 4; i++)
	{
		string = error_message[i];

		if (string)
		{
			if (i > 0)
				write(STDERR_FILENO, ": ", 3);
			write(STDERR_FILENO, string, _strlen(string) + 1);
			if (i == 0)
				write(STDERR_FILENO, ": 1", 4);
		}
	}
	write(STDERR_FILENO, "\n", 2);
}

/**
 * prompt - a function that displays the shell prompt
 */
void prompt(void)
{
	char *prompt = "$ ";

	write(STDOUT_FILENO, prompt, _strlen(prompt) + 1);
}
/**
 * free_input - function that frees a given memory buffers
 * @input: represents string input
 * @input_list: represents list input
 * @input_array: represents array of strings input
 */
void free_input(char *input, list_t *input_list, char **input_array)
{
	if (input)
		free(input);

	if (input_list)
		free_list(input_list);

	if (input_array)
		free_array(input_array);
}

/**
 * execute - function that executes a given input command
 * @input_array: represnts array of strings containing input
 *               command
 * @command: represents the name of command to execute
 * @shell_name: represents the name of shell program
 *
 * Return: the value of 0 for success. Otherwise negative integer
 */
int execute(char **input_array, char *command, char *shell_name)
{
	pid_t child_pid;
	int status;
	char *error_message[4];

	error_message_init(error_message, shell_name, command);

	child_pid = fork();
	if (child_pid == -1)
	{
		error_message[2] = "fork error";
		print_error(error_message);
		return (-1);
	}
	else if (child_pid == 0) /* we execute the command */
	{
		if (execve(command, input_array, NULL) == -1)
		{
			error_message[2] = "execve error";
			print_error(error_message);
			return (-2);
		}
	}
	else
	{
		wait(&status);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

/**
 * error_message_init - a  array with given values
 * @error_message: represents an error message array
 * @shell_name: represents the first value
 * @command: represents the second value
 */
void error_message_init(char **error_message, char *shell_name, char *command)
{
	error_message[0] = shell_name;
	error_message[1] = command;
	error_message[2] = NULL;
	error_message[3] = NULL;
}
