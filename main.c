#include "main.h"

/**
 * main - a function that implements super simple shell
 *
 * @ac: represents number of commandline arguments
 * @av: represents array of commandline arguments
 * @environ: represents array of environment variables
 *
 * Return: the value of 0 for success or 1 for otherwise
 */
int main(int ac, char **av, char **environ)
{
	list_t *environ_list = NULL;
	int shell_return;

	/* we  create environ_list */
	environ_list = create_environ(environ, environ_list);

	/* SIGINT- predefined signal associated with terminal interrupt*/
	signal(SIGINT, sig_handler);

	/* we start the start shell here */
	shell_return = shell(environ_list, av[0]);

	/*check for the return value of shell */
	if (shell_return)
	{
		free_list(environ_list);
		exit(shell_return);
	}

	(void)ac;

	free_list(environ_list);

	return (0);
}

/**
 * sig_handler - a function that causes the shell to stop the
 *               current process and return to its main loop, dis-
 *               playing a new command prompt to the user.
 * @sig: represents the SIGINT
 */
void sig_handler(int sig)
{
	signal(sig, sig_handler);
	write(STDOUT_FILENO, "\n", 2);
	prompt();
}
