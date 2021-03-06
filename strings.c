#include "main.h"
int is_in_str(const char *string, char c);

/**
 * _strcpy - a function that copy a string
 * @dest: represents the address of buffer of string to copy
 * @src: represents the address of string to be copied
 *
 * Return: the pointer to destination, Otherwise NULL
 */
char *_strcpy(char *dest, const char *src)
{
	unsigned int j;

	if (src == NULL || dest == NULL)
		return (NULL);

	for (j = 0; src[j] != '\0'; j++)
		dest[j] = src[j];

	dest[j] = '\0';

	return (dest);
}

/**
 * _strlen - a function that finds the length of a given string
 * @string: represents the given string
 * Return: the value of length of string
 */
unsigned int _strlen(const char *string)
{
	unsigned int length = 0;

	if (string == NULL)
		return (0);

	while (*string)
	{
		length++;
		string++;
	}

	return (length);
}

/**
* _strcmp - a function that compares 2 strings
* @string1: represents the first string
* @string2: represents the second string
*
* Return: a negative integer, 0 or positive integer if string1
*         is less than, equal to or greater than string2
*/
int _strcmp(const char *string1, const char *string2)
{
	int diff = 0;

	while (diff == 0)
	{
		diff = *string1 - *string2;

		/* break if one of the strings is empty */
		if (*string1 == '\0' || *string2 == '\0')
			break;

		string1++;
		string2++;
	}

	return (diff);
}

/**
 * _strdup - a function that creates a copy of a given string
 * @string: represents the string to copy
 * Return: the value of new string identical to str.
 *         Otherwise NULL
 */
char *_strdup(const char *string)
{
	unsigned int length;
	char *result;

	if (string == NULL)
		return (NULL);

	/* we allocate space for new string */
	length = _strlen(string);
	result = malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);

	/* we copy contents of string into new string */
	return (_strcpy(result, string));
}

/**
 * _strtok - a function that tokenizes a given string
 *           using a given delimiter
 * @string: represents a string
 * @delimeter: represents the delimiter
 *
 * Return: the value of pointer to next token. Otherwise NULL
 */
char *_strtok(char *string, const char *delimeter)
{
	char c;
	int found_char = 0;
	char *start;
	static char *current;

	start = (string ? string : current);

	if (string)
		current = string;

	if (delimeter == NULL || *current == '\0')
		return (NULL);

	c = delimeter[0];

	while (*current == c)
/* we ignore separators at beginning */
	{
		start++;
		current++;
	}

	while (*current)
	{
		if (*current == c && found_char) /* found a delimiter */
		{
			*current = '\0';
			current++;
			break;
		}

		found_char = 1;
		current++;
	}

	while (*current && *current == c)
/*we ignore separators at end */
		current++;

	return (_strlen(start) ? start : NULL);
}

/**
 * is_in_str - a function that checks wheather a given
 *             character is in a given string
 * @string: represnts a string
 * @c: character
 *
 * Return: the value of 1 if c is in string. 0 Otherwise
 */
int is_in_str(const char *string, char c)
{
	if (string == NULL)
		return (0);

	while (*string)
	{
		if (*string == c)
			return (1);

		string++;
	}

	return (0);
}

/**
 * _atoi - a function that converts a string to an integer
 * @string: represent a string
 *
 * Return: integer equivalent. Otherwise -1
 */
int _atoi(char *string)
{
	int i, j, n, result;

	if (string == NULL)
		return (-1);

	n = _strlen(string);

	for (i = n - 1, j = 1, result = 0; i >= 0; i--, j *= 10)
	{
		if (result < 0 || string[i] > '9' || string[i] < '0')
			return (-1);

		result += (string[i] - '0') * j;
	}

	return (result % 256);
}

/**
 * str_rep - a function that replaces all occurences of a
 *           non printable character in a string with space
 * @string: represnts a string
 */
void str_rep(char *string)
{
	while (*string)
	{
		if (*string < ' ')
			*string = ' ';

		string++;
	}
}
