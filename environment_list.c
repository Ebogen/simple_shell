#include "main.h"

/**
 * create_environ - a function that creates a list of environment  *                      variables
 * @environ: represents an array of environment variables
 * @environ_list: represents the list of environment variables
 *
 * Return: new list or NULL
 */
list_t *create_environ(char **environ, list_t *environ_list)
{
	unsigned int i;
	char *name, *value;

	if (environ == NULL)
	{
		return (NULL);
	}

	for (i = 0; environ[i]; i++)
	{
		name = _strtok(environ[i], "=");
		value = _strtok(NULL, "\n");

		if (add_node_end(&environ_list, name, value) == NULL)
		{
			return (NULL);
		}
	}

	return (environ_list);
}

/**
 * _getenv - a function that gets the value of an 
 *           environment variable
 * @environ_list: represents of environment variables list
 * @name: represents environment variable
 *
 * Return: value of name, Otherwise NULL
 */
char *_getenv(list_t *environ_list, char *name)
{
	list_t *tmp = environ_list;

	if (name == NULL)
	{
		return (NULL);
	}

	while (tmp && _strcmp(tmp->name, name))  
/* we check each node for a match */
	{
		tmp = tmp->next;
	}

	if (tmp)
		return (tmp->value);

	return (NULL);
}

/**
 * print_environ - is a function that is used to prints all the  
 *                 environment variables
 * @environ_list: list of environment variables
 */
void print_environ(list_t *environ_list)
{
	list_t *tmp = environ_list;

	while (tmp != NULL)
	{
		/*printf("[%d] ", tmp->index);*/
		/*printf("%s=%s\n", tmp->name, tmp->value);*/

		write(STDOUT_FILENO, tmp->name, _strlen(tmp->name) + 1);
		write(STDOUT_FILENO, "=", 2);
		write(STDOUT_FILENO, tmp->value, _strlen(tmp->value) + 1);
		write(STDOUT_FILENO, "\n", 2);

		tmp = tmp->next;
	}
}

/**
 * _setenv - is a function that adds or change an environment
 *           variable
 * @environ_list: reprents the list of environment variables
 * @name: represnts environment variable name
 * @value: environment variable value
 * @ow: represents overwrite flag
 *
 * Return: 0 if successful. Otherwise -1
 */
int _setenv(list_t *environ_list, const char *name, const char *value, int ow)
{
	int index;

	if (name == NULL || value == NULL || is_in_str(name, '='))
		return (-1);

	/* we find the index of node with name */
	index = find_name(environ_list, name);

	/* we check if name is not on list */
	if (index == -1)
	{
		if (add_node_end(&environ_list, name, value) == NULL)
			return (-1);

		return (0);
	}

	/* we update the node at index */
	if (ow)
		return (update_value(environ_list, index, value));

	return (0);
}

/**
 * _unsetenv - a function that deletes the variable name from the
 *             environment
 * @environ_list: list of environment variables
 * @name: name of variable to delete
 *
 * Return: 0 success. -1 otherwise
 */
int _unsetenv(list_t *environ_list, const char *name)
{
	int index;

	if (name == NULL)
		return (-1);

	/* we find the index of node we want to delete */
	index = find_name(environ_list, name);

	/* we check whether name is not on list */
	if (index == -1)
		return (0);

	/* we delete the node at index */
	if (delete_node_index(&environ_list, index) == -1)
		return (-1);

	return (0);
}
