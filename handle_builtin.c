#include "main.h"

/**
 * print_env - prints the enviroment variable
 *
 * Return:void
 */
void print_env(void)
{
	int i = 0;
	char *a, b;

	while (environ[i] != NULL)
	{
		a = environ[i++];
		while (*a != '\0')
		{
			b = *a;
			write(STDOUT_FILENO, &b, 1);
			a++;
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * handle_builtin - checks if the command is the builtin commands
 * @av: commands entered
 *
 * Return: 1 if exit , 2 cd & env, else 0
 */
int handle_builtin(char **av)
{
	if (compare(av[0], "exit"))
		return (1);
	if (compare(av[0], "env"))
	{
		print_env();
		return (2);
	}
	if (compare(av[0], "cd"))
	{
		if (av[1] == NULL)
			chdir("~/");
		else
			chdir(av[1]);
		return (2);
	}
	return (0);
}
