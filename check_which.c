#include "main.h"

/**
 * get_full_name - a function that gets full name
 *                 of a given command
 * @name: represents the string
 * @environ_list: represents the list of environment variables
 *
 * Return: the full name of a given command. Otherwise NULL
 */
char *get_full_name(char *name, list_t *environ_list)
{
	char *path, *fullname;
	list_t *path_dir_list;

	if (name == NULL)
		return (NULL);

	/* Here we get value of path */
	path = _getenv(environ_list, "PATH");

	/* Here we split the path */
	path_dir_list = split_string(path, ":");

	/*Here we get full path of the filename */
	fullname = get_full_path(name, path_dir_list);

	free_list(path_dir_list);

	return (fullname);
}

/**
 * get_full_path - a function that checks if a given file is in
 *                 PATH and returns its full path
 * @filename: represents the filename as string
 * @path_list: representst the list of the directories in PATH
 *
 * Return: the full path of filename otherwise NULL
 */
char *get_full_path(char *filename, list_t *path_list)
{
	char *full_path;
	list_t *track;

	if (filename == NULL || *filename == '\0')
	{
		return (NULL);
	}

	/* Here we check if filename starts with . or / */
	if (filename[0] == '/' || filename[0] == '.')
	{
		if (is_command(filename))
			return (_strdup(filename));

		return (NULL);
	}

	/* check for filename in all the directories */
	for (track = path_list; track; track = track->next)
	{
		/* Here we get the fullpath */
		full_path = create_path(track->name, filename);
		if (full_path)
		{
			if (valid_command(full_path))
				return (full_path);

			free(full_path);
		}
	}

	return (NULL);
}

/**
 * create_path - a function that concatenates directory name
 *               and filename to create full path
 * @dir: represents the directory name
 * @filename: represents the filename
 *
 * Return: new string which represents full file path.
 *         Otherwise NULL
 */

char *create_path(char *dir, char *filename)
{
	unsigned int m, n, r, len_dir, len_file;
	char *full_path;

	if (dir == NULL || filename == NULL)
		return (NULL);

	len_dir = _strlen(dir);
	len_file = _strlen(filename);

	/* Here we allocate space for new string */
	full_path = malloc(sizeof(char) * (len_dir + len_file + 2));
	if (full_path == NULL)
		return (NULL);

	/*Here we copy contents of dir */
	for (m = 0, r = 0; m < len_dir; m++, r++)
		full_path[r] = dir[m];

	full_path[r++] = '/';

	/* Here we copy contents of filename */
	for (n = 0; n < len_file; n++, r++)
		full_path[r] = filename[n];

	full_path[r] = '\0';

	return (full_path);
}

/**
 * valid_command - a function that checks if a given filename
 *                 is a valid command
 * @filename: represents a string
 *
 * Return: the value 1 if filename is valid command. Otherwise 0.
 */
int valid_command(char *filename)
{
	struct stat sfile;

	if (filename == NULL)
		return (0);

	/* Here we check if file exists and can be executed */
	if (access(filename, X_OK) == 0)
	{
		stat(filename, &sfile);
		if (sfile.st_mode & S_IFREG)
/*Here we ensure it's a regular file */
			return (1);
	}

	return (0);
}
