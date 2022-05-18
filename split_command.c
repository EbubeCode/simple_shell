#include "main.h"

/**
 * split_command - splits the commands entered
 * @command: the command to split
 * @delim: delimeter
 *
 * Return: a null terminated array of strings
 */
char **split_command(char *command, char *delim)
{
	char **args, *token;
	int i = 1, j;

	token = strtok(command, delim);
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		i++;
	}
	args = malloc(sizeof(char *) * i);
	if (args == NULL)
		return (NULL);
	for (j = 0; j < i - 1; j++)
	{
		args[j] = command;
		while (*command != '\0')
			command++;
		if (j < (i - 2))
			command++;
	}
	args[j] = NULL;
	return (args);
}
