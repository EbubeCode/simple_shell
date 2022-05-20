#include "main.h"

/**
 * execute - executes a program passed to it
 * @arg: the command
 * @argv: the string of command and parameters
 *
 * Return: 0 if no error
 */
int execute(char *arg, char *argv[])
{
	int status = -1, i, stat;
	char *file = NULL, *def[2];
	pid_t child_pid;

	if (*arg == '.' || *arg == '/')
		status = access(arg, F_OK | X_OK);
	if (status == -1)
	{
		file = search_path(arg);
		if (file != NULL)
			status = access(file, F_OK | X_OK);
		if (file == NULL || status == -1)
		{
			for (i = 0; arg[i] != '\0'; i++);

			free(file);
			write(STDERR_FILENO, "./hsh: 1: ", 10);
			write(STDERR_FILENO, arg, i);
			write(STDERR_FILENO, ": not found\n", 12);
			return (127);
		}
		arg = file;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
	}
	if (child_pid == 0)
	{
		if (argv == NULL)
		{
			def[0] = arg;
			def[1] = NULL;
			argv = def;
		}
		execve(arg, argv, NULL);
		perror("Error");
		return (1);
	}
	else
	{
		wait(&stat);
		free(file);
		return (0);
	}
}
/**
 * check_white : checks for only white space
 * @str: the string
 *
 * Return: 1 if no whitspace 0 otherwise
 */
int check_white(char *str)
{
	int i;

	for (i = 0; str[i] != '\n' && str[i] != '\0'; i++)
		if (str[i] != ' ')
			return (1);
	return (0);
}
/**
 * handle_pipe - handle inputs from pipe
 *
 * Retun: void
 */
void handle_pipe(void)
{
	char **args = NULL, *cmds = NULL, *a = NULL;
	int i, tr = 1, status = 0;
	size_t n = 0;
	ssize_t read;

	do {
		read = getline(&cmds, &n, stdin);
		if (cmds != NULL && read != -1)
		{
			if (check_white(cmds))
			{
				a = cmds;
				while (*a != '\n')
					a++;
				*a = '\0';
				args = split_command(cmds, " ");
				if (args != NULL)
				{
					i = 0;
					if (args[1] != NULL && !compare(args[0], args[1]))
						status = execute(args[0], args);
					else
						while (args[i] != NULL)
							status = execute(args[i++], NULL);
					free(args);
				}
			}
			n = 0;
		}
		else
			tr = 0;
		free(cmds);
	} while (tr && !status);
	if (status != 0)
		exit(status);
}


/**
 * main - Entry point of application
 *
 * Return: 0 sucess
 */
int main(void)
{
	char *prompt = NULL, *a = NULL, **av = NULL;
	size_t n = 0;
	ssize_t read;
	int status = 0, piped = 1;

	do {
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
			read = getline(&prompt, &n, stdin);
			if (prompt != NULL && read != -1)
			{
				piped = 0;
				a = prompt;
				while (*a != '\n')
					a++;
				*a = '\0';
				av = split_command(prompt, " ");
				if (av != NULL)
				{
					status = handle_builtin(av);
					if (status == 0)
						execute(av[0], av);
					else if (status == 1)
						piped = 1;
				}
			}
			else
				write(STDOUT_FILENO, "\n", 1);
			n = 0;
			free(prompt);
			if (read != -1)
				free(av);
			else
				piped = 1;
		}
		else
			handle_pipe();
	} while (!piped);
	return (0);
}
