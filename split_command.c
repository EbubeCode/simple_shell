#include "main.h"

/**
 * split_command - splits the commands entered
 * @command: the command to split
 *
 * Return: a null terminated array of strings
 */
char **split_command(char *command)
{
	char **args, *token;
	int i = 0;

	args = malloc(sizeof(char *) * 10);
	if (args == NULL)
		return (NULL);
	token = strtok(command, " ");
	while (token != NULL && i <= 10)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	return (args);
}
